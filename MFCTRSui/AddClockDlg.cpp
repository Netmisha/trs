// AddClockDlg.cpp : implementation file
//

#include "stdafx.h"
#include "AddClockDlg.h"
#include "afxdialogex.h"
#include "Functionality.h"

// AddClockDlg dialog

IMPLEMENT_DYNAMIC(AddClockDlg, CDialogEx)

AddClockDlg::AddClockDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(AddClockDlg::IDD, pParent)
{
	days[0] = &m_ButtonMonday;
	days[1] = &m_ButtonTuesday;
	days[2] = &m_ButtonWednesday;
	days[3] = &m_ButtonThursday;
	days[4] = &m_ButtonFriday;
	days[5] = &m_ButtonSaturday;
	days[6] = &m_ButtonSunday;
}



AddClockDlg::~AddClockDlg()
{
}

BOOL AddClockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	if (!initialized)
		return FALSE;

	m_ListCtrl.DeleteAllItems();
	m_EditName.Clear();
	m_EditTag.Clear();
	m_EditThreads.Clear();
	m_EditHour.Clear();
	m_EditMinute.Clear();

	m_ListCtrl.SetExtendedStyle(m_ListCtrl.GetExtendedStyle() | LVS_EX_CHECKBOXES | LVS_EX_TRANSPARENTSHADOWTEXT);

	for (int i = 0; i < coll.size(); ++i)
	{
		m_ListCtrl.InsertItem(m_ListCtrl.GetItemCount(), coll[i].get_path());
		m_ListCtrl.SetCheck(i, is_check[i]);
	}
	m_EditName.SetCurSel(name_sel);
	m_EditTag.SetCurSel(tag_sel);

	CString mes;
	CString helpMes;
	for (int i = 0; i < 9; ++i)
	{
		mes.Format(L"%S", "0");
		helpMes.Format(L"%d", i + 1);
		mes += helpMes;
		m_EditThreads.AddString(mes);
	}

	for (int i = 9; i < 100; ++i)
	{
		mes.Format(L"%d", int(i + 1));
		m_EditThreads.AddString(mes);
	}

	for (int i = 0; i < 10; ++i)
	{
		mes.Format(L"%S", "0");
		helpMes.Format(L"%d", i);
		mes += helpMes;
		m_EditHour.AddString(mes);
		m_EditMinute.AddString(mes);
	}

	for (int i = 10; i <= 24; ++i)
	{
		mes.Format(_T("%d"), i);
		m_EditHour.AddString(mes);
		m_EditMinute.AddString(mes);
	}

	for (int i = 25; i <= 60; ++i)
	{
		mes.Format(_T("%d"), i);
		m_EditMinute.AddString(mes);
	}
	m_EditHour.SetCurSel(0);
	m_EditMinute.SetCurSel(0);
	m_EditThreads.SetCurSel(thread_sel);
	if (first_called)
	{
		m_PathImageList.Create(32, 32, ILC_COLORDDB, 2, 2);
		CBitmap m_Bitmap5;
		m_Bitmap5.LoadBitmap(IDB_BITMAP5);
		m_PathImageList.Add(&m_Bitmap5, RGB(0, 0, 0));
		
		first_called = false;
	}
	m_ListCtrl.SetImageList(&m_PathImageList, LVSIL_SMALL);
	return TRUE;
}



void AddClockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListCtrl);
	DDX_Control(pDX, IDC_EDIT1, m_EditClockName);
	DDX_Control(pDX, IDC_COMBO1, m_EditTag);
	DDX_Control(pDX, IDC_COMBO2, m_EditName);
	DDX_Control(pDX, IDC_COMBO3, m_EditThreads);
	DDX_Control(pDX, IDC_COMBO5, m_EditHour);
	DDX_Control(pDX, IDC_COMBO6, m_EditMinute);
	DDX_Control(pDX, IDC_CHECK2, m_CheckRepeat);
	DDX_Control(pDX, IDC_CHECK3, m_ButtonMonday);
	DDX_Control(pDX, IDC_CHECK1, m_ButtonTuesday);
	DDX_Control(pDX, IDC_CHECK4, m_ButtonWednesday);
	DDX_Control(pDX, IDC_CHECK5, m_ButtonThursday);
	DDX_Control(pDX, IDC_CHECK6, m_ButtonFriday);
	DDX_Control(pDX, IDC_CHECK7, m_ButtonSaturday);
	DDX_Control(pDX, IDC_CHECK8, m_ButtonSunday);
}


BEGIN_MESSAGE_MAP(AddClockDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &AddClockDlg::OnBnClickedOk)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &AddClockDlg::OnLvnItemchangedList1)
END_MESSAGE_MAP()


// AddClockDlg message handlers


void AddClockDlg::OnBnClickedOk()
{
	m_EditClockName.GetWindowTextW(clock_name);
	if (clock_name.IsEmpty())
	{
		MessageBox(_T("You did not name the clock"), _T("Error"), MB_ICONERROR | MB_OK);
		return;
	}

	if (!selected_suites.size())
	{
		MessageBox(_T("You did not choose any suite. There will be nothing to Run."), _T("Error"), MB_ICONERROR | MB_OK);
		return;
	}
	
	m_EditHour.GetWindowTextW(hour_str);
	hour = _ttoi(hour_str);
	m_EditHour.GetWindowTextW(hour_str);

	m_EditMinute.GetWindowTextW(minute_str);
	minute = _ttoi(minute_str);
	m_EditMinute.GetWindowTextW(minute_str);

	m_EditTag.GetWindowTextW(tag);

	m_EditName.GetWindowTextW(name);

	m_EditThreads.GetWindowTextW(threads);

	weekly = m_CheckRepeat.GetCheck() == BST_CHECKED;

	days_flag = 0;
	for (int i = 0; i < 7; ++i)
	{
		if ((*days[i]).GetState() & BST_CHECKED)
			days_flag |= 1 << i;
	}

	if (!days_flag)
	{
		MessageBox(_T("You did not choose any day. There will be nothing to Run."), _T("Error"), MB_ICONERROR | MB_OK);
		return;
	}
	selected_paths.clear();
	for each(auto index in selected_suites)
	{
		selected_paths.push_back(m_ListCtrl.GetItemText(index, 0));
	}

	schedule.AddClocks(selected_paths, days_flag, hour, minute, weekly);

	CDialogEx::OnOK();
}

bool checkDiffName(int begin, char* source)
{
	int count = 0;
	for (int i = begin; i < strlen(source); ++i)
	{
		if (source[i] == '\\')
		{
			++count;
		}
	}
	return count == 1;
}

