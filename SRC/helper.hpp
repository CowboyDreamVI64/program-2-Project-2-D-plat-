#define LOAD_FROM_FILE  //  Options: 'LOAD_FROM_FILE', 'LOAD_FROM_MEMORY'

using namespace std;

static mt19937_64 psrand64_device;
const unsigned long long PSRAND64_MAX = numeric_limits<unsigned long long>::max();
unsigned long long psrand64() {
	return psrand64_device();
}
void seed64(const unsigned long long& inputSeed = 0, const bool& throwawayFirst = true) {
	psrand64_device.seed(inputSeed);
	if (throwawayFirst) {
		psrand64_device();
	}
	return;
}
template<typename T>
T psrand64_t(const T& outputMin = 0, const T& outputMax = static_cast<T>(is_floating_point_v<T> ? 1 : numeric_limits<T>::max()), const bool& inclusiveEnd = is_floating_point_v<T>) {
	if (is_floating_point_v<T>) {
		T randomNumber = psrand64()/(PSRAND64_MAX + static_cast<T>(1)*inclusiveEnd);
		randomNumber = randomNumber*(outputMax - outputMin) + outputMin;
		return static_cast<T>(randomNumber);
	} else {
		double randomNumber = psrand64()/(PSRAND64_MAX + 1.0);
		T randomInt = static_cast<T>(randomNumber*(outputMax - outputMin + inclusiveEnd)) + outputMin;
		return randomInt;
	}
}
			
float frandom(const float& outputMin = 0.0f, const float& outputMax = 1.0f, const bool& inclusiveEnd = false) {
	return psrand64_t(outputMin, outputMax, inclusiveEnd);
}
double drandom(const double& outputMin = 0.0, const double& outputMax = 1.0, const bool& inclusiveEnd = false) {
	return psrand64_t(outputMin, outputMax, inclusiveEnd);
}
int irandom(const int& outputMin = 0, const int& outputMax = numeric_limits<int>::max(), const bool& inclusiveEnd = false) {
	return psrand64_t(outputMin, outputMax, inclusiveEnd);
}
int size_t_random(const size_t& outputMin = 0, const size_t& outputMax = numeric_limits<size_t>::max(), const bool& inclusiveEnd = false) {
	return psrand64_t(outputMin, outputMax, inclusiveEnd);
}


class AlignDirection {
	public:
		const short directionValue;
		const bool movesLeft;
		const bool movesRight;
		const bool movesTop;
		const bool movesBottom;
		const bool movesHorizontal;
		const bool movesVertical;
		bool operator==(const AlignDirection& otherObject) const {
        	return directionValue == otherObject.directionValue;
    	}
    	constexpr AlignDirection opposite() const;
    	constexpr AlignDirection mirrorH() const;
    	constexpr AlignDirection mirrorV() const;
    	
		constexpr AlignDirection operator!() const {
			return opposite();
		}
		constexpr AlignDirection operator-() const {
			return mirrorH();
		}
		constexpr AlignDirection operator+() const {
			return mirrorV();
		}
    	constexpr AlignDirection(const short& inputDirectionValue, const bool& inputMovesLeft, const bool& inputMovesTop, const bool& inputMovesRight, const bool& inputMovesBottom, const bool& inputMovesHorizontal, const bool& inputMovesVertical) : directionValue(inputDirectionValue), movesLeft(inputMovesLeft), movesTop(inputMovesTop), movesRight(inputMovesRight), movesBottom(inputMovesBottom), movesHorizontal(inputMovesHorizontal), movesVertical(inputMovesVertical) {}
};
namespace Align {
	static constexpr AlignDirection None = AlignDirection(0,false,false,false,false,false,false);
	static constexpr AlignDirection Left = AlignDirection(1,true,false,false,false,true,false);
	static constexpr AlignDirection CenterLeft = AlignDirection(2,true,false,false,false,true,true);
	static constexpr AlignDirection TopLeft = AlignDirection(3,true,true,false,false,true,true);
	static constexpr AlignDirection Top = AlignDirection(4,false,true,false,false,false,true);
	static constexpr AlignDirection CenterTop = AlignDirection(5,false,true,false,false,true,true);
	static constexpr AlignDirection TopRight = AlignDirection(6,false,true,true,false,true,true);
	static constexpr AlignDirection Right = AlignDirection(7,false,false,true,false,true,false);
	static constexpr AlignDirection CenterRight = AlignDirection(8,false,false,true,false,true,true);
	static constexpr AlignDirection BottomRight = AlignDirection(9,false,false,true,true,true,true);
	static constexpr AlignDirection Bottom = AlignDirection(10,false,false,false,true,false,true);
	static constexpr AlignDirection CenterBottom = AlignDirection(11,false,false,false,true,true,true);
	static constexpr AlignDirection BottomLeft = AlignDirection(12,true,false,false,true,true,true);
	static constexpr AlignDirection CenterHorizontal = AlignDirection(13,false,false,false,false,true,false);
	static constexpr AlignDirection CenterVertical = AlignDirection(14,false,false,false,false,false,true);
	static constexpr AlignDirection Center = AlignDirection(15,false,false,false,false,true,true);
};	
constexpr AlignDirection AlignDirection::opposite() const {
	switch (directionValue) {
		case Align::Left.directionValue:
			return Align::Right;
			break;
		case Align::CenterLeft.directionValue:
			return Align::CenterRight;
			break;
		case Align::TopLeft.directionValue:
			return Align::BottomRight;
			break;
		case Align::Top.directionValue:
			return Align::Bottom;
			break;
		case Align::CenterTop.directionValue:
			return Align::CenterBottom;
			break;
		case Align::TopRight.directionValue:
			return Align::BottomLeft;
			break;
		case Align::Right.directionValue:
			return Align::Left;
			break;
		case Align::CenterRight.directionValue:
			return Align::CenterLeft;
			break;
		case Align::BottomRight.directionValue:
			return Align::TopLeft;
			break;
		case Align::Bottom.directionValue:
			return Align::Top;
			break;
		case Align::CenterBottom.directionValue:
			return Align::CenterTop;
			break;
		case Align::BottomLeft.directionValue:
			return Align::TopRight;
			break;
	}
	return *this;
}
constexpr AlignDirection AlignDirection::mirrorH() const {
	switch (directionValue) {
		case Align::Left.directionValue:
			return Align::Right;
			break;
		case Align::CenterLeft.directionValue:
			return Align::CenterRight;
			break;
		case Align::TopLeft.directionValue:
			return Align::TopRight;
			break;
		case Align::TopRight.directionValue:
			return Align::TopLeft;
			break;
		case Align::Right.directionValue:
			return Align::Left;
			break;
		case Align::CenterRight.directionValue:
			return Align::CenterLeft;
			break;
		case Align::BottomRight.directionValue:
			return Align::BottomLeft;
			break;
		case Align::BottomLeft.directionValue:
			return Align::BottomRight;
			break;
	}
	return *this;
}
constexpr AlignDirection AlignDirection::mirrorV() const {
	switch (directionValue) {
		case Align::TopLeft.directionValue:
			return Align::BottomLeft;
			break;
		case Align::Top.directionValue:
			return Align::Bottom;
			break;
		case Align::CenterTop.directionValue:
			return Align::CenterBottom;
			break;
		case Align::TopRight.directionValue:
			return Align::BottomRight;
			break;
		case Align::BottomRight.directionValue:
			return Align::TopRight;
			break;
		case Align::Bottom.directionValue:
			return Align::Top;
			break;
		case Align::CenterBottom.directionValue:
			return Align::CenterTop;
			break;
		case Align::BottomLeft.directionValue:
			return Align::TopLeft;
			break;
	}
	return *this;
}

namespace ColorChannel {
	const unsigned short None = 0;
	const unsigned short Red = 1;
	const unsigned short Green = 2;
	const unsigned short Blue = 3;
	const unsigned short Alpha = 4;
	const unsigned short All = 5;
	const unsigned short AllA = 6;
}
namespace Direction {
	const bool& Forward = false;
	const bool& Backward = true;
}
namespace ExtendedFunction {
	float getColor(const sf::Color& inputColor, const unsigned short& inputColorChannel = ColorChannel::None) {
		if (inputColorChannel == ColorChannel::Red) {
			return inputColor.r/255.0f;
		} else if (inputColorChannel == ColorChannel::Green) {
			return inputColor.g/255.0f;
		} else if (inputColorChannel == ColorChannel::Blue) {
			return inputColor.b/255.0f;
		} else if (inputColorChannel == ColorChannel::Alpha) {
			return inputColor.a/255.0f;
		}
		return nan("");
	}
	sf::Color setColor(const sf::Color& inputColor, float inputR = 1.0f, float inputG = 1.0f, float inputB = 1.0f) {
		inputR *= inputR >= 0.0f;
		inputR = inputR >= 1.0f ? 1.0f : inputR;
		inputG *= inputG >= 0.0f;
		inputG = inputG >= 1.0f ? 1.0f : inputG;
		inputB *= inputB >= 0.0f;
		inputB = inputB >= 1.0f ? 1.0f : inputB;
		return sf::Color(static_cast<uint8_t>(inputR*255.0f), static_cast<uint8_t>(inputG*255.0f), static_cast<uint8_t>(inputB*255.0f), inputColor.a);
	}
	sf::Color setTint(sf::Color inputColor, float& inputOpacity, float inputTint = 1.0, const unsigned short inputColorChannel = ColorChannel::All) {
		inputTint *= inputTint >= 0.0f;
		inputTint = inputTint >= 1.0f ? 1.0f : inputTint;
		if (inputColorChannel == ColorChannel::Red || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.r = static_cast<uint8_t>(inputTint * 255.0f);
		}
		if (inputColorChannel == ColorChannel::Green || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.g = static_cast<uint8_t>(inputTint * 255.0f);
		}
		if (inputColorChannel == ColorChannel::Blue || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.b = static_cast<uint8_t>(inputTint * 255.0f);
		}
		if (inputColorChannel == ColorChannel::Alpha || inputColorChannel == ColorChannel::AllA) {
			inputOpacity = inputTint;
		}
		return inputColor;
	}
	sf::Color multiplyTint(sf::Color inputColor, float& inputOpacity, float inputTint = 1.0, const unsigned short inputColorChannel = ColorChannel::All) {
		inputTint *= inputTint >= 0.0;
		if (inputColorChannel == ColorChannel::Red || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.r = static_cast<uint8_t>(inputColor.r * inputTint >= 255.0 ? 255.0 : inputColor.r * inputTint);
		}
		if (inputColorChannel == ColorChannel::Green || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.g = static_cast<uint8_t>(inputColor.g * inputTint >= 255.0 ? 255.0 : inputColor.g * inputTint);
		}
		if (inputColorChannel == ColorChannel::Blue || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.b = static_cast<uint8_t>(inputColor.b * inputTint >= 255.0 ? 255.0 : inputColor.b * inputTint);
		}
		if (inputColorChannel == ColorChannel::Alpha || inputColorChannel == ColorChannel::AllA) {
			inputOpacity *= inputTint;
			inputOpacity = inputOpacity >= 1.0 ? 1.0 : inputOpacity;
		}
		return inputColor;
	}
	sf::Color addTint(sf::Color inputColor, float& inputOpacity, float inputTint = 0.0, const unsigned short inputColorChannel = ColorChannel::All) {
		float newRedValue = inputColor.r;
		float newGreenValue = inputColor.g;
		float newBlueValue = inputColor.b;
		if (inputColorChannel == ColorChannel::Red || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			newRedValue += inputTint * 255.0;
			newRedValue *= newRedValue >= 0.0;
			newRedValue = newRedValue >= 255.0 ? 255.0 : newRedValue;
		}
		if (inputColorChannel == ColorChannel::Green || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			newGreenValue += inputTint * 255.0;
			newGreenValue *= newGreenValue >= 0.0;
			newGreenValue = newGreenValue >= 255.0 ? 255.0 : newGreenValue;
		}
		if (inputColorChannel == ColorChannel::Blue || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			newBlueValue += inputTint * 255.0;
			newBlueValue *= newBlueValue >= 0.0;
			newBlueValue = newBlueValue >= 255.0 ? 255.0 : newBlueValue;
		}
		inputColor.r = static_cast<uint8_t>(newRedValue);
		inputColor.g = static_cast<uint8_t>(newGreenValue);
		inputColor.b = static_cast<uint8_t>(newBlueValue);
		if (inputColorChannel == ColorChannel::Alpha || inputColorChannel == ColorChannel::AllA) {
			inputOpacity += inputTint;
			inputOpacity *= inputOpacity >= 0.0;
			inputOpacity = inputOpacity >= 1.0 ? 1.0 : inputOpacity;
		}
		return inputColor;
	}
	sf::Color resetTint(sf::Color inputColor, float& inputOpacity, const unsigned short inputColorChannel = ColorChannel::All) {
		if (inputColorChannel == ColorChannel::Red || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.r = static_cast<uint8_t>(255);
		}
		if (inputColorChannel == ColorChannel::Green || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.g = static_cast<uint8_t>(255);
		}
		if (inputColorChannel == ColorChannel::Blue || inputColorChannel == ColorChannel::All || inputColorChannel == ColorChannel::AllA) {
			inputColor.b = static_cast<uint8_t>(255);
		}
		if (inputColorChannel == ColorChannel::Alpha || inputColorChannel == ColorChannel::AllA) {
			inputOpacity = 1.0;
		}
		return inputColor;
	}
	sf::Vector2f getCenterDistance(const sf::FloatRect& boundsA, const sf::FloatRect& boundsB) {
		return sf::Vector2f({(boundsA.position.x - boundsB.position.x + boundsA.size.x/2.0f)/(boundsB.size.x) - 0.5f, (boundsA.position.y - boundsB.position.y + boundsA.size.y/2.0f)/(boundsB.size.y) - 0.5f});
	}
	sf::Vector2f getDimensions(const sf::FloatRect& boundsA, const sf::FloatRect& boundsB) {
		return sf::Vector2f({boundsA.size.x/boundsB.size.x, boundsA.size.y/boundsB.size.y});
	}
	sf::Vector2f getDimensions(const sf::FloatRect& boundsA, const sf::Vector2f& scaleA, const sf::FloatRect& boundsB) {
		return sf::Vector2f({boundsA.size.x*scaleA.x/(1.0f*boundsB.size.x), boundsA.size.y*scaleA.y/(1.0f*boundsB.size.y)});
	}
	sf::Vector2f center(const sf::FloatRect& boundsA, const sf::FloatRect& boundsB) {
		return sf::Vector2f({boundsB.position.x + (boundsB.size.x - boundsA.size.x)/2.0f, boundsB.position.y + (boundsB.size.y - boundsA.size.y)/2.0f});
	}
	sf::Vector2f offset(const sf::FloatRect& boundsA, const sf::FloatRect& boundsB, const sf::Vector2f& inputOffset) {
		return sf::Vector2f({boundsA.position.x + boundsB.size.x*inputOffset.x, boundsA.position.y + boundsB.size.y*inputOffset.y});
	}
	sf::Vector2f offset(const sf::FloatRect& boundsA, const sf::Vector2f& boundsB, const sf::Vector2f& inputOffset) {
		return sf::Vector2f({boundsA.position.x + boundsB.x*inputOffset.x, boundsA.position.y + boundsB.y*inputOffset.y});
	}
	sf::Vector2f offset(const sf::FloatRect& bounds, const sf::Vector2f& inputOffset, const bool& useGlobalContext = true) {
		if (useGlobalContext) {
			return sf::Vector2f({bounds.position.x + bounds.size.x*inputOffset.x, bounds.position.y + bounds.size.y*inputOffset.y});
		} else {
			return sf::Vector2f({bounds.position.x + inputOffset.x, bounds.position.y + inputOffset.y});
		}
	}
	vector<sf::Vector2f> multiply(const sf::FloatRect& bounds, const sf::Vector2f& inputScale, const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
		float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
		float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
		return vector<sf::Vector2f>({sf::Vector2f({inputScale.x * inputMultiplier.y, inputScale.y * inputMultiplier.y}), sf::Vector2f({bounds.position.x + 0.5f*bounds.size.x*(1 - inputMultiplier.x) + bounds.size.x*(1 - inputMultiplier.x)*xDirection, bounds.position.y + 0.5f*bounds.size.y*(1 - inputMultiplier.y) + bounds.size.y*(1 - inputMultiplier.y)*yDirection})});						
	}
	vector<sf::Vector2f> multiply(const sf::FloatRect& bounds, const sf::Vector2f& inputScale, const float& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
		return multiply(bounds, inputScale, sf::Vector2f({inputMultiplier, inputMultiplier}), alignDirection);
	}
	vector<sf::Vector2f> setScale(const sf::FloatRect& bounds, const sf::Vector2f& inputScale, const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
		float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
		float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
		return vector<sf::Vector2f>({sf::Vector2f({inputMultiplier.x, inputMultiplier.y}), sf::Vector2f({bounds.position.x + 0.5f*bounds.size.x*(1 - inputMultiplier.x/inputScale.x) + bounds.size.x*(1 - inputMultiplier.x/inputScale.x)*xDirection, bounds.position.y + 0.5f*bounds.size.y*(1 - inputMultiplier.y/inputScale.y) + bounds.size.y*(1 - inputMultiplier.y/inputScale.y)*yDirection})});						
	}
	vector<sf::Vector2f> setScale(const sf::FloatRect& bounds, const sf::Vector2f& inputScale, const float& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
		return setScale(bounds, inputScale, sf::Vector2f({inputMultiplier, inputMultiplier}), alignDirection);
	}	
	vector<sf::Vector2f> resizeToFit(const sf::FloatRect& boundsAGlobal, const sf::FloatRect& boundsBGlobal, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContextA = true, const sf::FloatRect& boundsALocal = sf::FloatRect(), const sf::Vector2f& boundsAScale = sf::Vector2f(), const bool& useGlobalContextB = true, const sf::FloatRect& boundsBLocal = sf::FloatRect(), const sf::Vector2f& boundsBScale = sf::Vector2f()) {
		float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
		float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
		float sizeMultiplier;
		sf::FloatRect boundsA = useGlobalContextA ? boundsAGlobal : boundsALocal;
		sf::FloatRect boundsB = useGlobalContextB ? boundsBGlobal : boundsBLocal;
		if (!useGlobalContextA) {
			boundsA.size = sf::Vector2f({boundsA.size.x * boundsAScale.x, boundsA.size.y * boundsAScale.y});
		}
		if (!useGlobalContextB) {
			boundsB.size = sf::Vector2f({boundsB.size.x * boundsBScale.x, boundsB.size.y * boundsBScale.y});
		}
		if (boundsB.size.x/boundsA.size.x < boundsB.size.y/boundsA.size.y) {
			sizeMultiplier = boundsB.size.x/boundsA.size.x;
		} else {
			sizeMultiplier = boundsB.size.y/boundsA.size.y;
		}
		return vector<sf::Vector2f>({sf::Vector2f({boundsAScale.x * sizeMultiplier, boundsAScale.y * sizeMultiplier}), sf::Vector2f({boundsAGlobal.position.x + 0.5f*boundsAGlobal.size.x*(1 - sizeMultiplier/boundsAScale.x) + boundsAGlobal.size.x*(1 - sizeMultiplier)*xDirection, boundsAGlobal.position.y + 0.5f*boundsAGlobal.size.y*(1 - sizeMultiplier/boundsAScale.y) + boundsAGlobal.size.y*(1 - sizeMultiplier)*yDirection})});
	}
	vector<sf::Vector2f> resizeToFill(const sf::FloatRect& boundsAGlobal, const sf::FloatRect& boundsBGlobal, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContextA = true, const sf::FloatRect& boundsALocal = sf::FloatRect(), const sf::Vector2f& boundsAScale = sf::Vector2f(), const bool& useGlobalContextB = true, const sf::FloatRect& boundsBLocal = sf::FloatRect(), const sf::Vector2f& boundsBScale = sf::Vector2f()) {
		float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
		float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
		float sizeMultiplier;
		sf::FloatRect boundsA = useGlobalContextA ? boundsAGlobal : boundsALocal;
		sf::FloatRect boundsB = useGlobalContextB ? boundsBGlobal : boundsBLocal;
		if (!useGlobalContextA) {
			boundsA.size = sf::Vector2f({boundsA.size.x * boundsAScale.x, boundsA.size.y * boundsAScale.y});
		}
		if (!useGlobalContextB) {
			boundsB.size = sf::Vector2f({boundsB.size.x * boundsBScale.x, boundsB.size.y * boundsBScale.y});
		}
		if (boundsB.size.x/boundsA.size.x > boundsB.size.y/boundsA.size.y) {
			sizeMultiplier = boundsB.size.x/boundsA.size.x;
		} else {
			sizeMultiplier = boundsB.size.y/boundsA.size.y;
		}
		return vector<sf::Vector2f>({sf::Vector2f({boundsAScale.x * sizeMultiplier, boundsAScale.y * sizeMultiplier}), sf::Vector2f({boundsAGlobal.position.x + 0.5f*boundsAGlobal.size.x*(1 - sizeMultiplier/boundsAScale.x) + boundsAGlobal.size.x*(1 - sizeMultiplier)*xDirection, boundsAGlobal.position.y + 0.5f*boundsAGlobal.size.y*(1 - sizeMultiplier/boundsAScale.y) + boundsAGlobal.size.y*(1 - sizeMultiplier)*yDirection})});
	}
	vector<sf::Vector2f> resizeToFit(const sf::FloatRect& boundsAGlobal, const sf::Vector2f& boundsBGlobal, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContextA = true, const sf::FloatRect& boundsALocal = sf::FloatRect(), const sf::Vector2f& boundsAScale = sf::Vector2f()) {
		return resizeToFit(boundsAGlobal, sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), boundsBGlobal), alignDirection, useGlobalContextA, boundsALocal, boundsAScale);
	}
	vector<sf::Vector2f> resizeToFill(const sf::FloatRect& boundsAGlobal, const sf::Vector2f& boundsBGlobal, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContextA = true, const sf::FloatRect& boundsALocal = sf::FloatRect(), const sf::Vector2f& boundsAScale = sf::Vector2f()) {
		return resizeToFill(boundsAGlobal, sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), boundsBGlobal), alignDirection, useGlobalContextA, boundsALocal, boundsAScale);
	}
	sf::Vector2f align(const sf::FloatRect& boundsA, const sf::FloatRect& boundsB, const AlignDirection& anchorSide = Align::None, const AlignDirection& alignDirection = Align::None) {
		float xAnchorDirection;
		float yAnchorDirection;
		if (anchorSide.movesHorizontal) {
			xAnchorDirection = (anchorSide.movesRight ? 1.0f : (anchorSide.movesLeft ? 0.0f : 0.5f));
		}
		if (anchorSide.movesVertical) {
			yAnchorDirection = (anchorSide.movesBottom ? 1.0f : (anchorSide.movesTop ? 0.0f : 0.5f));
		}
		float xAlignDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
		float yAlignDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
		return sf::Vector2f({(anchorSide.movesHorizontal ? boundsB.size.x*xAnchorDirection + boundsB.position.x - boundsA.size.x/2.0f : boundsA.position.x) + boundsA.size.x*xAlignDirection, (anchorSide.movesVertical ? boundsB.size.y*yAnchorDirection + boundsB.position.y - boundsA.size.y/2.0f : boundsA.position.y) + boundsA.size.y*yAlignDirection});
	}
	sf::Vector2f align(const sf::FloatRect& bounds, const AlignDirection& alignDirection = Align::None) {
		float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
		float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
		return sf::Vector2f({bounds.position.x + bounds.size.x * xDirection, bounds.position.y + bounds.size.y * yDirection});
	}
	sf::Vector2f getNormalizedPosition(const sf::FloatRect& boundsA, const sf::FloatRect& boundsB, sf::Vector2f offset = sf::Vector2f(), bool useNormalizedPosition = true) {
		if (useNormalizedPosition) {
			offset = sf::Vector2f({offset.x + 0.5f, offset.y + 0.5f});
		}
		return sf::Vector2f({(boundsA.position.x - boundsB.position.x + offset.x*boundsA.size.x)/boundsB.size.x - (useNormalizedPosition ? 0.5f : 0.0f), (boundsA.position.y - boundsB.position.y + offset.y*boundsA.size.y)/boundsB.size.y - (useNormalizedPosition ? 0.5f : 0.0f)});
	}
	template <typename T>
	sf::Vector2f getNormalizedPosition(const sf::Vector2<T>& positionA, const sf::FloatRect& boundsB, const sf::Vector2f offset = sf::Vector2f(), bool useNormalizedPosition = true) {
		return getNormalizedPosition(sf::FloatRect(sf::Vector2f({static_cast<float>(positionA.x), static_cast<float>(positionA.y)}), sf::Vector2f({0.0f, 0.0f})), boundsB, offset, useNormalizedPosition);
	}
	bool mouseContained(const sf::FloatRect bounds, const sf::RenderWindow* windowPtr, const bool& focusEnforced = true) {
		if (windowPtr && (!focusEnforced || windowPtr->hasFocus())) {
			return bounds.contains(windowPtr->mapPixelToCoords(sf::Mouse::getPosition(*windowPtr)));
		}
		return false;
	}
	bool mouseContained(const sf::FloatRect bounds, const sf::RenderWindow& window, const bool& focusEnforced = true) {
		if (!focusEnforced || window.hasFocus()) {
			return bounds.contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)));
		}
		return false;
	}
	template <typename T>
	vector<string> get_ids_with_all_tags(const T& extended_drawable, const vector<string>& inputTags = vector<string>()) {
		vector<string> outputIDs;
		for (const auto& pair : extended_drawable) {
			bool includeID = true;
			for (const string& currentTag : inputTags) {
				if (!pair.second.tag_exists(currentTag)) {
					includeID = false;
					break;
				}
			}
			if (includeID) {
				outputIDs.push_back(pair.first);
			}
		}
		return outputIDs;
	}
	template <typename T>
	vector<string> get_ids_with_any_tags(const T& extended_drawable, const vector<string>& inputTags = vector<string>()) {
		vector<string> outputIDs;
		for (const auto& pair : extended_drawable) {
			bool includeID = false;
			for (string currentTag : inputTags) {
				if (pair.second.tag_exists(currentTag)) {
					includeID = true;
					break;
				}
			}
			if (includeID) {
				outputIDs.push_back(pair.first);
			}
		}
		return outputIDs;
	}
	template <typename T>
	vector<string> get_ids_with_tag(const T& extended_drawable, const string& inputTag = string()) {
		vector<string> outputIDs;
		for (const auto& pair : extended_drawable) {
			if (pair.second.tag_exists(inputTag)) {
				outputIDs.push_back(pair.first);
			}
		}
		return outputIDs;
	}
	template <typename T>
	vector<string> get_ids_without_all_tags(const T& extended_drawable, const vector<string>& inputTags = vector<string>()) {
		vector<string> outputIDs;
		for (const auto& pair : extended_drawable) {
			bool includeID = true;
			for (const string& currentTag : inputTags) {
				if (!pair.second.tag_exists(currentTag)) {
					includeID = false;
					break;
				}
			}
			if (!includeID) {
				outputIDs.push_back(pair.first);
			}
		}
		return outputIDs;
	}
	template <typename T>
	vector<string> get_ids_without_any_tags(const T& extended_drawable, const vector<string>& inputTags = vector<string>()) {
		vector<string> outputIDs;
		for (const auto& pair : extended_drawable) {
			bool includeID = false;
			for (string currentTag : inputTags) {
				if (pair.second.tag_exists(currentTag)) {
					includeID = true;
					break;
				}
			}
			if (!includeID) {
				outputIDs.push_back(pair.first);
			}
		}
		return outputIDs;
	}
	template <typename T>
	vector<string> get_ids_without_tag(const T& extended_drawable, const string& inputTag = string()) {
		vector<string> outputIDs;
		for (const auto& pair : extended_drawable) {
			if (!pair.second.tag_exists(inputTag)) {
				outputIDs.push_back(pair.first);
			}
		}
		return outputIDs;
	}
}

