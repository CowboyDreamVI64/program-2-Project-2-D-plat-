//  Stores the instructions and details for a sprite to parallax

//  NOTE: Handle distances of infinity
struct ParallaxInstruction {
	private:
		string baseTextureID;
		sf::Vector2u gridSize = {1, 1};
		string gridTextureID;
		Vec2 apparentSize;
		Vec2 actualPosition;
	public:
		string spriteID;
		double distance;
		array<bool, 2> loopDirection;
	
		inline string getTextureID() const {
			return baseTextureID;
		}
		inline string getGridTextureID() const {
			return gridTextureID;
		}
		inline Vec2 getApparentSize() const {
			return apparentSize;
		}
		inline Vec2 getActualSize() const {
			return apparentSize*distance;
		}
		Vec2 getApparentPosition(const Vec2& inputOffset) const {
			if (isinf(distance)) {
				return inputOffset;
			}
			Vec2 loopFactor = 0;
			const Vec2 relativeApparentPosition = actualPosition/distance;
			const Vec2 absoluteApparentPosition = (actualPosition - inputOffset)/distance + inputOffset;
			if (loopDirection[0] || loopDirection[1]) {
				const Vec2 loopDirectionMultiplier = Vec2(loopDirection[0], loopDirection[1]);
				const Vec2 actualSize = apparentSize*distance;
				const Vec2 gridUnitSize = apparentSize/gridSize;
				const Vec2 apparentGridPosition = relativeApparentPosition/gridUnitSize;
				const Vec2 loopFloorFactor = ((inputOffset - actualPosition)*gridSize/(apparentSize*distance)).floor();
				loopFactor = loopDirectionMultiplier*(gridUnitSize*loopFloorFactor + apparentSize/(Vec2(gridSize)*2));
			}
			return absoluteApparentPosition + loopFactor;
		}
		inline Vec2 getActualPosition() const {
			return actualPosition;
		}
		inline sf::Vector2u getGridSize() const {
			return gridSize;
		}
		inline ParallaxInstruction& setApparentSize(const Vec2& inputSize) {
			apparentSize = inputSize;
			return *this;
		}
		inline ParallaxInstruction& setActualSize(const Vec2& inputSize) {
			apparentSize = inputSize/distance;
			return *this;
		}
		inline ParallaxInstruction& setApparentPosition(const Vec2& inputVector, const Vec2& inputOffset) {
			actualPosition = (inputVector - inputOffset)*distance + inputOffset;
			return *this;
		}
		inline ParallaxInstruction& setActualPosition(const Vec2& inputVector) {
			actualPosition = inputVector;
			return *this;
		}
		inline ParallaxInstruction& setGridSize(const sf::Vector2u& inputVector) {
			gridSize = inputVector;
			return *this;
		}
		ParallaxInstruction& loadToSprite() {
			if (sprites.exists(spriteID) && textures.exists(gridTextureID)) {
				sprites[spriteID].setTexture(textures[gridTextureID]);
			}
			return *this;
		}
		ParallaxInstruction& refreshGridTexture() {
			sf::Image baseImage = textures[baseTextureID].texture->copyToImage();
			const sf::Vector2u baseImageSize = baseImage.getSize();
			
			sf::Image gridImage = sf::Image();
			gridImage.resize(Vec2(gridSize)*baseImageSize);
			
			for (unsigned int Y = 0; Y < gridSize.y; ++Y) {
				for (unsigned int X = 0; X < gridSize.x; ++X) {
					if (gridImage.copy(baseImage, {X*baseImageSize.x, Y*baseImageSize.y}));
				}
			}
			sf::Texture gridTexture = sf::Texture(gridImage);
			
			gridTextureID = "[ParallaxInstructionGridTexture];sprite:\"" + spriteID + "\",baseTextureID:\"" + baseTextureID + "\";[\\ParallaxInstructionGridTexture]";
			
			if (textures.exists(gridTextureID)) {
				textures.erase(gridTextureID);
			}
			
			textures.load(gridTextureID, gridTexture);
			loadToSprite();
			return *this;
		}
		ParallaxInstruction& fitLoopToViewPort(const ViewPort& inputViewport) {
			actualPosition -= apparentSize*gridSize*distance/2;
			apparentSize /= gridSize;
			if (loopDirection[0] || loopDirection[1]) {
				const Vec2 loopDirectionMultiplier = Vec2(loopDirection[0], loopDirection[1]);
				gridSize = ((inputViewport.getPerceivedDimensions()/apparentSize).ceil() + 1)*loopDirectionMultiplier + (Vec2(1) - loopDirectionMultiplier);	
			} else {
				gridSize = {1, 1};
			}
			apparentSize *= gridSize;
			actualPosition += apparentSize*gridSize*distance/2;
			
			refreshGridTexture();
			return *this;
		}
		inline ParallaxInstruction& setTextureID(const string& inputTextureID) {
			if (textures.exists(inputTextureID)) {
				baseTextureID = inputTextureID;
				if (textures.exists(gridTextureID)) {
					textures.erase(gridTextureID);
				}
				refreshGridTexture();
			}
			return *this;
		}
		ParallaxInstruction& clear() {
			if (gridTextureID != "" && baseTextureID != "" && spriteID != "" && textures.exists(gridTextureID) && textures.exists(baseTextureID) && sprites.exists(spriteID)) {
				sprites[spriteID].setTexture(textures[baseTextureID]);
				textures.erase(gridTextureID);
			}
			return *this;
		}
		ParallaxInstruction(const string& inputSpriteID, const string& inputBaseTextureID, const double& inputDistance, const Vec2& inputApparentSize, const Vec2& inputActualPosition, const bool& loopDirectionX, const bool& loopDirectionY)
			: spriteID(inputSpriteID), baseTextureID(inputBaseTextureID), distance(inputDistance), apparentSize(inputApparentSize), actualPosition(inputActualPosition), loopDirection({loopDirectionX, loopDirectionY})
		{}
		ParallaxInstruction() {}
};