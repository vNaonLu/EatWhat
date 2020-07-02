#pragma once

#include <string>
#include <vector>



namespace vnaon_common {

	class Utility {

	public:
		static std::vector<std::string> StringTokenize(const std::string &arg_str, char arg_token);

	};

}
