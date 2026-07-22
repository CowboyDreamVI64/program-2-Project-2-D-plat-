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
		
		inline Container_c& erase(const string& inputID) {
			taggables.erase(inputID);
			return this_dref();
		}
		inline Container_c& remove(const string& inputID) {
			taggables.erase(inputID);
			return this_dref();
		}
		inline bool exists(const string& inputID) {
			return taggables.count(inputID) != 0;
		}
		inline Container_c& clear() {
			taggables = unordered_map<string, Element_c>();
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

		inline Element_c& at(const string& inputID) {
			return taggables.at(inputID);
		}
		inline const Element_c& at(const string& inputID) const {
			return taggables.at(inputID);
		}
		inline Element_c& operator[](const string& inputID) {
			return at(inputID);
		}
		inline const Element_c& operator[](const string& inputID) const {
			return at(inputID);
		}
};

template <typename Drawable_c, typename Container_c, typename Element_c>
class DrawableElement : public TaggableElement<Element_c> {
	friend DrawableContainer<Drawable_c, Container_c, Element_c>;
	friend Element_c;
	
	protected:
		inline Element_c& this_dref() {
			return static_cast<Element_c&>(*this);
		}
		inline const Element_c& this_dref() const {
			return static_cast<const Element_c&>(*this);
		}
		
		bool hidden = false;
		float opacity = 1.0;
	public:
		Container_c* parentContainer;
		Drawable_c d;
		sf::Shader* shader = nullptr;
		double z;
		
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
		
		inline operator Drawable_c&() & {
			return d;
		}
		inline operator const Drawable_c&() const & {
			return d;
		}

		template <typename dConstructorT>
		DrawableElement(Container_c* inputParentContainer, const dConstructorT& inputDConstructor, double inputZ = 0) : z(inputZ), d(inputDConstructor), parentContainer(inputParentContainer) {}
		DrawableElement(const DrawableElement& other) : z(other.z), d(other.d), parentContainer(other.parentContainer), shader(other.shader), hidden(other.hidden), opacity(other.opacity) {};
		DrawableElement(DrawableElement&& other) noexcept : z(other.z), d(other.d), parentContainer(other.parentContainer), shader(other.shader), hidden(other.hidden), opacity(other.opacity) {};
		DrawableElement& operator=(const DrawableElement& other) {
			z = other.z;
			d = other.d;
			parentContainer = other.parentContainer;
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			return this_dref();
		}
		DrawableElement& operator=(DrawableElement&& other) noexcept {
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
	friend DrawableElement<Drawable_c, Container_c, Element_c>;
	friend Element_c;
	
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
			return this->taggables;
		}
		inline const unordered_map<string, Element_c>& extended_drawable() const {
			return this->taggables;
		}
		
		inline Container_c& setMultiplier(float inputInitialSizeMultiplier) {
			initialSizeMultiplier = inputInitialSizeMultiplier;
			return this_dref();
		}
		
		inline float getMultiplier() const {
			return initialSizeMultiplier;
		}
		
		template <typename dConstructorT>
		Element_c& add(const string& inputID, const dConstructorT& inputDConstructor, const double& inputZ = 0) {
			extended_drawable().insert_or_assign(inputID, Element_c(&this_dref(), inputDConstructor, inputZ));
			extended_drawable().at(inputID).multiply(initialSizeMultiplier, Align::TopLeft);
			return extended_drawable().at(inputID);
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
		
		DrawableContainer(float inputInitialSizeMultiplier = 1.0) : initialSizeMultiplier(inputInitialSizeMultiplier) {}
};

template <typename Audible_c, typename Container_c, typename Element_c>
class AudibleElement : public TaggableElement<Element_c> {
	friend AudibleContainer<Audible_c, Container_c, Element_c>;
	friend Container_c;
	
	protected:
		inline Element_c& this_dref() {
			return static_cast<Element_c&>(*this);
		}
		inline const Element_c& this_dref() const {
			return static_cast<const Element_c&>(*this);
		}
		inline Audible_c& audible() {
			return this_dref().audible();
		}
		inline const Audible_c& audible() const {
			return this_dref().audible();
		}
		inline bool audibleValid() const {
			return this_dref().audibleValid();
		}
		
		float localVolume = 1.0;
		float localPan = 0.0;
		bool loop = false;
		bool paused = false;
		bool bypassPanShift = false;
	public:
		Container_c* parentContainer;
		
