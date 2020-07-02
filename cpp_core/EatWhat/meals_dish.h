#pragma once

#include <string>
#include <vector>


#include "meals_filter.h"

namespace vnaon_meals {

	class MealPicking {
	public:
		typedef std::shared_ptr<MealPicking> Shared;
		typedef std::unique_ptr<MealPicking> Unique;
		
	private:
		std::string name_;
		std::string address_;
		MealFilter::Unique filter_;

	public:
		MealPicking(
			const std::string &arg_name, 
			const std::string &arg_address, 
			MealFilter::Shared arg_filter
		);
		~MealPicking();

		std::string GetName() const;
		std::string GetAddress() const;
		MealFilter::Unique GetFilter() const;

		void SetName(const std::string &arg);
		void SetAddress(const std::string &arg);
		void SetFilter(const MealFilter::Shared &arg);

		bool MatchFilter(const MealFilter::Shared &arg_filter) const;

		MealPicking::Shared Clone() const;
		static MealPicking::Shared Create(
			const std::string &arg_name, 
			const std::string &arg_address, 
			MealFilter::Shared arg_filter = std::make_shared<MealFilter>()
		);

		bool operator==(const MealPicking::Shared &arg);

	};

}