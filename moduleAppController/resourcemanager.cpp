#include <QDir>
#include <QString>
#include <iostream>
#include <sstream>
#include "resourcemanager.hpp"

namespace app {

// Not used
std::string ResourceManager::m_projectOutputPath = "../../projectOutput";

std::string ResourceManager::m_projectName = "dummyProjectShowcase";
bool ResourceManager::m_alive = false;

ResourceManager &ResourceManager::instance()
{
	static ResourceManager rm;

	if (!m_alive) {
		initResourceManager();
		m_alive = true;
	}

	return rm;
}

std::string ResourceManager::getProjectOutputPath() const
{
	return m_projectOutputPath;
}

std::string ResourceManager::getProjectName() const
{
	return m_projectName;
}

ResourceManager::ResourceManager()
{
}

void ResourceManager::initResourceManager()
{
	// =====-----
	// TODO <----
	// -----=====
	// Once file dialog is added into application,
	// this method needs to be connected to the folder
	// user picks.
	// For now, I shall use a dummy code that creates a dummy folder
	// inside executables until that part of app is completed.
	const QString path = QString::fromStdString(m_projectName);
	QDir qdir;

	std::cout << "Initializing resource manager..." << std::endl;
	std::cout << "Attempting to create project folder -> " << m_projectName << std::endl;
	if (qdir.mkdir(path))
		std::cout << "Output folder created at " << path.toStdString() << std::endl;
	else if (qdir.exists(path))
		std::cout << "Output folder already exists!" << std::endl;
	else
		std::cout << "Failed creating output folder!  " << std::endl;
}

} // namespace end: app