		Element_c& update_volume() {
			if (audibleValid()) {
				if (parentContainer) {
					audible().setVolume(localVolume*parentContainer->masterVolume*100.0f);
				} else {
					audible().setVolume(localVolume*100.0f);
				}
			}
			return this_dref();
		}
		Element_c& update_pan() {
			if (audibleValid()){
				if (!bypassPanShift && parentContainer && parentContainer->panShift != 0.0) {
					audible().setPan(cos(acos(localPan) + parentContainer->panShift));
				} else {
					audible().setPan(localPan);
				}
			}
			return this_dref();
		}
		Element_c& update_pause() {
			if (audibleValid()) {
				if (paused || (parentContainer && parentContainer->masterPaused)) {
					audible().pause();
				} else {
					audible().play();
				}
			}
			return this_dref();
		}
		Element_c& update_loop() {
			if (audibleValid()) {
				audible().setLooping(loop);
			}
			return this_dref();
		}
		Element_c& update() {
			return this_dref().update();
		}
		sf::Time getDuration() const {
			return this_dref().getDuration();
		}
		float getVolume() const {
			return localVolume;
		}
		float getPan() const {
			return localPan;
		}
		bool getBypassPanShift() const {
			return bypassPanShift;
		}
		Element_c& setBypassPanShift(const bool& inputBypassPanShift = false) {
			bypassPanShift = inputBypassPanShift;
			update_pan();
			return this_dref();
		}
		float getPitch() const {
			if (audibleValid()) {
				return audible().getPitch();
			}
			return this_dref();
		}
		bool isPlaying() const {
			if (audibleValid()) {
				return (audible().getStatus() == sf::Sound::Status::Playing);
			}
			return false;
		}
		bool isPaused() const {
			return paused;
		}
		bool isStopped() const {
			if (audibleValid()) {
				return audible().getStatus() == sf::Sound::Status::Stopped;
			}
			return false;
		}
		bool isLooping() const {
			return loop;
		}
		sf::Time getTimestamp() const {
			if (audibleValid()) {
				return audible().getPlayingOffset();
			}
			return sf::Time();
		}
		Element_c& setTimestamp(const sf::Time& inputTime) {
			if (audibleValid()) {
				audible().setPlayingOffset(inputTime);
			}
			return this_dref();
		}
		float getTimestamp_sec() const {
			return getTimestamp().asSeconds();
		}
		float getTimestamp_ms() const {
			return getTimestamp().asMilliseconds();
		}
		float getTimestamp_us() const {
			return getTimestamp().asMicroseconds();
		}
		float getDuration_sec() const {
			return this_dref().getDuration().asSeconds();
		}
		float getDuration_ms() const {
			return this_dref().getDuration().asMilliseconds();
		}
		float getDuration_us() const {
			return this_dref().getDuration().asMicroseconds();
		}
		Element_c& setTimestamp_sec(const float& inputTimestamp) {
			setTimestamp(sf::seconds(inputTimestamp));
			return this_dref();
		}
		Element_c& setTimestamp_ms(const float& inputTimestamp) {
			setTimestamp(sf::milliseconds(inputTimestamp));
			return this_dref();
		}
		Element_c& setTimestamp_us(const float& inputTimestamp) {
			setTimestamp(sf::microseconds(inputTimestamp));
			return this_dref();
		}
		Element_c& setVolume(const float inputLocalVolume = 1.0) {
			localVolume = inputLocalVolume;
			update_volume();
			return this_dref();
		}
		Element_c& setPan(float inputPan = 0.0) {
			inputPan = inputPan >= 1.0 ? 1.0 : inputPan;
			inputPan = inputPan <= -1.0 ? -1.0 : inputPan;
			localPan = inputPan;
			update_pan();
			return this_dref();
		}
		Element_c& setPitch(float inputPitch = 1.0) {
			inputPitch *= inputPitch >= 0.0;
			if (audibleValid()) {
				audible().setPitch(inputPitch);
			}
			return this_dref();
		}
		Element_c& setPause(const bool& pauseNow) {
			paused = pauseNow;
			update_pause();
			return this_dref();
		}
		Element_c& setLooping(const bool& loopNow) {
			loop = loopNow;
			update_loop();
			return this_dref();
		}
		Element_c& pause() {
			paused = true;
			update_pause();
			return this_dref();
		}
		Element_c& unpause() {
			paused = false;
			update_pause();
			return this_dref();
		}
		Element_c& resume() {
			unpause();
			return this_dref();
		}
		Element_c& reset() {
			if (audibleValid()) {
				audible().stop();
			}
			setTimestamp_sec(0.0);
			pause();
			return this_dref();
		}
		Element_c& stop() {
			if (audibleValid()) {
				audible().stop();
			}
			return this_dref();
		}
		Element_c& replay() {
			reset();
			unpause();
			if (audibleValid()) {
				audible().play();
			}
			return this_dref();
		}
	
