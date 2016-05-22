#ifndef RESOURCEMANAGER_HPP
#define RESOURCEMANAGER_HPP

#include <string>
#include <fstream>
#include <boost/filesystem.hpp>

namespace app {

class ResourceManager {
public:

	static ResourceManager& instance();
	std::string getProjectOutputPath() const;
	std::string getProjectName() const;

private:
	ResourceManager();

	ResourceManager(const ResourceManager &) = delete;
    ResourceManager(const ResourceManager &&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;
    ResourceManager& operator=(const ResourceManager&&) = delete;

	static void initResourceManager();

protected:
	static std::string m_projectOutputPath;
	static std::string m_projectName;
	static bool m_alive;
};

} // namespace end: app

#endif // RESOURCEMANAGER_HPP
