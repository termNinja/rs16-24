#include <QDir>
#include <QString>
#include <QChar>
#include <iostream>
#include <sstream>
#include <fstream>
#include "resourcemanager.hpp"

namespace app {

// Not used
// std::string ResourceManager::m_projectOutputPath = "../../projectOutput";

// std::string ResourceManager::m_projectName = "dummyProjectShowcase";
// bool ResourceManager::m_alive = false;

ResourceManager &ResourceManager::instance()
{
	static ResourceManager rm;

//	if (!m_alive) {
//		initResourceManager();
//		m_alive = true;
//	}

	return rm;
}

QString ResourceManager::getProjectOutputPath() const
{
	return QString(m_projectOutputPath);
}

QString ResourceManager::getProjectName() const
{
	return QString(m_projectName);
}

void ResourceManager::setProjectPath(QString path)
{
	m_projectOutputPath = path;
	std::cout << "Path set to: " << path.toStdString() << std::endl;
}

ResourceManager::ResourceManager()
	: m_projectOutputPath(QDir::homePath()), m_projectName(QString("Untitled"))
{
}

bool ResourceManager::fileExists(std::string path) const
{
	return std::ifstream(path).good();
}

char ResourceManager::getPlatformSeparator() const
{
	QChar sep = QDir::separator();
	QString str(sep);
	return str.toStdString()[0];
}

//void ResourceManager::initResourceManager()
//{
	// =====-----
	// TODO <----
	// -----=====
	// Once file dialog is added into application,
	// this method needs to be connected to the folder
	// user picks.
	// For now, I shall use a dummy code that creates a dummy folder
	// inside executables until that part of app is completed.
//	QDir qdir;

//	std::cout << "Initializing resource manager..." << std::endl;
//	std::cout << "Attempting to create project folder -> " << m_projectOutputPath.toStdString() << std::endl;
//	if (qdir.mkdir(m_projectOutputPath))
//		std::cout << "Output folder created at " << m_projectOutputPath.toStdString() << std::endl;
//	else if (qdir.exists(m_projectOutputPath))
//		std::cout << "Output folder already exists!" << std::endl;
//	else
//		std::cout << "Failed creating output folder!  " << std::endl;
//}

} // namespace end: app
