#include <iostream>
#include "cmd_command.h"
#include "cmd_utility.h"



namespace vnaon_cmd {

	vnaon_meals::MealManager g_restaurant_manager;


	const std::vector<char> CommandUnit::kTokenChar
		= std::vector<char>{ '\"', '\'' };
	CommandUnit::CommandUnit(std::vector<std::string> arg_command) {
		this->total_size = 0;
		this->original_command = arg_command;
		this->key_list.clear();
		this->val_list.clear();
		this->key_index = 0;
		this->val_index = 0;
		this->Init();
	}
	CommandUnit::~CommandUnit() {
	}
	size_t CommandUnit::GetSize() const {
		return this->total_size;
	}
	std::string CommandUnit::GetKey() {
		return this->key_list.size() > this->key_index ? this->key_list[this->key_index++] : "";
	}
	std::string CommandUnit::GetValue() {
		return this->val_list.size() > this->val_index ? this->val_list[this->val_index++] : "";
	}
	std::vector<std::string> CommandUnit::GetOriginalCommand() const {
		return this->original_command;
	}
	void CommandUnit::Init() {
		char token_char = '\0';
		std::string temp_string;
		std::string current_key, current_value;
		temp_string.clear();
		current_key.clear();
		current_value.clear();
		for ( int i = 0; i < this->original_command.size(); i++ ) {
			auto current_trim = this->original_command[i];
			if ( token_char != '\0' ) {
				auto find_token = current_trim.find(token_char);
				if ( find_token == current_trim.size() - 1 ) {
					// end of literal.
					temp_string += " " + current_trim.substr(0, find_token);
					token_char = '\0';
				} else {
					temp_string += " " + current_trim;
				}
			} else {
				// find the literal char.
				for ( auto token : CommandUnit::kTokenChar ) {
					if ( token == current_trim.front() ) {
						token_char = token;
						if ( token == current_trim.back()) {
							temp_string = current_trim.substr(1, current_trim.size() - 2);
							token_char = '\0';
						} else {
							temp_string = current_trim.substr(1);
						}
					}
				}
				// fill the temp string.
				if ( temp_string.empty() )
					temp_string = current_trim;
			}
			if ( token_char == '\0' ) {
				// End of subcommand,
				if ( current_key.empty() ) {
					current_key = temp_string;
				} else {
					current_value = temp_string;
				}
				if ( !current_key.empty() && !current_value.empty() ) {
					this->key_list.push_back(current_key);
					this->val_list.push_back(current_value);
					current_key.clear();
					current_value.clear();
				}
				temp_string.clear();
			}
		}
		this->total_size = this->key_list.size() == this->val_list.size() ? this->val_list.size() : 0;
	}



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
		printf(KRED_L"Cannot find the proper command.");
	}
	void Command::Init(std::vector<std::string> arg_sub_command) {
		this->catch_command = arg_sub_command[1];
	}
	std::map<std::string, std::string> Command::AnalysisCommand(CommandUnit arg_command) {
		auto sub_command = arg_command.GetOriginalCommand();
		std::map<std::string, std::string> ret;
		std::string string_format;
		for ( int i = 0; i < sub_command.size(); i++ ) {
			string_format += sub_command[i] + " ";
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
			printf(KGRN_L"Successfully add the restaurant: ");
			printf(RESET"\'%s\'", this->name_.c_str());
		} else {
			printf(KRED_L"Inavalid the restaurant name: ");
			printf(RESET"\'%s\'", this->name_.c_str());
		}
	}
	void AddCommand::Init(std::vector<std::string> arg_sub_command) {
		auto cmd_map = AnalysisCommand(arg_sub_command);

		if ( cmd_map.count(Command::exception) <= 0 ) {
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

	std::map<std::string, std::string> AddCommand::AnalysisCommand(CommandUnit arg_command) {
		auto size = arg_command.GetSize();
		std::map<std::string, std::string> ret;
		if ( size > 0 ) {
			for ( size_t i = 0; i < size; i++ ) {
				auto key = arg_command.GetKey();
				auto val = arg_command.GetValue();
				if ( key == AddCommand::identifier_name )
					ret[key] = val;
				else if ( key == AddCommand::identifier_address )
					ret[key] = val;
				else if ( key == AddCommand::identifier_filter )
					ret[key] = val;
				else {
					ret = Command::AnalysisCommand(arg_command);
					break;
				}
			}
		} else {
			ret = Command::AnalysisCommand(arg_command);
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
			if ( choose != nullptr ) {
				printf(KCYN"You can eat ");
				printf(RESET"\'%s\'", choose->GetName().c_str());
			} else {
				printf(KRED_L"No proper restaurant with given filter.");
			}
		} else {
			printf(KRED_L"Failed to get a restaurant because of the empty inputs.");
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

	std::map<std::string, std::string> SelectCommand::AnalysisCommand(CommandUnit arg_command) {
		auto size = arg_command.GetSize();
		std::map<std::string, std::string> ret;
		if ( size > 0 ) {
			for ( size_t i = 0; i < size; i++ ) {
				auto key = arg_command.GetKey();
				auto val = arg_command.GetValue();
				if ( key == SelectCommand::identifier_filter )
					ret[key] = val;
				else {
					ret = Command::AnalysisCommand(arg_command);
					break;
				}
			}
		} else {
			ret = Command::AnalysisCommand(arg_command);
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