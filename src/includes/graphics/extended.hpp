//  --- EXTENDED FUNCTIONS ---
//  
//  The extended functions are helper functions for color-based extended SFML elements and containers.
//  
//  - getColor() gets the value of an SFML color's channel given the color and the channel. If no channel
//    is provided, the function returns NaN. Else, if something like getColor(inputColor, ColorChannel::Red)
//    is done, the red value of inputColor is got as a range from 0 to 1.
//  
//  [COMMENTS NOT FINISHED YET]
//  
//  -------------------------------------------------------------------------------------------------------
//  
namespace ExtendedFunction {
	//  Takes an input SFML color object and a target color channel and outputs the value of that
	//  color channel
	//  in the color object.
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

	//  Takes an input SFML color and red, green, and blue values, then returns a copy of the color
	//  given those color channel values and maintaining the alpha (transparency) value. This returns
	//  a copy of the color because a copy is required in a helper function used later down the code.
	sf::Color setColor(const sf::Color& inputColor, float inputR = 1.0f, float inputG = 1.0f, float inputB = 1.0f) {
		inputR *= inputR >= 0.0f;
		inputR = inputR >= 1.0f ? 1.0f : inputR;
		inputG *= inputG >= 0.0f;
		inputG = inputG >= 1.0f ? 1.0f : inputG;
		inputB *= inputB >= 0.0f;
		inputB = inputB >= 1.0f ? 1.0f : inputB;
		return sf::Color(static_cast<uint8_t>(inputR*255.0f), static_cast<uint8_t>(inputG*255.0f), static_cast<uint8_t>(inputB*255.0f), inputColor.a);
	}

	//  Takes an input SFML color, a custom referenced opacity, an input tint to apply to the color,
	//  and a target color channel, and outputs either the result color while also modifying the opacity
	//  when possible. The opacity is passed as a reference because this is used as a helper function
	//  for an object later down the code that stores an internal opacity.
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

	//  Does the above, but instead of setting the color channels, it multiplies select channels by the
	//  input. This is important for implementing blending modes like screen.
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

	//  Does the above, but instead of multiplying the color channels, it adds the input to select
	//  channels. This is important for implementing blending modes like linear dodge.
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

	//  Does the above, but it just resets the select color channels.
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
}