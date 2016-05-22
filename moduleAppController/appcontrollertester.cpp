#include "appcontrollertester.hpp"

#include <iostream>

namespace app {

void AppControllerTester::performTest()
{
	std::cout << "APP CONTROLLER TEST" << std::endl;
	// Fetching resource manager
	ResourceManager *rm = &ResourceManager::instance();
	if (rm == nullptr) {
		std::cerr << "Failed fetching resource manager!" << std::endl;
	} else {
		std::cout << "Succeded at fetching resource manager!" << std::endl;
	}

	// getting user project name
	std::cout << "Resource Manager: Project name -> " << rm->getProjectName() << std::endl;
}

} // namespace end: app
