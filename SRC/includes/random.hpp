//  --- RANDOM NUMBER HELPER FUNCTIONS ---
//  
//  The code below makes random value getting easier
//  
//  - Run seed64(time(0)) for the first time so that the seed of the random values
//    is based on the current time.
//  - bool throwAwayFirst just determines whether the first randomly generated number
//    should be discarded, as some first values for most seeds can be a little predictable.
//  
//  - Run psrand64_device() to get an integer between 0 and PSRAND64_MAX.
//  
//  - Rin psrand64_t(min, max, inclusiveEnd) to get a random number based on the input
//    types.
//  - For example, psrand64_t<int>() will get a random number between 0 and the
//    maximum int value, while psrand64_t<double>() will get a random number between
//    0 and 1.
//  - the inclusiveEnd boolean just determines whether the last number in a random
//    range should be included or excluded.
//  
//  - frandom() gets a random float given either no range (0 inclusive to 1 exclusive) or
//    given a range.
//  - drandom() gets a random double given either no range (0 inclusive to 1 exclusive) or
//    given a range.
//  - irandom() gets a random integer given either no range (0 to max integer value) or
//    given a range.
//  - size_t_random() gets a random unsigned long long integer given either no range (0 to
//    max unsigned long long integer value) or given a range.
//  
//  -------------------------------------------------------------------------------------------------------

//  "std::mt19937" is a class that generates pseudorandom numbers using the Mersenne Twister
//  algorithm. Doing psrand64_device() gets a new random number from this object.
mt19937_64 psrand64_device;

//  PSRAND64_MAX stores the maximum value possible attainable from psrand64_device(). This
//  allows you to do psrand64_device()*1.0/PSRAND64_MAX to get a random double between 0 and
//  1.
const unsigned long long PSRAND64_MAX = numeric_limits<unsigned long long>::max();

//  This is just a simple shorter-named function for getting the next random value from
//  psrand64_device.
//  
//  NOTE: When a function is called, a very small delay in runtime happens due to function overhead
//        (it takes more resources to run a function than to just run its code). Doing "inline" makes
//        it so that the compiler just runs the code in a function instead of running the function like
//        a function. This makes things run faster when functions are called, but it also increases the
//        size of a program a lot, so it's best to just use it for small functions.
inline unsigned long long psrand64() {
	return psrand64_device();
}

//  This function seeds the Mersenne Twister device with an input seed.
void seed64(const unsigned long long& inputSeed = 0, const bool& throwawayFirst = true) {
	psrand64_device.seed(inputSeed);
	//  If throwawayFirst is true, then the first random value got by the device will be discarded.
	if (throwawayFirst) {
		psrand64_device();
	}
	return;
}

//  This gets a random value based on input and type. If the type is a floating-point (like float or double),
//  it will default to a range from 0 to 1. If the type is an integral (like int or unsigned long long), it
//  will default to a range from 0 to the maximum integer value of tat type.
//  
//  NOTE: Function templating is a way to make a function be able to take multiple different kinds of types.
//        When a function has template<typename T> declared above it, the variable "T" can be used in the
//        function as a "universal" type. Then, when the function is called, you can either do function<int>()
//        or function<double> and so on to call the function with a certain type. Additionally, if one of the
//        arguments has the type (like myFunction(T inputValue)), then the function does not need to be
//        declared with <>, it will just automatically use the type of the value passed through it.
template<typename T>
T psrand64_t(const T& outputMin = 0, const T& outputMax = static_cast<T>(is_floating_point_v<T> ? 1 : numeric_limits<T>::max()), const bool& inclusiveEnd = !is_floating_point_v<T>) {
	//  Most of the math is just integrating the outputMin and outputMax features.
	if (is_floating_point_v<T>) {
		T randomNumber = psrand64()/(PSRAND64_MAX + static_cast<T>(1 - inclusiveEnd));
		randomNumber = randomNumber*(outputMax - outputMin) + outputMin;
		return static_cast<T>(randomNumber);
	} else {
		double randomNumber = psrand64()/(PSRAND64_MAX + 1.0);
		T randomInt = static_cast<T>(randomNumber*(outputMax - outputMin + inclusiveEnd)) + outputMin;
		return randomInt;
	}
}
	
//  This gets a random float.
inline float frandom(const float& outputMin = 0.0f, const float& outputMax = 1.0f, const bool& inclusiveEnd = false) {
	return psrand64_t<float>(outputMin, outputMax, inclusiveEnd);
}
//  This gets a random double
inline double drandom(const double& outputMin = 0.0, const double& outputMax = 1.0, const bool& inclusiveEnd = false) {
	return psrand64_t<double>(outputMin, outputMax, inclusiveEnd);
}
//  This gets a random integer
inline int irandom(const int& outputMin = 0, const int& outputMax = numeric_limits<int>::max(), const bool& inclusiveEnd = false) {
	return psrand64_t<int>(outputMin, outputMax, inclusiveEnd);
}

//  This gets a random size_t
//
//  NOTE: "std::size_t" is the C++ standard absolute guaranteed largest type with a size of 8 bytes. It is
//        guaranteed to be able to represent any possible index at all, which is why it is used in cases where
//        index math or counts are needed.
inline int size_t_random(const size_t& outputMin = 0, const size_t& outputMax = numeric_limits<size_t>::max(), const bool& inclusiveEnd = false) {
	return psrand64_t(outputMin, outputMax, inclusiveEnd);
}