		inline operator Audible_c&() & {
			return audible();
		}
		inline operator const Audible_c&() const & {
			return audible();
		}
		
		AudibleElement(Container_c* inputParentContainer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false)
			: parentContainer(inputParentContainer), localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), bypassPanShift(inputBypassPanShift) {}
		AudibleElement(const AudibleElement& other)
			: parentContainer(other.parentContainer), localVolume(other.localVolume), paused(other.paused), loop(other.loop), bypassPanShift(other.bypassPanShift), localPan(other.localPan) {};
		AudibleElement(AudibleElement&& other) noexcept
			: parentContainer(other.parentContainer), localVolume(other.localVolume), paused(other.paused), loop(other.loop), bypassPanShift(other.bypassPanShift), localPan(other.localPan) {};
		AudibleElement& operator=(const AudibleElement& other) {
			parentContainer = other.parentContainer;
			localVolume = other.localVolume;
			localPan = other.localPan;
			loop = other.loop;
			paused = other.paused;
			bypassPanShift = other.bypassPanShift;
			return this_dref();
		}
		AudibleElement& operator=(AudibleElement&& other) noexcept {
			parentContainer = other.parentContainer;
			localVolume = other.localVolume;
			localPan = other.localPan;
			loop = other.loop;
			paused = other.paused;
			bypassPanShift = other.bypassPanShift;
			return this_dref();
		};
		
};
template <typename Audible_c, typename Container_c, typename Element_c>
class AudibleContainer : public TaggableContainer<Container_c, Element_c> {
	friend AudibleElement<Audible_c, Container_c, Element_c>;
	friend Element_c;
	
	protected:
		float masterVolume = 1.0;
		float panShift = 0.0;
		bool masterPaused = false;
		
		inline Container_c& this_dref() {
			return static_cast<Container_c&>(*this);
		}
		inline const Container_c& this_dref() const {
			return static_cast<const Container_c&>(*this);
		}
	public:
		unordered_map<string, Element_c>& event;
		
		Container_c& update_volume() {
			for (pair<const string, Element_c>& currentEvent : event) {
				event.at(currentEvent.first).update_volume();
			}
			return this_dref();
		}
		Container_c& update_loop() {
			for (pair<const string, Element_c>& currentEvent : event) {
				event.at(currentEvent.first).update_loop();
			}
			return this_dref();
		}
		Container_c& update_pause() {
			for (pair<const string, Element_c>& currentEvent : event) {
				event.at(currentEvent.first).update_pause();
			}
			return this_dref();
		}
		Container_c& update() {
			for (pair<const string, Element_c>& currentEvent : event) {
				event.at(currentEvent.first).update_loop();
				event.at(currentEvent.first).update_volume();
				event.at(currentEvent.first).update_pause();
			}
			return this_dref();
		}
		inline float getVolume() const {
			return masterVolume;
		}
		inline bool isPlaying() const {
			return !masterPaused;
		}
		inline bool isPaused() const {
			return masterPaused;
		}
		Container_c& update_pan() {
			for (pair<const string, Element_c>& currentEvent : event) {
				event.at(currentEvent.first).update_pan();
			}
			return this_dref();
		}
		float getPanShift(const bool& deg = true) const {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		Container_c& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return this_dref();
		}
		Container_c& setVolume(const float& inputMasterVolume) {
			masterVolume = inputMasterVolume;
			update_volume();
			return this_dref();
		}
		Container_c& setPause(const bool& pauseNow) {
			masterPaused = pauseNow;
			update_pause();
			return this_dref();
		}
		Container_c& pause() {
			masterPaused = true;
			return this_dref();
		}
		Container_c& unpause() {
			masterPaused = false;
			update_pause();
			return this_dref();
		}
		Container_c& resume() {
			unpause();
			return this_dref();
		}
		Container_c& clean() {
			for (pair<const string, Element_c>& currentEvent : event) {
				if (event.at(currentEvent.first).isStopped()) {
					erase(currentEvent.first);
				}
			}
			return this_dref();
		}
		
		AudibleContainer(const float& inputMasterVolume = 1.0) : masterVolume(inputMasterVolume), event(this->taggables) {
			masterVolume = masterVolume >= 1.0 ? 1.0 : masterVolume;
			masterVolume *= masterVolume >= 0.0;
		}
};

template <typename Resource_c, typename Container_c, typename Element_c>
class ResourceElement : public TaggableElement<Element_c> {
	friend ResourceContainer<Resource_c, Container_c, Element_c>;
	
