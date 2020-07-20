#pragma once
#include <string>
#include <map>
#include <memory>
#include "meals_manager.h"

#ifndef __TERMINAL_COLOR
#define __TERMINAL_COLOR
#define KDRK "\x1B[0;30m"
#define KGRY "\x1B[1;30m"
#define KRED "\x1B[0;31m"
#define KRED_L "\x1B[1;31m"
#define KGRN "\x1B[0;32m"
#define KGRN_L "\x1B[1;32m"
#define KYEL "\x1B[0;33m"
#define KYEL_L "\x1B[1;33m"
#define KBLU "\x1B[0;34m"
#define KBLU_L "\x1B[1;34m"
#define KMAG "\x1B[0;35m"
#define KMAG_L "\x1B[1;35m"
#define KCYN "\x1B[0;36m"
#define KCYN_L "\x1B[1;36m"
#define WHITE "\x1B[0;37m"
#define WHITE_L "\x1B[1;37m"
#define RESET "\x1B[0m"
#endif


namespace vnaon_cmd {


	class CommandUnit {
	private:
		static const std::vector<char> kTokenChar;
		size_t total_size;
		size_t key_index;
		size_t val_index;
		std::vector<std::string> original_command;
		std::vector<std::string> key_list;
		std::vector<std::string> val_list;
	public:
		CommandUnit(std::vector<std::string> arg_command);
		~CommandUnit();
		size_t GetSize() const;
		std::string GetKey();
		std::string GetValue();
		std::vector<std::string> GetOriginalCommand() const;
	private:
		void Init();
	};

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
		virtual std::map<std::string, std::string> AnalysisCommand(CommandUnit arg_command); // Generate Exception.

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
		virtual std::map<std::string, std::string> AnalysisCommand(CommandUnit arg_command) override;
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
		virtual std::map<std::string, std::string> AnalysisCommand(CommandUnit arg_command) override;
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