#include "stdafx.h"
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
	delete[] path;
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
	TiXmlText* repeatText = new TiXmlText(currentSuite->getRepeat());
	repeat->LinkEndChild(repeatText);

	TiXmlElement* maxTime = new TiXmlElement("maxTime");
	element->LinkEndChild(maxTime);
	TiXmlText* maxTimeText = new TiXmlText(currentSuite->getMaxTime());
	maxTime->LinkEndChild(maxTimeText);

	TiXmlElement* maxThreads = new TiXmlElement("maxThreads");
	element->LinkEndChild(maxThreads);
	TiXmlText* maxThreadText = new TiXmlText(currentSuite->getMaxThreads());
	maxThreads->LinkEndChild(maxThreadText);

	TiXmlElement* priority = new TiXmlElement("priority");
	element->LinkEndChild(priority);
	TiXmlText* priorityText = new TiXmlText(currentSuite->getPriority());
	priority->LinkEndChild(priorityText);

	TiXmlElement* metadata = new TiXmlElement("metadata");
	element->LinkEndChild(metadata);

	TiXmlElement* author = new TiXmlElement("author");
	metadata->LinkEndChild(author);
	TiXmlText* authorText = new TiXmlText(currentSuite->getMetadata()->getName());
	author->LinkEndChild(authorText);

	TiXmlElement* date = new TiXmlElement("date");
	metadata->LinkEndChild(date);
	TiXmlText* dateText = new TiXmlText(currentSuite->getMetadata()->getDate());
	date->LinkEndChild(dateText);

	TiXmlElement* version = new TiXmlElement("version");
	metadata->LinkEndChild(version);
	TiXmlText* versionText = new TiXmlText(currentSuite->getMetadata()->getVersion());
	version->LinkEndChild(versionText);

	TiXmlElement* mail = new TiXmlElement("mail");
	metadata->LinkEndChild(mail);
	TiXmlText* mailText = new TiXmlText(currentSuite->getMetadata()->getMail());
	mail->LinkEndChild(mail);

	TiXmlElement* copyright = new TiXmlElement("copyright");
	metadata->LinkEndChild(copyright);
	TiXmlText* copyrightText = new TiXmlText(currentSuite->getMetadata()->getCopyright());
	copyright->LinkEndChild(copyrightText);

	TiXmlElement* license = new TiXmlElement("license");
	metadata->LinkEndChild(license);
	TiXmlText* licenseText = new TiXmlText(currentSuite->getMetadata()->getLicense());
	license->LinkEndChild(licenseText);

	TiXmlElement* info = new TiXmlElement("info");
	metadata->LinkEndChild(info);
	TiXmlText* infoText = new TiXmlText(currentSuite->getMetadata()->getInfo());
	info->LinkEndChild(infoText);

	std::list<TRSTest*>::iterator it = currentSuite->getList().begin();
	for (it; it != currentSuite->getList().end(); ++it)
	{
		TiXmlElement* test = new TiXmlElement("test");
		test->SetAttribute("name", (*it)->getName());
		test->SetAttribute("description", (*it)->getDescription());
		element->LinkEndChild(test);

		TiXmlElement* testPriority = new TiXmlElement("priority");
		test->LinkEndChild(testPriority);
		TiXmlText* testPriorityText = new TiXmlText((*it)->getPriority());
		testPriority->LinkEndChild(testPriorityText);

		TiXmlElement* testTag = new TiXmlElement("tag");
		test->LinkEndChild(testTag);
		TiXmlText* testTagText = new TiXmlText((*it)->getTag());
		testTag->LinkEndChild(testTagText);

		TiXmlElement* testDisable = new TiXmlElement("disable");
		test->LinkEndChild(testDisable);
		TiXmlText* testDisableText = new TiXmlText((*it)->getDisable());
		testDisable->LinkEndChild(testDisableText);

		TiXmlElement* testExecution = new TiXmlElement("execution");
		test->LinkEndChild(testExecution);
		TiXmlText* testExecutionText = new TiXmlText((*it)->get_executableName());
		testDisable->LinkEndChild(testExecutionText);

		TiXmlElement* testParameters = new TiXmlElement("parameters");
		test->LinkEndChild(testParameters);
		TiXmlText* testParametersText = new TiXmlText((*it)->getParameters());
		testDisable->LinkEndChild(testParametersText);

		TiXmlElement* testResult = new TiXmlElement("result");
		test->LinkEndChild(testResult);
		TiXmlText* testResultText = new TiXmlText((*it)->get_expectedResult());
		testDisable->LinkEndChild(testResultText);

		TiXmlElement* testRepeat = new TiXmlElement("repeat");
		test->LinkEndChild(testRepeat);
		TiXmlText* testRepeatText = new TiXmlText((*it)->getRepeat());
		testDisable->LinkEndChild(testRepeatText);

		TiXmlElement* testMaxTime = new TiXmlElement("maxTime");
		test->LinkEndChild(testMaxTime);
		TiXmlText* testMaxTimeText = new TiXmlText((*it)->getMaxTime());
		testDisable->LinkEndChild(testMaxTimeText);

		TiXmlElement* testWaitFor = new TiXmlElement("waitFor");
		test->LinkEndChild(testWaitFor);
		TiXmlText* testWaitForText = new TiXmlText((*it)->getWaitFor());
		testDisable->LinkEndChild(testWaitForText);

	}
	char* resPath = new char[strlen(path) + NAME_LENGTH];
	char name[] = "\\Test.xml";
	strncpy_s(resPath, strlen(path) + 1, path, strlen(path));
	strncpy_s(resPath + strlen(path), NAME_LENGTH, name, NAME_LENGTH - 1);
	doc.SaveFile(resPath);
	return true;
}