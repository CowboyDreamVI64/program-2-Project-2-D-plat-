class ExtendedWindow;
class SpriteContainer;
class TextContainer;
class SoundContainer;
class MusicContainer;
template <typename T>
class StopwatchContainer;
class TextureContainer;
class SoundBufferContainer;
class FontContainer;

template <typename Element_c>
class TaggableContainer;
template <typename Element_c>
class TaggableElement {
	public:
		unordered_set<string> tag;
		Element_c& tag_add(const string& inputTag) {
			if (count(tag.begin(), tag.end(), inputTag) <= 0) {
				tag.insert(inputTag);
			}
			return static_cast<Element_c&>(*this);
		}
		Element_c& tag_remove(const string& inputTag) {
			if (count(tag.begin(), tag.end(), inputTag) <= 0) {
				tag.erase(inputTag);
			}
			return static_cast<Element_c&>(*this);
		}
		Element_c& clear_tags() {
			tag = unordered_set<string>();
			return static_cast<Element_c&>(*this);
		}
		bool tag_exists(const string& inputTag) const {
			return count(tag.begin(), tag.end(), inputTag) > 0;
		}
		vector<string> get_tags() const {
			vector<string> outputVector = vector<string>(tag.begin(), tag.end());
			sort(outputVector.begin(), outputVector.end());
			return outputVector;
		}
};
template <typename Element_c>
class TaggableContainer {
	protected:
		unordered_map<string, Element_c>* taggables;
	public:
		vector<string> get_ids_with_all_tags(const vector<string>& inputTags = vector<string>()) const {
			vector<string> outputIDs;
			for (const auto& pair : *taggables) {
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
		vector<string> get_ids_with_any_tags(const vector<string>& inputTags = vector<string>()) const {
			vector<string> outputIDs;
			for (const auto& pair : *taggables) {
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
		vector<string> get_ids_with_tag(const string& inputTag = "") const {
			vector<string> outputIDs;
			for (const auto& pair : *taggables) {
				if (pair.second.tag_exists(inputTag)) {
					outputIDs.push_back(pair.first);
				}
			}
			return outputIDs;
		}
		vector<string> get_ids_without_all_tags(const vector<string>& inputTags = vector<string>()) const {
			vector<string> outputIDs;
			for (const auto& pair : *taggables) {
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
		vector<string> get_ids_without_any_tags(const vector<string>& inputTags = vector<string>()) const {
			vector<string> outputIDs;
			for (const auto& pair : *taggables) {
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
		vector<string> get_ids_without_tag(const string& inputTag = "") const {
			vector<string> outputIDs;
			for (const auto& pair : *taggables) {
				if (!pair.second.tag_exists(inputTag)) {
					outputIDs.push_back(pair.first);
				}
			}
			return outputIDs;
		}
};

template <typename Drawable_c, typename Container_c, typename Element_c>
class DrawableElement {
	public:
		Container_c* parentContainer;
		Drawable_c d;
		sf::Shader* shader = nullptr;
		double z;
		bool hidden = false;
		float opacity = 1.0;
		
		inline Drawable_c& drawable() {
			return d;
		}
		inline const Drawable_c& drawable() const {
			return d;
		}
		virtual inline Element_c& setPosition(sf::Vector2f inputPosition) {
			drawable().setPosition(inputPosition);
			return static_cast<Element_c&>(*this);
		}
		Element_c& updateOpacity() {
			opacity *= opacity >= 0.0;
			opacity = (opacity >= 1.0 ? 1.0 : opacity);
			sf::Color drawableColor = drawable().getColor();
			drawableColor.a = static_cast<uint8_t>(opacity * 255.0 * !hidden);
			drawable().setColor(drawableColor);
			return static_cast<Element_c&>(*this);
		}
		bool mouseHovering(const ExtendedWindow& windowContainer, const bool& focusEnforced, const bool& obstructionEnforced, const bool& visibilityEnforced) const {
			if (windowContainer.window && (!focusEnforced || windowContainer.window->hasFocus()) && (!obstructionEnforced || isnan(parentContainer->next_above(z))) && (!visibilityEnforced || !hidden)) {
				return drawable().getGlobalBounds().contains(*windowContainer.window.mapPixelToCoords(sf::Mouse::getPosition(*windowContainer.window)));
			}
			return false;
		}
		sf::FloatRect getGlobalBounds() const {
			return drawable().getGlobalBounds();
		}
		sf::Vector2f getScale() const {
			return drawable().getScale();
		}
		sf::FloatRect getLocalBounds(const bool& getTrueLocalBounds = false) const {
			return drawable().getLocalBounds();
		}
		inline bool isHidden() const {
			return hidden;
		}
		inline bool isVisible() const {
			return !hidden;
		}
		Element_c& hide() {
			hidden = true;
			static_cast<Element_c*>(this)->updateOpacity();
			return static_cast<Element_c&>(*this);
		}
		Element_c& unhide() {
			hidden = false;
			static_cast<Element_c*>(this)->updateOpacity();
			return static_cast<Element_c&>(*this);
		}
		Element_c& setVisibility(const bool& inputVisibility) {
			hidden = !inputVisibility;
			static_cast<Element_c*>(this)->updateOpacity();
			return static_cast<Element_c&>(*this);
		}
		inline float getOpacity() const {
			return opacity;
		}
		Element_c& setOpacity(const float& inputOpacity = 1.0f) {
			opacity = inputOpacity;
			static_cast<Element_c*>(this)->updateOpacity();
			return static_cast<Element_c&>(*this);
		}
		sf::Vector2f getNormalizedPosition(ExtendedWindow& windowContainer, sf::Vector2f offset = sf::Vector2f(), bool useNormalizedPosition = true) const {
			if (windowContainer.window) {
				if (useNormalizedPosition) {
					offset = sf::Vector2f({offset.x + 0.5f, offset.y + 0.5f});
				}
				const sf::FloatRect boundsA = drawable().getGlobalBounds();
				const sf::FloatRect boundsB = windowContainer.getGlobalBounds();
				return sf::Vector2f({(boundsA.position.x - boundsB.position.x + offset.x*boundsA.size.x)/boundsB.size.x - (useNormalizedPosition ? 0.5f : 0.0f), (boundsA.position.y - boundsB.position.y + offset.y*boundsA.size.y)/boundsB.size.y - (useNormalizedPosition ? 0.5f : 0.0f)});
			}
			return sf::Vector2f({nan(""),nan("")});
		}
		sf::Vector2f getDimensions(ExtendedWindow& windowContainer) const {
			if (windowContainer.window) {
				const sf::FloatRect boundsA = drawable().getLocalBounds();
				const sf::Vector2f scaleA = drawable().getScale();
				const sf::FloatRect boundsB = windowContainer.getGlobalBounds();
				return sf::Vector2f({boundsA.size.x*scaleA.x/(1.0f*boundsB.size.x), boundsA.size.y*scaleA.y/(1.0f*boundsB.size.y)});
			}
			return sf::Vector2f({nan(""),nan("")});
		}
		inline bool shaderExists() const {
			return shader != nullptr;
		}
		sf::Shader& getShader() {
			return *shader;
		}
		const sf::Shader& getShader() const {
			return *shader;
		}
		Element_c& setShader(const sf::Shader& inputShader) {
			shader = &inputShader;
			return static_cast<Element_c&>(*this);
		}
		Element_c& resetShader() {
			shader = nullptr;
			return static_cast<Element_c&>(*this);
		}
		template <typename referenceT>
		Element_c& center(referenceT& referenceDrawable) {
			const sf::FloatRect boundsA = drawable().getGlobalBounds();
			const sf::FloatRect boundsB = referenceDrawable.getGlobalBounds();
			setPosition(sf::Vector2f({boundsB.position.x + (boundsB.size.x - boundsA.size.x)/2.0f, boundsB.position.y + (boundsB.size.y - boundsA.size.y)/2.0f}));
			return static_cast<Element_c&>(*this);
		}
		template <typename referenceT>
		Element_c& offset(referenceT& referenceDrawable, const sf::Vector2f& inputOffset) {
			const sf::FloatRect boundsA = drawable().getGlobalBounds();
			const sf::FloatRect boundsB = referenceDrawable.getGlobalBounds();
			setPosition(sf::Vector2f({boundsA.position.x + boundsB.size.x*inputOffset.x, boundsA.position.y + boundsB.size.y*inputOffset.y}));
			return static_cast<Element_c&>(*this);
		}
		Element_c& offset(const sf::Vector2f& inputSize, const sf::Vector2f& inputOffset) {
			const sf::FloatRect boundsA = drawable().getGlobalBounds();
			setPosition(sf::Vector2f({boundsA.position.x + inputSize.x*inputOffset.x, boundsA.position.y + inputSize.y*inputOffset.y}));
			return static_cast<Element_c&>(*this);
		}
		Element_c& offset(const sf::Vector2f& inputOffset, const bool& useGlobalContext = true) {
			const sf::FloatRect bounds = drawable().getGlobalBounds();
			if (useGlobalContext) {
				setPosition(sf::Vector2f({bounds.position.x + bounds.size.x*inputOffset.x, bounds.position.y + bounds.size.y*inputOffset.y}));
			} else {
				setPosition(sf::Vector2f({bounds.position.x + inputOffset.x, bounds.position.y + inputOffset.y}));
			}
			return static_cast<Element_c&>(*this);
		}
		Element_c& multiply(const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			const sf::FloatRect bounds = drawable().getGlobalBounds();
			const sf::Vector2f scale = drawable().getScale();
			
			drawable().setScale({scale.x * inputMultiplier.x, scale.y * inputMultiplier.y});
			setPosition({
				bounds.position.x + 0.5f*bounds.size.x*(1 - inputMultiplier.x) + bounds.size.x*(1 - inputMultiplier.x)*xDirection,
				bounds.position.y + 0.5f*bounds.size.y*(1 - inputMultiplier.y) + bounds.size.y*(1 - inputMultiplier.y)*yDirection
			});						
			return static_cast<Element_c&>(*this);
		}
		Element_c& multiply(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			multiply({inputScale, inputScale}, alignDirection);
			return static_cast<Element_c&>(*this);
		}
		Element_c& setScale(const sf::Vector2f& inputMultiplier, const AlignDirection& alignDirection = Align::None) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			const sf::FloatRect bounds = drawable().getGlobalBounds();
			const sf::Vector2f scale = drawable().getScale();
			
			drawable().setScale(inputMultiplier);
			setPosition({
				bounds.position.x + 0.5f*bounds.size.x*(1 - inputMultiplier.x/scale.x) + bounds.size.x*(1 - inputMultiplier.x/scale.x)*xDirection,
				bounds.position.y + 0.5f*bounds.size.y*(1 - inputMultiplier.y/scale.y) + bounds.size.y*(1 - inputMultiplier.y/scale.y)*yDirection
			});
			return static_cast<Element_c&>(*this);
		}		
		Element_c& setScale(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			setScale(sf::Vector2f({inputScale, inputScale}), alignDirection);							
			return static_cast<Element_c&>(*this);
		}
		Element_c& resetScale(const AlignDirection& alignDirection = Align::None) {
			setScale(sf::Vector2f({1.0f, 1.0f}), alignDirection);							
			return static_cast<Element_c&>(*this);
		}
		Element_c& resizeToFit(sf::Vector2f referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			float sizeMultiplier;
			
			const sf::FloatRect boundsAGlobal = getGlobalBounds();
			const sf::Vector2f boundsAScale = getScale();
			sf::FloatRect boundsA = useGlobalContext ? boundsAGlobal : static_cast<Element_c*>(this)->getLocalBounds();
			if (!useGlobalContext) {
				boundsA.size = sf::Vector2f({boundsA.size.x * boundsAScale.x, boundsA.size.y * boundsAScale.y});
			}
			if (referenceBox.x/boundsA.size.x > referenceBox.y/boundsA.size.y) {
				sizeMultiplier = referenceBox.x/boundsA.size.x;
			} else {
				sizeMultiplier = referenceBox.y/boundsA.size.y;
			}
			
			drawable().setScale(sf::Vector2f({
				boundsAScale.x * sizeMultiplier,
				boundsAScale.y * sizeMultiplier
			}));
			setPosition(sf::Vector2f({
				boundsAGlobal.position.x + 0.5f*boundsAGlobal.size.x*(1 - sizeMultiplier/boundsAScale.x) + boundsAGlobal.size.x*(1 - sizeMultiplier)*xDirection,
				boundsAGlobal.position.y + 0.5f*boundsAGlobal.size.y*(1 - sizeMultiplier/boundsAScale.y) + boundsAGlobal.size.y*(1 - sizeMultiplier)*yDirection
			}));						
			return static_cast<Element_c&>(*this);
		}
		Element_c& resizeToFill(sf::Vector2f referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			float sizeMultiplier;
			
			const sf::FloatRect boundsAGlobal = getGlobalBounds();
			const sf::Vector2f boundsAScale = getScale();
			
			sf::FloatRect boundsA = useGlobalContext ? boundsAGlobal : static_cast<Element_c>(this)->getLocalBounds()();
			if (!useGlobalContext) {
				boundsA.size = sf::Vector2f({boundsA.size.x * boundsAScale.x, boundsA.size.y * boundsAScale.y});
			}
			if (referenceBox.x/boundsA.size.x > referenceBox.y/boundsA.size.y) {
				sizeMultiplier = referenceBox.x/boundsA.size.x;
			} else {
				sizeMultiplier = referenceBox.y/boundsA.size.y;
			}
			
			drawable().setScale(sf::Vector2f({
				boundsAScale.x * sizeMultiplier,
				boundsAScale.y * sizeMultiplier
			}));
			setPosition(sf::Vector2f({
				boundsAGlobal.position.x + 0.5f*boundsAGlobal.size.x*(1 - sizeMultiplier/boundsAScale.x) + boundsAGlobal.size.x*(1 - sizeMultiplier)*xDirection,
				boundsAGlobal.position.y + 0.5f*boundsAGlobal.size.y*(1 - sizeMultiplier/boundsAScale.y) + boundsAGlobal.size.y*(1 - sizeMultiplier)*yDirection
			}));						
			return static_cast<Element_c&>(*this);
		}
		template <typename referenceT>
		Element_c& resizeToFit(referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseGlobalContext = true) {
			sf::FloatRect boundsB = useGlobalContext ? referenceDrawable.getGlobalBounds() : referenceDrawable.getLocalBounds();
			const sf::Vector2f boundsBScale = referenceDrawable.getScale();
			if (!referenceUseGlobalContext) {
				boundsB.size = sf::Vector2f({boundsB.size.x * boundsBScale.x, boundsB.size.y * boundsBScale.y});
			}
			resizeToFit(boundsB.size, alignDirection, useGlobalContext);
			return static_cast<Element_c&>(*this);
		}
		template <typename referenceT>
		Element_c& resizeToFill(referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseGlobalContext = true) {
			sf::FloatRect boundsB = useGlobalContext ? referenceDrawable.getGlobalBounds() : referenceDrawable.getLocalBounds();
			const sf::Vector2u boundsBScale = referenceDrawable.getScale();
			if (!referenceUseGlobalContext) {
				boundsB.size = sf::Vector2f({boundsB.size.x * boundsBScale.x, boundsB.size.y * boundsBScale.y});
			}
			resizeToFill(boundsB.size, alignDirection, useGlobalContext);
			return static_cast<Element_c&>(*this);
		}
		Element_c& align(const AlignDirection& alignDirection = Align::None) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			const sf::FloatRect bounds = getGlobalBounds();
			
			setPosition(sf::Vector2f({
				bounds.position.x + bounds.size.x * xDirection,
				bounds.position.y + bounds.size.y * yDirection
			}));
			return static_cast<Element_c&>(*this);
		}
		Element_c& align(const sf::FloatRect& boundsB, const AlignDirection& anchorSide = Align::None, const AlignDirection& alignDirection = Align::None) {
			float xAnchorDirection;
			float yAnchorDirection;
			
			const sf::FloatRect boundsA = getGlobalBounds();
			
			if (anchorSide.movesHorizontal) {
				xAnchorDirection = (anchorSide.movesRight ? 1.0f : (anchorSide.movesLeft ? 0.0f : 0.5f));
			}
			if (anchorSide.movesVertical) {
				yAnchorDirection = (anchorSide.movesBottom ? 1.0f : (anchorSide.movesTop ? 0.0f : 0.5f));
			}
			const float xAlignDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yAlignDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			setPosition(sf::Vector2f({
				(anchorSide.movesHorizontal ? boundsB.size.x*xAnchorDirection + boundsB.position.x - boundsA.size.x/2.0f : boundsA.position.x) + boundsA.size.x*xAlignDirection,
				(anchorSide.movesVertical ? boundsB.size.y*yAnchorDirection + boundsB.position.y - boundsA.size.y/2.0f : boundsA.position.y) + boundsA.size.y*yAlignDirection
			}));
			
			return static_cast<Element_c&>(*this);
		}
		/*template <typename referenceT>
		Element_c& align(referenceT& referenceDrawable, const AlignDirection& anchorSide = Align::None, const AlignDirection& alignDirection = Align::None) {
			return align(referenceDrawable.getGlobalBounds(), anchorSide, alignDirection);
		}*/
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

		template <typename dConstructorT>
		DrawableElement(Container_c* inputParentContainer, const dConstructorT& inputDConstructor, double inputZ = 0) : z(inputZ), d(inputDConstructor), parentContainer(inputParentContainer) {}
};