#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <string>
#include <fstream>
#include <QString>

namespace app {

class ResourceManager {
public:

	static ResourceManager& instance();
	QString getProjectOutputPath() const;
	QString getProjectName() const;

	void setProjectPath(QString path);
	char getPlatformSeparator() const;

private:
	ResourceManager();

	ResourceManager(const ResourceManager &) = delete;
    ResourceManager(const ResourceManager &&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&&) = delete;

	bool fileExists(std::string path) const;

	static void initResourceManager();

protected:
	QString m_projectOutputPath;
	QString m_projectName;
	bool m_alive;
};

} // namespace end: app

#endif // RESOURCEMANAGER_HPP