template <typename CE>
class TaggableContainer;
template <typename CE>
class TaggableElement {
	public:
		unordered_set<string> tag;
		CE& tag_add(const string& inputTag) {
			if (count(tag.begin(), tag.end(), inputTag) <= 0) {
				tag.insert(inputTag);
			}
			return *static_cast<CE*>(this);
		}
		CE& tag_remove(const string& inputTag) {
			if (count(tag.begin(), tag.end(), inputTag) <= 0) {
				tag.erase(inputTag);
			}
			return *static_cast<CE*>(this);
		}
		CE& clear_tags() {
			tag = unordered_set<string>();
			return *static_cast<CE*>(this);
		}
		const bool tag_exists(const string& inputTag) const {
			return count(tag.begin(), tag.end(), inputTag) > 0;
		}
		vector<string> get_tags() {
			vector<string> outputVector = vector<string>(tag.begin(), tag.end());
			sort(outputVector.begin(), outputVector.end());
			return outputVector;
		}
};
template <typename CE>
class TaggableContainer {
	protected:
		unordered_map<string, CE>* taggables;
	public:
		vector<string> get_ids_with_all_tags(const vector<string>& inputTags = vector<string>()) {
			return ExtendedFunction::get_ids_with_all_tags(*taggables, inputTags);
		}
		vector<string> get_ids_with_any_tags(const vector<string>& inputTags = vector<string>()) {
			return ExtendedFunction::get_ids_with_any_tags(*taggables, inputTags);
		}
		vector<string> get_ids_with_tag(const string& inputTag = "") {
			return ExtendedFunction::get_ids_with_tag(*taggables, inputTag);
		}
		vector<string> get_ids_without_all_tags(const vector<string>& inputTags = vector<string>()) {
			return ExtendedFunction::get_ids_without_all_tags(*taggables, inputTags);
		}
		vector<string> get_ids_without_any_tags(const vector<string>& inputTags = vector<string>()) {
			return ExtendedFunction::get_ids_without_any_tags(*taggables, inputTags);
		}
		vector<string> get_ids_without_tag(const string& inputTag = "") {
			return ExtendedFunction::get_ids_without_tag(*taggables, inputTag);
		}
};

class SoundContainer;
class SoundEvent : public TaggableElement<SoundEvent> {
	public:
		SoundContainer* parentSoundContainer;
		sf::Sound* sound;
		float localVolume = 1.0;
		float localPan = 0.0;
		bool loop = false;
		bool paused = false;
		bool bypassPanShift = false;
		SoundEvent& update_volume();
		SoundEvent& update_pan();
		SoundEvent& update_pause();
		SoundEvent& update_loop() {
			if (sound) {
				sound->setLooping(loop);
			}
			return *this;
		}
		SoundEvent& update() {
			update_loop();
			update_volume();
			update_pause();
			update_pan();
			return *this;
		}
		float getVolume() {
			return localVolume;
		}
		float getPan() {
			if (sound) {
				return localPan;
			}
			return nan("");
		}
		bool getBypassPanShift() {
			return bypassPanShift;
		}
		SoundEvent& setBypassPanShift(const bool& inputBypassPanShift = false) {
			bypassPanShift = inputBypassPanShift;
			update_pan();
			return *this;
		}
		float getPitch() {
			if (sound) {
				return sound->getPitch();
			}
			return nan("");
		}
		bool isPlaying() {
			if (sound) {
				return (sound->getStatus() == sf::Sound::Status::Playing);
			}
			return false;
		}
		bool isPaused() {
			return paused;
		}
		bool isStopped() {
			if (sound) {
				return sound->getStatus() == sf::Sound::Status::Stopped;
			}
			return false;
		}
		bool isLooping() {
			return loop;
		}
		const sf::SoundBuffer& getBuffer() const {
			if (!sound) {
				throw runtime_error("Manual (std::runtime_error) from (!sound == true); sound buffer get failed");
			}
			return sound->getBuffer();
		}
		sf::Time getTimestamp() {
			if (sound) {
				return sound->getPlayingOffset();
			}
			return sf::Time();
		}
		sf::Time getDuration() {
			if (sound) {
				return sound->getBuffer().getDuration();
			}
			return sf::Time();
		}
		SoundEvent& setTimestamp(const sf::Time& inputTime) {
			if (sound) {
				sound->setPlayingOffset(inputTime);
			}
			return *this;
		}
		float getTimestamp_sec() {
			return getTimestamp().asSeconds();
		}
		float getTimestamp_ms() {
			return getTimestamp().asMilliseconds();
		}
		float getTimestamp_us() {
			return getTimestamp().asMicroseconds();
		}
		float getDuration_sec() {
			return getDuration().asSeconds();
		}
		float getDuration_ms() {
			return getDuration().asMilliseconds();
		}
		float getDuration_us() {
			return getDuration().asMicroseconds();
		}
		SoundEvent& setTimestamp_sec(const float& inputTimestamp) {
			setTimestamp(sf::seconds(inputTimestamp));
			return *this;
		}
		SoundEvent& setTimestamp_ms(const float& inputTimestamp) {
			setTimestamp(sf::milliseconds(inputTimestamp));
			return *this;
		}
		SoundEvent& setTimestamp_us(const float& inputTimestamp) {
			setTimestamp(sf::microseconds(inputTimestamp));
			return *this;
		}
		SoundEvent& setBuffer(sf::SoundBuffer& inputBuffer) {
			delete sound;
			sound = new sf::Sound(inputBuffer);
			update();
			return *this;
		}
		SoundEvent& setVolume(const float inputLocalVolume = 1.0) {
			localVolume = inputLocalVolume;
			update_volume();
			return *this;
		}
		SoundEvent& setPan(float inputPan = 0.0) {
			inputPan = inputPan >= 1.0 ? 1.0 : inputPan;
			inputPan = inputPan <= -1.0 ? -1.0 : inputPan;
			localPan = inputPan;
			update_pan();
			return *this;
		}
		SoundEvent& setPitch(float inputPitch = 1.0) {
			inputPitch *= inputPitch >= 0.0;
			if (sound) {
				sound->setPitch(inputPitch);
			}
			return *this;
		}
		SoundEvent& setPause(const bool& pauseNow) {
			paused = pauseNow;
			update_pause();
			return *this;
		}
		SoundEvent& setLooping(const bool& loopNow) {
			loop = loopNow;
			update_loop();
			return *this;
		}
		SoundEvent& pause() {
			paused = true;
			update_pause();
			return *this;
		}
		SoundEvent& unpause() {
			paused = false;
			update_pause();
			return *this;
		}
		SoundEvent& resume() {
			unpause();
			return *this;
		}
		SoundEvent& reset() {
			if (sound) {
				sound->stop();
			}
			setTimestamp_sec(0.0);
			pause();
			return *this;
		}
		SoundEvent& stop() {
			if (sound) {
				sound->stop();
			}
			return *this;
		}
		SoundEvent& replay() {
			reset();
			unpause();
			if (sound) {
				sound->play();
			}
			return *this;
		}
		SoundEvent(SoundContainer* SoundContainerObject, sf::SoundBuffer& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentSoundContainer(SoundContainerObject), bypassPanShift(inputBypassPanShift) {
			sound = new sf::Sound(inputBuffer);
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		~SoundEvent() {
			delete sound;
			sound = nullptr;
			return;
		}
		SoundEvent(SoundEvent& originalObject) {
			if (originalObject.sound) {
				sound = new sf::Sound(*originalObject.sound);
			} else {
				sound = nullptr;
			}
			localVolume = originalObject.localVolume,
			paused = originalObject.paused,
			loop = originalObject.loop;
			parentSoundContainer = originalObject.parentSoundContainer;
			update();
			return;
		}
		SoundEvent& operator=(SoundEvent& rObject) {
			if (this != &rObject) {
				delete sound;
				if (rObject.sound) {
					sound = new sf::Sound(*rObject.sound);
				} else {
					sound = nullptr;
				}
				localVolume = rObject.localVolume,
				paused = rObject.paused,
				loop = rObject.loop;
				parentSoundContainer = rObject.parentSoundContainer;
				update();
			}
			return *this;
		}
		SoundEvent(SoundEvent&& originalObject) noexcept : sound(originalObject.sound) {
			localVolume = originalObject.localVolume,
			paused = originalObject.paused,
			loop = originalObject.loop;
			parentSoundContainer = originalObject.parentSoundContainer;
			update_volume();
			update_loop();
			update_pause();
			originalObject.sound = nullptr;
			return;
		}
		SoundEvent& operator=(SoundEvent&& rObject) noexcept {
			if (this != &rObject) {
				sound = rObject.sound;
				localVolume = rObject.localVolume,
				paused = rObject.paused,
				loop = rObject.loop;
				parentSoundContainer = rObject.parentSoundContainer;
				update_volume();
				update_loop();
				update_pause();
				rObject.sound = nullptr;
			}
			return *this;
		}
};
class SoundContainer : public TaggableContainer<SoundEvent> {
	friend SoundEvent;
	
	private:
		float masterVolume = 1.0;
		float panShift = 0.0;
		bool masterPaused = false;
	public:
		unordered_map<string, SoundEvent> event;
		SoundEvent& play(const string& inputID, sf::SoundBuffer& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, SoundEvent(this, inputBuffer, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return event.at(inputID);
		}
		SoundContainer& update_volume() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_volume();
			}
			return *this;
		}
		SoundContainer& update_loop() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_loop();
			}
			return *this;
		}
		SoundContainer& update_pause() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pause();
			}
			return *this;
		}
		SoundContainer& update() {
			update_loop();
			update_volume();
			update_pause();
			return *this;
		}
		float getVolume() {
			return masterVolume;
		}
		bool isPlaying() {
			return !masterPaused;
		}
		bool isPaused() {
			return masterPaused;
		}
		bool exists(const string& inputID) {
			return event.count(inputID) != 0;
		}
		SoundContainer& update_pan() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pan();
			}
			return *this;
		}
		float getPanShift(const bool& deg = true) {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		SoundContainer& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return *this;
		}
		SoundContainer& setVolume(const float& inputMasterVolume) {
			masterVolume = inputMasterVolume;
			update_volume();
			return *this;
		}
		SoundContainer& setPause(const bool& pauseNow) {
			masterPaused = pauseNow;
			update_pause();
			return *this;
		}
		SoundContainer& pause() {
			masterPaused = true;
			return *this;
		}
		SoundContainer& unpause() {
			masterPaused = false;
			update_pause();
			return *this;
		}
		SoundContainer& resume() {
			unpause();
			return *this;
		}
		SoundContainer& erase(const string& inputID) {
			event.erase(inputID);
			return *this;
		}
		SoundContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		SoundContainer& clear() {
			event = unordered_map<string, SoundEvent>();
			return *this;
		}
		SoundContainer& clean() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				if (event.at(currentEvent.first).isStopped()) {
					erase(currentEvent.first);
				}
			}
			return *this;
		}
		SoundEvent& operator[](const string& inputID) {
			return event.at(inputID);
		}
		const SoundEvent& operator[](const string& inputID) const {
			return event.at(inputID);
		}
		SoundContainer(const float& inputMasterVolume = 1.0) : masterVolume(inputMasterVolume) {
			taggables = &event;
			masterVolume = masterVolume >= 1.0 ? 1.0 : masterVolume;
			masterVolume *= masterVolume >= 0.0;
			return;
		}
};
SoundEvent& SoundEvent::update_volume() {
	if (sound && parentSoundContainer) {
		sound->setVolume(localVolume*parentSoundContainer->masterVolume*100.0f);
	}
	return *this;
}
SoundEvent& SoundEvent::update_pan() {
	if (sound){
		if (!bypassPanShift && parentSoundContainer && parentSoundContainer->panShift != 0.0) {
			sound->setPan(cos(acos(localPan) + parentSoundContainer->panShift));
		} else {
			sound->setPan(localPan);
		}
	}
	return *this;
}
SoundEvent& SoundEvent::update_pause() {
	if (sound && parentSoundContainer) {
		if (paused || parentSoundContainer->masterPaused) {
			sound->pause();
		} else {
			sound->play();
		}
	}
	return *this;
}

