//  There's already a vec2 in SFML, but operator overloads are useful here
struct Vec2 {
	array<double, 2> arr = {0.0, 0.0};
	double& x = arr[0];
	double& y = arr[1];
	
	Vec2 copy() const {
		return *this;
	}
	
	Vec2& operator+=(const Vec2& other) {
		x += other.x;
		y += other.y;
		return *this;
	}
	Vec2 operator+(const Vec2& other) const {
		return this->copy() += other;
	}
	Vec2& operator-=(const Vec2& other) {
		x -= other.x;
		y -= other.y;
		return *this;
	}
	Vec2 operator-(const Vec2& other) const {
		return this->copy() -= other;
	}
	Vec2& operator*=(const Vec2& other) {
		x *= other.x;
		y *= other.y;
		return *this;
	}
	Vec2 operator*(const Vec2& other) const {
		return this->copy() *= other;
	}
	Vec2& operator/=(const Vec2& other) {
		x /= other.x;
		y /= other.y;
		return *this;
	}
	Vec2 operator/(const Vec2& other) const {
		return this->copy() /= other;
	}
	Vec2& operator%=(const Vec2& other) {
		x = fmod(x, other.x);
		y = fmod(y, other.y);
		return *this;
	}
	Vec2 operator%(const Vec2& other) const {
		return this->copy() %= other;
	}
	double& operator[](const size_t& inputIndex) {
		return arr[inputIndex];
	}
	double operator[](const size_t& inputIndex) const {
		if (inputIndex >= 2) {
			return 0.0;
		}
		return arr[inputIndex];
	}
	
	
	inline double x_abs() const {
		return x > 0.0 ? x : -x;
	}
	inline double y_abs() const {
		return y > 0.0 ? y : -y;
	}
	inline double sq_magnitude() const {
		return x*x + y*y;
	}
	inline double magnitude() const {
		return sqrt(x*x + y*y);
	}
	
	inline Vec2 fabs() const {
		return Vec2(std::fabs(x), std::fabs(y));
	}
	inline Vec2 abs() const {
		return fabs();
	}
	inline Vec2 exp() const {
		return Vec2(std::exp(x), std::exp(y));
	}
	inline Vec2 floor() const {
		return Vec2(std::floor(x), std::floor(y));
	}
	inline Vec2 ceil() const {
		return Vec2(std::ceil(x), std::ceil(y));
	}
	inline Vec2 normalize() const {
		return *this/magnitude();
	}
	inline double atan2() const {
		return std::atan2(y, x);
	}
	static Vec2 AngleToVector(double angle, const bool& useDegrees = false) {
		if (useDegrees) {
			angle *= std::acos(-1)/180.0;
		}
		return {std::cos(angle), std::sin(angle)};
	}
	
	Vec2& operator=(const Vec2& other) {
		arr[0] = other.arr[0];
		arr[1] = other.arr[1];
		return *this;
	}
	Vec2(const array<double, 2>& inputArray) : arr(inputArray) {}
	Vec2(const Vec2& other) {
		arr[0] = other.arr[0];
		arr[1] = other.arr[1];
	}
	Vec2(const sf::Vector2f& inputVector) : arr({inputVector.x, inputVector.y}) {}
	Vec2(const sf::Vector2u& inputVector) : arr({static_cast<double>(inputVector.x), static_cast<double>(inputVector.y)}) {}
	Vec2(const sf::Vector2i& inputVector) : arr({static_cast<double>(inputVector.x), static_cast<double>(inputVector.y)}) {}
	Vec2(const double& inputX, const double& inputY) : arr({inputX, inputY}) {}
	Vec2(const double& inputScale = 0.0) : arr({inputScale, inputScale}) {}
	operator sf::Vector2f() const {
		return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
	}
	operator sf::Vector2u() const {
		return sf::Vector2u(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
	}
	operator sf::Vector2i() const {
		return sf::Vector2i(static_cast<int>(x), static_cast<int>(y));
	}
};