#pragma once

#include <vector>



#include "meals_dish.h"



namespace vnaon_meals {
	
	class MealSelector {
	private:
		const static int kMaxPickingsCount;
		std::vector<MealPicking::Shared> pickings_;

	public:
		MealSelector();
		~MealSelector();

		MealPicking::Shared Select(const MealFilter::Shared &arg_filter = nullptr) const;

		void PushDishes(MealPicking::Shared arg_pickings);
		void ClearDishes();
		bool ExistDish(MealPicking::Shared arg_pickings) const;

		std::vector<MealPicking::Shared> Dump() const;

	private:
		std::vector<MealPicking::Shared> MatchedPickings(const MealFilter::Shared &arg_filter) const;

	};

}