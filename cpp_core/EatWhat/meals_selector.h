#pragma once

#include <random>
#include <vector>



#include "meals_dish.h"



namespace vnaon_meals {
	
	class MealSelector {
	private:
		const static int kMaxPickingsCount;
		static std::default_random_engine random_generator;

	public:
		MealSelector();
		~MealSelector();

		MealPicking::Shared Select(
			const std::vector<MealPicking::Shared> &arg_pickings,
			const MealFilter::Shared &arg_filter
		);

	private:
		const std::vector<MealPicking::Shared> MatchedPickings(
			const std::vector<MealPicking::Shared> &arg_pickings,
			const MealFilter::Shared &arg_filter
		) const;

	};

}