	public:
		Resource_c* r;
	protected:
		inline Element_c& this_dref() {
			return static_cast<Element_c&>(*this);
		}
		inline const Element_c& this_dref() const {
			return static_cast<const Element_c&>(*this);
		}
	public:
		Container_c* parentContainer;
		
		Element_c& load(const Resource_c& inputResource) {
			if (r) {
				delete r;
				r = nullptr;
			}
			r = new Resource_c(inputResource);
			return this_dref();
		}
		inline Element_c& loadFromFile(const string& inputFileDirectory) {
			if (r && r->loadFromFile(inputFileDirectory)) {}
			
			return this_dref();
		}
		inline Element_c& loadFromMemory(const unsigned char* data, const size_t& size) {
			if (r && r->loadFromMemory(data, size)) {}
			
			return this_dref();
		}
		inline Element_c& open(const Resource_c& inputResource) {
			return load(inputResource);
		}
		inline Element_c& openFromFile(const string& inputFileDirectory) {
			return loadFromFile(inputFileDirectory);
		}
		inline Element_c& openFromMemory(const unsigned char* data, const size_t& size) {
			return loadFromMemory(data, size);
		}
		Element_c& unload() {
			if (r) {
				delete r;
				r = nullptr;
			}
			
			return this_dref();
		}
		
		inline operator Resource_c&() & {
			return *r;
		}
		inline operator const Resource_c&() const & {
			return *r;
		}
		
		template <typename dConstructorT>
		ResourceElement(Container_c* inputParentContainer, const dConstructorT& inputDConstructor) : parentContainer(inputParentContainer) {
			r = new Resource_c(inputDConstructor);
			return;
		}
		ResourceElement(Container_c* inputParentContainer, const unsigned char* data, const size_t& size) : parentContainer(inputParentContainer) {
			r = new Resource_c(data, size);
			return;
		}
		ResourceElement(Container_c* inputParentContainer) : parentContainer(inputParentContainer) {
			r = nullptr;
			return;
		}
		~ResourceElement() {
			delete r;
			r = nullptr;
			return;
		}
		ResourceElement(Element_c& other) : parentContainer(other.parentContainer) {
			if (this != &other) {
				if (r) {
					delete r;
					r = nullptr;
				}
				if (other.r) {
					r = new Resource_c(*other.r);
				}
			}
		}
		ResourceElement& operator=(Element_c& other) {
			if (this != &other) {
				if (r) {
					delete r;
					r = nullptr;
				}
				if (other.r) {
					r = new Resource_c(*other.r);
				}
			}
			parentContainer = other.parentContainer;
			return this_dref();
		}
		ResourceElement(Element_c&& other) noexcept : r(other.r), parentContainer(other.parentContainer) {
			if (this != &other) {
				other.r = nullptr;
			}
		}
		ResourceElement& operator=(Element_c&& other) noexcept {
			if (this != &other) {
				r = other.r;
				other.r = nullptr;
			}
			parentContainer = other.parentContainer;
			return this_dref();
		}

};
template <typename Resource_c, typename Container_c, typename Element_c>
class ResourceContainer : public TaggableContainer<Container_c, Element_c> {
	protected:
		inline Container_c& this_dref() {
			return static_cast<Container_c&>(*this);
		}
		inline const Container_c& this_dref() const {
			return static_cast<const Container_c&>(*this);
		}
	public:
		ResourceContainer& clean() {
			for (pair<const string, Element_c>& currentResource : this->taggables) {
				if (!this->taggables.at(currentResource.first).r) {
					erase(currentResource.first);
				}
			}
			return *this;
		}
		
		ResourceContainer& load(const std::string& inputID, const Resource_c& inputResource) {
			this->taggables.insert_or_assign(inputID, Element_c(&this_dref(), inputResource));
			return *this;
		}
		ResourceContainer& loadFromFile(const std::string& inputID, const std::string& fileDirectory) {
			this->taggables.insert_or_assign(inputID, Element_c(&this_dref(), fileDirectory));
			return *this;
		}
		ResourceContainer& loadFromMemory(const std::string& inputID, const unsigned char* data, const size_t& size) {
			this->taggables.insert_or_assign(inputID, Element_c(&this_dref(), data, size));
			return *this;
		}
		ResourceContainer& open(const std::string& inputID, const sf::Font& inputFont) {
			return load(inputID, inputFont);
		}
		ResourceContainer& openFromFile(const std::string& inputID, const std::string& fileDirectory) {
			return loadFromFile(inputID, fileDirectory);
		}
		ResourceContainer& openFromMemory(const std::string& inputID, const unsigned char* data, const size_t& size) {
			return loadFromMemory(inputID, data, size);
		}
		
		ResourceContainer() {}
};