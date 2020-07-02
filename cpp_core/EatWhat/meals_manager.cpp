#include "meals_manager.h"



namespace vnaon_meals {

	const int MealManager::kMaxDishCount = 10;
	MealManager::MealManager() {
		this->input_dishes_.reserve(MealManager::kMaxDishCount);
	}

	MealManager::~MealManager() {
	}

	MealPicking::Shared MealManager::AddDish(
		const std::string &arg_name,
		const std::string &arg_address,
		MealFilter::Shared arg_filter
	) {
		MealPicking::Shared ret = nullptr;
		if ( this->input_dishes_.size() < MealManager::kMaxDishCount - 1 ) {
			bool same_dish = false;
			for ( auto dish : this->input_dishes_ ) {
				if ( dish->GetName() == arg_name && dish->GetAddress() == arg_address ) {
					dish->SetFilter(arg_filter);
					same_dish = true;
					break;
				}
			}
			if ( !same_dish ) {
				ret = MealPicking::Create(arg_name, arg_address, arg_filter);
				this->input_dishes_.push_back(ret);
			}
		}
		return ret;
	}

	bool MealManager::RemoveDish(MealPicking::Shared arg_dish) {
		int ret = ExistDish(arg_dish);
		if ( ret != -1 )
			this->input_dishes_.erase(this->input_dishes_.begin() + ret);
		return ret >= 0;
	}

	void MealManager::ClearDish() {
		this->input_dishes_.clear();
	}

	int MealManager::ExistDish(MealPicking::Shared arg_dish) {
		int ret = -1;
		for ( int i = 0; i < this->input_dishes_.size(); i++ ){
			if ( arg_dish == this->input_dishes_[i] ) {
				ret = i;
				break;
			}
		}
		return ret;
	}

	MealPicking::Shared MealManager::Select(MealFilter::Shared arg_filter) {
		MealSelector selector;
		return selector.Select(this->input_dishes_, arg_filter);
	}

}
