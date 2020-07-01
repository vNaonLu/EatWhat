#include "meals_filter.h"



namespace vnaon_meals {

	const int MealFilter::kMaxFilterCount = 1;
	MealFilter::MealFilter() {
		this->filter_.reserve(MealFilter::kMaxFilterCount);
	}

	MealFilter::~MealFilter() {
	}

	void MealFilter::Push(const MEAL_TYPE &arg_type) {
		if ( !Match(arg_type) && this->filter_.size() < MealFilter::kMaxFilterCount ) {
			this->filter_.push_back(arg_type);
		}
	}

	void MealFilter::Erase(const MEAL_TYPE &arg_type) {
		auto iterator = std::find(this->filter_.cbegin(), this->filter_.cend(), arg_type);
		if( iterator != this->filter_.cend())
			this->filter_.erase(iterator);
	}

	void MealFilter::Clear() {
		this->filter_.clear();
	}

	bool MealFilter::Match(const MEAL_TYPE &arg_type) const {
		auto iterator = std::find(this->filter_.cbegin(), this->filter_.cend(), arg_type);
		return  iterator != this->filter_.cend();
	}

	bool MealFilter::Match(const MealFilter::Shared &arg_filter) const {
		// TODO: more effectiveness, now O(n2)
		bool match_ret = true;
		for ( auto filter : this->filter_ ) {
			if ( !(match_ret &= arg_filter->Match(filter)) )
				break;
		}
		return match_ret;
	}

	MealFilter::Unique MealFilter::Clone() const {
		auto ret = std::make_unique<MealFilter>();
		for ( int i = 0; i < this->filter_.size(); i++ ) ret->Push(this->filter_[i]);
		return ret;
	}

	MealFilter::Shared MealFilter::Create() {
		return std::make_shared<MealFilter>();
	}

}