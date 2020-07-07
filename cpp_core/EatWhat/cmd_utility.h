#pragma once
#include "cmd_command.h"




namespace vnaon_cmd {

	class Utility {
	public:
		static const char *kSperateLine;
		static const char *kTitle;
		static const char *kUsage;
		static const char *kVersion;

		static Command::Shared CreateCommand(const std::vector<std::string> &arg_cmd);
		static std::vector<std::string> ParseFilter(const std::string &arg_cmd);
		static std::vector<std::string> Tokenize(const std::string &arg_str, char arg_token);
	};

}