class MusicContainer;
class MusicEvent : public TaggableElement<MusicEvent> {
	public:
		MusicContainer* parentMusicContainer;
		sf::Music music;
		float localVolume = 1.0;
		float localPan = 0.0;
		bool loop = false;
		bool paused = false;
		bool bypassPanShift = false;
		sf::Time loopStart = sf::Time::Zero;
		sf::Time loopEnd = sf::Time::Zero;
		MusicEvent& update_volume();
		MusicEvent& update_pan();
		MusicEvent& update_pause();
		MusicEvent& update_loop() {
			music.setLooping(loop);
			return *this;
		}
		MusicEvent& update_loop_points() {
			sf::Time musicDuration = music.getDuration();
			if (loopStart < sf::Time::Zero) {
				loopStart = sf::Time::Zero;
			} else if (loopEnd > musicDuration) {
				loopEnd = musicDuration;
			}
			if (loopEnd < sf::Time::Zero) {
				loopStart = sf::Time::Zero;
			} else if (loopEnd > musicDuration) {
				loopEnd = musicDuration;
			}
			music.setLoopPoints(sf::Music::TimeSpan({loopStart, loopEnd}));
			return *this;
		}
		MusicEvent& update() {
			update_loop();
			update_volume();
			update_pause();
			update_pan();
			update_loop_points();
			return *this;
		}
		sf::Music::TimeSpan getLoopPoints() {
			return music.getLoopPoints();
		}
		sf::Time getLoopPointStart() {
			return loopStart;
		}
		sf::Time getLoopPointDuration(const bool& useEndAsDuration = true) {
			if (useEndAsDuration) {
				return loopEnd - loopStart;
			} else {
				return loopEnd;
			}
		}
		MusicEvent& setLoopPoints(const sf::Time& startDuration, const sf::Time& endDuration, const bool& useEndAsDuration = true) {
			loopStart = startDuration;
			loopEnd = endDuration;
			if (useEndAsDuration) {
				loopEnd += startDuration;
			}
			update_loop_points();
			return *this;
		}
		MusicEvent& resetLoopPoints() {
			loopStart = sf::Time::Zero;
			loopEnd = music.getDuration();
			update_loop_points();
			return *this;
		}
		MusicEvent& setLoopPoints_sec(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::seconds(startDuration), sf::seconds(endDuration), useEndAsDuration);
			return *this;
		}
		MusicEvent& setLoopPoints_ms(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::milliseconds(startDuration), sf::milliseconds(endDuration), useEndAsDuration);
			return *this;
		}
		MusicEvent& setLoopPoints_us(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::microseconds(startDuration), sf::microseconds(endDuration), useEndAsDuration);
			return *this;
		}
		sf::Time loop_begin() {
			return loopStart;
		}
		sf::Time loop_end() {
			return loopEnd;
		}
		sf::Time loop_duration() {
			return loopEnd - loopStart;
		}
		sf::Time duration() {
			return music.getDuration();
		}
		float getLoopPointStart_sec() {
			return getLoopPointStart().asSeconds();
		}
		float getLoopPointStart_ms() {
			return getLoopPointStart().asMilliseconds();
		}
		float getLoopPointStart_us() {
			return getLoopPointStart().asMicroseconds();
		}
		float getLoopPointDuration_sec(const bool& useEndAsDuration = true) {
			return getLoopPointDuration(useEndAsDuration).asSeconds();
		}
		float getLoopPointDuration_ms(const bool& useEndAsDuration = true) {
			return getLoopPointDuration(useEndAsDuration).asMilliseconds();
		}
		float getLoopPointDuration_us(const bool& useEndAsDuration = true) {
			return getLoopPointDuration(useEndAsDuration).asMicroseconds();
		}
		float getVolume() {
			return localVolume;
		}
		float getPan() {
			return localPan;
		}
		bool getBypassPanShift() {
			return bypassPanShift;
		}
		MusicEvent& setBypassPanShift(const bool& inputBypassPanShift = false) {
			bypassPanShift = inputBypassPanShift;
			update_pan();
			return *this;
		}
		float getPitch() {
			return music.getPitch();
		}
		bool isPlaying() {
			return (music.getStatus() == sf::Music::Status::Playing);
		}
		bool isPaused() {
			return paused;
		}
		bool isStopped() {
			return music.getStatus() == sf::Music::Status::Stopped;
		}
		bool isLooping() {
			return loop;
		}
		sf::Time getTimestamp() {
			return music.getPlayingOffset();
		}
		sf::Time getDuration() {
			return music.getDuration();
		}
		MusicEvent& setTimestamp(const sf::Time& inputTime) {
			music.setPlayingOffset(inputTime);
			return *this;
		}
		float getTimestamp_sec() {
			return getTimestamp().asSeconds();
		}
		float getTimestamp_ms() {
			return getTimestamp().asMilliseconds();
		}
		float getTimestamp_us() {
			return getTimestamp().asMicroseconds();
		}
		float getDuration_sec() {
			return getDuration().asSeconds();
		}
		float getDuration_ms() {
			return getDuration().asMilliseconds();
		}
		float getDuration_us() {
			return getDuration().asMicroseconds();
		}
		MusicEvent& setTimestamp_sec(const float& inputTimestamp) {
			setTimestamp(sf::seconds(inputTimestamp));
			return *this;
		}
		MusicEvent& setTimestamp_ms(const float& inputTimestamp) {
			setTimestamp(sf::milliseconds(inputTimestamp));
			return *this;
		}
		MusicEvent& setTimestamp_us(const float& inputTimestamp) {
			setTimestamp(sf::microseconds(inputTimestamp));
			return *this;
		}
		MusicEvent& setVolume(const float inputLocalVolume = 1.0) {
			localVolume = inputLocalVolume;
			update_volume();
			return *this;
		}
		MusicEvent& setPan(float inputPan = 0.0) {
			inputPan = inputPan >= 1.0 ? 1.0 : inputPan;
			inputPan = inputPan <= -1.0 ? -1.0 : inputPan;
			localPan = inputPan;
			update_pan();
			return *this;
		}
		MusicEvent& setPitch(float inputPitch = 1.0) {
			inputPitch *= inputPitch >= 0.0;
			music.setPitch(inputPitch);
			return *this;
		}
		MusicEvent& setPause(const bool& pauseNow) {
			paused = pauseNow;
			update_pause();
			return *this;
		}
		MusicEvent& setLooping(const bool& loopNow) {
			loop = loopNow;
			update_loop();
			return *this;
		}
		MusicEvent& pause() {
			paused = true;
			update_pause();
			return *this;
		}
		MusicEvent& unpause() {
			paused = false;
			update_pause();
			return *this;
		}
		MusicEvent& resume() {
			unpause();
			return *this;
		}
		MusicEvent& reset() {
			music.stop();
			setTimestamp_sec(0.0);
			pause();
			return *this;
		}
		MusicEvent& stop() {
			music.stop();
			return *this;
		}
		MusicEvent& replay() {
			reset();
			unpause();
			music.play();
			return *this;
		}
		MusicEvent& openFromFile(const string& inputPath) {
			if (!music.openFromFile(inputPath)) {
				throw runtime_error("Manual (std::runtime_error) from (!music.openFromFile(inputPath) == true); music buffer load failed");
			}
			resetLoopPoints();
			return *this;
		}
		MusicEvent& openFromMemory(const char* inputData, size_t inputSize) {
			if (!music.openFromMemory(inputData, inputSize)) {
				throw runtime_error("Manual (std::runtime_error) from (!music.openFromMemory(inputData, inputSize) == true); music buffer load failed");
			}
			loopStart = sf::Time::Zero;
			loopEnd = getDuration();
			return *this;
		}
		MusicEvent& openFromMemory(const vector<char>& inputBuffer) {
			openFromMemory(inputBuffer.data(), inputBuffer.size());
			return *this;
		}
		MusicEvent& loadFromFile(const string& inputPath) {
			openFromFile(inputPath);
			return *this;
		}
		MusicEvent& loadFromMemory(const char* inputData, size_t inputSize) {
			openFromMemory(inputData, inputSize);
			return *this;
		}
		MusicEvent& loadFromMemory(const vector<char>& inputBuffer) {
			openFromMemory(inputBuffer);
			return *this;
		}
		MusicEvent(MusicContainer* MusicContainerObject, const string& inputPath, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentMusicContainer(MusicContainerObject), bypassPanShift(inputBypassPanShift) {
			music = sf::Music(inputPath);
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		MusicEvent(MusicContainer* MusicContainerObject, const char* inputData, const size_t& inputSize, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentMusicContainer(MusicContainerObject), bypassPanShift(inputBypassPanShift) {
			music = sf::Music(inputData, inputSize);
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		MusicEvent(MusicContainer* MusicContainerObject, const vector<char>& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentMusicContainer(MusicContainerObject), bypassPanShift(inputBypassPanShift) {
			music = sf::Music(inputBuffer.data(), inputBuffer.size());
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
};
class MusicContainer : public TaggableContainer<MusicEvent> {
	friend MusicEvent;
	
	private:
		float masterVolume = 1.0;
		float panShift = 0.0;
		bool masterPaused = false;
	public:
		unordered_map<string, MusicEvent> event;
		MusicContainer& play(const string& inputID, const string& inputPath, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputPath, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer& play(const string& inputID, const char* inputData, const size_t& inputSize, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputData, inputSize, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer& play(const string& inputID, const vector<char>& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputBuffer, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer& update_volume() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_volume();
			}
			return *this;
		}
		MusicContainer& update_loop() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_loop();
			}
			return *this;
		}
		MusicContainer& update_pause() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pause();
			}
			return *this;
		}
		MusicContainer& update() {
			update_loop();
			update_volume();
			update_pause();
			return *this;
		}
		float getVolume() {
			return masterVolume;
		}
		bool isPlaying() {
			return !masterPaused;
		}
		bool isPaused() {
			return masterPaused;
		}
		bool exists(const string& inputID) {
			return event.count(inputID) != 0;
		}
		MusicContainer& update_pan() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pan();
			}
			return *this;
		}
		float getPanShift(const bool& deg = true) {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		MusicContainer& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return *this;
		}
		MusicContainer& setVolume(const float& inputMasterVolume) {
			masterVolume = inputMasterVolume;
			update_volume();
			return *this;
		}
		MusicContainer& setPause(const bool& pauseNow) {
			masterPaused = pauseNow;
			update_pause();
			return *this;
		}
		MusicContainer& pause() {
			masterPaused = true;
			return *this;
		}
		MusicContainer& unpause() {
			masterPaused = false;
			update_pause();
			return *this;
		}
		MusicContainer& resume() {
			unpause();
			return *this;
		}
		MusicContainer& erase(const string& inputID) {
			event.erase(inputID);
			return *this;
		}
		MusicContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		MusicContainer& clear() {
			event = unordered_map<string, MusicEvent>();
			return *this;
		}
		MusicContainer& clean() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				if (event.at(currentEvent.first).isStopped()) {
					erase(currentEvent.first);
				}
			}
			return *this;
		}
		MusicEvent& operator[](const string& inputID) {
			return event.at(inputID);
		}
		const MusicEvent& operator[](const string& inputID) const {
			return event.at(inputID);
		}
		MusicContainer(const float& inputMasterVolume = 1.0) : masterVolume(inputMasterVolume) {
			masterVolume = masterVolume >= 1.0 ? 1.0 : masterVolume;
			masterVolume *= masterVolume >= 0.0;
			
			taggables = &event;
			return;
		}
};
MusicEvent& MusicEvent::update_volume() {
	if (parentMusicContainer) {
		music.setVolume(localVolume*parentMusicContainer->masterVolume*100.0f);
	}
	return *this;
}
MusicEvent& MusicEvent::update_pan() {
	if (!bypassPanShift && parentMusicContainer && parentMusicContainer->panShift != 0.0) {
		music.setPan(cos(acos(localPan) + parentMusicContainer->panShift));
	} else {
		music.setPan(localPan);
	}
	return *this;
}
MusicEvent& MusicEvent::update_pause() {
	if (parentMusicContainer) {
		if (paused || parentMusicContainer->masterPaused) {
			music.pause();
		} else {
			music.play();
		}
	}
	return *this;
}

class SpriteContainer;
class TextContainer;
class ExtendedWindow {
	private:
		sf::Vector2u last_size;
		sf::Vector2i last_position;
		bool inputFullscreen = false;
	public:
		ExtendedWindow& refresh(const bool& declareBoundsUniforms, const SpriteContainer& inputSpriteContainer, const TextContainer& inputTextContainer);
		template <typename T, typename U>
		ExtendedWindow& ExtendedDraw(const T* extendedDrawable, const U& drawable, const bool& declareBoundsUniforms);
		sf::RenderWindow* window;
		unsigned int framerate;
		bool fullscreen = false;
		bool mouseLocked = false;
		bool mouseVisible = true;
		bool vsync;
		string title;
		sf::Vector2u resolution;
		float initialSizeMultiplier;
		sf::Image icon;
		
		sf::RenderWindow*& drawable() {
			return window;
		}
		
		ExtendedWindow& update_icon() {
			if (window) {
				window->setIcon(icon);
			}
			return *this;
		}
		ExtendedWindow& update_mouse_lock(const bool& overrideBoolean = false, const bool& overrideMouseLocked = false) {
			if (window) {
				bool lock = overrideBoolean ? overrideMouseLocked : mouseLocked;
				if (lock) {
					window->setMouseCursorGrabbed(true);
				} else {
					window->setMouseCursorGrabbed(false);
				}
			}
			return *this;
		}
		
		ExtendedWindow& update_mouse_visibility(const bool& overrideBoolean = false, const bool& overrideMouseVisible = true) {
			if (window) {
				bool hide = overrideBoolean ? !overrideMouseVisible : !mouseVisible;
				if (hide) {
					window->setMouseCursorVisible(false);
				} else {
					window->setMouseCursorVisible(true);
				}
			}
			return *this;
		}
		
		ExtendedWindow& update_resolution() {
			if (window) {
				window->setSize(resolution);
			}
			return *this;
		}
		
		ExtendedWindow& update_framerate() {
			if (window) {
				window->setFramerateLimit(framerate);
			}
			return *this;
		}
		
		ExtendedWindow& update_vsync() {
			if (window) {
				window->setVerticalSyncEnabled(vsync);
			}
			return *this;
		}
		
		sf::Image getIcon() {
			return icon;
		}
		
		ExtendedWindow& setIcon(const sf::Image& inputImage) {
			icon = inputImage;
			update_icon();
			return *this;
		}
		
		ExtendedWindow& setIcon(const sf::Texture& inputTexture) {
			icon = inputTexture.copyToImage();
			update_icon();
			return *this;
		}
		
		ExtendedWindow& resetIcon() {
			icon = sf::Image();
			update_icon();
			return *this;
		}
		
		void toggleFullscreen() {
			if (window) {
				sf::View currentView = window->getView();
				if (fullscreen) {
				window->create(sf::VideoMode(last_size), title, sf::State::Windowed);
				window->setPosition(last_position);
				} else {
					last_size = window->getSize();
					last_position = window->getPosition();
					sf::View currentView = window->getView();
					window->create(sf::VideoMode(resolution), title, sf::State::Fullscreen);
				}
				fullscreen = !fullscreen;
				window->setView(currentView);
				window->setVerticalSyncEnabled(vsync);
				window->setFramerateLimit(framerate);
			}
			update_mouse_lock();
			update_mouse_visibility();
			update_icon();
			return;
		}
		
		bool pollForClosure(const optional<sf::Event>& event) {
			if (window && event) {
				if (event->is<sf::Event::Closed>()) {
					return true;
				}
			}
			return false;
		}
		
		bool pollForF11(const bool& focusEnforced = true) {
			if (window) {
				if (focusEnforced) {
					if (!window->hasFocus()) {
						return false;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::F11)) {
					return true;
				}
			}
			return false;
		}
		
		bool pollForEscape(const bool& focusEnforced = true) {
			if (window) {
				if (focusEnforced) {
					if (!window->hasFocus()) {
						return false;
					}
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
					return true;
				}
			}
			return false;
		}
		
		bool pollForKey(const sf::Keyboard::Key& inputKey, const bool& focusEnforced = true) {
			if (window) {
				if (focusEnforced) {
					if (!window->hasFocus()) {
						return false;
					}
				}
				if (sf::Keyboard::isKeyPressed(inputKey)) {
					return true;
				}
			}
			return false;
		}
		
		bool stableState(const bool& inputBoolean = true) {
			return inputBoolean && window && window->isOpen();
		}
		
		ExtendedWindow& setTitle(const string& inputTitle) {
			title = inputTitle;
			if (window) {
				window->setTitle(inputTitle);
			}
			return *this;
		}
		
		ExtendedWindow& setResolution(const sf::Vector2u& inputResolution) {
			resolution = inputResolution;
			update_resolution();
			return *this;
		}
		
		ExtendedWindow& setFramerate(const unsigned int& inputFramerate) {
			framerate = inputFramerate;
			update_framerate();
			return *this;
		}
		
		ExtendedWindow& setVsync(const bool& useVsync) {
			vsync = useVsync;
			update_vsync();
			update_framerate();
			return *this;
		}
		
		ExtendedWindow& setFullscreen(const bool& useFullscreen) {
			if (useFullscreen != fullscreen) {
				toggleFullscreen();
			}
			return *this;
		}
		
		sf::FloatRect getGlobalBounds() {
			if (window) {
				sf::View windowView = window->getView();
				sf::Vector2f windowViewSize = windowView.getSize();
				sf::Vector2f windowViewCenter = windowView.getCenter();
				return sf::FloatRect({windowViewCenter.x - windowViewSize.x/2.0f, windowViewCenter.y - windowViewSize.y/2.0f}, windowViewSize);
			}
			return sf::FloatRect();
		}
		
		sf::FloatRect getLocalBounds() {
			if (window) {
				return sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), sf::Vector2f{static_cast<float>(resolution.x), static_cast<float>(resolution.y)});
			}
			return sf::FloatRect();
		}
		
		sf::Vector2f getScale() {
			if (window) {
				return window->getView().getSize();
			}
			return sf::Vector2f();
		}
		
		sf::Vector2u getWindowSize() {
			if (window) {
				return window->getSize();
			}
			return sf::Vector2u();
		}
		
		template <typename T>
		ExtendedWindow& refresh(const vector<T>& inputDrawables, const vector<sf::Shader*>& inputShaders = vector<sf::Shader*>(0), const bool& declareBoundsUniforms = false) {
			if (window) {
				window->clear();
				for (size_t i = 0; i < inputDrawables.size(); ++i) {
					if (inputShaders.size() >= i + 1 && inputShaders[i] != nullptr) {
						if (declareBoundsUniforms) {
							sf::FloatRect windowGlobalBounds = getGlobalBounds();
							sf::FloatRect drawableGlobalBounds = inputDrawables[i].getGlobalBounds();
							inputShaders[i]->setUniform("drawableTexture", sf::Shader::CurrentTexture);
							inputShaders[i]->setUniform("windowPosition", windowGlobalBounds.position);
							inputShaders[i]->setUniform("windowSize", windowGlobalBounds.size);
							inputShaders[i]->setUniform("drawablePosition", drawableGlobalBounds.position);
							inputShaders[i]->setUniform("drawableSize", drawableGlobalBounds.size);
						}
						window->draw(inputDrawables[i], inputShaders[i]);
					} else {
						window->draw(inputDrawables[i]);
					}
				}
				window->display();
			}
			return *this;
		}
		
		sf::Texture screenshot() {
			sf::Texture screenshotTexture;
			if (window) {
				if (screenshotTexture.resize(window->getSize())) {
					screenshotTexture.update(*window);
				}
			}
			return screenshotTexture;
		}
		
		ExtendedWindow& open(const string& inputTitle, const sf::Vector2u& inputResolution = sf::Vector2u(600, 400), const unsigned short& inputFramerate = 60, const bool& useFullscreen = false, const bool& useVsync = false, const float& initialSizeMultiplier = 0.67) {
			title = inputTitle;
			resolution = inputResolution;
			framerate = inputFramerate;
			vsync = useVsync;
			fullscreen = false;
			inputFullscreen = useFullscreen;
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(resolution), title, sf::State::Windowed);
			sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
			bool fitWidth = (resolution.x*1.0/resolution.y)/(desktop.size.x*1.0/desktop.size.y) >= 1.0;
			float resolutionMultiplier = fitWidth ? desktop.size.x*1.0/resolution.x : desktop.size.y*1.0/resolution.y;
			if (window) {
				window->setSize(sf::Vector2u({static_cast<unsigned int>(resolution.x * resolutionMultiplier * initialSizeMultiplier), static_cast<unsigned int>(resolution.y * resolutionMultiplier * initialSizeMultiplier)}));
			}
			update_framerate();
			update_vsync();
			update_mouse_lock();
			update_mouse_visibility();
			update_icon();
			if (useFullscreen) {
				toggleFullscreen();
			}
			return *this;
		}
		
		ExtendedWindow& open() {
			fullscreen = false;
			delete window;
			window = new sf::RenderWindow(sf::VideoMode(resolution), title, sf::State::Windowed);
			sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
			bool fitWidth = (resolution.x*1.0/resolution.y)/(desktop.size.x*1.0/desktop.size.y) >= 1.0;
			float resolutionMultiplier = fitWidth ? desktop.size.x*1.0/resolution.x : desktop.size.y*1.0/resolution.y;
			if (window) {
				window->setSize(sf::Vector2u({static_cast<unsigned int>(resolution.x * resolutionMultiplier * initialSizeMultiplier), static_cast<unsigned int>(resolution.y * resolutionMultiplier * initialSizeMultiplier)}));
			}
			update_framerate();
			update_vsync();
			update_mouse_lock();
			update_mouse_visibility();
			update_icon();
			if (inputFullscreen) {
				toggleFullscreen();
			}
			return *this;
		}
		
		ExtendedWindow& close() {
			update_mouse_lock(true, false);
			update_mouse_visibility(true, true);
			inputFullscreen = fullscreen;
			delete window;
			window = nullptr;
			return *this;
		}
		
		ExtendedWindow& requestFocus() {
			if (window) {
				window->requestFocus();
			}
			return *this;
		}
		
		ExtendedWindow& getFocus() {
			requestFocus();
			return *this;
		}
		
		bool getMouseLock() {
			return mouseLocked;
		}
		
		ExtendedWindow& setMouseLock(const bool& inputMouseLocked) {
			mouseLocked = inputMouseLocked;
			update_mouse_lock();
			return *this;
		}
		
		ExtendedWindow& lockMouse() {
			mouseLocked = true;
			update_mouse_lock();
			return *this;
		}
		
		ExtendedWindow& unlockMouse() {
			mouseLocked = false;
			update_mouse_lock();
			return *this;
		}
		
		bool getMouseVisibility() {
			return mouseVisible;
		}
		
		ExtendedWindow& setMouseVisibility(const bool& inputMouseVisibility) {
			mouseVisible = inputMouseVisibility;
			update_mouse_lock();
			return *this;
		}
		
		ExtendedWindow& unhideMouse() {
			mouseVisible = true;
			update_mouse_visibility();
			return *this;
		}
		
		ExtendedWindow& hideMouse() {
			mouseVisible = false;
			update_mouse_visibility();
			return *this;
		}
					
		bool isFocused() {
			if (window) {
				return window->hasFocus();
			}
			return false;
		}
		bool mouseLeftHeld(const bool& focusEnforced = true) {
			if (!focusEnforced || isFocused()) {
				return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			}
			return false;
		}
		bool mouseRightHeld(const bool& focusEnforced = true) {
			if (!focusEnforced || isFocused()) {
				return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
			}
			return false;
		}
		
		sf::Vector2f getMousePosition(const bool& useDesktopContext = false, const bool& focusRequired = true, const bool& normalize = true, const bool& setNanTo0 = true) {
			sf::Vector2i mousePosition;
			sf::Vector2u containerSize;
			float normalizeOffset = normalize ? 0.5f : 0.0f;
			if (useDesktopContext) {
				mousePosition = sf::Mouse::getPosition();
				containerSize = sf::VideoMode::getDesktopMode().size;
			} else {
				if (window && !(focusRequired && !window->hasFocus())) {
					mousePosition = sf::Mouse::getPosition(*window);
					containerSize = window->getSize();
				} else {
					if (setNanTo0) {
						return sf::Vector2f({0.0f, 0.0f});
					} else {
						return sf::Vector2f({nan(""), nan("")});
					}
				}
			}
			return sf::Vector2f({mousePosition.x*1.0f/(containerSize.x - 1) - normalizeOffset, mousePosition.y*1.0f/(containerSize.y - 1) - normalizeOffset});
		}
		
		ExtendedWindow& setMousePosition(sf::Vector2f inputPosition = sf::Vector2f(), const bool& useDesktopContext = false, const bool& focusRequired = true, const bool& normalize = true, const bool& setNanTo0 = true) {
			sf::Vector2u containerSize;
			float normalizeOffset = normalize ? 0.5f : 0.0f;
			if (useDesktopContext) {
				containerSize = sf::VideoMode::getDesktopMode().size;
			} else {
				if (window && !(focusRequired && !window->hasFocus())) {
					containerSize = window->getSize();
				} else {
					if (setNanTo0) {
						inputPosition = sf::Vector2f({0.0f, 0.0f});
					} else {
						return *this;
					}
				}
			}
			sf::Mouse::setPosition(sf::Vector2i({static_cast<int>((inputPosition.x + normalizeOffset) * (containerSize.x - 1.0f)), static_cast<int>((inputPosition.y + normalizeOffset) * (containerSize.y - 1.0f))}));
			return *this;
		}
		
		ExtendedWindow& offsetMousePosition(const sf::Vector2f& inputOffset = sf::Vector2f(), const bool& useDesktopContext = false, const bool& focusRequired = true, const bool& normalize = true, const bool& setNanTo0 = true) {
			sf::Vector2f mousePosition = getMousePosition(useDesktopContext, focusRequired, normalize, setNanTo0);
			sf::Vector2f inputPosition = sf::Vector2f({mousePosition.x + inputOffset.x, mousePosition.y + inputOffset.y});
			setMousePosition(inputPosition, useDesktopContext, focusRequired, normalize, setNanTo0);
			return *this;
		}
		
		ExtendedWindow(const string& inputTitle = "window", const sf::Vector2u& inputResolution = sf::Vector2u(600, 400), const unsigned int& inputFramerate = 60, const bool& useFullscreen = false, const bool& useVsync = true, const float& inputInitialSizeMultiplier = 0.67) : title(inputTitle), resolution(inputResolution), framerate(inputFramerate), inputFullscreen(useFullscreen), vsync(useVsync), initialSizeMultiplier(inputInitialSizeMultiplier) {
			window = nullptr;
			return;
		}
		
		~ExtendedWindow() {
			delete window;
			window = nullptr;
		}
		
		ExtendedWindow(ExtendedWindow& originalObject) {
			if (originalObject.window) {
				open(originalObject.title, originalObject.resolution, originalObject.framerate, originalObject.fullscreen, originalObject.vsync, originalObject.window->getSize().x*1.0/originalObject.resolution.x);
			} else {
				window = nullptr;
			}
			return;
		}
		ExtendedWindow& operator=(ExtendedWindow& rObject) {
			if (this != &rObject) {
				delete window;
				if (rObject.window) {
					open(rObject.title, rObject.resolution, rObject.framerate, rObject.fullscreen, rObject.vsync, rObject.window->getSize().x*1.0/rObject.resolution.x);
				} else {
					window = nullptr;
				}
			}
			return *this;
		}
		ExtendedWindow(ExtendedWindow&& originalObject) noexcept : window(originalObject.window) {
			originalObject.window = nullptr;
			return;        
		}
		ExtendedWindow& operator=(ExtendedWindow&& rObject) noexcept {
			if (this != &rObject) {
				if (rObject.window) {
					open(rObject.title, rObject.resolution, rObject.framerate, rObject.fullscreen, rObject.vsync, rObject.window->getSize().x*1.0/rObject.resolution.x);
					rObject.window = nullptr;
				}
			}
			return *this;
		}
};

