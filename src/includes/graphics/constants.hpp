//  --- SFML FUNCTION HELPER CONSTANTS ---
//  
//  These define things like alignment values, alignment mirroring, color channel IDs, and
//  stopwatch directions.
//  
//  - AlignDirection is used in some of the later functions to define which side, corner, or
//    direction a sprite alignment takes place through, so if I wanted to align a sprite A to
//    right side of a sprite B, I could do spriteA.align(spriteB, Align::Left, Align::Right).
//  
//  - If an alignment operation takes two values, then the first value is the alignment point
//    of the destination position, while the second value is the direction to move a moving
//    sprite along AFTER it has been moved to the destination position.
//  
//  - If an alignment operation takes one value, then the alignment point is just the direction
//    to move a sprite along. If only one argument is taken for alignment, then passing
//    Align::BottomLeft will place the top right of the sprite at where the center of the sprite
//    currently is.
//  
//  - The ColorChannel constants are for color-related functions and methods (I will get into them
//    later) so that instead of needing to pass something like setTint(2, 0.5) to set the green
//    intensity of a sprite to 50%, you can type setTint(ColorChannel::Green, 0.5).
//  
//  - The Direction constants is used in stopwatch operations to determine directionality so that 
//    instead of doing something like setTickDirection(true), you can do something like
//    setTickDirection(Direction::Backwards).
//  
//  -------------------------------------------------------------------------------------------------------
//  
//  The AlignDirection class stores details about how a certain direction moves. These values
//  are used in later functions and methods. Alignment directions can also be mirrored horizontally,
//  vertically, and both. The operator ! gets the opposite alignment direction, the operator - mirrors
//  the alignment direction horizontally, and the operator + mirrors the alignment direction vertically.
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
//  These are some AlignDirection constants so that instead of constructing an AlignDirection every
//  time an alignment direction needs to be used, these can be called instead.
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
//  These are the forward-declared AlignDirection mirroring methods for alignment directions.
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
//  This is an enumeration for color channel value constants.
namespace ColorChannel {
	const unsigned short None = 0;
	const unsigned short Red = 1;
	const unsigned short Green = 2;
	const unsigned short Blue = 3;
	const unsigned short Alpha = 4;
	const unsigned short All = 5;
	const unsigned short AllA = 6;
}
//  This is an enumeration for stopwatch direction constants.
namespace Direction {
	const bool& Forward = false;
	const bool& Backward = true;
}