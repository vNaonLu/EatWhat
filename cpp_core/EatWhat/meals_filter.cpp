#include "meals_filter.h"



namespace vnaon_meals {

	const int MealFilter::kMaxFilterCount = 10;
	int MealFilter::filter_hash = 0;
	std::map<std::string, int> MealFilter::filter_name = std::map<std::string, int>();
	MealFilter::MealFilter() {
		this->filter_.reserve(MealFilter::kMaxFilterCount);
	}

	MealFilter::~MealFilter() {
	}

	void MealFilter::Push(const std::string &arg_type) {
		FilterIdentifier type_identifier = -1;
		if ( MealFilter::filter_name.count(arg_type) > 0 ) {
			type_identifier = MealFilter::filter_name.at(arg_type);
		} else {
			MealFilter::filter_name[arg_type] = MealFilter::filter_hash++;
			type_identifier = MealFilter::filter_name.at(arg_type);
		}

		if ( !Match(type_identifier) &&
			this->filter_.size() < MealFilter::kMaxFilterCount ) {
			this->filter_.push_back(type_identifier);
		}
	}

	void MealFilter::Erase(const std::string &arg_type) {
		if ( MealFilter::filter_name.count(arg_type) > 0 ) {
			auto iterator = std::find(
				this->filter_.cbegin(), 
				this->filter_.cend(),
				MealFilter::filter_name.at(arg_type)
			);
			if ( iterator != this->filter_.cend() )
				this->filter_.erase(iterator);
		}
	}

	void MealFilter::Clear() {
		this->filter_.clear();
	}

	bool MealFilter::Match(const FilterIdentifier &arg_type) const {
		auto iterator = std::find(this->filter_.cbegin(), this->filter_.cend(), arg_type);
		return  iterator != this->filter_.cend();
	}

	bool MealFilter::Match(const MealFilter::Unique &arg_filter) const {
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
		ret->filter_.resize(this->filter_.size());
		for ( int i = 0; i < this->filter_.size(); i++ ) {
			ret->filter_[i] = this->filter_[i];
		}
		return ret;
	}

	MealFilter::Shared MealFilter::Create() {
		return std::make_shared<MealFilter>();
	}

}