class SpriteContainer;
class ExtendedSprite : public TaggableElement<ExtendedSprite> {
	public:
		SpriteContainer* parentSpriteContainer;
		sf::Shader* shader = nullptr;
		sf::Sprite sprite;
		double z;
		bool hidden = false;
		float opacity = 1.0;
		bool mouseHovering(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true);
		const sf::Sprite& drawable() const {
			return sprite;
		}
		const sf::FloatRect getGlobalBounds() const {
			return sprite.getGlobalBounds();
		}
		sf::FloatRect getLocalBounds() {
			return sprite.getLocalBounds();
		}
		sf::Vector2f getScale() {
			return sprite.getScale();
		}
		ExtendedSprite& updateOpacity() {
			opacity *= opacity >= 0.0;
			opacity = (opacity >= 1.0 ? 1.0 : opacity);
			sf::Color spriteColor = sprite.getColor();
			spriteColor.a = static_cast<uint8_t>(opacity * 255.0 * !hidden);
			sprite.setColor(spriteColor);
			return *this;
		}
		sf::Color getColor() {
			return sprite.getColor();
		}
		float getColor(const unsigned short inputColorChannel = ColorChannel::None) {
			return ExtendedFunction::getColor(sprite.getColor(), inputColorChannel);
		}
		ExtendedSprite& setColor(float inputR = 1.0f, float inputG = 1.0f, float inputB = 1.0f) {
			sprite.setColor(ExtendedFunction::setColor(sprite.getColor(), inputR, inputG, inputB));
			updateOpacity();
			return *this;
		}
		ExtendedSprite& setColor(const sf::Color& inputColor = sf::Color(255, 255, 255, 255)) {
			sprite.setColor(inputColor);
			opacity = inputColor.a;
			updateOpacity();
			return *this;
		}
		ExtendedSprite& resetColor() {
			sprite.setColor(sf::Color(255, 255, 255, 255));
			opacity = 1.0f;
			updateOpacity();
			return *this;
		}
		ExtendedSprite& setTint(float inputTint, const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::setTint(sprite.getColor(), opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedSprite& multiplyTint(float inputTint = 1.0, const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::multiplyTint(sprite.getColor(), opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedSprite& addTint(float inputTint = 0.0, const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::addTint(sprite.getColor(), opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedSprite& resetTint(const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::resetTint(sprite.getColor(), opacity, inputColorChannel));
			updateOpacity();
			return *this;
		}
		bool isHidden() {
			return hidden;
		}
		bool isVisible() {
			return !hidden;
		}
		ExtendedSprite& hide() {
			hidden = true;
			updateOpacity();
			return *this;
		}
		ExtendedSprite& unhide() {
			hidden = false;
			updateOpacity();
			return *this;
		}
		ExtendedSprite& setVisibility(const bool& inputVisibility) {
			hidden = !inputVisibility;
			updateOpacity();
			return *this;
		}
		float getOpacity() {
			return opacity;
		}
		ExtendedSprite& setOpacity(const float& inputOpacity) {
			opacity = inputOpacity;
			updateOpacity();
			return *this;
		}
		sf::Vector2f getNormalizedPosition(ExtendedWindow& windowContainer, sf::Vector2f offset = sf::Vector2f(), bool useNormalizedPosition = true) {
			if (windowContainer.window) {
				return ExtendedFunction::getNormalizedPosition(sprite.getGlobalBounds(), windowContainer.getGlobalBounds(), offset, useNormalizedPosition);
			}
			return sf::Vector2f({nan(""),nan("")});
		}
		sf::Vector2f getDimensions(ExtendedWindow& windowContainer) {
			if (windowContainer.window) {
				return ExtendedFunction::getDimensions(sprite.getLocalBounds(), sprite.getScale(), windowContainer.getGlobalBounds());
			}
			return sf::Vector2f({nan(""),nan("")});
		}
		bool shaderExists() {
			return shader != nullptr;
		}
		sf::Shader& getShader() {
			return *shader;
		}
		ExtendedSprite& setShader(sf::Shader& inputShader) {
			shader = &inputShader;
			return *this;
		}
		ExtendedSprite& resetShader() {
			shader = nullptr;
			return *this;
		}
		template <typename referenceT>
		ExtendedSprite& center(referenceT& referenceDrawable) {
			sprite.setPosition(ExtendedFunction::center(sprite.getGlobalBounds(), referenceDrawable.getGlobalBounds()));
			return *this;
		}
		template <typename referenceT>
		ExtendedSprite& offset(referenceT& referenceDrawable, const sf::Vector2f& inputOffset) {
			sprite.setPosition(ExtendedFunction::offset(sprite.getGlobalBounds(), referenceDrawable.getGlobalBounds(), inputOffset));
			return *this;
		}
		ExtendedSprite& offset(const sf::Vector2f& inputSize, const sf::Vector2f& inputOffset) {
			sprite.setPosition(ExtendedFunction::offset(sprite.getGlobalBounds(), inputSize, inputOffset));
			return *this;
		}
		ExtendedSprite& offset(const sf::Vector2f& inputOffset, const bool& useGlobalContext = true) {
			sprite.setPosition(ExtendedFunction::offset(sprite.getGlobalBounds(), inputOffset, useGlobalContext));
			return *this;
		}
		ExtendedSprite& multiply(const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
			vector<sf::Vector2f> multiplyResult = ExtendedFunction::multiply(sprite.getGlobalBounds(), sprite.getScale(), inputMultiplier, alignDirection);
			sprite.setScale(multiplyResult[0]);
			sprite.setPosition(multiplyResult[1]);						
			return *this;
		}
		ExtendedSprite& multiply(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			multiply({inputScale, inputScale}, alignDirection);
			return *this;
		}
		ExtendedSprite& setTexture(const sf::Texture& inputTexture, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldSpriteGlobalBounds = sprite.getGlobalBounds();
			sprite.setTexture(inputTexture, true);
			sf::FloatRect newSpriteGlobalBounds = sprite.getGlobalBounds();
			sprite.setPosition(ExtendedFunction::align(newSpriteGlobalBounds, oldSpriteGlobalBounds, alignDirection, !alignDirection));
			return *this;
		}
		ExtendedSprite& setScale(const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
			vector<sf::Vector2f> scaleResult = ExtendedFunction::setScale(sprite.getGlobalBounds(), sprite.getScale(), inputMultiplier, alignDirection);
			sprite.setScale(scaleResult[0]);
			sprite.setPosition(scaleResult[1]);
			return *this;
		}
		ExtendedSprite& setScale(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			setScale(sf::Vector2f({inputScale, inputScale}), alignDirection);							
			return *this;
		}
		ExtendedSprite& resetScale(const AlignDirection& alignDirection = Align::None) {
			setScale(sf::Vector2f({1.0f, 1.0f}), alignDirection);							
			return *this;
		}
		template <typename referenceT>
		ExtendedSprite& resizeToFit(referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFit(sprite.getGlobalBounds(), referenceDrawable.getGlobalBounds(), alignDirection, useGlobalContext, sprite.getLocalBounds(), sprite.getScale(), referenceUseGlobalContext, referenceDrawable.getLocalBounds(), referenceDrawable.getScale());
			sprite.setScale(resizeResult[0]);
			sprite.setPosition(resizeResult[1]);						
			return *this;
		}
		template <typename referenceT>
		ExtendedSprite& resizeToFill(referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFill(sprite.getGlobalBounds(), referenceDrawable.getGlobalBounds(), alignDirection, useGlobalContext, sprite.getLocalBounds(), sprite.getScale(), referenceUseGlobalContext, referenceDrawable.getLocalBounds(), referenceDrawable.getScale());
			sprite.setScale(resizeResult[0]);
			sprite.setPosition(resizeResult[1]);						
			return *this;
		}
		ExtendedSprite& resizeToFit(sf::Vector2f referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFit(sprite.getGlobalBounds(), sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), referenceBox), alignDirection, useGlobalContext, sprite.getLocalBounds(), sprite.getScale());
			sprite.setScale(resizeResult[0]);
			sprite.setPosition(resizeResult[1]);						
			return *this;
		}
		ExtendedSprite& resizeToFill(sf::Vector2f referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFill(sprite.getGlobalBounds(), sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), referenceBox), alignDirection, useGlobalContext, sprite.getLocalBounds(), sprite.getScale());
			sprite.setScale(resizeResult[0]);
			sprite.setPosition(resizeResult[1]);						
			return *this;
		}
		ExtendedSprite& align(const AlignDirection& alignDirection = Align::None) {
			sprite.setPosition(ExtendedFunction::align(sprite.getGlobalBounds(), alignDirection));
			return *this;
		}
		template <typename referenceT>
		ExtendedSprite& align(referenceT& referenceDrawable, const AlignDirection& anchorSide = Align::None, const AlignDirection& alignDirection = Align::None) {
			sprite.setPosition(ExtendedFunction::align(sprite.getGlobalBounds(), referenceDrawable.getGlobalBounds(), anchorSide, alignDirection));
			return *this;
		}
		bool mouseLeftHeld(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true) {
			if (windowContainer.window && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return mouseHovering(windowContainer, focusEnforced, obstructionEnforced, visibilityEnforced);
			}
			return false;
		}
		bool mouseRightHeld(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true) {
			if (windowContainer.window && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				return mouseHovering(windowContainer, focusEnforced, obstructionEnforced, visibilityEnforced);
			}
			return false;
		}
		sf::IntRect getTextureRect() {
			return sprite.getTextureRect();
		}
		sf::FloatRect getNormalTextureRect() {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			sf::IntRect textureRect = sprite.getTextureRect();
			return sf::FloatRect(sf::Vector2f({textureRect.position.x*1.0f/textureSize.x, textureRect.position.y*1.0f/textureSize.y}), sf::Vector2f({textureRect.size.x*1.0f/textureSize.x, textureRect.size.y*1.0f/textureSize.y}));
		}
		sf::Vector2f getNormalTexturePixelSize() {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			return sf::Vector2f({1.0f/textureSize.x, 1.0f/textureSize.y});
		}
		sf::Vector2u getTextureSize() {
			return sprite.getTexture().getSize();
		}
		ExtendedSprite setTextureRect(const sf::IntRect& inputRect, const AlignDirection& alignDirection = Align::None, const sf::Vector2i& offset = sf::Vector2i(), const bool& offsetWithRotation = true) {
			sf::FloatRect oldSpriteGlobalBounds = sprite.getGlobalBounds();
			sprite.setTextureRect(inputRect);
			sf::FloatRect newSpriteGlobalBounds = sprite.getGlobalBounds();
			sprite.setPosition(ExtendedFunction::align(newSpriteGlobalBounds, oldSpriteGlobalBounds, alignDirection, !alignDirection));
			if (offset == sf::Vector2i()) {
				newSpriteGlobalBounds = sprite.getGlobalBounds();
				sf::Vector2f newSpriteScale = sprite.getScale();
				sf::Vector2f offsetMultiplier = sprite.getLocalBounds().size;
				offsetMultiplier = sf::Vector2f({offsetMultiplier.x * newSpriteScale.x / inputRect.size.x, offsetMultiplier.y * newSpriteScale.y / inputRect.size.y});
				if (offsetWithRotation) {
					sf::Angle newSpriteRotation = sprite.getRotation();
					offsetMultiplier = sf::Vector2f({offsetMultiplier.x * cos(newSpriteRotation.asRadians()), offsetMultiplier.y * sin(newSpriteRotation.asRadians())});
				}
				sprite.setPosition(sf::Vector2f({newSpriteGlobalBounds.position.x + offsetMultiplier.x * offset.x, newSpriteGlobalBounds.position.y + offsetMultiplier.y * offset.y}));
			}
			return *this;
		}
		ExtendedSprite setTextureRect(const sf::FloatRect& inputRect, const AlignDirection& alignDirection = Align::None, const sf::Vector2f& offset = sf::Vector2f()) {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			setTextureRect(sf::IntRect(sf::Vector2i({static_cast<int>(inputRect.position.x*textureSize.x), static_cast<int>(inputRect.position.y*textureSize.y)}), sf::Vector2i({static_cast<int>(inputRect.size.x*textureSize.x), static_cast<int>(inputRect.size.y*textureSize.y)})), alignDirection, sf::Vector2i({static_cast<int>(offset.x*textureSize.x), static_cast<int>(offset.y*textureSize.y)}));
			return *this;
		}
		ExtendedSprite resetTextureRect(const AlignDirection& alignDirection = Align::None) {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			setTextureRect(sf::IntRect(sf::Vector2i({0, 0}), sf::Vector2i({static_cast<int>(textureSize.x), static_cast<int>(textureSize.y)})), alignDirection);
			return *this;
		}
		ExtendedSprite(SpriteContainer* inputParentSpriteContainer, sf::Texture& inputTexture, double inputZ = 0) : parentSpriteContainer(inputParentSpriteContainer), sprite(inputTexture), z(inputZ) {}
		ExtendedSprite(SpriteContainer* inputParentSpriteContainer, sf::Sprite inputSprite, double inputZ = 0) : parentSpriteContainer(inputParentSpriteContainer), sprite(inputSprite), z(inputZ) {}
};
class SpriteContainer : public TaggableContainer<ExtendedSprite> {
	friend ExtendedSprite;
	
