#include "meals_selector.h" 



namespace vnaon_meals {

	std::default_random_engine MealSelector::random_generator;
	MealSelector::MealSelector() {
	}

	MealSelector::~MealSelector() {
	}

	MealPicking::Shared MealSelector::Select(
		const std::vector<MealPicking::Shared> &arg_pickings,
		const MealFilter::Shared &arg_filter
	) {
		auto candidate_dishes = MatchedPickings(arg_pickings, arg_filter);
		int max_count = (int)candidate_dishes.size();
		MealPicking::Shared ret = nullptr;
		if ( max_count > 0 ) {
			std::uniform_int_distribution<int> distribution(0, max_count - 1);
			int index = distribution(MealSelector::random_generator);
			ret = candidate_dishes[index]->Clone();
		}
		return ret;
	}

	const std::vector<MealPicking::Shared> MealSelector::MatchedPickings(
		const std::vector<MealPicking::Shared> &arg_pickings,
		const MealFilter::Shared &arg_filter
	) const {
		std::vector<MealPicking::Shared> ret;
		if ( arg_filter == nullptr ) {
			ret = arg_pickings;
		} else {
			ret.reserve(arg_pickings.size());
			for ( auto dish : arg_pickings ) {
				if ( dish->MatchFilter(arg_filter) )
					ret.push_back(dish);
			}
		}
		return ret;
	}

}