#include "meals_selector.h" 
#include "common_random_engine.h"



namespace vnaon_meals {

	const int MealSelector::kMaxPickingsCount = 10;
	MealSelector::MealSelector() {
		pickings_.reserve(MealSelector::kMaxPickingsCount);
	}

	MealSelector::~MealSelector() {
	}

	MealPicking::Shared MealSelector::Select(const MealFilter::Shared &arg_filter) const {
		vnaon_common::RandomEngine random;
		auto candidate_dishes = MatchedPickings(arg_filter);
		size_t max_count = candidate_dishes.size();
		MealPicking::Shared ret = nullptr;
		if ( max_count > 0 ) {
			size_t index = random.Get<size_t>(0, max_count - 1);
			ret = candidate_dishes[index]->Clone();
		}
		return ret;
	}

	void MealSelector::PushDishes(MealPicking::Shared arg_pickings) {
		if ( !ExistDish(arg_pickings) ) {
			this->pickings_.push_back(arg_pickings);
		}
	}

	void MealSelector::ClearDishes() {
		this->pickings_.clear();
	}

	bool MealSelector::ExistDish(MealPicking::Shared arg_pickings) const {
		bool ret = false;
		for ( auto dish : this->pickings_ ) {
			if ( ret |= (dish == arg_pickings) )
				break;
		}
		return ret;
	}

	std::vector<MealPicking::Shared> MealSelector::Dump() const {
		std::vector<MealPicking::Shared> ret;
		ret.resize(this->pickings_.size(), nullptr);
		for ( int i = 0; i < this->pickings_.size(); i++ ) {
			ret[i] = this->pickings_[i]->Clone();
		}
		return ret;
	}

	std::vector<MealPicking::Shared> MealSelector::MatchedPickings(const MealFilter::Shared &arg_filter) const {
		std::vector<MealPicking::Shared> ret;
		ret.reserve(this->pickings_.size());
		for ( auto dish : this->pickings_ ) {
			if ( dish->MatchFilter(arg_filter) )
				ret.push_back(dish);
		}
		return ret;
	}

}