	public:
		float initialSizeMultiplier;
		unordered_map<string, ExtendedSprite> extended_sprite;
		const unordered_map<string, ExtendedSprite>& extended_drawable() const {
			return extended_sprite;
		}
		SpriteContainer& setMultiplier(float inputInitialSizeMultiplier) {
			initialSizeMultiplier = inputInitialSizeMultiplier;
			return *this;
		}
		float getMultiplier() {
			return initialSizeMultiplier;
		}
		ExtendedSprite& add(const string& inputID, sf::Texture& inputTexture, const double&  inputZ = 0) {
			extended_sprite.insert_or_assign(inputID, ExtendedSprite(this, inputTexture, inputZ));
			extended_sprite.at(inputID).multiply(initialSizeMultiplier, Align::TopLeft);
			return extended_sprite.at(inputID);
		}
		ExtendedSprite& add(const string& inputID, const sf::Sprite& inputSprite, const double& inputZ = 0) {
			extended_sprite.insert_or_assign(inputID, ExtendedSprite(this, inputSprite, inputZ));
			extended_sprite.at(inputID).multiply(initialSizeMultiplier, Align::TopLeft);
			return extended_sprite.at(inputID);
		}
		SpriteContainer& remove(const string& inputID) {
			extended_sprite.erase(inputID);
			return *this;
		}
		bool exists(const string& inputID) {
			return extended_sprite.count(inputID) != 0;
		}
		SpriteContainer& clear() {
			extended_sprite = unordered_map<string, ExtendedSprite>();
			return *this;
		}
		double highest() {
			double currentValue = nan("");
			for (pair<string, ExtendedSprite> currentExtendedSprite : extended_sprite) {
				if (isnan(currentValue)) {
					currentValue = currentExtendedSprite.second.z;
				} else if (currentExtendedSprite.second.z > currentValue) {
					currentValue = currentExtendedSprite.second.z;
				}
			}
			return currentValue;
		}
		double lowest() {
			double currentValue = nan("");
			for (pair<string, ExtendedSprite> currentExtendedSprite : extended_sprite) {
				if (isnan(currentValue)) {
					currentValue = currentExtendedSprite.second.z;
				} else if (currentExtendedSprite.second.z < currentValue) {
					currentValue = currentExtendedSprite.second.z;
				}
			}
			return currentValue;
		}
		vector<double> all() {
			vector<double> outputZ;
			for (pair<string, ExtendedSprite> currentExtendedSprite : extended_sprite) {
				outputZ.push_back(currentExtendedSprite.second.z);
			}
			return outputZ;
		}
		double next_above(const double& inputZ, const double& visibilityEnforced = true) {
			double highestZ = highest();
			bool aboveFound = false;
			for (pair<string, ExtendedSprite> currentExtendedSprite : extended_sprite) {
				if (currentExtendedSprite.second.z > inputZ && currentExtendedSprite.second.z < highestZ && (!visibilityEnforced || !currentExtendedSprite.second.hidden)) {
					highestZ = currentExtendedSprite.second.z;
					aboveFound = true;
				}
			}
			if (aboveFound) {
				return highestZ;
			} else {
				return nan("");
			}
		}
		double next_below(const double& inputZ, const double& visibilityEnforced = true) {
			double lowestZ = lowest();
			bool belowFound = false;
			for (pair<string, ExtendedSprite> currentExtendedSprite : extended_sprite) {
				if (currentExtendedSprite.second.z < inputZ && currentExtendedSprite.second.z > lowestZ && (!visibilityEnforced || !currentExtendedSprite.second.hidden)) {
					lowestZ = currentExtendedSprite.second.z;
					belowFound = true;
				}
			}
			if (belowFound) {
				return lowestZ;
			} else {
				return nan("");
			}
		}
		double next_closest(const double& inputZ, const bool& round_down = false, const double& visibilityEnforced = true) {
			double next_lower = next_below(inputZ);
			double next_upper = next_above(inputZ);
			if (isnan(next_lower)) {
				if (isnan(next_upper)) {
					return nan("");
				} else {
					return next_upper;
				}
			} else if (isnan(next_upper)) {
				return next_lower;
			} else {
				return (round_down ? (next_upper - inputZ >= inputZ - next_lower ? next_lower : next_upper) : (next_upper - inputZ > inputZ - next_lower ? next_lower : next_upper));
			}
		}
		vector<string> at(const double& inputZ) {
			vector<string> outputIDs;
			for (pair<string, ExtendedSprite> currentExtendedSprite : extended_sprite) {
				if (currentExtendedSprite.second.z == inputZ) {
					outputIDs.push_back(currentExtendedSprite.first);
				}
			}
			return outputIDs;
		}
		static bool sortCondition(const ExtendedSprite* inputExtendedSpriteA, const ExtendedSprite* inputExtendedSpriteB) {
			return inputExtendedSpriteA->z < inputExtendedSpriteB->z;
		}
		vector<sf::Sprite> toVector() {
			vector<const ExtendedSprite*> extendedSprites;
			extendedSprites.reserve(extended_sprite.size());
			for (const pair<const string&, const ExtendedSprite&> currentExtendedSprite : extended_sprite) {
				extendedSprites.push_back(&extended_sprite.at(currentExtendedSprite.first));
			}
			sort(extendedSprites.begin(), extendedSprites.end(), sortCondition);
			vector<sf::Sprite> outputSprites;
			outputSprites.reserve(extendedSprites.size());
			for (const ExtendedSprite* currentExtendedSprite : extendedSprites) {
				outputSprites.push_back(currentExtendedSprite->sprite);
			}
			return outputSprites;
		}
		vector<sf::Shader*> getShaderVector() {
			vector<const ExtendedSprite*> extendedSprites;
			extendedSprites.reserve(extended_sprite.size());
			for (const pair<const string&, const ExtendedSprite&> currentExtendedSprite : extended_sprite) {
				extendedSprites.push_back(&extended_sprite.at(currentExtendedSprite.first));
			}
			sort(extendedSprites.begin(), extendedSprites.end(), sortCondition);
			vector<sf::Shader*> outputShaders;
			outputShaders.reserve(extendedSprites.size());
			for (const ExtendedSprite* currentExtendedSprite : extendedSprites) {
				outputShaders.push_back(currentExtendedSprite->shader);
			}
			return outputShaders;
		}
		ExtendedSprite& operator[](const string& inputID) {
			return extended_sprite.at(inputID);
		}
		const ExtendedSprite& operator[](const string& inputID) const {
			return extended_sprite.at(inputID);
		}
		SpriteContainer(float inputInitialSizeMultiplier = 1.0) : initialSizeMultiplier(inputInitialSizeMultiplier) {
			taggables = &extended_sprite;
		}
};
bool ExtendedSprite::mouseHovering(const ExtendedWindow& windowContainer, const bool& focusEnforced, const bool& obstructionEnforced, const bool& visibilityEnforced) {
	if (windowContainer.window && (!obstructionEnforced || isnan(parentSpriteContainer->next_above(z))) && (!visibilityEnforced || !hidden)) {
		return ExtendedFunction::mouseContained(sprite.getGlobalBounds(), windowContainer.window, focusEnforced);
	}
	return false;
}

class TextContainer;
class ExtendedText : public TaggableElement<ExtendedText> {
	public:
		TextContainer* parentTextContainer;
		sf::Shader* shader = nullptr;
		sf::Text text;
		double z;
		bool hidden = false;
		float opacity = 1.0;
		float fill_opacity = 1.0;
		float outline_opacity = 1.0;
		bool styleBold = false;
		bool styleItalic = false;
		bool styleUnderlined = false;
		bool mouseHovering(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true);
		const sf::Text& drawable() const {
			return text;
		}
		ExtendedText& update_style() {
			uint32_t outputStyle = sf::Text::Style::Regular;
			if (styleBold) {
				outputStyle |= sf::Text::Bold;
			}
			if (styleItalic) {
				outputStyle |= sf::Text::Italic;
			}
			if (styleUnderlined) {
				outputStyle |= sf::Text::Underlined;
			}
			text.setStyle(outputStyle);
			return *this;
		}
		bool getBold() {
			return styleBold;
		}
		ExtendedText& setBold(const bool& inputBoolean) {
			styleBold = inputBoolean;
			update_style();
			return *this;
		}
		bool getItalic() {
			return styleBold;
		}
		ExtendedText& setItalic(const bool& inputBoolean) {
			styleItalic = inputBoolean;
			update_style();
			return *this;
		}
		bool getUnderlined() {
			return styleUnderlined;
		}
		ExtendedText& setUnderlined(const bool& inputBoolean) {
			styleUnderlined = inputBoolean;
			update_style();
			return *this;
		}
		uint32_t getStyle() {
			return text.getStyle();
		}
		ExtendedText& setStyle(const uint32_t& inputStyle) {
			styleBold = inputStyle & sf::Text::Bold;
			styleItalic = inputStyle & sf::Text::Italic;
			styleUnderlined = inputStyle & sf::Text::Underlined;
			update_style();
			return *this;
		}
		ExtendedText& resetStyle(const bool& inputBoolean) {
			styleBold = false;
			styleItalic = false;
			styleUnderlined = false;
			update_style();
			return *this;
		}
		const sf::FloatRect getGlobalBounds() const {
			return text.getGlobalBounds();
		}
		sf::Vector2f getScale() {
			return text.getScale();
		}
		string getString() {
			return text.getString();
		}
		string getText() {
			return getString();
		}
		ExtendedText& setString(const string& inputString = "") {
			text.setString(inputString);
			return *this;
		}
		ExtendedText& setText(const string& inputString = "") {
			setString(inputString);
			return *this;
		}
		float getLocalLineLength() {
			return text.getLineSpacing() * text.getFont().getLineSpacing(text.getCharacterSize());
		}
		float getGlobalLineLength() {
			return getLocalLineLength() * text.getScale().y;
		}
		sf::Vector2f getTextBoxGlobalPosition() {
			sf::FloatRect textLocalBounds = text.getLocalBounds();
			sf::FloatRect textGlobalBounds = text.getGlobalBounds();
			return {textGlobalBounds.position.x - textLocalBounds.position.x*textGlobalBounds.size.x/(textLocalBounds.size.x), textGlobalBounds.position.y - textLocalBounds.position.y*textGlobalBounds.size.y/(textLocalBounds.size.y)};
		}
		sf::Vector2f getTextBoxGlobalPositionOffset() {
			sf::FloatRect textLocalBounds = text.getLocalBounds();
			sf::FloatRect textGlobalBounds = text.getGlobalBounds();
			return {-textLocalBounds.position.x*textGlobalBounds.size.x/(textLocalBounds.size.x), -textLocalBounds.position.y*textGlobalBounds.size.y/(textLocalBounds.size.y)};
		}
		sf::FloatRect getTextBoxGlobalBounds() {
			sf::FloatRect textGlobalBounds = text.getGlobalBounds();
			sf::Vector2f textBoxPosition = getTextBoxGlobalPosition();
			textGlobalBounds.position = sf::Vector2f({textGlobalBounds.position.x + textBoxPosition.x, textGlobalBounds.position.y + textBoxPosition.y - getGlobalLineLength()});
			textGlobalBounds.size = sf::Vector2f({textGlobalBounds.size.x, getGlobalLineLength()});
			return textGlobalBounds;
		}
		sf::FloatRect getTextLocalBounds() {
			sf::FloatRect textLocalBounds = text.getLocalBounds();
			textLocalBounds.position = sf::Vector2f({0.0f, 0.0f});
			textLocalBounds.size = sf::Vector2f({textLocalBounds.size.x, getLocalLineLength()});
			return textLocalBounds;
		}
		sf::FloatRect getLocalBounds(const bool& getTrueLocalBounds = false) {
			if (getTrueLocalBounds) {
				return text.getLocalBounds();
			} else {
				return getTextLocalBounds();
			}
		}
		ExtendedText& setPosition(sf::Vector2f inputPosition, const bool& useGlobalContext = true) {
			if (useGlobalContext) {
				sf::Vector2f currentPosition = text.getGlobalBounds().position;
				text.move(inputPosition - currentPosition);
			} else {
				text.setPosition(inputPosition);
			}
			return *this;
		}
		ExtendedText& setFont(const sf::Font& inputFont, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldTextGlobalBounds = text.getGlobalBounds();
			text.setFont(inputFont);
			sf::FloatRect newTextGlobalBounds = text.getGlobalBounds();
			setPosition(ExtendedFunction::align(newTextGlobalBounds, oldTextGlobalBounds, alignDirection, !alignDirection));
			return *this;
		}
		ExtendedText& setCharacterSize(const unsigned int& inputCharacterSize, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldTextGlobalBounds = text.getGlobalBounds();
			text.setCharacterSize(inputCharacterSize);
			sf::FloatRect newTextGlobalBounds = text.getGlobalBounds();
			setPosition(ExtendedFunction::align(newTextGlobalBounds, oldTextGlobalBounds, alignDirection, !alignDirection));
			return *this;
		}
		ExtendedText& setLetterSpacing(const float& inputLetterSpacing, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldTextGlobalBounds = text.getGlobalBounds();
			text.setLetterSpacing(inputLetterSpacing);
			sf::FloatRect newTextGlobalBounds = text.getGlobalBounds();
			setPosition(ExtendedFunction::align(newTextGlobalBounds, oldTextGlobalBounds, alignDirection, !alignDirection));
			return *this;
		}
		unsigned int getCharacterSize() {
			return text.getCharacterSize();
		}
		float getLetterSpacing() {
			return text.getLetterSpacing();
		}
		ExtendedText& resetCharacterSize(const AlignDirection& alignDirection = Align::Center) {
			setCharacterSize(30, alignDirection);
			return *this;
		}
		ExtendedText& resetLetterSpacing(const AlignDirection& alignDirection = Align::Center) {
			setLetterSpacing(1.0f, alignDirection);
			return *this;
		}
		ExtendedText& updateOpacity() {
			opacity *= opacity > 0.0;
			opacity = opacity > 1.0 ? 1.0 : opacity;
			fill_opacity *= fill_opacity > 0.0;
			fill_opacity = fill_opacity > 1.0 ? 1.0 : fill_opacity;
			outline_opacity *= outline_opacity > 0.0;
			outline_opacity = outline_opacity > 1.0 ? 1.0 : outline_opacity;
			sf::Color textFillColor = text.getFillColor();
			sf::Color textOutlineColor = text.getOutlineColor();
			textFillColor.a = static_cast<uint8_t>(opacity * fill_opacity * 255.0 * !hidden);
			textOutlineColor.a = static_cast<uint8_t>(opacity * outline_opacity * 255.0 * !hidden);
			text.setFillColor(textFillColor);
			text.setOutlineColor(textOutlineColor);
			return *this;
		}
		sf::Color getFillColor() {
			return text.getFillColor();
		}
		sf::Color getOutlineColor() {
			return text.getOutlineColor();
		}
		float getFillColor(const unsigned short& inputColorChannel = ColorChannel::None) {
			return ExtendedFunction::getColor(text.getFillColor(), inputColorChannel);
		}
		float getOutlineColor(const unsigned short& inputColorChannel = ColorChannel::None) {
			return ExtendedFunction::getColor(text.getOutlineColor(), inputColorChannel);
		}
		ExtendedText& setFillColor(const float& inputR = 1.0f, const float& inputG = 1.0f, const float& inputB = 1.0f) {
			text.setFillColor(ExtendedFunction::setColor(text.getFillColor(), inputR, inputG, inputB));
			updateOpacity();
			return *this;
		}
		ExtendedText& setFillColor(const sf::Color& inputColor) {
			text.setFillColor(inputColor);
			updateOpacity();
			return *this;
		}
		ExtendedText& setOutlineColor(const float& inputR = 1.0f, const float& inputG = 1.0f, const float& inputB = 1.0f) {
			text.setOutlineColor(ExtendedFunction::setColor(text.getOutlineColor(), inputR, inputG, inputB));
			updateOpacity();
			return *this;
		}
		ExtendedText& setOutlineColor(const sf::Color& inputColor) {
			text.setOutlineColor(inputColor);
			updateOpacity();
			return *this;
		}
		ExtendedText& setColor(const float& inputR = 1.0f, const float& inputG = 1.0f, const float& inputB = 1.0f) {
			setFillColor(inputR, inputG, inputB);
			setOutlineColor(inputR, inputG, inputB);
			return *this;
		}
		ExtendedText& setColor(const sf::Color& inputColor) {
			setFillColor(inputColor);
			setOutlineColor(inputColor);
			updateOpacity();
			return *this;
		}
		ExtendedText& setFillTint(const float& inputTint, const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setFillColor(ExtendedFunction::setTint(text.getFillColor(), fill_opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedText& setOutlineTint(const float& inputTint, const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setOutlineColor(ExtendedFunction::setTint(text.getOutlineColor(), outline_opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedText& setTint(const float& inputTint, const unsigned short& inputColorChannel = ColorChannel::All) {
			setFillTint(inputTint, inputColorChannel);
			setOutlineTint(inputTint, inputColorChannel);
			return *this;
		}
		ExtendedText& multiplyFillTint(const float& inputTint = 1.0, const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setFillColor(ExtendedFunction::multiplyTint(text.getFillColor(), fill_opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedText& multiplyOutlineTint(const float& inputTint = 1.0, const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setOutlineColor(ExtendedFunction::multiplyTint(text.getOutlineColor(), outline_opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedText& multiplyTint(const float& inputTint = 1.0, const unsigned short& inputColorChannel = ColorChannel::All) {
			multiplyFillTint(inputTint, inputColorChannel);
			multiplyOutlineTint(inputTint, inputColorChannel);
			return *this;
		}
		ExtendedText& addFillTint(const float& inputTint = 0.0, const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setFillColor(ExtendedFunction::addTint(text.getFillColor(), fill_opacity, inputTint, inputColorChannel));
			updateOpacity();
			return *this;
		}
		ExtendedText& addOutlineTint(const float& inputTint = 0.0, const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setOutlineColor(ExtendedFunction::addTint(text.getOutlineColor(), outline_opacity, inputTint, inputColorChannel));
			return *this;
		}
		ExtendedText& addTint(const float& inputTint = 0.0, const unsigned short& inputColorChannel = ColorChannel::All) {
			addFillTint(inputTint, inputColorChannel);
			addOutlineTint(inputTint, inputColorChannel);
			return *this;
		}
		ExtendedText& resetFillTint(const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setFillColor(ExtendedFunction::resetTint(text.getFillColor(), fill_opacity, inputColorChannel));
			return *this;
		}
		ExtendedText& resetOutlineTint(const unsigned short& inputColorChannel = ColorChannel::All) {
			text.setOutlineColor(ExtendedFunction::resetTint(text.getOutlineColor(), outline_opacity, inputColorChannel));
			return *this;
		}
		ExtendedText& resetTint(const unsigned short& inputColorChannel = ColorChannel::All) {
			resetFillTint(inputColorChannel);
			resetOutlineTint(inputColorChannel);
			return *this;
		}
		float getOutlineThickness() {
			return text.getOutlineThickness();
		}
		ExtendedText& setOutlineThickness(float inputThickness = 0.0f) {
			inputThickness *= inputThickness > 0.0f;
			text.setOutlineThickness(inputThickness);
			return *this;
		}
		ExtendedText& resetOutlineThickness() {
			text.setOutlineThickness(0.0f);
			return *this;
		}
		bool isHidden() {
			return hidden;
		}
		bool isVisible() {
			return !hidden;
		}
		ExtendedText& hide() {
			hidden = true;
			updateOpacity();
			return *this;
		}
		ExtendedText& unhide() {
			hidden = false;
			updateOpacity();
			return *this;
		}
		ExtendedText& setVisibility(const bool& inputVisibility) {
			hidden = !inputVisibility;
			updateOpacity();
			return *this;
		}
		float getFillOpacity() {
			return fill_opacity;
		}
		float getOutlineOpacity() {
			return outline_opacity;
		}
		float getOpacity() {
			return opacity;
		}
		ExtendedText& setFillOpacity(const float& inputOpacity = 1.0f) {
			fill_opacity = inputOpacity;
			updateOpacity();
			return *this;
		}
		ExtendedText& setOutlineOpacity(const float& inputOpacity = 1.0f) {
			outline_opacity = inputOpacity;
			updateOpacity();
			return *this;
		}
		ExtendedText& setOpacity(const float& inputOpacity = 1.0f) {
			opacity = inputOpacity;
			updateOpacity();
			return *this;
		}
		ExtendedText& resetOpacity(const float& inputOpacity = 1.0f) {
			fill_opacity = 1.0f;
			outline_opacity = 1.0f;
			opacity = inputOpacity;
			updateOpacity();
			return *this;
		}
		sf::Vector2f getNormalizedPosition(ExtendedWindow& windowContainer, sf::Vector2f offset = sf::Vector2f(), bool useNormalizedPosition = true) {
			if (windowContainer.window) {
				return ExtendedFunction::getNormalizedPosition(text.getGlobalBounds(), windowContainer.getGlobalBounds(), offset, useNormalizedPosition);
			}
			return sf::Vector2f({nan(""),nan("")});
		}
		sf::Vector2f getDimensions(ExtendedWindow& windowContainer) {
			if (windowContainer.window) {
				return ExtendedFunction::getDimensions(text.getLocalBounds(), text.getScale(), windowContainer.getGlobalBounds());
			}
			return sf::Vector2f({nan(""),nan("")});
		}
		bool shaderExists() {
			return shader != nullptr;
		}
		sf::Shader& getShader() {
			return *shader;
		}
		ExtendedText& setShader(sf::Shader& inputShader) {
			shader = &inputShader;
			return *this;
		}
		ExtendedText& resetShader() {
			shader = nullptr;
			return *this;
		}
		template <typename referenceT>
		ExtendedText& center(referenceT& referenceDrawable) {
			setPosition(ExtendedFunction::center(text.getGlobalBounds(), referenceDrawable.getGlobalBounds()));
			return *this;
		}
		template <typename referenceT>
		ExtendedText& offset(referenceT& referenceDrawable, const sf::Vector2f& inputOffset) {
			setPosition(ExtendedFunction::offset(text.getGlobalBounds(), referenceDrawable.getGlobalBounds(), inputOffset));
			return *this;
		}
		ExtendedText& offset(const sf::Vector2f& inputSize, const sf::Vector2f& inputOffset) {
			setPosition(ExtendedFunction::offset(text.getGlobalBounds(), inputSize, inputOffset));
			return *this;
		}
		ExtendedText& offset(const sf::Vector2f& inputOffset, const bool& useGlobalContext = true) {
			setPosition(ExtendedFunction::offset(text.getGlobalBounds(), inputOffset, useGlobalContext));
			return *this;
		}
		ExtendedText& multiply(const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
			vector<sf::Vector2f> multiplyResult = ExtendedFunction::multiply(text.getGlobalBounds(), text.getScale(), inputMultiplier, alignDirection);
			text.setScale(multiplyResult[0]);
			setPosition(multiplyResult[1]);	
			return *this;
		}
		ExtendedText& multiply(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			multiply({inputScale, inputScale}, alignDirection);
			return *this;
		}
		ExtendedText& setScale(const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
			vector<sf::Vector2f> scaleResult = ExtendedFunction::setScale(text.getGlobalBounds(), text.getScale(), inputMultiplier, alignDirection);
			text.setScale(scaleResult[0]);
			setPosition(scaleResult[1]);
			return *this;
		}
		ExtendedText& setScale(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			setScale({inputScale, inputScale}, alignDirection);							
			return *this;
		}
		ExtendedText& resetScale(const AlignDirection& alignDirection = Align::None) {
			setScale({1.0, 1.0}, alignDirection);							
			return *this;
		}
		template <typename referenceT>
		ExtendedText& resizeToFit(referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseReferenceGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFit(text.getGlobalBounds(), referenceDrawable.getGlobalBounds(), alignDirection, useGlobalContext, getLocalBounds(), text.getScale(), referenceUseReferenceGlobalContext, referenceDrawable.getLocalBounds(), referenceDrawable.getScale());
			text.setScale(resizeResult[0]);
			setPosition(resizeResult[1]);
			return *this;
		}
		template <typename referenceT>
		ExtendedText& resizeToFill(referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseReferenceGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFill(text.getGlobalBounds(), referenceDrawable.getGlobalBounds(), alignDirection, useGlobalContext, getLocalBounds(), text.getScale(), referenceUseReferenceGlobalContext, referenceDrawable.getLocalBounds(), referenceDrawable.getScale());
			text.setScale(resizeResult[0]);
			setPosition(resizeResult[1]);
			return *this;
		}
		ExtendedText& resizeToFit(sf::Vector2f referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFit(text.getGlobalBounds(), sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), referenceBox), alignDirection, useGlobalContext, getLocalBounds(), text.getScale());
			text.setScale(resizeResult[0]);
			setPosition(resizeResult[1]);						
			return *this;
		}
		ExtendedText& resizeToFill(sf::Vector2f referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			vector<sf::Vector2f> resizeResult = ExtendedFunction::resizeToFill(text.getGlobalBounds(), sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), referenceBox), alignDirection, useGlobalContext, getLocalBounds(), text.getScale());
			text.setScale(resizeResult[0]);
			setPosition(resizeResult[1]);						
			return *this;
		}
		float getCharacterSizeMultiplierForWidthFit(const float& inputLength) {
			return 1.0f*inputLength/getGlobalBounds().size.x;
		}
		float getCharacterSizeMultiplierForHeightFit(const float& inputLength) {
			return 1.0f*inputLength/getGlobalBounds().size.y;
		}
		float getCharacterSizeMultiplierToFit(const sf::Vector2f& inputSize) {
			sf::FloatRect textBounds = getGlobalBounds();
			float widthMultiplier = 1.0f*inputSize.x/textBounds.size.x;
			float heightMultiplier = 1.0f*inputSize.y/textBounds.size.y;
			return widthMultiplier < heightMultiplier ? widthMultiplier : heightMultiplier;
		}
		float getCharacterSizeMultiplierToFill(const sf::Vector2f& inputSize, const float& inputLength) {
			sf::FloatRect textBounds = getGlobalBounds();
			float widthMultiplier = 1.0f*inputSize.x/textBounds.size.x;
			float heightMultiplier = 1.0f*inputSize.y/textBounds.size.y;
			return widthMultiplier > heightMultiplier ? widthMultiplier : heightMultiplier;
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierForWidthFit(referenceT& referenceDrawable) {
			return getCharacterSizeMultiplierForWidthFit(referenceDrawable.getGlobalBounds().size.x);
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierForHeightFit(referenceT& referenceDrawable) {
			return getCharacterSizeMultiplierForHeightFit(referenceDrawable.getGlobalBounds().size.y);
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierToFit(referenceT& referenceDrawable) {
			return getCharacterSizeMultiplierToFit(referenceDrawable.getGlobalBounds().size);
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierToFill(referenceT& referenceDrawable) {
			return getCharacterSizeMultiplierToFill(referenceDrawable.getGlobalBounds().size);
		}
		ExtendedText& align(const AlignDirection& alignDirection = Align::None) {
			setPosition(ExtendedFunction::align(text.getGlobalBounds(), alignDirection));
			return *this;
		}
		template <typename referenceT>
		ExtendedText& align(referenceT& referenceDrawable, const AlignDirection& anchorSide = Align::None, const AlignDirection& alignDirection = Align::None) {
			setPosition(ExtendedFunction::align(text.getGlobalBounds(), referenceDrawable.getGlobalBounds(), anchorSide, alignDirection));
			return *this;
		}
		bool mouseLeftHeld(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true) {
			if (windowContainer.window && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
				return mouseHovering(windowContainer, focusEnforced, obstructionEnforced, visibilityEnforced);
			}
			return false;
		}
		bool mouseRightHeld(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true) {
			if (windowContainer.window && sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
				return mouseHovering(windowContainer, focusEnforced, obstructionEnforced, visibilityEnforced);
			}
			return false;
		}
		ExtendedText(TextContainer* inputParentTextContainer, sf::Font& inputFont, double inputZ = 0) : parentTextContainer(inputParentTextContainer), text(inputFont), z(inputZ) {}
		ExtendedText(TextContainer* inputParentTextContainer, sf::Text inputText, double inputZ = 0) : parentTextContainer(inputParentTextContainer), text(inputText), z(inputZ) {}
};
class TextContainer : public TaggableContainer<ExtendedText> {
	public:
		float initialSizeMultiplier;
		unordered_map<string, ExtendedText> extended_text;
		const unordered_map<string, ExtendedText>& extended_drawable() const {
			return extended_text;
		}
		TextContainer& setMultiplier(float inputInitialSizeMultiplier) {
			initialSizeMultiplier = inputInitialSizeMultiplier;
			return *this;
		}
		float getMultiplier() {
			return initialSizeMultiplier;
		}
		ExtendedText& add(const string& inputID, sf::Font& inputFont, const double&  inputZ = 0) {
			extended_text.insert_or_assign(inputID, ExtendedText(this, inputFont, inputZ));
			extended_text.at(inputID).multiply(initialSizeMultiplier, Align::TopLeft);
			return extended_text.at(inputID);
		}
		ExtendedText& add(const string& inputID, const sf::Text& inputText, const double& inputZ = 0) {
			extended_text.insert_or_assign(inputID, ExtendedText(this, inputText, inputZ));
			extended_text.at(inputID).multiply(initialSizeMultiplier, Align::TopLeft);
			return extended_text.at(inputID);
		}
		TextContainer& remove(const string& inputID) {
			extended_text.erase(inputID);
			return *this;
		}
		bool exists(const string& inputID) {
			return extended_text.count(inputID) != 0;
		}
		TextContainer& clear() {
			extended_text = unordered_map<string, ExtendedText>();
			return *this;
		}
		double highest() {
			double currentValue = nan("");
			for (pair<string, ExtendedText> currentExtendedText : extended_text) {
				if (isnan(currentValue)) {
					currentValue = currentExtendedText.second.z;
				} else if (currentExtendedText.second.z > currentValue) {
					currentValue = currentExtendedText.second.z;
				}
			}
			return currentValue;
		}
		double lowest() {
			double currentValue = nan("");
			for (std::pair<string, ExtendedText> currentExtendedText : extended_text) {
				if (isnan(currentValue)) {
					currentValue = currentExtendedText.second.z;
				} else if (currentExtendedText.second.z < currentValue) {
					currentValue = currentExtendedText.second.z;
				}
			}
			return currentValue;
		}
		vector<double> all() {
			vector<double> outputZ;
			for (pair<string, ExtendedText> currentExtendedSprite : extended_text) {
				outputZ.push_back(currentExtendedSprite.second.z);
			}
			return outputZ;
		}
		double next_above(const double& inputZ, const double& visibilityEnforced = true) {
			double highestZ = highest();
			bool aboveFound = false;
			for (pair<string, ExtendedText> currentExtendedText : extended_text) {
				if (currentExtendedText.second.z > inputZ && currentExtendedText.second.z < highestZ && (!visibilityEnforced || !currentExtendedText.second.hidden)) {
					highestZ = currentExtendedText.second.z;
					aboveFound = true;
				}
			}
			if (aboveFound) {
				return highestZ;
			} else {
				return nan("");
			}
		}
		double next_below(const double& inputZ, const double& visibilityEnforced = true) {
			double lowestZ = lowest();
			bool belowFound = false;
			for (pair<string, ExtendedText> currentExtendedText : extended_text) {
				if (currentExtendedText.second.z < inputZ && currentExtendedText.second.z > lowestZ && (!visibilityEnforced || !currentExtendedText.second.hidden)) {
					lowestZ = currentExtendedText.second.z;
					belowFound = true;
				}
			}
			if (belowFound) {
				return lowestZ;
			} else {
				return nan("");
			}
		}
		double next_closest(const double& inputZ, const bool& round_down = false, const double& visibilityEnforced = true) {
			double next_lower = next_below(inputZ);
			double next_upper = next_above(inputZ);
			if (isnan(next_lower)) {
				if (isnan(next_upper)) {
					return nan("");
				} else {
					return next_upper;
				}
			} else if (isnan(next_upper)) {
				return next_lower;
			} else {
				return (round_down ? (next_upper - inputZ >= inputZ - next_lower ? next_lower : next_upper) : (next_upper - inputZ > inputZ - next_lower ? next_lower : next_upper));
			}
		}
		vector<string> at(const double& inputZ) {
			vector<string> outputIDs;
			for (pair<string, ExtendedText> currentExtendedText : extended_text) {
				if (currentExtendedText.second.z == inputZ) {
					outputIDs.push_back(currentExtendedText.first);
				}
			}
			return outputIDs;
		}
		static bool sortCondition(const ExtendedText* inputExtendedTextA, const ExtendedText* inputExtendedTextB) {
			return inputExtendedTextA->z < inputExtendedTextB->z;
		}
		vector<sf::Text> toVector() {
			vector<const ExtendedText*> extendedTexts;
			extendedTexts.reserve(extended_text.size());
			for (const pair<const string&, const ExtendedText&> currentExtendedText : extended_text) {
				extendedTexts.push_back(&extended_text.at(currentExtendedText.first));
			}
			sort(extendedTexts.begin(), extendedTexts.end(), sortCondition);
			vector<sf::Text> outputTexts;
			outputTexts.reserve(extendedTexts.size());
			for (const ExtendedText* currentExtendedText : extendedTexts) {
				outputTexts.push_back(currentExtendedText->text);
			}
			return outputTexts;
		}
		vector<sf::Shader*> getShaderVector() {
			vector<const ExtendedText*> extendedTexts;
			extendedTexts.reserve(extended_text.size());
			for (const pair<const string&, const ExtendedText&> currentExtendedText : extended_text) {
				extendedTexts.push_back(&extended_text.at(currentExtendedText.first));
			}
			sort(extendedTexts.begin(), extendedTexts.end(), sortCondition);
			vector<sf::Shader*> outputShaders;
			outputShaders.reserve(extendedTexts.size());
			for (const ExtendedText* currentExtendedText : extendedTexts) {
				outputShaders.push_back(currentExtendedText->shader);
			}
			return outputShaders;
		}
		ExtendedText& operator[](const string& inputID) {
			return extended_text.at(inputID);
		}
		const ExtendedText& operator[](const string& inputID) const {
			return extended_text.at(inputID);
		}
		TextContainer(float inputInitialSizeMultiplier = 1.0) : initialSizeMultiplier(inputInitialSizeMultiplier) {
			taggables = &extended_text;
		}
};
bool ExtendedText::mouseHovering(const ExtendedWindow& windowContainer, const bool& focusEnforced, const bool& obstructionEnforced, const bool& visibilityEnforced) {
	if (windowContainer.window && (!focusEnforced || windowContainer.window->hasFocus()) && (!obstructionEnforced || isnan(parentTextContainer->next_above(z))) && (!visibilityEnforced || !hidden)) {
		return ExtendedFunction::mouseContained(text.getGlobalBounds(), windowContainer.window, focusEnforced);
	}
	return false;
}

template <typename T>
class StopwatchContainer;
template <typename T>
class Stopwatch : public TaggableElement<Stopwatch<T>> {
	public:
		StopwatchContainer<T>* parentStopwatchContainer;
		T frame;
		T maxFrame;
		bool localPause;
		bool loop;
		bool tickBackwards;
		bool useMax;
		bool setBackState = false;
		Stopwatch& elapse(const T& elapseAmount = 1);
		Stopwatch& clamp() {
			if (useMax) {
				if (frame > maxFrame) {
					if (loop) {
						frame = 0;
					} else {
						frame = maxFrame;
					}
				} else if (frame < 0) {
					if (loop) {
						frame = maxFrame;
					} else {
						frame = 0;
					}
				}
			} else if (frame < 0) {
				frame = 0;
			}
			return *this;
		}
		Stopwatch& add(const T& frames = 1) {
			frame += frames;
			clamp();
			return *this;
		}
		Stopwatch& subtract(const T& frames = 1) {
			if (frame > frames) {
				frame -= frames;
			} else {
				frame = 0;
			}
			clamp();
			return *this;
		}
		Stopwatch& offset(const T& frames = 0, const bool& reverseDirection = false) {
			short multiplier = reverseDirection ? -1 : 1;
			if (frames*multiplier >= 0) {
				add(frames*multiplier);
			} else {
				subtract(-frames*multiplier);
			}
			return *this;
		}
		Stopwatch& set(const T& frames = 0) {
			frame = frames;
			clamp();
			return *this;
		}
		Stopwatch& setTickDirection(const bool& inputTickBackwards = false) {
			tickBackwards = inputTickBackwards;
			return *this;
		}
		bool getTickDirection() {
			return tickBackwards;
		}
		Stopwatch& setBack(const T& frames = 0) {
			frame = frames;
			clamp();
			setBackState = true;
			return *this;
		}
		Stopwatch& reset() {
			frame = 0;
			clamp();
			return *this;
		}
		Stopwatch& pause() {
			localPause = true;
			return *this;
		}
		Stopwatch& unpause() {
			localPause = false;
			return *this;
		}
		Stopwatch& resume() {
			localPause = false;
			return *this;
		}
		Stopwatch& setLoop(const bool& inputLoop) {
			loop = inputLoop;
			clamp();
			return *this;
		}
		bool isPaused() {
			return localPause;
		}
		bool isLooping() {
			return loop;
		}
		Stopwatch& setMax(const T& inputMaxFrame) {
			maxFrame = inputMaxFrame;
			useMax = true;
			clamp();
			return *this;
		}
		Stopwatch& resetMax() {
			maxFrame = 0;
			useMax = false;
			clamp();
			return *this;
		}
		T getMax() {
			return maxFrame;
		}
		float invlerp(const double& intervalStart, const double& intervalEnd) {
			if (intervalStart == intervalEnd) {
				return nan("");
			}
			float invLerpValue = (frame - intervalStart)/(intervalEnd - intervalStart);
			invLerpValue *= invLerpValue >= 0.0;
			invLerpValue = invLerpValue >= 1.0 ? 1.0 : invLerpValue;
			return static_cast<float>(invLerpValue);
		}
		Stopwatch(StopwatchContainer<T>* StopwatchContainerObject, const T& startingFrame = 0, const bool& inputPause = false, const bool& inputLoop = false, const bool& inputUseMax = false, const T& inputMaxFrame = 0, const bool& inputTickBackwards = false) : frame(startingFrame), localPause(inputPause), loop(inputLoop), useMax(inputUseMax), maxFrame(inputMaxFrame), parentStopwatchContainer(StopwatchContainerObject), tickBackwards(inputTickBackwards) {};
};
template <typename T>
class StopwatchContainer : public TaggableContainer<Stopwatch<T>> {
	public:
		bool masterPause;
		unordered_map<string, Stopwatch<T>> stopwatch;
		Stopwatch<T>& start(const string& inputID, const T& startingFrame = 0, const bool& inputPause = false, const bool& inputLoop = false, const bool& inputUseMax = false, const T& inputMaxFrame = 0, const bool& inputTickBackwards = false) {
			stopwatch.insert_or_assign(inputID, Stopwatch(this, startingFrame, inputPause, inputLoop, inputUseMax, inputMaxFrame, inputTickBackwards));
			return stopwatch.at(inputID);
		}
		StopwatchContainer& stop(const string& inputID) {
			stopwatch.erase(inputID);
			return *this;
		}
		StopwatchContainer& add(const T& frames = 1) {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).add(frames);
			}
			return *this;
		}
		StopwatchContainer& subtract(const T& frames = 1) {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).subtract(frames);
			}
			return *this;
		}
		StopwatchContainer& offset(const T& frames = 0, const bool& reverseDirection = false) {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).offset(frames, reverseDirection);
			}
			return *this;
		}
		StopwatchContainer& reset() {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).reset();
			}
			return *this;
		}
		StopwatchContainer& elapse(const T& elapseAmount = 1) {
			if (!masterPause) {
				for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
					stopwatch.at(currentWatch.first).elapse(elapseAmount);
				}
			}
			return *this;
		}
		bool exists(const string& inputID) {
			return stopwatch.count(inputID) != 0;
		}
		StopwatchContainer& pause() {
			masterPause = true;
			return *this;
		}
		StopwatchContainer& unpause() {
			masterPause = false;
			return *this;
		}
		StopwatchContainer& resume() {
			masterPause = false;
			return *this;
		}
		bool isPaused() {
			return masterPause;
		}
		StopwatchContainer& clear() {
			stopwatch = unordered_map<string, Stopwatch<T>>();
			return *this;
		}
		Stopwatch<T>& operator[](const string& inputID) {
			return stopwatch.at(inputID);
		}
		const Stopwatch<T>& operator[](const string& inputID) const {
			return stopwatch.at(inputID);
		}
		StopwatchContainer(const bool& inputPause = false) : masterPause(inputPause) {
			this->taggables = &stopwatch;
		}
};
template <typename T>
Stopwatch<T>& Stopwatch<T>::elapse(const T& elapseAmount) {
	if (parentStopwatchContainer) {
		if (!parentStopwatchContainer->masterPause && !localPause) {
			if (!setBackState) {
				if (!tickBackwards) {
					add(elapseAmount);
				} else {
					subtract(elapseAmount);
				}
			} else {
				setBackState = false;
			}
		}
	}
	clamp();
	return *this;
}

class TextureContainer;
class ExtendedTexture : public TaggableElement<ExtendedTexture> {
	public:
		TextureContainer* parentTextureContainer;
		sf::Texture* texture;
		ExtendedTexture& setSmooth(const bool& inputSmooth) {
			if (texture) {
				texture->setSmooth(inputSmooth);
			}
			return *this;
		}
		ExtendedTexture& load(const sf::Texture& inputTexture) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture(inputTexture);
			return *this;
		}
		ExtendedTexture& loadFromImage(const sf::Image& inputImage) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture();
			if (texture->loadFromImage(inputImage));
			return *this;
		}
		ExtendedTexture& loadFromFile(const string& fileDirectory) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture();
			if(!texture->loadFromFile(fileDirectory)) {
				texture = nullptr;
			}
			return *this;
		}
		ExtendedTexture& loadFromMemory(const unsigned char* data, const size_t& size) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture();
			if(!texture->loadFromMemory(data, size)) {
				texture = nullptr;
			}
			return *this;
		}
		ExtendedTexture& unload() {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			return *this;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const sf::Texture& inputTexture) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture(inputTexture);
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const sf::Image& inputImage) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture();
			if (texture->loadFromImage(inputImage));
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const string& fileDirectory) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture(fileDirectory);
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const unsigned char* data, const size_t& size) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture(data, size);
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject) : parentTextureContainer(TextureContainerObject) {
			texture = nullptr;
			return;
		}
		~ExtendedTexture() {
			delete texture;
			texture = nullptr;
			return;
		}
		ExtendedTexture(ExtendedTexture& originalObject) {
			if (originalObject.texture) {
				texture = new sf::Texture(*originalObject.texture);
			} else {
				texture = nullptr;
			}
			parentTextureContainer = originalObject.parentTextureContainer;
			return;
		}
		ExtendedTexture& operator=(ExtendedTexture& rObject) {
			if (this != &rObject) {
				delete texture;
				if (rObject.texture) {
					texture = new sf::Texture(*rObject.texture);
				} else {
					texture = nullptr;
				}
				parentTextureContainer = rObject.parentTextureContainer;
			}
			return *this;
		}
		ExtendedTexture(ExtendedTexture&& originalObject) noexcept : texture(originalObject.texture) {
			parentTextureContainer = originalObject.parentTextureContainer;
			originalObject.texture = nullptr;
			return;
		}
		ExtendedTexture& operator=(ExtendedTexture&& rObject) noexcept {
			if (this != &rObject) {
				texture = rObject.texture;
				parentTextureContainer = rObject.parentTextureContainer;
				rObject.texture = nullptr;
			}
			return *this;
		}
};
class TextureContainer : public TaggableContainer<ExtendedTexture> {
	public:
		bool defaultTextureSmoothness = false;
		unordered_map<string, ExtendedTexture> extended_texture;
		TextureContainer& update_smoothness() {
			for (pair<const string, ExtendedTexture>& currentExtendedTexture : extended_texture) {
				extended_texture.at(currentExtendedTexture.first).setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& load(string inputID, const sf::Texture& inputTexture) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).load(inputTexture);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, inputTexture));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& loadFromImage(string inputID, const sf::Image& inputImage) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).loadFromImage(inputImage);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, inputImage));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& loadFromFile(string inputID, const string& fileDirectory) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).loadFromFile(fileDirectory);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, fileDirectory));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& loadFromMemory(string inputID, const unsigned char* data, const size_t size) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).loadFromMemory(data, size);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, data, size));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		bool exists(const string& inputID) {
			return extended_texture.count(inputID) != 0;
		}
		TextureContainer& erase(const string& inputID) {
			extended_texture.erase(inputID);
			return *this;
		}
		TextureContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		TextureContainer& clear() {
			extended_texture = unordered_map<string, ExtendedTexture>();
			return *this;
		}
		TextureContainer& clean() {
			for (pair<const string, ExtendedTexture>& currentExtendedTexture : extended_texture) {
				if (!extended_texture.at(currentExtendedTexture.first).texture) {
					erase(currentExtendedTexture.first);
				}
			}
			return *this;
		}
		TextureContainer& setSmooth(const bool& inputSmooth = true) {
			defaultTextureSmoothness = inputSmooth;
			update_smoothness();
			return *this;
		}
		sf::Texture& operator[](const string& inputID) {
			return *extended_texture.at(inputID).texture;
		}
		const sf::Texture& operator[](const string& inputID) const {
			return *extended_texture.at(inputID).texture;
		}
		TextureContainer() {
			taggables = &extended_texture;
		}
};

