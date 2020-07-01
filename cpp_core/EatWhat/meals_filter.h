#pragma once

#include <vector>
#include <memory>


namespace vnaon_meals {


	class MealFilter {
	public:
		typedef std::shared_ptr<MealFilter> Shared;
		typedef std::unique_ptr<MealFilter> Unique;
		enum class MEAL_TYPE {
			kUndefine// TODO: fill type
		};
		const static int kMaxFilterCount;

	private:
		std::vector<MEAL_TYPE> filter_;
		
	public:
		MealFilter();
		~MealFilter();

		void Push(const MEAL_TYPE &arg_type);
		void Erase(const MEAL_TYPE &arg_type);
		void Clear();

		bool Match(const MEAL_TYPE &arg_type) const;
		bool Match(const MealFilter::Shared &arg_filter) const;
		MealFilter::Unique Clone() const;

		static MealFilter::Shared Create();
	};

}