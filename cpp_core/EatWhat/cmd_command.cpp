#include <iostream>
#include "cmd_command.h"
#include "cmd_utility.h"



namespace vnaon_cmd {

	vnaon_meals::MealManager g_restaurant_manager;

	const char *Command::exception = "__exception__";
	Command::Command() {
		this->catch_command = "";
		this->valid_cmd = false;
	}
	Command::~Command() {
	}
	void Command::Excute() {
		if ( this->valid_cmd ) {
			Process();
		} else {
			Command::Process();
		}
	}
	void Command::Process() {
		printf("Cannot find the proper command.");
	}
	void Command::Init(std::vector<std::string> arg_sub_command) {
		this->catch_command = arg_sub_command[1];
	}
	std::map<std::string, std::string> Command::AnalysisCommand(std::vector<std::string> arg_sub_command) {
		std::map<std::string, std::string> ret;
		std::string string_format;
		for ( int i = 0; i < arg_sub_command.size(); i++ ) {
			string_format += arg_sub_command[i] + " ";
		}
		if ( !string_format.empty() )
			ret[Command::exception] = string_format;
		return ret;
	}
	Command::Shared Command::Create(CommandType arg_type) {
		Command::Shared command = nullptr;
		switch ( arg_type ) {
		case CommandType::kHelp:
			command = std::make_shared<HelpCommand>();
			break;
		case CommandType::kVersion:
			command = std::make_shared<VersionCommand>();
			break;
		case CommandType::kAdd:
			command = std::make_shared<AddCommand>();
			break;
		case CommandType::kSelect:
			command = std::make_shared<SelectCommand>();
			break;
		default:
			command = std::make_shared<Command>();
			break;
		}
		return command;
	}



	const char *AddCommand::identifier = "--add";
	const char *AddCommand::identifier_name = "-n";
	const char *AddCommand::identifier_address = "-a";
	const char *AddCommand::identifier_filter = "-f";
	AddCommand::AddCommand() {
		this->name_ = "";
		this->address_ = "";
		this->filter_ = vnaon_meals::MealFilter::Create();
	}
	AddCommand::~AddCommand() {
	}
	void AddCommand::Process() {
		if ( this->name_ != "" ) {
			g_restaurant_manager.AddDish(
				this->name_,
				this->address_,
				this->filter_
			);
			printf("Successfully add the restaurant : \'%s\'", this->name_.c_str());
		}else{
			printf("Inavalid the restaurant name: \'%s\'", this->name_.c_str());
		}
	}
	void AddCommand::Init(std::vector<std::string> arg_sub_command) {
		auto cmd_map = AnalysisCommand(arg_sub_command);

		if ( cmd_map.count(Command::exception) <= 0) {
			if ( cmd_map.count(AddCommand::identifier_name) )
				this->name_ = cmd_map.at(AddCommand::identifier_name);
			if ( cmd_map.count(AddCommand::identifier_address) )
				this->address_ = cmd_map.at(AddCommand::identifier_address);
			if ( cmd_map.count(AddCommand::identifier_filter) ) {
				auto filter_name = Utility::ParseFilter(
					cmd_map.at(AddCommand::identifier_filter)
				);
				for ( auto name : filter_name ) {
					this->filter_->Push(name);
				}
			}
			this->valid_cmd = true;
		}
	}

	std::map<std::string, std::string> AddCommand::AnalysisCommand(std::vector<std::string> arg_sub_command) {
		std::map<std::string, std::string> ret;
		std::string current_key, current_value;
		current_key.clear();
		current_value.clear();
		for ( int i = 0; i < arg_sub_command.size(); i++ ) {
			auto current_trim = arg_sub_command[i];
			if ( current_key.empty() ) {
				if ( current_trim == AddCommand::identifier_name )
					current_key = current_trim;
				else if ( current_trim == AddCommand::identifier_address )
					current_key = current_trim;
				else if ( current_trim == AddCommand::identifier_filter )
					current_key = current_trim;
				else {
					ret = Command::AnalysisCommand(arg_sub_command);
					break;
				}
			} else {
				// value is empty.
				current_value = current_trim;
			}

			if ( !current_key.empty() && !current_value.empty() ) {
				ret[current_key] = current_value;
				current_key.clear();
				current_value.clear();
			}
		}
		return ret;
	}



