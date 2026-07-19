//  Basically an easy-to-control camera.
struct ViewPort {
	private:
		//  This is the mutable viewport width size variable. It should NOT be directly modifiable; that's
		//  what setSize() and the &size reference are for.
		double SIZE;
	public:
		//  pos stores the position of the viewport.
		Vec2 pos;
		Vec2& position = pos;
		const double& size = SIZE;
		
		//  This is an alias for getting the size of the viewport.
		inline double getSize() {
			return SIZE;
		}
		
		//  This sets the size (with error-checking).
		inline ViewPort& setSize(const double& inputSize) {
			SIZE = inputSize * (inputSize > 0.0);
			return *this;
		}
		
		//  This sets the size so that the width of the camera equals the input (default behavior).
		inline ViewPort& setSizeToWidth(const double& inputSize, const Vec2& resolution = 1.0) {
			return setSize(inputSize);
		}
		
		//  This sets the size so that the height of the camera equals the input.
		ViewPort& setSizeToHeight(const double& inputSize, const Vec2& resolution = 1.0) {
			if (resolution.y == 0.0) {
				return setSize(0);
			}
			return setSize(inputSize*resolution.x/resolution.y);
		}
		
		//  This sets the size so that the viewport is guaranteed to be within a square of side length inputSize.
		ViewPort& setSizeToFit(const double& inputSize, const Vec2& resolution = 1.0) {
			if (resolution.y == 0.0) {
				return setSize(0);
			}
			const double aspectRatio = resolution.x/resolution.y;
			return setSize(aspectRatio < 1.0 ? inputSize*aspectRatio : inputSize);
		}
		//  This sets the size so that a square of side length inputSize is guaranteed to be within the viewport.
		ViewPort& setSizeToFill(const double& inputSize, const Vec2& resolution = 1.0) {
			if (resolution.y == 0.0) {
				return setSize(0);
			}
			const double aspectRatio = resolution.x/resolution.y;
			return setSize(aspectRatio < 1.0 ? inputSize : inputSize*aspectRatio);
		}
		
		//  This gets the dimensions of the camera given a resolution (since height for different resolutions isn't
		//  the same given a constant width).
		inline Vec2 getPerceivedDimensions(const Vec2& resolution = 1.0) const {
			return Vec2(SIZE, SIZE*resolution.y/resolution.x);
		}
		
		//  Default viewport constructor; takes a size and an optional position.
		inline ViewPort(const double& inputSize, const Vec2& inputPos = 0.0) : pos(inputPos) {
			setSize(inputSize);
		}
		
		//  Alters the size and position of drawables like sprites and texts to have a certain position and size when
		//  rendered depending on where in the viewport it is. This allows lengths to be unit-based rather than pixel-based.
		template <typename ExtendedDrawable>
		ViewPort& setInViewport(const ExtendedWindow& window, ExtendedDrawable& drawable, const Vec2& drawablePos, const Vec2& drawableScale = 1.0) {
			if (SIZE == 0) {
				return *this;
			}
			
			//  Takes the size as the width of the smallest dimension; that's why setSizeToFit() just sets to input			
			const double aspectRatio = window.resolution.x*1.0/window.resolution.y;
			const Vec2 viewDimensions = {SIZE, SIZE/aspectRatio};
			const Vec2 pixelsPerMeter = {window.resolution.x/viewDimensions.x, window.resolution.y/viewDimensions.y};
			const Vec2 newScale = drawableScale*pixelsPerMeter/drawable.getLocalBounds().size;
			Vec2 newOffset = (drawablePos - pos)/viewDimensions;
			//  SFML uses a left-right x and a top-down y, so y needs to be multiplied by -1 to keep backend math cartesian/standard
			newOffset.y *= -1;
			
			drawable.setScale(newScale).center(window).offset(window, newOffset);
			
			return *this;
		}
};