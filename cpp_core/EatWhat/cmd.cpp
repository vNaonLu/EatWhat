#include <iostream>
#include <random>
#include <string>
#include <sstream>


#include "cmd_command.h"
#include "cmd_utility.h"

int main() {


	printf("%s\n  %s\tv%s\n  @vnaon\n\n\n", 
		vnaon_cmd::Utility::kSperateLine,
		vnaon_cmd::Utility::kTitle,
		vnaon_cmd::Utility::kVersion
	);
	printf(vnaon_cmd::Utility::kUsage,
		vnaon_cmd::AddCommand::identifier,
		vnaon_cmd::AddCommand::identifier_name,
		vnaon_cmd::AddCommand::identifier_address,
		vnaon_cmd::AddCommand::identifier_filter,
		vnaon_cmd::SelectCommand::identifier,
		vnaon_cmd::SelectCommand::identifier_filter,
		vnaon_cmd::HelpCommand::identifier,
		vnaon_cmd::VersionCommand::identifier,
		vnaon_cmd::HelpCommand::identifier,
		vnaon_cmd::VersionCommand::identifier,
		vnaon_cmd::AddCommand::identifier,
		vnaon_cmd::SelectCommand::identifier
	);
	printf("\n%s\n\n", vnaon_cmd::Utility::kSperateLine);

    while ( true ) {
		std::string cmd_line;
        std::cout << "EatWhat > ";

		std::getline(std::cin, cmd_line);
		std::stringstream cmd_stream(cmd_line);
        std::vector<std::string> cmd_string;
		std::string cmd_trim;
        while ( cmd_stream >> cmd_trim ) {
            cmd_string.push_back(cmd_trim);
        }

		if ( cmd_string.size() > 0 ) {
			auto cmd = vnaon_cmd::Utility::CreateCommand(cmd_string);
			if ( cmd != nullptr ) {
				cmd->Excute();
			}
		}
		printf(RESET"\n\n");
    }

    return 0;
}