	const char *SelectCommand::identifier = "--select";
	const char *SelectCommand::identifier_filter = "-f";
	SelectCommand::SelectCommand() {
		this->filter_ = vnaon_meals::MealFilter::Create();
	}
	SelectCommand::~SelectCommand() {
	}
	void SelectCommand::Process() {
		if ( !g_restaurant_manager.IsEmpty() ) {
			auto choose = g_restaurant_manager.Select(this->filter_);
			if ( choose != nullptr )
				printf("YOU CAN EAT \'%s\'", choose->GetName().c_str());
			else
				printf("No proper restaurant with given filter.");
		} else {
			printf("Failed to get a restaurant because of the empty inputs.");
		}
	}
	void SelectCommand::Init(std::vector<std::string> arg_sub_command) {
		auto cmd_map = AnalysisCommand(arg_sub_command);
		if ( cmd_map.count(Command::exception) <= 0 ) {
			if ( cmd_map.count(SelectCommand::identifier_filter) ) {
				auto filter_name = Utility::ParseFilter(
					cmd_map.at(SelectCommand::identifier_filter)
				);
				for ( auto name : filter_name ) {
					this->filter_->Push(name);
				}
			}
			this->valid_cmd = true;
		}
	}

	std::map<std::string, std::string> SelectCommand::AnalysisCommand(std::vector<std::string> arg_sub_command) {
		std::map<std::string, std::string> ret;
		std::string current_key, current_value;
		current_key.clear();
		current_value.clear();
		for ( int i = 0; i < arg_sub_command.size(); i++ ) {
			auto current_trim = arg_sub_command[i];
			if ( current_key.empty() ) {
				if ( current_trim == SelectCommand::identifier_filter )
					current_key = current_trim;
				else {
					ret = Command::AnalysisCommand(arg_sub_command);
					break;
				}
			} else {
				// value is empty.
				current_value = current_trim;
			}

			if ( !current_key.empty() && !current_value.empty() ) {
				ret[current_key] = current_value;
				current_key.clear();
				current_value.clear();
			}
		}
		return ret;
	}



	const char *HelpCommand::identifier = "--help";
	HelpCommand::HelpCommand() {
	}
	HelpCommand::~HelpCommand() {
	}
	void HelpCommand::Process() {
		printf(Utility::kUsage, 
			AddCommand::identifier, 
			AddCommand::identifier_name, 
			AddCommand::identifier_address,
			AddCommand::identifier_filter,
			SelectCommand::identifier,
			SelectCommand::identifier_filter,
			HelpCommand::identifier,
			VersionCommand::identifier,
			HelpCommand::identifier,
			VersionCommand::identifier,
			AddCommand::identifier,
			SelectCommand::identifier
		);
	}
	void HelpCommand::Init(std::vector<std::string> arg_sub_command) {
		auto cmd_map = AnalysisCommand(arg_sub_command);
		if ( cmd_map.count(Command::exception) <= 0 ) {
			this->valid_cmd = true;
		}
	}



	const char *VersionCommand::identifier = "--version";
	VersionCommand::VersionCommand() {
	}
	VersionCommand::~VersionCommand() {
	}
	void VersionCommand::Process() {
		printf("%s v%s", Utility::kTitle, Utility::kVersion);
	}
	void VersionCommand::Init(std::vector<std::string> arg_sub_command) {
		auto cmd_map = AnalysisCommand(arg_sub_command);
		if ( cmd_map.count(Command::exception) <= 0 ) {
			this->valid_cmd = true;
		}
	}

}