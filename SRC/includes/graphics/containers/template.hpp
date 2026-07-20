template <typename Element_c>
class TaggableElement {
	protected:
		inline Element_c& this_dref() {
			return static_cast<Element_c&>(*this);
		}
		inline const Element_c& this_dref() const {
			return static_cast<const Element_c&>(*this);
		}
	public:
		unordered_set<string> tag;
		Element_c& tag_add(const string& inputTag) {
			if (count(tag.begin(), tag.end(), inputTag) <= 0) {
				tag.insert(inputTag);
			}
			return this_dref();
		}
		Element_c& tag_remove(const string& inputTag) {
			if (count(tag.begin(), tag.end(), inputTag) <= 0) {
				tag.erase(inputTag);
			}
			return this_dref();
		}
		Element_c& clear_tags() {
			tag = unordered_set<string>();
			return this_dref();
		}
		inline bool tag_exists(const string& inputTag) const {
			return count(tag.begin(), tag.end(), inputTag) > 0;
		}
		vector<string> get_tags() const {
			vector<string> outputVector = vector<string>(tag.begin(), tag.end());
			sort(outputVector.begin(), outputVector.end());
			return outputVector;
		}
};
template <typename Container_c, typename Element_c>
class TaggableContainer {
	protected:
		inline Container_c& this_dref() {
			return static_cast<Container_c&>(*this);
		}
		inline const Container_c& this_dref() const {
			return static_cast<const Container_c&>(*this);
		}
	public:
		unordered_map<string, Element_c> taggables;
		Container_c& remove(const string& inputID) {
			this_dref().taggables.erase(inputID);
			return this_dref();
		}
		bool exists(const string& inputID) {
			return this_dref().taggables.count(inputID) != 0;
		}
		Container_c& clear() {
			this_dref().taggables = unordered_map<string, Element_c>();
			return this_dref();
		}
		
