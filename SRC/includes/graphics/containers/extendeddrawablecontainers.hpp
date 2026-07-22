class ExtendedSprite : public DrawableElement<sf::Sprite, SpriteContainer, ExtendedSprite> {
	public:
		SpriteContainer*& parentSpriteContainer = parentContainer;
		sf::Sprite& sprite = d;
		
		inline sf::Color getColor() const {
			return sprite.getColor();
		}
		float getColor(const unsigned short inputColorChannel = ColorChannel::None) const {
			return ExtendedFunction::getColor(sprite.getColor(), inputColorChannel);
		}
		inline ExtendedSprite& setColor(float inputR = 1.0f, float inputG = 1.0f, float inputB = 1.0f) {
			sprite.setColor(ExtendedFunction::setColor(sprite.getColor(), inputR, inputG, inputB));
			return updateOpacity();
		}
		inline ExtendedSprite& setColor(const sf::Color& inputColor = sf::Color(255, 255, 255, 255)) {
			sprite.setColor(inputColor);
			opacity = inputColor.a;
			return updateOpacity();
		}
		inline ExtendedSprite& resetColor() {
			sprite.setColor(sf::Color(255, 255, 255, 255));
			opacity = 1.0f;
			return updateOpacity();
		}
		inline ExtendedSprite& setTint(float inputTint, const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::setTint(sprite.getColor(), opacity, inputTint, inputColorChannel));
			return updateOpacity();
		}
		inline ExtendedSprite& multiplyTint(float inputTint = 1.0, const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::multiplyTint(sprite.getColor(), opacity, inputTint, inputColorChannel));
			return updateOpacity();
		}
		inline ExtendedSprite& addTint(float inputTint = 0.0, const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::addTint(sprite.getColor(), opacity, inputTint, inputColorChannel));
			return updateOpacity();
		}
		inline ExtendedSprite& resetTint(const unsigned short inputColorChannel = ColorChannel::All) {
			sprite.setColor(ExtendedFunction::resetTint(sprite.getColor(), opacity, inputColorChannel));
			return updateOpacity();
		}
		ExtendedSprite& setTexture(const sf::Texture& inputTexture, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldSpriteGlobalBounds = sprite.getGlobalBounds();
			sprite.setTexture(inputTexture, true);
			sf::FloatRect newSpriteGlobalBounds = sprite.getGlobalBounds();
			align(oldSpriteGlobalBounds, alignDirection, !alignDirection);
			return *this;
		}
		inline sf::IntRect getTextureRect() const {
			return sprite.getTextureRect();
		}
		sf::FloatRect getNormalTextureRect() const {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			sf::IntRect textureRect = sprite.getTextureRect();
			return sf::FloatRect(sf::Vector2f({textureRect.position.x*1.0f/textureSize.x, textureRect.position.y*1.0f/textureSize.y}), sf::Vector2f({textureRect.size.x*1.0f/textureSize.x, textureRect.size.y*1.0f/textureSize.y}));
		}
		inline sf::Vector2f getNormalTexturePixelSize() const {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			return sf::Vector2f({1.0f/textureSize.x, 1.0f/textureSize.y});
		}
		inline sf::Vector2u getTextureSize() const {
			return sprite.getTexture().getSize();
		}
		ExtendedSprite& setTextureRect(const sf::IntRect& inputRect, const AlignDirection& alignDirection = Align::None, const sf::Vector2i& offset = sf::Vector2i(), const bool& offsetWithRotation = true) {
			sf::FloatRect oldSpriteGlobalBounds = sprite.getGlobalBounds();
			sprite.setTextureRect(inputRect);
			sf::FloatRect newSpriteGlobalBounds = sprite.getGlobalBounds();
			align(oldSpriteGlobalBounds, alignDirection, !alignDirection);
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
		ExtendedSprite& setTextureRect(const sf::FloatRect& inputRect, const AlignDirection& alignDirection = Align::None, const sf::Vector2f& offset = sf::Vector2f()) {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			setTextureRect(sf::IntRect(sf::Vector2i({static_cast<int>(inputRect.position.x*textureSize.x), static_cast<int>(inputRect.position.y*textureSize.y)}), sf::Vector2i({static_cast<int>(inputRect.size.x*textureSize.x), static_cast<int>(inputRect.size.y*textureSize.y)})), alignDirection, sf::Vector2i({static_cast<int>(offset.x*textureSize.x), static_cast<int>(offset.y*textureSize.y)}));
			return *this;
		}
		ExtendedSprite& resetTextureRect(const AlignDirection& alignDirection = Align::None) {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			setTextureRect(sf::IntRect(sf::Vector2i({0, 0}), sf::Vector2i({static_cast<int>(textureSize.x), static_cast<int>(textureSize.y)})), alignDirection);
			return *this;
		}
		inline ExtendedSprite(SpriteContainer* inputParentSpriteContainer, const sf::Texture& inputTexture, double inputZ = 0) : DrawableElement(inputParentSpriteContainer, inputTexture, inputZ) {}
		inline ExtendedSprite(SpriteContainer* inputParentSpriteContainer, sf::Sprite inputSprite, double inputZ = 0) : DrawableElement(inputParentSpriteContainer, inputSprite, inputZ) {}
		
		//  Copy and move stuff since static polymorphism is being stubborn about &sprite
		inline ExtendedSprite(const ExtendedSprite& other) : DrawableElement(other), sprite(d), parentSpriteContainer(parentContainer) {}
		inline ExtendedSprite(ExtendedSprite&& other) : DrawableElement(other), sprite(d), parentSpriteContainer(parentContainer) {}
		inline ExtendedSprite& operator=(const ExtendedSprite& other) noexcept {
			DrawableElement::operator=(other);
			sprite = d;
			parentSpriteContainer = parentContainer;
			return *this;
		}
		inline ExtendedSprite& operator=(ExtendedSprite&& other) noexcept {
			DrawableElement::operator=(other);
			sprite = d;
			parentSpriteContainer = parentContainer;
			return *this;
		}
};
class SpriteContainer : public DrawableContainer<sf::Sprite, SpriteContainer, ExtendedSprite> {
	friend ExtendedSprite;
	
