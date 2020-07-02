#pragma once

#include <vector>
#include <map>
#include <memory>
#include <string>


namespace vnaon_meals {


	class MealFilter {
	private:
		typedef int FilterIdentifier;
		static std::map<std::string, FilterIdentifier> filter_name;
	public:
		typedef std::shared_ptr<MealFilter> Shared;
		typedef std::unique_ptr<MealFilter> Unique;
		const static int kMaxFilterCount;

	private:
		std::vector<FilterIdentifier> filter_;
		
	public:
		MealFilter();
		~MealFilter();

		void Push(const std::string &arg_type);
		void Erase(const std::string &arg_type);
		void Clear();

		bool Match(const FilterIdentifier &arg_type) const;
		bool Match(const MealFilter::Shared &arg_filter) const;
		MealFilter::Unique Clone() const;

		static MealFilter::Shared Create();
	};

}