#include <sstream>



#include "cmd_utility.h"



namespace vnaon_cmd {

	const char *Utility::kSperateLine = "===========================================";
	const char *Utility::kTitle = "EatWhat";
	const char *Utility::kVersion = "1.1";
	const char *Utility::kUsage = R"(
   Usage:
      eat_what %s %s <name> [%s <address> |  %s <filter1\filter2...>]
      eat_what %s [-%s <filter1\filter2...>]
      eat_what %s
      eat_what %s

   Options:
      %s   
            Show this screen.
      %s   
            Show version.
      %s   
            Add a restaurant.
      %s   
            Choose a restaurant from the data.
)";

    Command::Shared Utility::CreateCommand(const std::vector<std::string> &arg_cmd) {
        Command::CommandType commad_header = Command::CommandType::kUnkonw;
        std::map<std::string, std::string> command_body;

        if ( arg_cmd.size() > 0 ) {
            auto cmd_header = arg_cmd[0];
            if ( cmd_header == AddCommand::identifier ) commad_header = Command::CommandType::kAdd;
            else  if ( cmd_header == SelectCommand::identifier ) commad_header = Command::CommandType::kSelect;
            else  if ( cmd_header == HelpCommand::identifier ) commad_header = Command::CommandType::kHelp;
            else  if ( cmd_header == VersionCommand::identifier ) commad_header = Command::CommandType::kVersion;
        }
        auto ret = Command::Create(commad_header);
        // delete the header.
        ret->Init(std::vector<std::string>(arg_cmd.begin() + 1, arg_cmd.end()));
        return ret;
    }
    std::vector<std::string> Utility::ParseFilter(const std::string &arg_cmd) {
        return Tokenize(arg_cmd, '\\');
    }
    std::vector<std::string> Utility::Tokenize(const std::string &arg_str, char arg_token) {
        std::vector<std::string> ret;
        std::stringstream check(arg_str);
        std::string intermediate;
        while ( getline(check, intermediate, arg_token) )
            ret.push_back(intermediate);
        return ret;
    }
}