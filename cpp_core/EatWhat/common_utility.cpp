#include <sstream>


#include "common_utility.h"


namespace vnaon_common {

	std::vector<std::string> Utility::StringTokenize(const std::string &arg_str, char arg_token) {
		std::vector<std::string> ret;
		std::stringstream check(arg_str);
		std::string intermediate;
		while ( getline(check, intermediate, arg_token) )
			ret.push_back(intermediate);
		return ret;
	}

}