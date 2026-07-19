//  There's already a vec2 in SFML, but operator overloads are useful here
struct Vec2 {
	public:
		//  These references allow coordinate access via .x and .y
		double x;
		double y;
		
		//  This just returns a copy of the object
		inline Vec2 copy() const {
			return *this;
		}
		
		//  This allows doing object += object
		inline Vec2& operator+=(const Vec2& other) {
			x += other.x;
			y += other.y;
			return *this;
		}
		
		//  This allows doing object + object
		inline Vec2 operator+(const Vec2& other) const {
			return this->copy() += other;
		}
		
		//  This allows doing object -= object
		inline Vec2& operator-=(const Vec2& other) {
			x -= other.x;
			y -= other.y;
			return *this;
		}
		
		//  This allows doing object - object
		inline Vec2 operator-(const Vec2& other) const {
			return this->copy() -= other;
		}
		
		//  This allows doing object *= object
		inline Vec2& operator*=(const Vec2& other) {
			x *= other.x;
			y *= other.y;
			return *this;
		}
		
		//  This allows doing object * object
		inline Vec2 operator*(const Vec2& other) const {
			return this->copy() *= other;
		}
		
		//  This allows doing object /= object
		inline Vec2& operator/=(const Vec2& other) {
			x /= other.x;
			y /= other.y;
			return *this;
		}
		
		//  This allows doing object / object
		inline Vec2 operator/(const Vec2& other) const {
			return this->copy() /= other;
		}
		
		//  This allows doing object %= object
		inline Vec2& operator%=(const Vec2& other) {
			x = fmod(x, other.x);
			y = fmod(y, other.y);
			return *this;
		}
		
		//  This allows doing object % object
		inline Vec2 operator%(const Vec2& other) const {
			return this->copy() %= other;
		}
		
		//  This gets the absolute value of the x component
		inline double x_abs() const {
			return std::fabs(x);
		}
		
		//  This gets the absolute value of the y component
		inline double y_abs() const {
			return std::fabs(y);
		}
		
		//  This gets the square length of a vector with these components
		inline double sq_magnitude() const {
			return x*x + y*y;
		}
		
		//  This gets the length of a vector with these components
		inline double magnitude() const {
			return sqrt(x*x + y*y);
		}
		
		//  This gets the absolute value of both components
		inline Vec2 fabs() const {
			return Vec2(std::fabs(x), std::fabs(y));
		}
		
		//  This is just a name alias for the above
		inline Vec2 abs() const {
			return this->fabs();
		}
		
		//  This performs the exponential function on both components
		inline Vec2 exp() const {
			return Vec2(std::exp(x), std::exp(y));
		}
		
		//  This performs the floor function on both components
		inline Vec2 floor() const {
			return Vec2(std::floor(x), std::floor(y));
		}
		
		//  This performs the ceiling function on both components
		inline Vec2 ceil() const {
			return Vec2(std::ceil(x), std::ceil(y));
		}
		
		//  This returns the components of the normal of a vector with these components
		inline Vec2 normalize() const {
			return *this/magnitude();
		}
		
		//  This returns the angle of a vector with these components
		inline double atan2() const {
			return std::atan2(y, x);
		}
		
		//  This creates one of these Vec2 objects given an angle
		inline static Vec2 AngleToVector(double angle, const double& radius = 1, const bool& useDegrees = false) {
			if (useDegrees) {
				angle *= std::acos(-1)/180.0;
			}
			return Vec2(radius*std::cos(angle), radius*std::sin(angle));
		}
		
		//  This allows arrays of size 2 to be converted into Vec2
		//  This also allows Vec2 to take an array of size 2 as a constructor argument
		inline Vec2(const array<double, 2>& inputArray) : x(inputArray[0]), y(inputArray[1]) {}
		
		//  This allows Vec2 to take an SFML sf::Vector2f (float 2D vector) as a constructor argument
		inline Vec2(const sf::Vector2f& inputVector) : x(inputVector.x), y(inputVector.y) {}
		
		//  This allows Vec2 to take an SFML sf::Vector2u (unsigned int 2D vector) as a constructor argument
		inline Vec2(const sf::Vector2u& inputVector) : x(static_cast<double>(inputVector.x)), y(static_cast<double>(inputVector.y)) {}
		
		//  This allows Vec2 to take an SFML sf::Vector2i (int 2D vector) as a constructor argument
		inline Vec2(const sf::Vector2i& inputVector) : x(static_cast<double>(inputVector.x)), y(static_cast<double>(inputVector.y)) {}
		
		//  This allows Vec2 to take two doubles as constructor arguments
		inline Vec2(const double& inputX, const double& inputY) : x(inputX), y(inputY) {}
		
		//  This allows Vec2 to take one double as a constructor argument
		inline Vec2(const double& inputScale = 0.0) : x(inputScale), y(inputScale) {}
		
		//  This allows Vec2 to convert into an SFML sf::Vector2f automatically when needed
		inline operator sf::Vector2f() const {
			return sf::Vector2f(static_cast<float>(x), static_cast<float>(y));
		}
		
		//  This allows Vec2 to convert into an SFML sf::Vector2u automatically when needed	
		inline operator sf::Vector2u() const {
			return sf::Vector2u(static_cast<unsigned int>(x), static_cast<unsigned int>(y));
		}
		
		//  This allows Vec2 to convert into an SFML sf::Vector2i automatically when needed
		inline operator sf::Vector2i() const {
			return sf::Vector2i(static_cast<int>(x), static_cast<int>(y));
		}
};