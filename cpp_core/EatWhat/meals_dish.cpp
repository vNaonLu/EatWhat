#include "meals_dish.h"



namespace vnaon_meals {

	MealPicking::MealPicking(
		const std::string &arg_name,
		const std::string &arg_address, 
		MealFilter::Shared arg_filter
	) {
		this->name_ = arg_name;
		this->address_ = arg_address;
		this->filter_ = arg_filter->Clone();
	}

	MealPicking::~MealPicking() {
	}

	std::string MealPicking::GetName() const {
		return this->name_;
	}

	std::string MealPicking::GetAddress() const {
		return this->address_;
	}

	MealFilter::Unique MealPicking::GetFilter() const {
		return this->filter_->Clone();
	}

	void MealPicking::SetName(const std::string &arg) {
		this->name_ = arg;
	}

	void MealPicking::SetAddress(const std::string &arg) {
		this->address_ = arg;
	}

	void MealPicking::SetFilter(const MealFilter::Shared &arg) {
		this->filter_ = arg->Clone();
	}

	bool MealPicking::MatchFilter(const MealFilter::Shared &arg_filter) const {
		return arg_filter->Match(this->filter_);
	}

	MealPicking::Shared MealPicking::Clone() const {
		return MealPicking::Create(this->name_, this->address_, this->filter_->Clone());
	}

	MealPicking::Shared MealPicking::Create(
		const std::string &arg_name,
		const std::string &arg_address, 
		MealFilter::Shared arg_filter
	) {
		return std::make_shared<MealPicking>(arg_name, arg_address, arg_filter);
	}

	bool MealPicking::operator==(const MealPicking::Shared &arg) {
		// TODO: address.
		return this->name_ == arg->name_ && this->address_ == arg->address_;
	}

}