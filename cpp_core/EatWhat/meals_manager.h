#pragma once

#include "meals_filter.h"
#include "meals_dish.h"
#include "meals_selector.h"



namespace vnaon_meals {

	class MealManager {
		
	private:
		const static int kMaxDishCount;
		std::vector<MealPicking::Shared> input_dishes_;

	public:
		MealManager();
		~MealManager();

		MealPicking::Shared AddDish(
			const std::string &arg_name,
			const std::string &arg_address,
			MealFilter::Shared arg_filter
		);
		bool RemoveDish(MealPicking::Shared arg_dish);
		void ClearDish();
		int ExistDish(MealPicking::Shared arg_dish);
		bool IsEmpty() const;

		MealPicking::Shared Select(MealFilter::Shared arg_filter = nullptr);
	};

}
