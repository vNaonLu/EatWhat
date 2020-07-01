#pragma once
#include <random>



namespace vnaon_common {

	class RandomEngine {
	private:
		std::default_random_engine random_generator_;

	public:
		RandomEngine();
		~RandomEngine();

		template<typename T = int>
		T Get(T arg_beg, T arg_end) {
			std::uniform_int_distribution<T> distribution(arg_beg, arg_end);
			return distribution(this->random_generator_);
		}

	};

}