	public:
		unordered_map<string, ExtendedSprite>& extended_sprite;
		
		SpriteContainer(float inputInitialSizeMultiplier = 1.0) : extended_sprite(taggables), DrawableContainer(inputInitialSizeMultiplier) {}
};

class ExtendedText : public DrawableElement<sf::Text, TextContainer, ExtendedText> {
	private:
		bool styleBold = false;
		bool styleItalic = false;
		bool styleUnderlined = false;
	public:
		TextContainer*& parentTextContainer = parentContainer;
		sf::Text& text = d;
		float fill_opacity = 1.0;
		float outline_opacity = 1.0;
		
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
		inline bool getBold() const {
			return styleBold;
		}
		ExtendedText& setBold(const bool& inputBoolean) {
			styleBold = inputBoolean;
			update_style();
			return *this;
		}
		inline bool getItalic() const {
			return styleBold;
		}
		ExtendedText& setItalic(const bool& inputBoolean) {
			styleItalic = inputBoolean;
			update_style();
			return *this;
		}
		inline bool getUnderlined() const {
			return styleUnderlined;
		}
		ExtendedText& setUnderlined(const bool& inputBoolean) {
			styleUnderlined = inputBoolean;
			update_style();
			return *this;
		}
		inline uint32_t getStyle() const {
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
		inline string getString() const {
			return text.getString();
		}
		inline string getText() const {
			return getString();
		}
		inline ExtendedText& setString(const string& inputString = "") {
			text.setString(inputString);
			return *this;
		}
		inline ExtendedText& setText(const string& inputString = "") {
			setString(inputString);
			return *this;
		}
		float getLocalLineLength() const {
			return text.getLineSpacing() * text.getFont().getLineSpacing(text.getCharacterSize());
		}
		float getGlobalLineLength() const {
			return getLocalLineLength() * text.getScale().y;
		}
		sf::Vector2f getTextBoxGlobalPosition() const {
			sf::FloatRect textLocalBounds = text.getLocalBounds();
			sf::FloatRect textGlobalBounds = text.getGlobalBounds();
			return {textGlobalBounds.position.x - textLocalBounds.position.x*textGlobalBounds.size.x/(textLocalBounds.size.x), textGlobalBounds.position.y - textLocalBounds.position.y*textGlobalBounds.size.y/(textLocalBounds.size.y)};
		}
		sf::Vector2f getTextBoxGlobalPositionOffset() const {
			sf::FloatRect textLocalBounds = text.getLocalBounds();
			sf::FloatRect textGlobalBounds = text.getGlobalBounds();
			return {-textLocalBounds.position.x*textGlobalBounds.size.x/(textLocalBounds.size.x), -textLocalBounds.position.y*textGlobalBounds.size.y/(textLocalBounds.size.y)};
		}
		sf::FloatRect getTextBoxGlobalBounds() const {
			sf::FloatRect textGlobalBounds = text.getGlobalBounds();
			sf::Vector2f textBoxPosition = getTextBoxGlobalPosition();
			textGlobalBounds.position = sf::Vector2f({textGlobalBounds.position.x + textBoxPosition.x, textGlobalBounds.position.y + textBoxPosition.y - getGlobalLineLength()});
			textGlobalBounds.size = sf::Vector2f({textGlobalBounds.size.x, getGlobalLineLength()});
			return textGlobalBounds;
		}
		sf::FloatRect getTextLocalBounds() const {
			sf::FloatRect textLocalBounds = text.getLocalBounds();
			textLocalBounds.position = sf::Vector2f({0.0f, 0.0f});
			textLocalBounds.size = sf::Vector2f({textLocalBounds.size.x, getLocalLineLength()});
			return textLocalBounds;
		}
		sf::FloatRect getLocalBounds(const bool& getTrueLocalBounds = false) const {
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
			align(oldTextGlobalBounds, alignDirection, !alignDirection);
			return *this;
		}
		ExtendedText& setCharacterSize(const unsigned int& inputCharacterSize, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldTextGlobalBounds = text.getGlobalBounds();
			text.setCharacterSize(inputCharacterSize);
			sf::FloatRect newTextGlobalBounds = text.getGlobalBounds();
			align(oldTextGlobalBounds, alignDirection, !alignDirection);
			return *this;
		}
		ExtendedText& setLetterSpacing(const float& inputLetterSpacing, const AlignDirection& alignDirection = Align::Center) {
			sf::FloatRect oldTextGlobalBounds = text.getGlobalBounds();
			text.setLetterSpacing(inputLetterSpacing);
			sf::FloatRect newTextGlobalBounds = text.getGlobalBounds();
			align(oldTextGlobalBounds, alignDirection, !alignDirection);
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
			return static_cast<ExtendedText&>(*this);
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
		float getCharacterSizeMultiplierForWidthFit(const float& inputLength) const {
			return 1.0f*inputLength/getGlobalBounds().size.x;
		}
		float getCharacterSizeMultiplierForHeightFit(const float& inputLength) const {
			return 1.0f*inputLength/getGlobalBounds().size.y;
		}
		float getCharacterSizeMultiplierToFit(const sf::Vector2f& inputSize) const {
			sf::FloatRect textBounds = getGlobalBounds();
			float widthMultiplier = 1.0f*inputSize.x/textBounds.size.x;
			float heightMultiplier = 1.0f*inputSize.y/textBounds.size.y;
			return widthMultiplier < heightMultiplier ? widthMultiplier : heightMultiplier;
		}
		float getCharacterSizeMultiplierToFill(const sf::Vector2f& inputSize, const float& inputLength) const {
			sf::FloatRect textBounds = getGlobalBounds();
			float widthMultiplier = 1.0f*inputSize.x/textBounds.size.x;
			float heightMultiplier = 1.0f*inputSize.y/textBounds.size.y;
			return widthMultiplier > heightMultiplier ? widthMultiplier : heightMultiplier;
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierForWidthFit(referenceT& referenceDrawable) const {
			return getCharacterSizeMultiplierForWidthFit(referenceDrawable.getGlobalBounds().size.x);
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierForHeightFit(referenceT& referenceDrawable) const {
			return getCharacterSizeMultiplierForHeightFit(referenceDrawable.getGlobalBounds().size.y);
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierToFit(referenceT& referenceDrawable) const {
			return getCharacterSizeMultiplierToFit(referenceDrawable.getGlobalBounds().size);
		}
		template <typename referenceT>
		float getCharacterSizeMultiplierToFill(referenceT& referenceDrawable) const {
			return getCharacterSizeMultiplierToFill(referenceDrawable.getGlobalBounds().size);
		}
		ExtendedText(TextContainer* inputParentTextContainer, sf::Font& inputFont, double inputZ = 0) : DrawableElement(inputParentTextContainer, inputFont, inputZ) {}
		ExtendedText(TextContainer* inputParentTextContainer, sf::Text inputText, double inputZ = 0) : DrawableElement(inputParentTextContainer, inputText, inputZ) {}
		
		//  Copy and move stuff since static polymorphism is being stubborn about &text
		ExtendedText(const ExtendedText& other) : DrawableElement(other), text(d) {}
		ExtendedText(ExtendedText&& other) : DrawableElement(other), text(d) {}
		ExtendedText& operator=(const ExtendedText& other) noexcept {
			DrawableElement::operator=(other);
			text = d;
			return *this;
		}
		ExtendedText& operator=(ExtendedText&& other) noexcept {
			DrawableElement::operator=(other);
			text = d;
			return *this;
		}
};
class TextContainer : public DrawableContainer<sf::Text, TextContainer, ExtendedText> {
	public:
		unordered_map<string, ExtendedText>& extended_text;
		
		TextContainer(float inputInitialSizeMultiplier = 1.0) : extended_text(taggables), DrawableContainer(inputInitialSizeMultiplier) {}
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