void TreeParse(std::list<Suite*>::iterator& it, std::list<Suite*>* suiteColl, int& count, std::list<Suite*>* checkList)
{
	// $$$ as I understood it is kind of a guard for redrawing Tree on exactly the same one?! 
	if (count != suiteColl->size())
	{
		unsigned path_lenght = strlen((*it)->get_path());
		char* rootPath = new char[path_lenght + 1];
		strcpy_s(rootPath, path_lenght + 1, (*it)->get_path());

		unsigned name_lenght = strlen((*it)->getName());
		char* rootName = new char[name_lenght + 1];
		strcpy_s(rootName, name_lenght + 1, (*it)->getName());

		std::list<Suite*>::iterator itHelp = it;

		// $$$ writing variable name in the initializing section of for-statement is useless and just slowing the program
		for (/*$$$ it*/; it != suiteColl->end(); ++it)
		{
			// $$$ I suggest you to move this checking into for-statement's condition expression in the same order, as I wrote lower
			//  count == suiteColl->size() && it != suiteColl->end()
			if (count == suiteColl->size())
			{
				break;
			}

			std::list<Suite*>::iterator helper = std::find(checkList->begin(), checkList->end(), *it);
			// @ if this suite is already in the list
			if (helper == (checkList->end()))
			{
				// @ checking whether we are not iterating the root path
				if (strlen((*it)->get_path()) != strlen(rootPath))
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)))
					{
						if (checkDiffName(strlen(rootPath), (*it)->get_path()))
							TreeParse(it, suiteColl, count, checkList);
					}

				}
				else
				{
					// $$$ again, despite the path checking is correct, because this else is executed only when path sizes are equal
					// there might be bugs when comparing names using strncmp function instead of strcmp
					// $$$ What is the purpose to compare names when pathes are identical and it is imposible for two folders to have the same path. 
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						
						++count;

						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						checkList->push_back((*it));
					
					}

				}
			}
		}
		--it;
		for (/*$$$ it*/; it != suiteColl->begin(); --it)
		{
			// $$$ the same remark as to the loop above
			if (count == suiteColl->size())
			{
				break;
			}

			std::list<Suite*>::iterator helper = std::find(checkList->begin(), checkList->end(), *it);
			if (helper == (checkList->end()))
			{
				if (strlen((*it)->get_path()) != strlen(rootPath))
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)))
					{
						if (checkDiffName(strlen(rootPath), (*it)->get_path()))
							TreeParse(it, suiteColl, count, checkList);
					}

				}
				else
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						
						++count;

						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						
						checkList->push_back((*it));
						
					}

				}
			}
		}
		// $$$ Eventually, I made your loop above using reverse iterator, because you yet need to process first element too)
		// EDIT: I reconsider my descision =D
		if (count != suiteColl->size())
		{
			std::list<Suite*>::iterator helper = std::find(checkList->begin(), checkList->end(), *it);
			if (helper == checkList->end())
			{

				if (strlen((*it)->get_path()) != strlen(rootPath))
				{
					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)))
					{
						if (checkDiffName(strlen(rootPath), (*it)->get_path()))
							TreeParse(it, suiteColl, count, checkList);
					}
				}
				else
				{

					if (!strncmp(rootPath, (*it)->get_path(), strlen(rootPath)) && !strncmp((*it)->getName(), rootName, strlen(rootName)))
					{
						
						++count;

						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();
						
						checkList->push_back((*it));
						
					}
				}

			}
		}
		it = itHelp;
		
		delete[] rootName;
		delete[] rootPath;
	}
	
}

void AddClockDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW  pNMLV = reinterpret_cast<LPNMLISTVIEW >(pNMHDR);

	UINT state = pNMLV->uOldState ^ pNMLV->uNewState;
	if (pNMLV->uChanged & LVIF_STATE) // item state has been changed
	{
		switch (pNMLV->uNewState & LVIS_STATEIMAGEMASK)
		{
		case INDEXTOSTATEIMAGEMASK(BST_CHECKED + 1): // new state: checked
		{
	//		selected_suites.push_back(SuiteRoot(m_ListCtrl.GetItemText(pNMLV->iItem, 0)));
			selected_suites.push_back(pNMLV->iItem);

			CString path = m_ListCtrl.GetItemText(pNMLV->iItem, 0);
			char* pPa = fromCStringToChar(path);
			std::list<Suite*>*suiteColl = Manager.List(pPa, nullptr, nullptr);
			delete[] pPa;
			m_EditName.Clear();
			m_EditTag.Clear();
			m_EditTag.ResetContent();
			m_EditTag.AddString(L"All");
			m_EditTag.SetCurSel(0);
			m_EditName.ResetContent();
			m_EditName.AddString(L"All");

			m_EditName.SetCurSel(0);

			m_EditThreads.SetCurSel(9);
			int count = 0;
			std::list<Suite*>::iterator it = suiteColl->begin();
			count = strlen((*it)->get_path());
			for (it; it != suiteColl->end(); ++it)
			{
				if (strlen((*it)->get_path()) < count)
				{
					count = strlen((*it)->get_path());
				}
			}
			--it;
			int lic = 0;
			std::list<Suite*> checkList;
			std::vector<char*> TagColl;
			std::vector<char*> NameColl;
			for (it; it != suiteColl->begin(); --it)
			{
				if (strlen((*it)->get_path()) == count)
				{
					TreeParse(it, suiteColl, lic, &checkList);
				}
			}
			if (strlen((*it)->get_path()) == count)
			{
				TreeParse(it, suiteColl, lic, &checkList);
			}
			for (it; it != suiteColl->end(); ++it)
			{
				std::list<TRSTest*>::iterator iter = (*it)->getList().begin();

				for (iter; iter != (*it)->getList().end(); ++iter)
				{
					std::vector<char*>::iterator iterator = TagColl.begin();
					if (TagColl.size() == 0)
					{
						if ((*iter)->getTag())
						{
							std::vector<char*>::iterator first = std::find(TagColl.begin(), TagColl.end(), (*iter)->getTag());
							if (first == TagColl.end())
							TagColl.push_back((*iter)->getTag());
						}
					}
					else
					{
						bool check = false;
						for (iterator; iterator != TagColl.end(); ++iterator)
						{
							if (!strncmp(*iterator, (*iter)->getTag(), strlen((*iter)->getTag())))
							{
								check = true;
								break;
							}

						}
						if (!check)
						{
							TagColl.push_back((*iter)->getTag());
						}
					}
					std::vector<char*>::iterator Nameit = NameColl.begin();
					if (NameColl.size() == 0)
					{
						if ((*iter)->getName())
						{
							NameColl.push_back((*iter)->getName());
						}
					}
					else
					{
						bool checkSecond = false;
						for (Nameit; Nameit != NameColl.end(); ++Nameit)
						{
							if (!strncmp(*Nameit, (*iter)->getName(), strlen((*iter)->getName())))
							{
								checkSecond = true;
								break;
							}

						}
						if (!checkSecond)
						{
							NameColl.push_back((*iter)->getName());
						}
					}
				}

			}
			for (int i = 0; i < TagColl.size(); ++i)
			{
				TCHAR*buf = new TCHAR[strlen(TagColl[i]) + 1];
				convertToTCHAR(buf, TagColl[i]);
				m_EditTag.AddString(buf);
				delete[] buf;
			}
			for (int i = 0; i < NameColl.size(); ++i)
			{
				TCHAR*buf = new TCHAR[strlen(NameColl[i]) + 1];
				convertToTCHAR(buf, NameColl[i]);
				m_EditName.AddString(buf);
				delete[] buf;
			}


			break;
		}
		case INDEXTOSTATEIMAGEMASK(BST_UNCHECKED + 1): // new state: unchecked
		{
			/*auto iter = std::find(selected_suites.begin(), selected_suites.end(), m_ListCtrl.GetItemText(pNMLV->iItem, 0));*/
			auto iter = std::find(selected_suites.begin(), selected_suites.end(), pNMLV->iItem);
		    if (iter != selected_suites.end())
				selected_suites.erase(iter);
			m_EditTag.ResetContent();
			m_EditTag.AddString(L"All");
			m_EditTag.SetCurSel(0);
			m_EditName.ResetContent();
			m_EditName.AddString(L"All");

			m_EditName.SetCurSel(0);
			if (m_EditName.GetCurSel() > 0)
			{
				m_EditName.SetCurSel(-1);
			}
			if (m_EditTag.GetCurSel() > 0)
			{
				m_EditTag.SetCurSel(-1);
			}
			for (int i = 0; i < m_ListCtrl.GetItemCount(); ++i)
			{
				if (m_ListCtrl.GetCheck(i))
				{
					CString path = m_ListCtrl.GetItemText(i, 0);
					char* pPa = fromCStringToChar(path);
					std::list<Suite*>*suiteColl = Manager.List(pPa, nullptr, nullptr);
					delete[] pPa;
					m_EditName.Clear();
					m_EditTag.Clear();
					m_EditTag.ResetContent();
					m_EditTag.AddString(L"All");
					m_EditTag.SetCurSel(0);
					m_EditName.ResetContent();
					m_EditName.AddString(L"All");

					m_EditName.SetCurSel(0);

					m_EditThreads.SetCurSel(9);
					int count = 0;
					std::list<Suite*>::iterator it = suiteColl->begin();
					count = strlen((*it)->get_path());
					for (it; it != suiteColl->end(); ++it)
					{
						if (strlen((*it)->get_path()) < count)
						{
							count = strlen((*it)->get_path());
						}
					}
					--it;
					int lic = 0;
					std::list<Suite*> checkList;
					std::vector<char*> TagColl;
					std::vector<char*> NameColl;
					for (it; it != suiteColl->begin(); --it)
					{
						if (strlen((*it)->get_path()) == count)
						{
							TreeParse(it, suiteColl, lic, &checkList);
						}
					}
					if (strlen((*it)->get_path()) == count)
					{
						TreeParse(it, suiteColl, lic, &checkList);
					}
					for (it; it != suiteColl->end(); ++it)
					{
						std::list<TRSTest*>::iterator iter = (*it)->getList().begin();

						for (iter; iter != (*it)->getList().end(); ++iter)
						{
							std::vector<char*>::iterator iterator = TagColl.begin();
							if (TagColl.size() == 0)
							{
								if ((*iter)->getTag())
								{
									std::vector<char*>::iterator first = std::find(TagColl.begin(), TagColl.end(), (*iter)->getTag());
									if (first == TagColl.end())
										TagColl.push_back((*iter)->getTag());
								}
							}
							else
							{
								bool check = false;
								for (iterator; iterator != TagColl.end(); ++iterator)
								{
									if (!strncmp(*iterator, (*iter)->getTag(), strlen((*iter)->getTag())))
									{
										check = true;
										break;
									}

								}
								if (!check)
								{
									TagColl.push_back((*iter)->getTag());
								}
							}
							std::vector<char*>::iterator Nameit = NameColl.begin();
							if (NameColl.size() == 0)
							{
								if ((*iter)->getName())
								{
									NameColl.push_back((*iter)->getName());
								}
							}
							else
							{
								bool checkSecond = false;
								for (Nameit; Nameit != NameColl.end(); ++Nameit)
								{
									if (!strncmp(*Nameit, (*iter)->getName(), strlen((*iter)->getName())))
									{
										checkSecond = true;
										break;
									}

								}
								if (!checkSecond)
								{
									NameColl.push_back((*iter)->getName());
								}
							}
						}

					}
					for (int i = 0; i < TagColl.size(); ++i)
					{
						TCHAR*buf = new TCHAR[strlen(TagColl[i]) + 1];
						convertToTCHAR(buf, TagColl[i]);
						m_EditTag.AddString(buf);
						delete[] buf;
					}
					for (int i = 0; i < NameColl.size(); ++i)
					{
						TCHAR*buf = new TCHAR[strlen(NameColl[i]) + 1];
						convertToTCHAR(buf, NameColl[i]);
						m_EditName.AddString(buf);
						delete[] buf;
					}
				}
			}


			break;
		}
		default:
			break;
		}
	}
	*pResult = 0;
}



BOOL AddClockDlg::Init(std::vector<SuiteRoot> coll_, vector<bool> check, DWORD name_sel_, DWORD tag_sel_, DWORD thread_sel_)
{
	initialized = false;
	coll = coll_;
	is_check = check;
	if (!coll.size() || coll.size() != is_check.size() || (thread_sel = thread_sel_) > 100)
		return FALSE;

	name_sel = name_sel_;
	tag_sel = tag_sel_;
	
	initialized = true;
	return TRUE;
}
