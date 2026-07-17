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

class ExtendedSprite : public TaggableElement<ExtendedSprite>, public DrawableElement<sf::Sprite, SpriteContainer, ExtendedSprite> {
	public:
		SpriteContainer*& parentSpriteContainer = parentContainer;
		sf::Sprite& sprite = d;
		
		
		//  Copy and move stuff since static polymorphism is being stubborn about &sprite
		ExtendedSprite(const ExtendedSprite& other) noexcept : DrawableElement(other.parentContainer, other.drawable(), other.z)  {
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
		}
		ExtendedSprite(const ExtendedSprite&& other) noexcept : DrawableElement(other.parentContainer, other.drawable(), other.z)  {
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
		}
		ExtendedSprite& operator=(const ExtendedSprite&& other) noexcept {
			parentContainer = other.parentContainer;
			drawable() = other.drawable();
			z = other.z;
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			
			return *this;
		}
		
		
		inline sf::Color getColor() const {
			return sprite.getColor();
		}
		float getColor(const unsigned short inputColorChannel = ColorChannel::None) const {
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
		sf::Vector2f getNormalTexturePixelSize() const {
			sf::Vector2u textureSize = sprite.getTexture().getSize();
			return sf::Vector2f({1.0f/textureSize.x, 1.0f/textureSize.y});
		}
		inline sf::Vector2u getTextureSize() const {
			return sprite.getTexture().getSize();
		}
		ExtendedSprite setTextureRect(const sf::IntRect& inputRect, const AlignDirection& alignDirection = Align::None, const sf::Vector2i& offset = sf::Vector2i(), const bool& offsetWithRotation = true) {
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
		ExtendedSprite(SpriteContainer* inputParentSpriteContainer, sf::Texture& inputTexture, double inputZ = 0) : DrawableElement(inputParentSpriteContainer, inputTexture, inputZ) {}
		ExtendedSprite(SpriteContainer* inputParentSpriteContainer, sf::Sprite inputSprite, double inputZ = 0) : DrawableElement(inputParentSpriteContainer, inputSprite, inputZ) {}
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

class ExtendedText : public TaggableElement<ExtendedText>, public DrawableElement<sf::Text, TextContainer, ExtendedText> {
	private:
		bool styleBold = false;
		bool styleItalic = false;
		bool styleUnderlined = false;
	public:
		TextContainer*& parentTextContainer = parentContainer;
		sf::Text& text = d;
		float fill_opacity = 1.0;
		float outline_opacity = 1.0;
		
		//  Copy and move stuff since static polymorphism is being stubborn about &text
		ExtendedText(const ExtendedText& other) noexcept : DrawableElement(other.parentContainer, other.drawable(), other.z)  {
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			fill_opacity = other.fill_opacity;
			outline_opacity = other.outline_opacity;
			styleBold = other.styleBold;
			styleItalic = other.styleItalic;
			styleUnderlined = other.styleUnderlined;
		}
		ExtendedText(const ExtendedText&& other) noexcept : DrawableElement(other.parentContainer, other.drawable(), other.z)  {
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			fill_opacity = other.fill_opacity;
			outline_opacity = other.outline_opacity;
			styleBold = other.styleBold;
			styleItalic = other.styleItalic;
			styleUnderlined = other.styleUnderlined;
		}
		ExtendedText& operator=(const ExtendedText&& other) noexcept {
			parentContainer = other.parentContainer;
			drawable() = other.drawable();
			z = other.z;
			shader = other.shader;
			hidden = other.hidden;
			opacity = other.opacity;
			fill_opacity = other.fill_opacity;
			outline_opacity = other.outline_opacity;
			styleBold = other.styleBold;
			styleItalic = other.styleItalic;
			styleUnderlined = other.styleUnderlined;
			
			return *this;
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