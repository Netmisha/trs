#include "stdafx.h"
#define FolderCreator_EXPORT
#include "XmlCreator.h"

XmlCreator::XmlCreator(char* path_, Suite* suite)
{
	path = path;
	currentSuite = suite;
}

XmlCreator::XmlCreator()
{

}

XmlCreator::~XmlCreator()
{
	delete[] currentSuite;
}

bool XmlCreator::setPath(char* path_)
{
	path = path_;
	return true;
}

bool XmlCreator::setSuite(Suite*suite)
{
	currentSuite = suite;
	return true;
}

char* XmlCreator::getPath() const
{
	return path;
}

Suite* XmlCreator::getSuite()
{
	return currentSuite;
}

bool XmlCreator::CreateXML()
{
	TiXmlDocument doc;
	TiXmlDeclaration* decl = new TiXmlDeclaration("1.0", "", "");
	doc.LinkEndChild(decl);

	TiXmlElement* element = new TiXmlElement("suite");
	element->SetAttribute("name", currentSuite->getName());
	element->SetAttribute("description", currentSuite->getDescription());
	doc.LinkEndChild(element);

	TiXmlElement* tag = new TiXmlElement("tag");
	element->LinkEndChild(tag);
	TiXmlText* tagText = new TiXmlText(currentSuite->getTag());
	tag->LinkEndChild(tagText);
	
		TiXmlElement* repeat = new TiXmlElement("repeat");
		element->LinkEndChild(repeat);
		if (currentSuite->getRepeat())
		{
			TiXmlText* repeatText = new TiXmlText(currentSuite->getRepeat());
			repeat->LinkEndChild(repeatText);
		}

		TiXmlElement* maxTime = new TiXmlElement("maxTime");
		element->LinkEndChild(maxTime);
		if (currentSuite->getMaxTime())
		{
		TiXmlText* maxTimeText = new TiXmlText(currentSuite->getMaxTime());
		maxTime->LinkEndChild(maxTimeText);
		}

		TiXmlElement* maxThreads = new TiXmlElement("maxThreads");
		element->LinkEndChild(maxThreads);
		if (currentSuite->getMaxThreads())
		{
		TiXmlText* maxThreadText = new TiXmlText(currentSuite->getMaxThreads());
		maxThreads->LinkEndChild(maxThreadText);
		}

		TiXmlElement* priority = new TiXmlElement("priority");
		element->LinkEndChild(priority);
		if (currentSuite->getPriority())
		{
		TiXmlText* priorityText = new TiXmlText(currentSuite->getPriority());
		priority->LinkEndChild(priorityText);
		}
	
	TiXmlElement* metadata = new TiXmlElement("metadata");
	element->LinkEndChild(metadata);

		TiXmlElement* author = new TiXmlElement("author");
		metadata->LinkEndChild(author);
		if (currentSuite->getMetadata()->getName())
		{
		TiXmlText* authorText = new TiXmlText(currentSuite->getMetadata()->getName());
		author->LinkEndChild(authorText);
		}

		TiXmlElement* date = new TiXmlElement("date");
		metadata->LinkEndChild(date);
		if (currentSuite->getMetadata()->getDate())
		{
		TiXmlText* dateText = new TiXmlText(currentSuite->getMetadata()->getDate());
		date->LinkEndChild(dateText);
		}

		TiXmlElement* version = new TiXmlElement("version");
		metadata->LinkEndChild(version);
		if (currentSuite->getMetadata()->getVersion())
		{
		TiXmlText* versionText = new TiXmlText(currentSuite->getMetadata()->getVersion());
		version->LinkEndChild(versionText);
		}

		TiXmlElement* mail = new TiXmlElement("mail");
		metadata->LinkEndChild(mail);
		if (currentSuite->getMetadata()->getMail())
		{
		TiXmlText* mailText = new TiXmlText(currentSuite->getMetadata()->getMail());
		mail->LinkEndChild(mailText);
		}

		TiXmlElement* copyright = new TiXmlElement("copyright");
		metadata->LinkEndChild(copyright);
		if (currentSuite->getMetadata()->getCopyright())
		{
		TiXmlText* copyrightText = new TiXmlText(currentSuite->getMetadata()->getCopyright());
		copyright->LinkEndChild(copyrightText);
		}

	TiXmlElement* license = new TiXmlElement("license");
	metadata->LinkEndChild(license);
	if (currentSuite->getMetadata()->getLicense())
	{
		TiXmlText* licenseText = new TiXmlText(currentSuite->getMetadata()->getLicense());
		license->LinkEndChild(licenseText);
	}

	TiXmlElement* info = new TiXmlElement("info");
	metadata->LinkEndChild(info);
	if (currentSuite->getMetadata()->getInfo())
	{
		TiXmlText* infoText = new TiXmlText(currentSuite->getMetadata()->getInfo());
		info->LinkEndChild(infoText);
	}

	std::list<TRSTest*>::iterator it = currentSuite->getList().begin();
	for (it; it != currentSuite->getList().end(); ++it)
	{
		TiXmlElement* test = new TiXmlElement("test");
		test->SetAttribute("name", (*it)->getName());
		if ((*it)->getDescription())
		{
			test->SetAttribute("description", (*it)->getDescription());
			element->LinkEndChild(test);
		}

		TiXmlElement* testPriority = new TiXmlElement("priority");
		test->LinkEndChild(testPriority);
		if ((*it)->getPriority())
		{
			TiXmlText* testPriorityText = new TiXmlText((*it)->getPriority());
			testPriority->LinkEndChild(testPriorityText);
		}

		TiXmlElement* testTag = new TiXmlElement("tag");
		test->LinkEndChild(testTag);
		if ((*it)->getTag())
		{
			TiXmlText* testTagText = new TiXmlText((*it)->getTag());
			testTag->LinkEndChild(testTagText);
		}

		TiXmlElement* testDisable = new TiXmlElement("disable");
		test->LinkEndChild(testDisable);
		if ((*it)->getDisable())
		{
			TiXmlText* testDisableText = new TiXmlText((*it)->getDisable());
			testDisable->LinkEndChild(testDisableText);
		}

		TiXmlElement* testExecution = new TiXmlElement("execution");
		test->LinkEndChild(testExecution);
		if ((*it)->get_executableName())
		{
			TiXmlText* testExecutionText = new TiXmlText((*it)->get_executableName());
			testExecution->LinkEndChild(testExecutionText);
		}

		TiXmlElement* testParameters = new TiXmlElement("parameters");
		test->LinkEndChild(testParameters);
		if ((*it)->getParameters())
		{
			TiXmlText* testParametersText = new TiXmlText((*it)->getParameters());
			testParameters->LinkEndChild(testParametersText);
		}

		TiXmlElement* testResult = new TiXmlElement("result");
		test->LinkEndChild(testResult);
		if ((*it)->get_expectedResult())
		{
			TiXmlText* testResultText = new TiXmlText((*it)->get_expectedResult());
			testResult->LinkEndChild(testResultText);
		}

		TiXmlElement* testRepeat = new TiXmlElement("repeat");
		test->LinkEndChild(testRepeat);
		if ((*it)->getRepeat())
		{
			TiXmlText* testRepeatText = new TiXmlText((*it)->getRepeat());
			testRepeat->LinkEndChild(testRepeatText);
		}

		TiXmlElement* testMaxTime = new TiXmlElement("maxTime");
		test->LinkEndChild(testMaxTime);
		if ((*it)->getMaxTime())
		{
			TiXmlText* testMaxTimeText = new TiXmlText((*it)->getMaxTime());
			testMaxTime->LinkEndChild(testMaxTimeText);
		}

		TiXmlElement* testWaitFor = new TiXmlElement("waitFor");
		test->LinkEndChild(testWaitFor);
		if ((*it)->getWaitFor())
		{
			TiXmlText* testWaitForText = new TiXmlText((*it)->getWaitFor());
			testWaitFor->LinkEndChild(testWaitForText);
		}
	}
	char* resPath = new char[strlen(path) + strlen(currentSuite->getName())+FILE_EXPANSION];
	strncpy_s(resPath, strlen(path) + 1, path, strlen(path));
	strncpy_s(resPath + strlen(path), 2, "//", 1);
	strncpy_s(resPath + strlen(path)+1, strlen(currentSuite->getName()) + 1, currentSuite->getName(), strlen(currentSuite->getName()));
	strncpy_s(resPath + strlen(path) + strlen(currentSuite->getName()) + 1, FILE_EXPANSION-1, ".xml", FILE_EXPANSION - 2);
	doc.SaveFile(resPath);
	return true;
}