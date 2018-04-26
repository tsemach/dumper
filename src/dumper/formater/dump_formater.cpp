
#include "dump_formater.h"

CDumpFormater::CDumpFormater()
{
}

CDumpFormater::~CDumpFormater()
{
}

bool
CDumpFormater::load(const std::string &_filename)
{
	m_ddoc = YAML::LoadFile(_filename);

/*
	YAML::Node consts = ctest["constructors"];
	std::cout << "main: consts size = " << consts.size() << std::endl;
	for (std::size_t i = 0; i < consts.size(); i++) {
		std::cout << consts[i].as<std::string>() << std::endl;
	}
		
	std::string  name = ctest["name"].as<std::string>();

	std::cout << "main: ctest class name = " << name << std::endl;

	YAML::Node access = ctest["access"];
*/
	/*
	// parse access list by vector, it is a list (sequance)
  	//	access:
    //		- getter: m_id is getX();       # call this getter to get m_id value during dumping
	//		- setter: m_name is setName();  # call this setter to set m_name during loading
	//		- access: m_index is X();       # call this getX() / setX() to get and set during dumping and loading
	//		- access: m_name by name;       # call to name() and name(const std::string &) to get and set m_name.
	std::cout << "main: access size = " << access.size() << std::endl;
	for(std::size_t i = 0; i < access.size(); i++) {
		if (access[i]["getter"]) {
			std::cout << access[i]["getter"].as<std::string>() << "\n";
		}		
		if (access[i]["setter"]) {
			std::cout << access[i]["setter"].as<std::string>() << "\n";	
		}
		if (access[i]["access"]) {
			std::cout << access[i]["access"].as<std::string>() << "\n";
		}
	}
	*/
	// parse accessm by maps
//	for(YAML::const_iterator it = access.begin(); it != access.end(); ++it) {
  //		std::cout << "accessm - " << it->first.as<std::string>() << " |value is| " << it->second.as<std::string>() << "\n";
//	}
}

std::string 
CDumpFormater::getConstructor(const std::string &_class) const
{
	YAML::Node cnode = m_ddoc[_class];

	YAML::Node consts = cnode["constructor"];


	if (consts.size() == 0) {
		return std::string();
	}

	std::cout << consts[0].as<std::string>() << std::endl;

	return consts[0].as<std::string>();
}

