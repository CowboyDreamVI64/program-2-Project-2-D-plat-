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
		ViewPort& setSizeToWidth(const double& inputSize, const sf::Vector2f& resolution = sf::Vector2f({1.0f, 1.0f})) {
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
		Vec2 getPerceivedDimensions(const Vec2& resolution = 1.0) const {
			const double aspectRatio = resolution.x/resolution.y;
			return Vec2(__SIZE, __SIZE/aspectRatio);
		}
		
		ViewPort(const double& inputSize = 10, const Vec2& inputPos = 1.0) : pos(inputPos) {
			setSize(inputSize);
		}
		
		template <typename ExtendedDrawable>
		ViewPort& setInViewport(ExtendedWindow& window, ExtendedDrawable& drawable, const Vec2& drawablePos, const Vec2& drawableScale = 1.0) {
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