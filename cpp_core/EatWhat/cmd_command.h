#pragma once
#include <string>
#include <map>
#include <memory>
#include "meals_manager.h"


namespace vnaon_cmd {

	class Command {
	public:
		enum class CommandType {
			kUnkonw, kHelp, kVersion, kAdd, kSelect
		};
	private:
		std::string catch_command;
	protected:
		static const char *exception;
		bool valid_cmd;
	public:
		typedef std::shared_ptr<Command> Shared;
		Command();
		~Command();
		void Excute();
		static Command::Shared Create(CommandType arg_type);

	protected:
		virtual void Process();
		virtual void Init(std::vector<std::string> arg_sub_command);
		virtual std::map<std::string, std::string> AnalysisCommand(std::vector<std::string> arg_sub_command); // Generate Exception.

		friend class Utility;
	};

	class AddCommand : public Command {
	public:
		static const char *identifier;
		static const char *identifier_name;
		static const char *identifier_address;
		static const char *identifier_filter;
	private:
		std::string name_;
		std::string address_;
		vnaon_meals::MealFilter::Shared filter_;
	public:
		AddCommand();
		~AddCommand();

		virtual void Process() override;
		virtual void Init(std::vector<std::string> arg_sub_command) override;
		virtual std::map<std::string, std::string> AnalysisCommand(std::vector<std::string> arg_sub_command) override;
	};

	class SelectCommand : public Command {
	public:
		static const char *identifier;
		static const char *identifier_filter;
	private:
		vnaon_meals::MealFilter::Shared filter_;
	public:
		SelectCommand();
		~SelectCommand();

		virtual void Process() override;
		virtual void Init(std::vector<std::string> arg_sub_command) override;
		virtual std::map<std::string, std::string> AnalysisCommand(std::vector<std::string> arg_sub_command) override;
	};

	class HelpCommand : public Command {
	public:
		static const char *identifier;
		HelpCommand();
		~HelpCommand();

		virtual void Process() override;
		virtual void Init(std::vector<std::string> arg_sub_command) override;
	};

	class VersionCommand : public Command {
	public:
		static const char *identifier;
		VersionCommand();
		~VersionCommand();

		virtual void Process() override;
		virtual void Init(std::vector<std::string> arg_sub_command) override;
	};
}