class SoundBufferContainer;
class ExtendedSoundBuffer : public TaggableElement<ExtendedSoundBuffer> {
	public:
		SoundBufferContainer* parentSoundBufferContainer;
		sf::SoundBuffer* buffer;
		ExtendedSoundBuffer& load(const sf::SoundBuffer& inputSoundBuffer) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			buffer = new sf::SoundBuffer(inputSoundBuffer);
			return *this;
		}
		ExtendedSoundBuffer& loadFromFile(const string& fileDirectory) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			buffer = new sf::SoundBuffer();
			if(!buffer->loadFromFile(fileDirectory)) {
				buffer = nullptr;
			}
			return *this;
		}
		ExtendedSoundBuffer& loadFromMemory(const unsigned char* data, const size_t& size) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			buffer = new sf::SoundBuffer();
			if(!buffer->loadFromMemory(data, size)) {
				buffer = nullptr;
			}
			return *this;
		}
		ExtendedSoundBuffer& unload() {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			return *this;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject, const sf::SoundBuffer& inputSoundBuffer) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = new sf::SoundBuffer(inputSoundBuffer);
			return;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject, const string& fileDirectory) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = new sf::SoundBuffer(fileDirectory);
			return;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject, const unsigned char* data, const size_t& size) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = new sf::SoundBuffer(data, size);
			return;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = nullptr;
			return;
		}
		~ExtendedSoundBuffer() {
			delete buffer;
			buffer = nullptr;
			return;
		}
		ExtendedSoundBuffer(ExtendedSoundBuffer& originalObject) {
			if (originalObject.buffer) {
				buffer = new sf::SoundBuffer(*originalObject.buffer);
			} else {
				buffer = nullptr;
			}
			parentSoundBufferContainer = originalObject.parentSoundBufferContainer;
			return;
		}
		ExtendedSoundBuffer& operator=(ExtendedSoundBuffer& rObject) {
			if (this != &rObject) {
				delete buffer;
				if (rObject.buffer) {
					buffer = new sf::SoundBuffer(*rObject.buffer);
				} else {
					buffer = nullptr;
				}
				parentSoundBufferContainer = rObject.parentSoundBufferContainer;
			}
			return *this;
		}
		ExtendedSoundBuffer(ExtendedSoundBuffer&& originalObject) noexcept : buffer(originalObject.buffer) {
			parentSoundBufferContainer = originalObject.parentSoundBufferContainer;
			originalObject.buffer = nullptr;
			return;
		}
		ExtendedSoundBuffer& operator=(ExtendedSoundBuffer&& rObject) noexcept {
			if (this != &rObject) {
				buffer = rObject.buffer;
				parentSoundBufferContainer = rObject.parentSoundBufferContainer;
				rObject.buffer = nullptr;
			}
			return *this;
		}
};
class SoundBufferContainer : public TaggableContainer<ExtendedSoundBuffer> {
	public:
		unordered_map<string, ExtendedSoundBuffer> extended_buffer;
		SoundBufferContainer& load(const string& inputID, const sf::SoundBuffer& inputSoundBuffer) {
			extended_buffer.insert_or_assign(inputID, ExtendedSoundBuffer(this, inputSoundBuffer));
			return *this;
		}
		SoundBufferContainer& loadFromFile(const string& inputID, const string& fileDirectory) {
			extended_buffer.insert_or_assign(inputID, ExtendedSoundBuffer(this, fileDirectory));
			return *this;
		}
		SoundBufferContainer& loadFromMemory(const string& inputID, const unsigned char* data, const size_t& size) {
			extended_buffer.insert_or_assign(inputID, ExtendedSoundBuffer(this, data, size));
			return *this;
		}
		bool exists(const string& inputID) {
			return extended_buffer.count(inputID) != 0;
		}
		SoundBufferContainer& erase(const string& inputID) {
			extended_buffer.erase(inputID);
			return *this;
		}
		SoundBufferContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		SoundBufferContainer& clear() {
			extended_buffer = unordered_map<string, ExtendedSoundBuffer>();
			return *this;
		}
		SoundBufferContainer& clean() {
			for (pair<const string, ExtendedSoundBuffer>& currentExtendedSoundBuffer : extended_buffer) {
				if (!extended_buffer.at(currentExtendedSoundBuffer.first).buffer) {
					erase(currentExtendedSoundBuffer.first);
				}
			}
			return *this;
		}
		sf::SoundBuffer& operator[](const string& inputID) {
			return *extended_buffer.at(inputID).buffer;
		}
		const sf::SoundBuffer& operator[](const string& inputID) const {
			return *extended_buffer.at(inputID).buffer;
		}
		SoundBufferContainer() {
			taggables = &extended_buffer;
		}
};