		vector<string> get_ids_with_all_tags(const vector<string>& inputTags = vector<string>()) const {
			vector<string> outputIDs;
			for (const auto& pair : this_dref().taggables) {
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
			for (const auto& pair : this_dref().taggables) {
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
			for (const auto& pair : this_dref().taggables) {
				if (pair.second.tag_exists(inputTag)) {
					outputIDs.push_back(pair.first);
				}
			}
			return outputIDs;
		}
		vector<string> get_ids_without_all_tags(const vector<string>& inputTags = vector<string>()) const {
			vector<string> outputIDs;
			for (const auto& pair : this_dref().taggables) {
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
			for (const auto& pair : this_dref().taggables) {
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
			for (const auto& pair : this_dref().taggables) {
				if (!pair.second.tag_exists(inputTag)) {
					outputIDs.push_back(pair.first);
				}
			}
			return outputIDs;
		}
};

template <typename Drawable_c, typename Container_c, typename Element_c>
class DrawableElement : public TaggableElement<Element_c> {
	protected:
		inline Element_c& this_dref() {
			return static_cast<Element_c&>(*this);
		}
		inline const Element_c& this_dref() const {
			return static_cast<const Element_c&>(*this);
		}
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
		virtual inline Element_c& setPosition(const sf::Vector2f& inputPosition) {
			drawable().setPosition(inputPosition);
			return this_dref();
		}
		Element_c& updateOpacity() {
			opacity *= opacity >= 0.0;
			opacity = (opacity >= 1.0 ? 1.0 : opacity);
			sf::Color drawableColor = drawable().getColor();
			drawableColor.a = static_cast<uint8_t>(opacity * 255.0 * !hidden);
			drawable().setColor(drawableColor);
			return this_dref();
		}
		bool mouseHovering(const ExtendedWindow& windowContainer, const bool& focusEnforced = true, const bool& obstructionEnforced = true, const bool& visibilityEnforced = true) const {
			if (windowContainer.window && (!focusEnforced || windowContainer.window->hasFocus()) && (!obstructionEnforced || (!parentContainer || isnan(parentContainer->next_above(z)))) && (!visibilityEnforced || !hidden)) {
				return drawable().getGlobalBounds().contains(windowContainer.window->mapPixelToCoords(sf::Mouse::getPosition(*windowContainer.window)));
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
			this_dref().updateOpacity();
			return this_dref();
		}
		Element_c& unhide() {
			hidden = false;
			this_dref().updateOpacity();
			return this_dref();
		}
		Element_c& setVisibility(const bool& inputVisibility) {
			hidden = !inputVisibility;
			this_dref().updateOpacity();
			return this_dref();
		}
		inline float getOpacity() const {
			return opacity;
		}
		Element_c& setOpacity(const float& inputOpacity = 1.0f) {
			opacity = inputOpacity;
			this_dref().updateOpacity();
			return this_dref();
		}
		sf::Vector2f getNormalizedPosition(const ExtendedWindow& windowContainer, sf::Vector2f offset = sf::Vector2f(), bool useNormalizedPosition = true) const {
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
		sf::Vector2f getDimensions(const ExtendedWindow& windowContainer) const {
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
			return this_dref();
		}
		Element_c& resetShader() {
			shader = nullptr;
			return this_dref();
		}
		template <typename referenceT>
		Element_c& center(const referenceT& referenceDrawable) {
			const sf::FloatRect boundsA = drawable().getGlobalBounds();
			const sf::FloatRect boundsB = referenceDrawable.getGlobalBounds();
			setPosition(sf::Vector2f({boundsB.position.x + (boundsB.size.x - boundsA.size.x)/2.0f, boundsB.position.y + (boundsB.size.y - boundsA.size.y)/2.0f}));
			return this_dref();
		}
		template <typename referenceT>
		Element_c& offset(const referenceT& referenceDrawable, const sf::Vector2f& inputOffset) {
			const sf::FloatRect boundsA = drawable().getGlobalBounds();
			const sf::FloatRect boundsB = referenceDrawable.getGlobalBounds();
			setPosition(sf::Vector2f({boundsA.position.x + boundsB.size.x*inputOffset.x, boundsA.position.y + boundsB.size.y*inputOffset.y}));
			return this_dref();
		}
		Element_c& offset(const sf::Vector2f& inputSize, const sf::Vector2f& inputOffset) {
			const sf::FloatRect boundsA = drawable().getGlobalBounds();
			setPosition(sf::Vector2f({boundsA.position.x + inputSize.x*inputOffset.x, boundsA.position.y + inputSize.y*inputOffset.y}));
			return this_dref();
		}
		Element_c& offset(const sf::Vector2f& inputOffset, const bool& useGlobalContext = true) {
			const sf::FloatRect bounds = drawable().getGlobalBounds();
			if (useGlobalContext) {
				setPosition(sf::Vector2f({bounds.position.x + bounds.size.x*inputOffset.x, bounds.position.y + bounds.size.y*inputOffset.y}));
			} else {
				setPosition(sf::Vector2f({bounds.position.x + inputOffset.x, bounds.position.y + inputOffset.y}));
			}
			return this_dref();
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
			return this_dref();
		}
		Element_c& multiply(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			multiply({inputScale, inputScale}, alignDirection);
			return this_dref();
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
			return this_dref();
		}		
		Element_c& setScale(const float& inputScale, const AlignDirection& alignDirection = Align::None) {
			setScale(sf::Vector2f({inputScale, inputScale}), alignDirection);							
			return this_dref();
		}
		Element_c& resetScale(const AlignDirection& alignDirection = Align::None) {
			setScale(sf::Vector2f({1.0f, 1.0f}), alignDirection);							
			return this_dref();
		}
		Element_c& resizeToFit(const sf::Vector2f& referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			float sizeMultiplier;
			
			const sf::FloatRect boundsAGlobal = getGlobalBounds();
			const sf::Vector2f boundsAScale = getScale();
			sf::FloatRect boundsA = useGlobalContext ? boundsAGlobal : this_dref().getLocalBounds();
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
			return this_dref();
		}
		Element_c& resizeToFill(const sf::Vector2f& referenceBox, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			float sizeMultiplier;
			
			const sf::FloatRect boundsAGlobal = getGlobalBounds();
			const sf::Vector2f boundsAScale = getScale();
			
			sf::FloatRect boundsA = useGlobalContext ? boundsAGlobal : this_dref().getLocalBounds()();
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
			return this_dref();
		}
		template <typename referenceT>
		Element_c& resizeToFit(const referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseGlobalContext = true) {
			sf::FloatRect boundsB = useGlobalContext ? referenceDrawable.getGlobalBounds() : referenceDrawable.getLocalBounds();
			const sf::Vector2f boundsBScale = referenceDrawable.getScale();
			if (!referenceUseGlobalContext) {
				boundsB.size = sf::Vector2f({boundsB.size.x * boundsBScale.x, boundsB.size.y * boundsBScale.y});
			}
			resizeToFit(boundsB.size, alignDirection, useGlobalContext);
			return this_dref();
		}
		template <typename referenceT>
		Element_c& resizeToFill(const referenceT& referenceDrawable, const AlignDirection& alignDirection = Align::None, const bool& useGlobalContext = true, const bool& referenceUseGlobalContext = true) {
			sf::FloatRect boundsB = useGlobalContext ? referenceDrawable.getGlobalBounds() : referenceDrawable.getLocalBounds();
			const sf::Vector2u boundsBScale = referenceDrawable.getScale();
			if (!referenceUseGlobalContext) {
				boundsB.size = sf::Vector2f({boundsB.size.x * boundsBScale.x, boundsB.size.y * boundsBScale.y});
			}
			resizeToFill(boundsB.size, alignDirection, useGlobalContext);
			return this_dref();
		}
		Element_c& align(const AlignDirection& alignDirection = Align::None) {
			const float xDirection = (alignDirection.movesRight ? 0.5f : (alignDirection.movesLeft ? -0.5f : 0.0f));
			const float yDirection = (alignDirection.movesBottom ? 0.5f : (alignDirection.movesTop ? -0.5f : 0.0f));
			
			const sf::FloatRect bounds = getGlobalBounds();
			
			setPosition(sf::Vector2f({
				bounds.position.x + bounds.size.x * xDirection,
				bounds.position.y + bounds.size.y * yDirection
			}));
			return this_dref();
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
			
			return this_dref();
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
		DrawableElement(const DrawableElement& other) : z(other.z), d(other.d), parentContainer(other.parentContainer), shader(other.shader), hidden(other.hidden), opacity(other.opacity) {};
		DrawableElement(DrawableElement&& other) : z(other.z), d(other.d), parentContainer(other.parentContainer), shader(other.shader), hidden(other.hidden), opacity(other.opacity) {};
		DrawableElement& operator=(const DrawableElement& other) {
			z = other.z;
			d = other.d;
			parentContainer = other.parentContainer;
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			return this_dref();
		}
		DrawableElement& operator=(DrawableElement&& other) {
			z = other.z;
			d = other.d;
			parentContainer = other.parentContainer;
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			return this_dref();
		};
};
template <typename Drawable_c, typename Container_c, typename Element_c>
class DrawableContainer : public TaggableContainer<Container_c, Element_c> {
	protected:
		inline Container_c& this_dref() {
			return static_cast<Container_c&>(*this);
		}
		inline const Container_c& this_dref() const {
			return static_cast<const Container_c&>(*this);
		}
	public:
		float initialSizeMultiplier;
		
		inline unordered_map<string, Element_c>& extended_drawable() {
			return this_dref().taggables;
		}
		inline const unordered_map<string, Element_c>& extended_drawable() const {
			return this_dref().taggables;
		}
		
		inline Container_c& setMultiplier(float inputInitialSizeMultiplier) {
			initialSizeMultiplier = inputInitialSizeMultiplier;
			return this_dref();
		}
		
		inline float getMultiplier() const {
			return initialSizeMultiplier;
		}
		
		template <typename dConstructorT>
		Element_c& add(const string& inputID, dConstructorT& inputDConstructor, const double& inputZ = 0) {
			extended_drawable().insert_or_assign(inputID, Element_c(&this_dref(), inputDConstructor, inputZ));
			extended_drawable().at(inputID).multiply(initialSizeMultiplier, Align::TopLeft);
			return extended_drawable().at(inputID);
		}
		
		inline Container_c& remove(const string& inputID) {
			extended_drawable().erase(inputID);
			return this_dref();
		}
		
		inline bool exists(const string& inputID) const {
			return extended_drawable().count(inputID) != 0;
		}
		
		inline Container_c& clear() {
			extended_drawable() = unordered_map<string, Element_c>();
			return this_dref();
		}
		
		double highest() const {
			double currentValue = nan("");
			for (pair<string, Element_c> currentDrawable : extended_drawable()) {
				if (isnan(currentValue) || currentDrawable.second.z > currentValue) {
					currentValue = currentDrawable.second.z;
				}
			}
			return currentValue;
		}
		
		double lowest() const {
			double currentValue = nan("");
			for (std::pair<string, Element_c> currentDrawable : extended_drawable()) {
				if (isnan(currentValue) || currentDrawable.second.z < currentValue) {
					currentValue = currentDrawable.second.z;
				}
			}
			return currentValue;
		}
		
		vector<double> all() const {
			vector<double> outputZ;
			for (pair<string, Element_c> currentDrawable : extended_drawable()) {
				outputZ.push_back(currentDrawable.second.z);
			}
			return outputZ;
		}
		
		double next_above(const double& inputZ, const double& visibilityEnforced = true) const {
			double highestZ = highest();
			bool aboveFound = false;
			for (pair<string, Element_c> currentDrawable : extended_drawable()) {
				if (currentDrawable.second.z > inputZ && currentDrawable.second.z < highestZ && (!visibilityEnforced || !currentDrawable.second.hidden)) {
					highestZ = currentDrawable.second.z;
					aboveFound = true;
				}
			}
			if (aboveFound) {
				return highestZ;
			} else {
				return nan("");
			}
		}
		
		double next_below(const double& inputZ, const double& visibilityEnforced = true) const {
			double lowestZ = lowest();
			bool belowFound = false;
			for (pair<string, Element_c> currentDrawable : extended_drawable()) {
				if (currentDrawable.second.z < inputZ && currentDrawable.second.z > lowestZ && (!visibilityEnforced || !currentDrawable.second.hidden)) {
					lowestZ = currentDrawable.second.z;
					belowFound = true;
				}
			}
			if (belowFound) {
				return lowestZ;
			} else {
				return nan("");
			}
		}
		
		double next_closest(const double& inputZ, const bool& round_down = false, const double& visibilityEnforced = true) const {
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
		
		vector<string> at(const double& inputZ) const {
			vector<string> outputIDs;
			for (pair<string, Element_c> currentDrawable : extended_drawable()) {
				if (currentDrawable.second.z == inputZ) {
					outputIDs.push_back(currentDrawable.first);
				}
			}
			return outputIDs;
		}
		
		inline static bool sortCondition(const Element_c* inputDrawableA, const Element_c* inputDrawableB) {
			return inputDrawableA->z < inputDrawableB->z;
		}
		
		vector<Drawable_c> toVector() {
			vector<const Element_c*> extendedDrawables;
			extendedDrawables.reserve(extended_drawable().size());
			for (const pair<const string&, const Element_c&> currentDrawable : extended_drawable()) {
				extendedDrawables.push_back(&extended_drawable().at(currentDrawable.first));
			}
			sort(extendedDrawables.begin(), extendedDrawables.end(), sortCondition);
			vector<Drawable_c> outputDrawables;
			outputDrawables.reserve(extendedDrawables.size());
			for (const Element_c* currentDrawable : extendedDrawables) {
				outputDrawables.push_back(currentDrawable->d);
			}
			return outputDrawables;
		}
		
		vector<sf::Shader*> getShaderVector() {
			vector<const Element_c*> extendedDrawables;
			extendedDrawables.reserve(extended_drawable().size());
			for (const pair<const string&, const Element_c&> currentDrawable : extended_drawable()) {
				extendedDrawables.push_back(&extended_drawable().at(currentDrawable.first));
			}
			sort(extendedDrawables.begin(), extendedDrawables.end(), sortCondition);
			vector<sf::Shader*> outputShaders;
			outputShaders.reserve(extendedDrawables.size());
			for (const Element_c* currentDrawable : extendedDrawables) {
				outputShaders.push_back(currentDrawable->shader);
			}
			return outputShaders;
		}
		
		inline Element_c& operator[](const string& inputID) {
			return extended_drawable().at(inputID);
		}
		
		inline const Element_c& operator[](const string& inputID) const {
			return extended_drawable().at(inputID);
		}
		
		DrawableContainer(float inputInitialSizeMultiplier = 1.0) : initialSizeMultiplier(inputInitialSizeMultiplier) {}
};

template <typename Audible_c, typename Container_c, typename Element_c>
class AudibleElement : public TaggableElement<Element_c> {
	protected:
		inline Element_c& this_dref() {
			return static_cast<Element_c&>(*this);
		}
		inline const Element_c& this_dref() const {
			return static_cast<const Element_c&>(*this);
		}
		inline virtual Audible_c& audible() = 0;
		inline const virtual Audible_c& audible() const = 0;
		bool audibleValid() const = 0;
	public:
		
	
};
template <typename Audible_c, typename Container_c, typename Element_c>
class AudibleContainer : public TaggableContainer<Container_c, Element_c> {
	protected:
		inline Container_c& this_dref() {
			return static_cast<Container_c&>(*this);
		}
		inline const Container_c& this_dref() const {
			return static_cast<const Container_c&>(*this);
		}
	public:
		
};