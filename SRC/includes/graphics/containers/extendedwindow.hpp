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
		
		inline sf::RenderWindow*& drawable() {
			return window;
		}
		
		inline ExtendedWindow& update_icon() {
			if (window) {
				window->setIcon(icon);
			}
			return *this;
		}
		ExtendedWindow& update_mouse_lock(const bool& overrideBoolean = false, const bool& overrideMouseLocked = false) {
			if (window) {
				if (overrideBoolean ? overrideMouseLocked : mouseLocked) {
					window->setMouseCursorGrabbed(true);
				} else {
					window->setMouseCursorGrabbed(false);
				}
			}
			return *this;
		}
		
		ExtendedWindow& update_mouse_visibility(const bool& overrideBoolean = false, const bool& overrideMouseVisible = true) {
			if (window) {
				if (overrideBoolean ? !overrideMouseVisible : !mouseVisible) {
					window->setMouseCursorVisible(false);
				} else {
					window->setMouseCursorVisible(true);
				}
			}
			return *this;
		}
		
		inline ExtendedWindow& update_resolution() {
			if (window) {
				window->setSize(resolution);
			}
			return *this;
		}
		
		inline ExtendedWindow& update_framerate() {
			if (window) {
				window->setFramerateLimit(framerate);
			}
			return *this;
		}
		
		inline ExtendedWindow& update_vsync() {
			if (window) {
				window->setVerticalSyncEnabled(vsync);
			}
			return *this;
		}
		
		inline sf::Image getIcon() const {
			return icon;
		}
		
		inline ExtendedWindow& setIcon(const sf::Image& inputImage) {
			icon = inputImage;
			return update_icon();
		}
		
		inline ExtendedWindow& setIcon(const sf::Texture& inputTexture) {
			icon = inputTexture.copyToImage();
			return update_icon();
		}
		
		inline ExtendedWindow& resetIcon() {
			icon = sf::Image();
			return update_icon();
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
		
		bool pollForClosure(const optional<sf::Event>& event) const {
			if (window && event) {
				if (event->is<sf::Event::Closed>()) {
					return true;
				}
			}
			return false;
		}
		
		bool pollForF11(const bool& focusEnforced = true) const {
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
		
		bool pollForEscape(const bool& focusEnforced = true) const {
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
		
		bool pollForKey(const sf::Keyboard::Key& inputKey, const bool& focusEnforced = true) const {
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
		
		inline bool stableState(const bool& inputBoolean = true) const {
			return inputBoolean && window && window->isOpen();
		}
		
		ExtendedWindow& setTitle(const string& inputTitle) {
			title = inputTitle;
			if (window) {
				window->setTitle(inputTitle);
			}
			return *this;
		}
		
		inline ExtendedWindow& setResolution(const sf::Vector2u& inputResolution) {
			resolution = inputResolution;
			return update_resolution();
		}
		
		inline ExtendedWindow& setFramerate(const unsigned int& inputFramerate) {
			framerate = inputFramerate;
			return update_framerate();
		}
		
		ExtendedWindow& setVsync(const bool& useVsync) {
			vsync = useVsync;
			update_vsync();
			update_framerate();
			return *this;
		}
		
		inline ExtendedWindow& setFullscreen(const bool& useFullscreen) {
			if (useFullscreen != fullscreen) {
				toggleFullscreen();
			}
			return *this;
		}
		
		sf::FloatRect getGlobalBounds() const {
			if (window) {
				sf::View windowView = window->getView();
				sf::Vector2f windowViewSize = windowView.getSize();
				sf::Vector2f windowViewCenter = windowView.getCenter();
				return sf::FloatRect({windowViewCenter.x - windowViewSize.x/2.0f, windowViewCenter.y - windowViewSize.y/2.0f}, windowViewSize);
			}
			return sf::FloatRect();
		}
		
		inline sf::FloatRect getLocalBounds() const {
			if (window) {
				return sf::FloatRect(sf::Vector2f({0.0f, 0.0f}), sf::Vector2f{static_cast<float>(resolution.x), static_cast<float>(resolution.y)});
			}
			return sf::FloatRect();
		}
		
		inline sf::Vector2f getScale() const {
			if (window) {
				return window->getView().getSize();
			}
			return sf::Vector2f();
		}
		
		inline sf::Vector2u getWindowSize() const {
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
		
		sf::Texture screenshot() const {
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
		
		inline ExtendedWindow& requestFocus() {
			if (window) {
				window->requestFocus();
			}
			return *this;
		}
		
		inline ExtendedWindow& getFocus() {
			return requestFocus();
		}
		
		inline bool getMouseLock() const {
			return mouseLocked;
		}
		
		inline ExtendedWindow& setMouseLock(const bool& inputMouseLocked) {
			mouseLocked = inputMouseLocked;
			return update_mouse_lock();
		}
		
		inline ExtendedWindow& lockMouse() {
			mouseLocked = true;
			return update_mouse_lock();
		}
		
		inline ExtendedWindow& unlockMouse() {
			mouseLocked = false;
			return update_mouse_lock();
		}
		
		inline bool getMouseVisibility() const {
			return mouseVisible;
		}
		
		inline ExtendedWindow& setMouseVisibility(const bool& inputMouseVisibility) {
			mouseVisible = inputMouseVisibility;
			return update_mouse_lock();
		}
		
		inline ExtendedWindow& unhideMouse() {
			mouseVisible = true;
			return update_mouse_visibility();
		}
		
		inline ExtendedWindow& hideMouse() {
			mouseVisible = false;
			return update_mouse_visibility();
		}
					
		inline bool isFocused() const {
			if (window) {
				return window->hasFocus();
			}
			return false;
		}
		inline bool mouseLeftHeld(const bool& focusEnforced = true) const {
			if (!focusEnforced || isFocused()) {
				return sf::Mouse::isButtonPressed(sf::Mouse::Button::Left);
			}
			return false;
		}
		inline bool mouseRightHeld(const bool& focusEnforced = true) const {
			if (!focusEnforced || isFocused()) {
				return sf::Mouse::isButtonPressed(sf::Mouse::Button::Right);
			}
			return false;
		}
		
		sf::Vector2f getMousePosition(const bool& useDesktopContext = false, const bool& focusRequired = true, const bool& normalize = true, const bool& setNanTo0 = true) const {
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
		
		inline ExtendedWindow(const string& inputTitle = "window", const sf::Vector2u& inputResolution = sf::Vector2u(600, 400), const unsigned int& inputFramerate = 60, const bool& useFullscreen = false, const bool& useVsync = true, const float& inputInitialSizeMultiplier = 0.67) : title(inputTitle), resolution(inputResolution), framerate(inputFramerate), inputFullscreen(useFullscreen), vsync(useVsync), initialSizeMultiplier(inputInitialSizeMultiplier) {
			window = nullptr;
			return;
		}
		
		~ExtendedWindow() {
			delete window;
			window = nullptr;
		}
		
		ExtendedWindow(const ExtendedWindow& originalObject) {
			if (originalObject.window) {
				open(originalObject.title, originalObject.resolution, originalObject.framerate, originalObject.fullscreen, originalObject.vsync, originalObject.window->getSize().x*1.0/originalObject.resolution.x);
			} else {
				window = nullptr;
			}
			return;
		}
		ExtendedWindow& operator=(const ExtendedWindow& rObject) {
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