class FontContainer;
class ExtendedFont : public TaggableElement<ExtendedFont> {
	public:
		FontContainer* parentFontContainer;
		sf::Font* font;
		ExtendedFont& setSmooth(const bool& inputSmooth) {
			if (font) {
				font->setSmooth(inputSmooth);
			}
			return *this;
		}
		ExtendedFont& open(const sf::Font& inputFont) {
			if (font) {
				delete font;
				font = nullptr;
			}
			font = new sf::Font(inputFont);
			return *this;
		}
		ExtendedFont& openFromFile(const string& fileDirectory) {
			if (font) {
				delete font;
				font = nullptr;
			}
			font = new sf::Font();
			if(!font->openFromFile(fileDirectory)) {
				font = nullptr;
			}
			return *this;
		}
		ExtendedFont& openFromMemory(const unsigned char* data, const size_t& size) {
			if (font) {
				delete font;
				font = nullptr;
			}
			font = new sf::Font();
			if(!font->openFromMemory(data, size)) {
				font = nullptr;
			}
			return *this;
		}
		ExtendedFont& load(const sf::Font& inputFont) {
			return open(inputFont);
		}
		ExtendedFont& loadFromFile(const string& fileDirectory) {
			return openFromFile(fileDirectory);
		}
		ExtendedFont& loadFromMemory(const unsigned char* data, const size_t& size) {
			return openFromMemory(data, size);
		}
		ExtendedFont& unload() {
			if (font) {
				delete font;
				font = nullptr;
			}
			return *this;
		}
		ExtendedFont(FontContainer* FontContainerObject, const sf::Font& inputFont) : parentFontContainer(FontContainerObject) {
			font = new sf::Font(inputFont);
			return;
		}
		ExtendedFont(FontContainer* FontContainerObject, const string& fileDirectory) : parentFontContainer(FontContainerObject) {
			font = new sf::Font(fileDirectory);
			return;
		}
		ExtendedFont(FontContainer* FontContainerObject, const unsigned char* data, const size_t& size) : parentFontContainer(FontContainerObject) {
			font = new sf::Font(data, size);
			return;
		}
		ExtendedFont(FontContainer* FontContainerObject) : parentFontContainer(FontContainerObject) {
			font = nullptr;
			return;
		}
		~ExtendedFont() {
			delete font;
			font = nullptr;
			return;
		}
		ExtendedFont(ExtendedFont& originalObject) {
			if (originalObject.font) {
				font = new sf::Font(*originalObject.font);
			} else {
				font = nullptr;
			}
			parentFontContainer = originalObject.parentFontContainer;
			return;
		}
		ExtendedFont& operator=(ExtendedFont& rObject) {
			if (this != &rObject) {
				delete font;
				if (rObject.font) {
					font = new sf::Font(*rObject.font);
				} else {
					font = nullptr;
				}
				parentFontContainer = rObject.parentFontContainer;
			}
			return *this;
		}
		ExtendedFont(ExtendedFont&& originalObject) noexcept : font(originalObject.font) {
			parentFontContainer = originalObject.parentFontContainer;
			originalObject.font = nullptr;
			return;
		}
		ExtendedFont& operator=(ExtendedFont&& rObject) noexcept {
			if (this != &rObject) {
				font = rObject.font;
				parentFontContainer = rObject.parentFontContainer;
				rObject.font = nullptr;
			}
			return *this;
		}
};
class FontContainer : public TaggableContainer<ExtendedFont> {
	public:
		bool defaultFontSmoothness = false;
		unordered_map<string, ExtendedFont> extended_font;
		FontContainer& update_smoothness() {
			for (pair<const string, ExtendedFont>& currentExtendedFont : extended_font) {
				extended_font.at(currentExtendedFont.first).setSmooth(defaultFontSmoothness);
			}
			return *this;
		}
		FontContainer& open(const string& inputID, const sf::Font& inputFont) {
			extended_font.insert_or_assign(inputID, ExtendedFont(this, inputFont));
			return *this;
		}
		FontContainer& openFromFile(const string& inputID, const string& fileDirectory) {
			extended_font.insert_or_assign(inputID, ExtendedFont(this, fileDirectory));
			return *this;
		}
		FontContainer& openFromMemory(const string& inputID, const unsigned char* data, const size_t& size) {
			extended_font.insert_or_assign(inputID, ExtendedFont(this, data, size));
			return *this;
		}
		FontContainer& load(const string& inputID, const sf::Font& inputFont) {
			return open(inputID, inputFont);
		}
		FontContainer& loadFromFile(const string& inputID, const string& fileDirectory) {
			return openFromFile(inputID, fileDirectory);
		}
		FontContainer& loadFromMemory(const string& inputID, const unsigned char* data, const size_t& size) {
			return openFromMemory(inputID, data, size);
		}
		bool exists(const string& inputID) {
			return extended_font.count(inputID) != 0;
		}
		FontContainer& erase(const string& inputID) {
			extended_font.erase(inputID);
			return *this;
		}
		FontContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		FontContainer& clear() {
			extended_font = unordered_map<string, ExtendedFont>();
			return *this;
		}
		FontContainer& clean() {
			for (pair<const string, ExtendedFont>& currentExtendedFont : extended_font) {
				if (!extended_font.at(currentExtendedFont.first).font) {
					erase(currentExtendedFont.first);
				}
			}
			return *this;
		}
		FontContainer& setSmooth(const bool& inputSmooth = true) {
			defaultFontSmoothness = inputSmooth;
			update_smoothness();
			return *this;
		}
		sf::Font& operator[](const string& inputID) {
			return *extended_font.at(inputID).font;
		}
		const sf::Font& operator[](const string& inputID) const {
			return *extended_font.at(inputID).font;
		}
		FontContainer() {
			taggables = &extended_font;
		}
};

class TexturePage {
	public:
		sf::Texture* texture;
		size_t length = 0;
		double weight = 0.0;
		TexturePage(sf::Texture& inputTexture, const size_t& inputLength = 1, const double& inputWeight = 1.0) : texture(&inputTexture), length(inputLength), weight(inputWeight) {
			weight *= weight > 0.0;
			return;
		}
		TexturePage() {
			return;
		}
};
class TextureFlipbook {
	public:
		bool looping;
		size_t loop_starting_frame;
		vector<TexturePage> texture_pages;
		TextureFlipbook& add(const vector<TexturePage>& inputTexturePages) {
			for (const TexturePage& texturePage : inputTexturePages) {
				texture_pages.push_back(texturePage);
			}
			return *this;
		}
		TextureFlipbook& add(vector<sf::Texture>& inputTextures) {
			for (sf::Texture& inputTexture : inputTextures) {
				texture_pages.push_back(TexturePage(inputTexture));
			}
			return *this;
		}
		size_t getFrameTotal() {
			size_t totalFrames = 0;
			for (const TexturePage& texturePage : texture_pages) {
				totalFrames += texturePage.length;
			}
			return totalFrames;
		}
		double getWeightTotal() {
			double totalWeight = 0;
			for (const TexturePage& texturePage : texture_pages) {
				totalWeight += texturePage.weight;
			}
			return totalWeight;
		}
		sf::Texture& getAtIndex(const size_t& inputIndex) {
			return *texture_pages.at(inputIndex).texture;
		}
		TextureFlipbook& removeAtIndex(const size_t& inputIndex) {
			texture_pages.erase(texture_pages.begin() + inputIndex);
			return *this;
		}
		TexturePage& insertAtIndex(const size_t& inputIndex, const TexturePage& inputTexturePage) {
			texture_pages.insert(texture_pages.begin() + inputIndex, inputTexturePage);
			return texture_pages.at(inputIndex);
		}
		long long getIndex(long long inputFrame = 0) {
			long long maxFrame = getFrameTotal() - 1;
			long long targetFrame = inputFrame;
			if (looping) {
				if (inputFrame > maxFrame) {
					inputFrame -= maxFrame + 1;
					targetFrame %= maxFrame + 1 - loop_starting_frame;
					targetFrame += loop_starting_frame;
				}
			} else if (inputFrame >= maxFrame) {
				targetFrame = maxFrame;
			} else if (inputFrame < 0) {
				targetFrame = 0;
			}
			for (size_t i = 0; i < texture_pages.size(); ++i) {
				if (targetFrame < texture_pages[i].length) {
					return i;
				} else {
					targetFrame -= texture_pages[i].length;
				}
			}
			return texture_pages.size() - 1;
		}
		long long getIndex(const double& inputLerpValue = 0.0) {
			return getIndex(static_cast<long long>(getFrameTotal() * inputLerpValue));
		}
		sf::Texture& get(const long long& inputFrame = 0) {
			return *texture_pages.at(getIndex(inputFrame)).texture;
		}
		sf::Texture& get(const double& inputLerpValue = 0.0) {
			return *texture_pages.at(getIndex(inputLerpValue)).texture;
		}
		sf::Texture& getRandom() {
			double targetWeight = getWeightTotal() * drandom();
			for (size_t i = 0; i < texture_pages.size(); ++i) {
				if (targetWeight < texture_pages[i].weight) {
					return *texture_pages.at(i).texture;
				} else {
					targetWeight -= texture_pages[i].weight;
				}
			}
			return *texture_pages.at(0).texture;
		}
		TextureFlipbook& remove(const long long& inputFrame = 0) {
			texture_pages.erase(texture_pages.begin() + getIndex(inputFrame));
			return *this;
		}
		TextureFlipbook& remove(const double& inputLerpValue = 0.0) {
			texture_pages.erase(texture_pages.begin() + getIndex(inputLerpValue));
			return *this;
		}
		bool getLoop() {
			return looping;
		}
		TextureFlipbook& setLoop(const bool& inputLoop) {
			looping = inputLoop;
			return *this;
		}
		TextureFlipbook& clear() {
			texture_pages = vector<TexturePage>();
			return *this;
		}
		TextureFlipbook& create(const vector<TexturePage>& inputTexturePages) {
			texture_pages = inputTexturePages;
			return *this;
		}
		TextureFlipbook& create(vector<sf::Texture>& inputTextures) {
			for (sf::Texture& inputTexture : inputTextures) {
				texture_pages.push_back(TexturePage(inputTexture, 1, 1.0));
			}
			return *this;
		}
		TextureFlipbook& safeAssignAtIndex(const size_t& inputIndex, const TexturePage& inputTexturePage) {
			if (texture_pages.size() <= inputIndex) {
				texture_pages.resize(inputIndex + 1, TexturePage());
			}
			texture_pages[inputIndex] = inputTexturePage;
			return *this;
		}
		TextureFlipbook& safeAssignAtIndex(const size_t& inputIndex, sf::Texture& inputTexture) {
			if (texture_pages.size() <= inputIndex) {
				texture_pages.resize(inputIndex + 1, TexturePage());
			}
			texture_pages[inputIndex] = TexturePage(inputTexture);
			return *this;
		}
		sf::Texture& operator[](const long long& inputFrame) {
			return get(inputFrame);
		}
		TextureFlipbook(const vector<TexturePage>& inputTexturePages, const bool& inputLoop = false, const size_t& inputLoopStartingFrame = 0) : looping(inputLoop), loop_starting_frame(inputLoopStartingFrame) {
			texture_pages = inputTexturePages;
			return;
		}
		TextureFlipbook(vector<sf::Texture>& inputTextures, const bool& inputLoop = false, const size_t& inputLoopStartingFrame = 0) : looping(inputLoop), loop_starting_frame(inputLoopStartingFrame) {
			for (sf::Texture& inputTexture : inputTextures) {
				texture_pages.push_back(TexturePage(inputTexture, 1, 1.0));
			}
			return;
		}
		TextureFlipbook() {
			return;
		}
};
class TextureFlipbookContainer {
	public:
		unordered_map<string, TextureFlipbook> texture_flipbooks;
		TextureFlipbook& add(const string& inputID, const TextureFlipbook& inputTextureFlipbook) {
			texture_flipbooks.insert_or_assign(inputID, inputTextureFlipbook);
			return texture_flipbooks.at(inputID);
		}
		TextureFlipbookContainer& remove(const string& inputID) {
			texture_flipbooks.erase(inputID);
			return *this;
		}
		TextureFlipbookContainer& clear() {
			texture_flipbooks = unordered_map<string, TextureFlipbook>();
			return *this;
		}
		TextureFlipbook& at(const string& inputID) {
			return texture_flipbooks.at(inputID);
		}
		bool exists(const string& inputID) {
			return texture_flipbooks.count(inputID) != 0;
		}
		TextureFlipbook& operator[](const string& inputID) {
			return texture_flipbooks.at(inputID);
		}
		const TextureFlipbook& operator[](const string& inputID) const {
			return texture_flipbooks.at(inputID);
		}
};

class SoundEntry {
	public:
		sf::Sound sound;
		float localVolume;
		float localPan;
		double weight;
		SoundEntry(const sf::SoundBuffer& inputSoundBuffer = sf::SoundBuffer(), const float& inputLocalVolume = 1.0, float inputPanning = 0.0, float inputPitch = 1.0, double inputWeight = 1.0) : sound(sf::Sound(inputSoundBuffer)), localVolume(inputLocalVolume) {
			inputPanning = inputPanning >= 1.0 ? 1.0 : inputPanning;
			inputPanning = inputPanning <= -1.0 ? -1.0 : inputPanning;
			localPan = inputPanning;
			inputPitch *= inputPitch >= 0.0;
			inputWeight *= inputWeight > 0.0;
			weight = inputWeight;
			sound.setPan(localPan);
			sound.setPitch(inputPitch);
		}
};
class SoundList {
	public:
		float masterVolume = 1.0;
		bool masterPaused = false;
		float panShift = 0.0;
		vector<SoundEntry> sound_entries;
		SoundList& update_volume() {
			for (SoundEntry& inputSoundEntry : sound_entries) {
				inputSoundEntry.sound.setVolume(masterVolume * inputSoundEntry.localVolume * 100.0f);
			}
			return *this;
		}
		SoundList& update_pause() {
			if (masterPaused) {
				for (SoundEntry& inputSoundEntry : sound_entries) {
					inputSoundEntry.sound.pause();
				}
			} else {
				for (SoundEntry& inputSoundEntry : sound_entries) {
					inputSoundEntry.sound.play();
				}
			}
			return *this;
		}
		SoundList& update_pan() {
			for (SoundEntry& inputSoundEntry : sound_entries) {
				if (panShift == 0.0) {
					inputSoundEntry.sound.setPan(inputSoundEntry.localPan);
				} else {
					inputSoundEntry.sound.setPan(cos(acos(inputSoundEntry.localPan) + panShift));
				}
			}
			return *this;
		}
		bool getVolume() {
			return masterVolume;
		}
		SoundList& setVolume(float inputMasterVolume) {
			inputMasterVolume *= inputMasterVolume > 0.0;
			inputMasterVolume = inputMasterVolume > 1.0 ? 1.0 : inputMasterVolume;
			masterVolume = inputMasterVolume;
			update_volume();
			return *this;
		}
		SoundList& setPause(const bool& inputPause) {
			masterPaused = inputPause;
			update_pause();
			return *this;
		}
		SoundList& pause() {
			masterPaused = true;
			update_pause();
			return *this;
		}
		SoundList& unpause() {
			masterPaused = false;
			update_pause();
			return *this;
		}
		SoundList& resume() {
			unpause();
			return *this;
		}
		bool inactive() {
			for (size_t i = 0; i < sound_entries.size(); ++i) {
				if (sound_entries[i].sound.getStatus() != sf::Sound::Status::Stopped) {
					return false;
				}
			}
			return true;
		}
		SoundList& clean() {
			for (size_t i = 0; i < sound_entries.size(); ++i) {
				if (sound_entries[i].sound.getStatus() == sf::Sound::Status::Stopped) {
					sound_entries.erase(sound_entries.begin() + i);
					--i;
				}
			}
			return *this;
		}
		SoundList& clear() {
			sound_entries = vector<SoundEntry>();
			return *this;
		}
		float getPanShift(const bool& deg = true) {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		SoundList& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return *this;
		}
		SoundList& add(const sf::SoundBuffer& inputSoundBuffer, float inputLocalVolume = 1.0, float inputPanning = 0.0, float inputPitch = 1.0, double inputWeight = 1.0, const bool& forcePlay = false) {
			sound_entries.push_back(SoundEntry(inputSoundBuffer, inputLocalVolume, inputPanning, inputPitch, inputWeight));
			if (!forcePlay && masterPaused) {
				sound_entries[sound_entries.size() - 1].sound.pause();
			} else {
				sound_entries[sound_entries.size() - 1].sound.play();
			}
			update_volume();
			return *this;
		}
		SoundList& add(const vector<SoundEntry>& inputSoundEntries, const bool& forcePlay = false) {
			size_t oldSize = sound_entries.size();
			sound_entries.insert(sound_entries.begin(), inputSoundEntries.begin(), inputSoundEntries.end());
			if (!forcePlay && masterPaused) {
				for (size_t i = oldSize - 1;  i < sound_entries.size(); ++i) {
					sound_entries[i].sound.pause();
				}
			} else {
				for (size_t i = oldSize - 1;  i < sound_entries.size(); ++i) {
					sound_entries[i].sound.play();
				}
			}
			update_volume();
			return *this;
		}
		SoundList& insert(const SoundEntry& inputSoundEntry, const size_t& inputIndex) {
			sound_entries.insert(sound_entries.begin() + inputIndex, inputSoundEntry);
			return *this;
		}
		SoundList& remove(const size_t& inputIndex) {
			sound_entries.erase(sound_entries.begin() + inputIndex);
			return *this;
		}
		SoundEntry& get(const size_t& inputIndex) {
			return sound_entries[inputIndex];
		}
		SoundList& play(const size_t& inputIndex) {
			get(inputIndex).sound.play();
			return *this;
		}
		SoundEntry& getRandom() {
			return sound_entries[size_t_random(0, sound_entries.size() - 1)];
		}
		SoundList& playRandom() {
			getRandom().sound.play();
			return *this;
		}
		SoundList(const vector<SoundEntry>& inputSoundEntries = vector<SoundEntry>(), float inputMasterVolume = 1.0, const bool inputMasterPaused = false, const float& inputPanShift = 0.0) : masterVolume(inputMasterVolume), masterPaused(inputMasterPaused), panShift(inputPanShift) {
			sound_entries = inputSoundEntries;
			update_volume();
			update_pause();
			return;
		}
		SoundList(vector<sf::SoundBuffer>& inputSoundBuffers, float inputMasterVolume = 1.0, const bool inputMasterPaused = false, const float& inputPanShift = 0.0) : masterVolume(inputMasterVolume), masterPaused(inputMasterPaused), panShift(inputPanShift) {
			for (sf::SoundBuffer& inputSoundBuffer : inputSoundBuffers) {
				sound_entries.push_back(SoundEntry(inputSoundBuffer));
			}
			update_volume();
			update_pause();
			return;
		}
};
class SoundListContainer {
	public:
		unordered_map<string, SoundList> sound_flipbooks;
		SoundList& add(const string& inputID, const SoundList& inputSoundList = SoundList()) {
			sound_flipbooks.insert_or_assign(inputID, inputSoundList);
			return sound_flipbooks.at(inputID);
		}
		SoundListContainer& remove(const string& inputID) {
			sound_flipbooks.erase(inputID);
			return *this;
		}
		SoundListContainer& clear() {
			sound_flipbooks = unordered_map<string, SoundList>();
			return *this;
		}
		SoundList& at(const string& inputID) {
			return sound_flipbooks.at(inputID);
		}
		bool exists(const string& inputID) {
			return sound_flipbooks.count(inputID) != 0;
		}
		SoundList& operator[](const string& inputID) {
			return sound_flipbooks.at(inputID);
		}
		const SoundList& operator[](const string& inputID) const {
			return sound_flipbooks.at(inputID);
		}
};

template <typename T, typename U>
ExtendedWindow& ExtendedWindow::ExtendedDraw(const T* extendedDrawable, const U& drawable, const bool& declareBoundsUniforms) {
	if (declareBoundsUniforms && extendedDrawable->shader) {
		sf::FloatRect windowGlobalBounds = getGlobalBounds();
		sf::FloatRect drawableGlobalBounds = extendedDrawable->getGlobalBounds();
		extendedDrawable->shader->setUniform("drawableTexture", sf::Shader::CurrentTexture);
		extendedDrawable->shader->setUniform("windowPosition", windowGlobalBounds.position);
		extendedDrawable->shader->setUniform("windowSize", windowGlobalBounds.size);
		extendedDrawable->shader->setUniform("drawablePosition", drawableGlobalBounds.position);
		extendedDrawable->shader->setUniform("drawableSize", drawableGlobalBounds.size);
	}
	window->draw(drawable, extendedDrawable->shader);
	return *this;
}
ExtendedWindow& ExtendedWindow::refresh(const bool& declareBoundsUniforms = false, const SpriteContainer& containerA = SpriteContainer(), const TextContainer& containerB = TextContainer()) {
	if (window) {
		window->clear();
		vector<const ExtendedSprite*> extendedDrawablesA;
		vector<const ExtendedText*> extendedDrawablesB;
		extendedDrawablesA.reserve(containerA.extended_drawable().size());
		extendedDrawablesB.reserve(containerB.extended_drawable().size());
		for (const pair<const string&, const ExtendedSprite&> currentExtendedDrawable : containerA.extended_drawable()) {
			extendedDrawablesA.push_back(&containerA[currentExtendedDrawable.first]);
		}
		for (const pair<const string&, const ExtendedText&> currentExtendedDrawable : containerB.extended_drawable()) {
			extendedDrawablesB.push_back(&containerB[currentExtendedDrawable.first]);
		}
		sort(extendedDrawablesA.begin(), extendedDrawablesA.end(), containerA.sortCondition);
		sort(extendedDrawablesB.begin(), extendedDrawablesB.end(), containerB.sortCondition);
		size_t cursorA = 0;
		size_t cursorB = 0;
		while (true) {
			if (cursorA < extendedDrawablesA.size() && cursorB < extendedDrawablesB.size()) {
				if (extendedDrawablesA[cursorA]->z < extendedDrawablesB[cursorB]->z) {
					ExtendedDraw(extendedDrawablesA[cursorA], extendedDrawablesA[cursorA]->drawable(), declareBoundsUniforms);
					++cursorA;
				} else {
					ExtendedDraw(extendedDrawablesB[cursorB], extendedDrawablesB[cursorB]->drawable(), declareBoundsUniforms);
					++cursorB;
				}
			} else if (cursorA < extendedDrawablesA.size()) {
				ExtendedDraw(extendedDrawablesA[cursorA], extendedDrawablesA[cursorA]->drawable(), declareBoundsUniforms);
				++cursorA;
			} else if (cursorB < extendedDrawablesB.size()) {
				ExtendedDraw(extendedDrawablesB[cursorB], extendedDrawablesB[cursorB]->drawable(), declareBoundsUniforms);
				++cursorB;
			} else {
				break;
			}
		}
		window->display();
	}
	return *this;
}

