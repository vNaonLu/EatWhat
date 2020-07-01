#include "common_random_engine.h"



namespace vnaon_common {

	RandomEngine::RandomEngine() {
		std::random_device random;
		random_generator_ = std::default_random_engine(random());
	}

	RandomEngine::~RandomEngine() {
	}

}