#ifdef LOAD_FROM_FILE
string replaceall(string inputString, const string& replaceString, const string& replaceWith) {
	if (replaceString == "") {
		return inputString;
	}
	size_t currentIndex = 0;
	while ((currentIndex = inputString.find(replaceString, currentIndex)) != string::npos) {
		inputString.replace(currentIndex, replaceString.size(), replaceWith);
		currentIndex += replaceWith.size();
	}
	return inputString;
}


short readfromfile(ifstream& inputFile, vector<unsigned char>& outputVector) {
	if (!inputFile.is_open()) {
		return -1;
	}
	inputFile.seekg(0, std::ios::end);
	streampos fileSize = inputFile.tellg();
	inputFile.seekg(0, ios::beg);
	outputVector = vector<unsigned char>(fileSize);
	inputFile.read(reinterpret_cast<char*>(outputVector.data()), fileSize);
	if (inputFile.fail() && !inputFile.eof()) {
		return -2;
	}
	return 0;
}


vector<string> printdir(const string& directory, const unsigned short& fileNameMode = 0, const unsigned short& filter = 0, const bool& useForwardSlash = false) {
    vector<string> fileNames;
    const filesystem::path directoryObject = directory;
    if (filesystem::exists(directoryObject) && filesystem::is_directory(directoryObject)) {
	  	for (const filesystem::directory_entry& currentFilePath : filesystem::directory_iterator(directoryObject)) {
    		if (filter == 0 || (filter == 1 && filesystem::is_regular_file(currentFilePath)) || (filter == 2 && filesystem::is_directory(currentFilePath))) {
                if (fileNameMode == 3) {
                    fileNames.push_back(filesystem::path(currentFilePath.path().string()).extension().string() + (filesystem::is_directory(currentFilePath) ? (useForwardSlash ? "/" : "\\") : ""));
                } else if (fileNameMode == 2) {
                    fileNames.push_back(filesystem::path(currentFilePath.path().string()).stem().string());
                } else if (fileNameMode == 1) {
                    fileNames.push_back(filesystem::path(currentFilePath.path().string()).filename().string() + (filesystem::is_directory(currentFilePath) ? (useForwardSlash ? "/" : "\\") : ""));
                } else {
                    fileNames.push_back(currentFilePath.path().string() + (filesystem::is_directory(currentFilePath) ? (useForwardSlash ? "/" : "\\") : ""));
                }
	        }
	    }
    }
    return fileNames;
}

vector<string> getFileDirectories(const string& initialDirectory, const bool& useForwardSlash = false) {
	vector<string> fileDirectories = printdir(initialDirectory), newDirectories;
	for (size_t i = 0; i < fileDirectories.size(); ++i) {
		if (fileDirectories[i][fileDirectories[i].size() - 1] == (useForwardSlash ? '/' : '\\')) {
			newDirectories.push_back(fileDirectories[i]);
			fileDirectories.erase(fileDirectories.begin() + i);
			--i;
		}
	}
	for (size_t i = 0; i < newDirectories.size(); ++i) {
		vector<string> fileSubdirectories = getFileDirectories(newDirectories[i]);
		for (size_t j = 0; j < fileSubdirectories.size(); ++j) {
			fileDirectories.push_back(fileSubdirectories[j]);
		}
	}
	return fileDirectories;
}
			
unordered_map<string, vector<unsigned char>> loadSubfilesToMap(string initialDirectory, bool keysUseForwardSlash = true, const bool& useForwardSlash = false) {
	if (useForwardSlash) {
		initialDirectory = replaceall(initialDirectory, "\\", "/");
	} else {
		initialDirectory = replaceall(initialDirectory, "/", "\\");
	}
	if ((initialDirectory[0] == '\"' && initialDirectory[initialDirectory.size() - 1] == '\"') || (initialDirectory[0] == '\'' && initialDirectory[initialDirectory.size() - 1] == '\'')) {
		initialDirectory.erase(initialDirectory.end() - 1);
		initialDirectory.erase(initialDirectory.begin());
	}
	if (initialDirectory[initialDirectory.size() - 1] != (useForwardSlash ? '/' : '\\')) {
		initialDirectory += (useForwardSlash ? "/" : "\\");
	}
	vector<string> fileDirectories = getFileDirectories(initialDirectory);
	unordered_map<string, vector<unsigned char>> outputAssets;
	size_t pathStartingIndex = (initialDirectory.substr(0,initialDirectory.size() - 1).rfind((useForwardSlash ? '/' : '\\')) != string::npos) ? initialDirectory.substr(0,initialDirectory.size() - 1).rfind((useForwardSlash ? '/' : '\\')) + 1 : 0;
	for (size_t i = 0; i < fileDirectories.size(); ++i) {
		ifstream inputFile(fileDirectories[i], ios::binary);
		if (inputFile.is_open()) {
			vector<unsigned char> bytes;
			readfromfile(inputFile, bytes);
			outputAssets.insert_or_assign(keysUseForwardSlash ? replaceall(fileDirectories[i].substr(pathStartingIndex, fileDirectories[i].size() - pathStartingIndex), "\\", "/") : replaceall(fileDirectories[i].substr(pathStartingIndex, fileDirectories[i].size() - pathStartingIndex), "/", "\\"), bytes);
		}
	}
	return outputAssets;
}

unordered_map<string, vector<unsigned char>> assets = loadSubfilesToMap("assets\\", true);
vector<string> findAssetsWithPrefix(const string& prefix) {
	vector<string> output;
	for (const auto& [key, value] : assets) {
		if (key.substr(0, prefix.size()) == prefix) {
			output.push_back(key.substr(prefix.size(), key.size() - prefix.size()));
		}
	}
	return output;
}
#endif
#ifdef LOAD_FROM_MEMORY
#include "assets.cpp"
vector<string> findAssetsWithPrefix(const string& prefix) {
	vector<string> output;
	for (size_t i = 0; i < assets.size(); ++i) {
		if (assets.data[i].key.substr(0, prefix.size()) == prefix) {
			output.push_back(string(assets.data[i].key.substr(prefix.size(), assets.data[i].key.size() - prefix.size())));
		}
	}
	
	return output;
}
#endif

sf::Texture lastFrameScreenshot;
ExtendedWindow game = ExtendedWindow("Platformer", {1280, 720}, 60, false, false, 0.67);	
SoundContainer sounds = SoundContainer();
MusicContainer musics = MusicContainer();
SpriteContainer sprites = SpriteContainer();
TextContainer texts = TextContainer();
StopwatchContainer istopwatches = StopwatchContainer<long long>();
StopwatchContainer fstopwatches = StopwatchContainer<float>();
TextureContainer textures = TextureContainer();
SoundBufferContainer sound_buffers = SoundBufferContainer();
FontContainer fonts = FontContainer();
TextureFlipbookContainer texture_flipbooks = TextureFlipbookContainer();
SoundListContainer sound_lists = SoundListContainer();

namespace Omit {
	const short Screenshot = 1;
	const short Sounds = 2;
	const short Musics = 3;
	const short Sprites = 4;
	const short Texts = 5;
	const short IStopwatches = 6;
	const short FStopwatches = 7;
	const short Textures = 8;
	const short SoundBuffers = 9;
	const short Fonts = 10;
	const short TextureFlipbooks = 11;
	const short SoundLists = 12;
}
bool clearcondition(const vector<short>& omitValues, const short& inputCondition) {
	return !count(omitValues.begin(), omitValues.end(), inputCondition) > 0;
}
void clearall(const vector<short>& omitValues = vector<short>(0)) {
	if (clearcondition(omitValues, Omit::Screenshot)) {
		lastFrameScreenshot = game.screenshot();
	}
	if (clearcondition(omitValues, Omit::Sounds)) {
		sounds.clear();
	}
	if (clearcondition(omitValues, Omit::Musics)) {
		musics.clear();
	}
	if (clearcondition(omitValues, Omit::Sprites)) {
		sprites.clear();
	}
	if (clearcondition(omitValues, Omit::Texts)) {
		texts.clear();
	}
	if (clearcondition(omitValues, Omit::IStopwatches)) {
		istopwatches.clear();
	}
	if (clearcondition(omitValues, Omit::FStopwatches)) {
		fstopwatches.clear();
	}
	if (clearcondition(omitValues, Omit::Textures)) {
		textures.clear();
	}
	if (clearcondition(omitValues, Omit::SoundBuffers)) {
		sound_buffers.clear();
	}
	if (clearcondition(omitValues, Omit::Fonts)) {
		fonts.clear();
	}
	if (clearcondition(omitValues, Omit::TextureFlipbooks)) {
		texture_flipbooks.clear();
	}
	if (clearcondition(omitValues, Omit::SoundLists)) {
		sound_lists.clear();
	}
	return;
}

TextureContainer& loadAllTextures(TextureContainer& inputTextureContainer, const vector<vector<string>>& inputTextures) {
	for (size_t i = 0; i < inputTextures.size(); ++i) {
		inputTextureContainer.loadFromMemory(inputTextures[i][0], assets[inputTextures[i][1]].data(), assets[inputTextures[i][1]].size());
	}
	return inputTextureContainer;
}
SoundBufferContainer& loadAllSoundBuffers(SoundBufferContainer& inputSoundBufferContainer, const vector<vector<string>>& inputSoundBuffers) {
	for (size_t i = 0; i < inputSoundBuffers.size(); ++i) {
		inputSoundBufferContainer.loadFromMemory(inputSoundBuffers[i][0], assets[inputSoundBuffers[i][1]].data(), assets[inputSoundBuffers[i][1]].size());
	}
	return inputSoundBufferContainer;
}
FontContainer& loadAllFonts(FontContainer& inputFontContainer, const vector<vector<string>>& inputFonts) {
	for (size_t i = 0; i < inputFonts.size(); ++i) {
		inputFontContainer.openFromMemory(inputFonts[i][0], assets[inputFonts[i][1]].data(), assets[inputFonts[i][1]].size());
	}
	return inputFontContainer;
}

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

struct ViewPort {
	private:
		double __SIZE;
	public:
		Vec2 pos;
		Vec2& position = pos;
		const double& size = __SIZE;
		
		double getSize() {
			return __SIZE;
		}
		ViewPort& setSize(const double& inputSize) {
			__SIZE = inputSize * (inputSize > 0.0);
			return *this;
		}
		ViewPort& setSizeToWidth(const double& inputSize, const sf::Vector2f& resolution = {1.0f, 1.0f}) {
			//  Aspect ratio is inverted so a division step can be skipped and multiplication can be used instead (faster)
			const double inverseAspectRatio = resolution.y/resolution.x;
			if (resolution.x == 0.0) {
				__SIZE = 0;
				return *this;
			}
			__SIZE = inputSize;
			__SIZE *= inverseAspectRatio < 1.0 ? inverseAspectRatio : 1.0;
			return *this;
		}
		ViewPort& setSizeToHeight(const double& inputSize, const sf::Vector2f& resolution = {1.0f, 1.0f}) {
			const double aspectRatio = resolution.x/resolution.y;
			if (resolution.y == 0.0) {
				__SIZE = 0;
				return *this;
			}
			__SIZE = inputSize;
			__SIZE *= aspectRatio < 1.0 ? aspectRatio : 1.0;
			return *this;
		}
		ViewPort& setSizeToFit(const double& inputSize, const sf::Vector2f& resolution = {1.0f, 1.0f}) {
			__SIZE = inputSize;
			return *this;
		}
		ViewPort& setSizeToFill(const double& inputSize, const sf::Vector2f& resolution = {1.0f, 1.0f}) {
			const double aspectRatio = resolution.x/resolution.y;
			if (resolution.y == 0.0) {
				__SIZE = 0;
				return *this;
			}
			__SIZE = inputSize;
			if (aspectRatio < 1.0) {
				__SIZE /= aspectRatio;
			} else  {
				__SIZE *= aspectRatio;
			}
			return *this;
		}
		Vec2 getPerceivedDimensions(const Vec2& resolution = {1.0, 1.0}) const {
			const double aspectRatio = resolution.x/resolution.y;
			return Vec2(__SIZE, __SIZE/aspectRatio);
		}
		
		ViewPort(const double& inputSize = 10, const Vec2& inputPos = {0.0, 0.0}) : pos(inputPos) {
			setSize(inputSize);
		}
		
		template <typename ExtendedDrawable>
		ViewPort& setInViewport(ExtendedWindow& window, ExtendedDrawable& drawable, const Vec2& drawablePos, const Vec2& drawableScale = {1.0, 1.0}) {
			//  Takes the size as the width of the smallest dimension; that's why setSizeToFit() just sets to input			
			const double aspectRatio = window.resolution.x*1.0/window.resolution.y;
			const Vec2 viewDimensions = {__SIZE, __SIZE/aspectRatio};
			const Vec2 pixelsPerMeter = {window.resolution.x/viewDimensions.x, window.resolution.y/viewDimensions.y};
			const Vec2 newScale = drawableScale*pixelsPerMeter/drawable.getLocalBounds().size;
			const Vec2 newOffset = (drawablePos - pos)/viewDimensions;
			//  SFML uses a left-right x and a top-down y, so y needs to be multiplied by -1 to keep backend math cartesian/standard
			newOffset.y *= -1;
			
			drawable.setScale(newScale).center(window).offset(window, newOffset);
			
			return *this;
		}
};

struct KeyBind {
	sf::Keyboard::Key up;
	sf::Keyboard::Key left;
	sf::Keyboard::Key down;
	sf::Keyboard::Key right;
	sf::Keyboard::Key jump;
	sf::Keyboard::Key sprint;
	
	array<bool, 6> getInputBool(ExtendedWindow& window) const {
		return {
			game.pollForKey(up),
			game.pollForKey(left),
			game.pollForKey(down),
			game.pollForKey(right),
			game.pollForKey(jump),
			game.pollForKey(sprint)
		};
	}
};
KeyBind defaultKeyBinds{sf::Keyboard::Key::W, sf::Keyboard::Key::A, sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::Space, sf::Keyboard::Key::LShift};

class Entity {
	protected:
		bool __UP = false;
		bool __UP_TRIGGERED = false;
		bool __LEFT = false;
		bool __LEFT_TRIGGERED = false;
		bool __DOWN = false;
		bool __DOWN_TRIGGERED = false;
		bool __RIGHT = false;
		bool __RIGHT_TRIGGERED = false;
		bool __JUMP = false;
		bool __JUMP_TRIGGERED = false;
		bool __SPRINT = false;
		bool __SPRINT_TRIGGERED = false;
		bool __ON_GROUND = false;
		bool __ON_GROUND_TRIGGERED = false;
		bool __IS_JUMPING = false;
		bool __IS_JUMPING_TRIGGERED = false;
		bool __IS_SKIDDING = false;
		bool __IS_SKIDDING_TRIGGERED = false;
		size_t __JUMP_FRAMES = 0;
		
		double maxSpeed = 0.0;
	public:
		const bool& up = __UP;
		const bool& left = __LEFT;
		const bool& down = __DOWN;
		const bool& right = __RIGHT;
		const bool& jump = __JUMP;
		const bool& sprint = __SPRINT;
		
		const bool& up_triggered = __UP_TRIGGERED;
		const bool& left_triggered = __LEFT_TRIGGERED;
		const bool& down_triggered = __DOWN_TRIGGERED;
		const bool& right_triggered = __RIGHT_TRIGGERED;
		const bool& jump_triggered = __JUMP_TRIGGERED;
		const bool& sprint_triggered = __SPRINT_TRIGGERED;
		
		const bool& onGround = __ON_GROUND;
		const bool& isJumping = __IS_JUMPING;
		const size_t& jumpFrames = __JUMP_FRAMES;
		
		const bool& on_ground_triggered = __ON_GROUND_TRIGGERED;
		const bool& is_jumping_triggered = __IS_JUMPING_TRIGGERED;
		
		const bool& isSkidding = __IS_SKIDDING;
		const bool& is_skidding_triggered = __IS_SKIDDING_TRIGGERED;
		
		Vec2 hitbox;
		Vec2 acceleration_const;
		Vec2 acceleration = {0.0, 0.0};
		Vec2 velocity = {0.0, 0.0};
		Vec2 position;
		bool snapToSpeed = false;
		
		double accelerationConstYJumpingMultiplier = 1.0;
		
		double frictionCoefficient;
		double frictionCoefficientAirMultiplier = 0.0;
		double dragCoefficient;
		double dragCoefficientJumpingMultiplier = 0.1;
		double skidMultiplier = 0.0;
		
		double speed;
		double sprintSpeedMultiplier = 2;
		
		double jumpForce;
		double jumpForceSprintingMultiplier = 1.15;
		size_t maxJumpFrames = 0;
		bool holdToJump = true;
	
		std::array<bool, 6> constInput;
	
		Entity& receiveInput(const std::array<bool, 6>& booleans = std::array<bool, 6>()) {
			__UP_TRIGGERED = false;
			__LEFT_TRIGGERED = false;
			__DOWN_TRIGGERED = false;
			__RIGHT_TRIGGERED = false;
			__JUMP_TRIGGERED = false;
			__SPRINT_TRIGGERED = false;
			
			if (booleans[0]) {
				if (!__UP) {
					__UP_TRIGGERED = true;
				}
				__UP = true;
			} else {
				__UP = false;
			}
			if (booleans[1]) {
				if (!__LEFT) {
					__LEFT_TRIGGERED = true;
				}
				__LEFT = true;
			} else {
				__LEFT = false;
			}
			if (booleans[2]) {
				if (!__DOWN) {
					__DOWN_TRIGGERED = true;
				}
				__DOWN = true;
			} else {
				__DOWN = false;
			}
			if (booleans[3]) {
				if (!__RIGHT) {
					__RIGHT_TRIGGERED = true;
				}
				__RIGHT = true;
			} else {
				__RIGHT = false;
			}
			if (booleans[4]) {
				if (!__JUMP) {
					__JUMP_TRIGGERED = true;
				}
				__JUMP = true;
			} else {
				__JUMP = false;
			}
			if (booleans[5]) {
				if (!__SPRINT) {
					__SPRINT_TRIGGERED = true;
				}
				__SPRINT = true;
			} else {
				__SPRINT = false;
			}
			return *this;
		}
		Entity& receiveInput() {
			return receiveInput(constInput);
		}
		Entity& receiveInput(ExtendedWindow& window, const KeyBind& inputKeyBinds) {
			return receiveInput(inputKeyBinds.getInputBool(window));
		}
		
		
			
		Entity& tickPhysics(const size_t& TPS) {
			__ON_GROUND_TRIGGERED = false;
			__IS_JUMPING_TRIGGERED = false;
			
			
			if (jump_triggered) {
				__JUMP_FRAMES = maxJumpFrames;
			} else if (__JUMP_FRAMES > 0) {
				--__JUMP_FRAMES;
			}
			
			
			maxSpeed = speed * (sprint ? sprintSpeedMultiplier : 1.0);
			
			
			if (jump) {
				if (onGround && (holdToJump || jump_triggered || jumpFrames != 0)) {
					__IS_JUMPING_TRIGGERED = true;
					__IS_JUMPING = true;
					__ON_GROUND = false;
					velocity.y += jumpForce * (velocity.x_abs() > speed ? jumpForceSprintingMultiplier : 1.0);
				}
			} else {
				__IS_JUMPING = false;
			}
			
			
			__IS_SKIDDING_TRIGGERED = false;
			if (onGround && ((left && !right && velocity.x > speed*0.8) || (right && !left && velocity.x < -speed*0.8))) {
				if (!__IS_SKIDDING) {
					__IS_SKIDDING_TRIGGERED = true;
				}
				__IS_SKIDDING = true;
			} else {
				__IS_SKIDDING = false;
			}
			
			
			if (!snapToSpeed || velocity.x_abs() > maxSpeed) {
				if (left && !right && velocity.x > -maxSpeed) {
					acceleration.x -= (isSkidding ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(onGround ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
				if (right && !left && velocity.x < maxSpeed) {
					acceleration.x += (isSkidding ? 1.0 - skidMultiplier : 1.0)*maxSpeed*(onGround ? (velocity.x_abs() > speed ? 2.2 : 1.8) : velocity.x_abs() > speed ? 0.7 : 1.6);
				}
			} else {
				velocity.x = 0.0;
				if (left && !right) {
					velocity.x = -maxSpeed;
				}
				if (right && !left) {
					velocity.x = maxSpeed;
				}
			}
			
			
			
			if (isJumping && velocity.y > 0) {
				acceleration.y -= (1.0 - accelerationConstYJumpingMultiplier)*acceleration_const.y;
			}
			
			
			velocity += acceleration/TPS;
			
			
			velocity.x *= exp(-frictionCoefficient*(onGround ? 1.0 : frictionCoefficientAirMultiplier)/TPS);
			velocity.y *= exp(-dragCoefficient*(isJumping && velocity.y > 0 ? dragCoefficientJumpingMultiplier : 1.0)/TPS);
			
			position += velocity/TPS;
			
			acceleration = acceleration_const;
			
			
			const double GROUND_HEIGHT = 0.7;
			if (position.y < GROUND_HEIGHT + hitbox.y/2) {
				position.y = GROUND_HEIGHT + hitbox.y/2;
				velocity.y = 0.0;
				if (!__ON_GROUND) {
					__ON_GROUND_TRIGGERED = true;
				}
				__ON_GROUND = true;
			}
			
			
			return *this;
		}
	
		Entity(
			const Vec2& inputPosition = {0.0, 0.0},
			const Vec2& inputHitbox = {1.0, 1.0},
			const Vec2& inputAccelerationConst = {0.0, -36.0},
			const double& inputSpeed = 8,
			const double& inputJumpForce = 8,
			const double& inputFrictionCoefficient = 2.0,
			const double& inputDragCoefficient = 2
		) :
			position(inputPosition),
			hitbox(inputHitbox),
			acceleration_const(inputAccelerationConst),
			speed(inputSpeed),
			jumpForce(inputJumpForce),
			frictionCoefficient(inputFrictionCoefficient),
			dragCoefficient(inputDragCoefficient)
		{};
};