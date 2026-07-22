//  Stores the instructions and details for a sprite to parallax

//  NOTE: Handle distances of infinity
struct ParallaxInstruction {
	private:
		string baseTextureID;
		sf::Vector2u gridSize;
		string gridTextureID;
	public:
		string spriteID;
		double distance;
		Vec2 apparentSize;
		Vec2 actualPosition;
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
		inline Vec2 getApparentPosition() const {
			//  HANDLE LOOPING HERE
			return actualPosition/distance;
		}
		inline Vec2 getActualPosition() const {
			//  HANDLE LOOPING HERE
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
		inline ParallaxInstruction& setApparentPosition(const Vec2& inputVector) {
			actualPosition = inputVector*distance;
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
				sprites[spriteID].setTexture(gridTextureID);
			}
			return *this;
		}
		ParallaxInstruction& refreshGridTexture() {
			sf::Image baseImage = textures[baseTextureID].texture.copyToImage();
			const sf::Vector2u baseImageSize = baseImage.getSize();
			
			sf::Image gridImage = sf::Image().resize(gridSize*baseImageSize);
			for (std::size_t Y = 0; Y < gridSize.y; ++Y) {
				for (std::size_t X = 0; X < gridSize.x; ++X) {
					gridImage.copy(baseImage, {X*baseImageSize.x, Y*baseImageSize.y});
				}
			}
			sf::Texture gridTexture = sf::Texture(gridImage);
			
			gridTextureID = "[ParallaxInstructionGridTexture].baseTextureID == \"" + baseTextureID + "\"";
			textures.load(gridTextureID, gridTexture);
			loadToSprite();
			return *this;
		}
		inline ParallaxInstruction& setTextureID(const string& inputTextureID) {
			if (textures.exists(inputTextureID)) {
				textureID = inputTextureID;
				if (textures.exists(gridTextureID)) {
					textures.erase(gridTextureID);
				}
				refreshGridTexture();
			}
			return *this;
		}
		ParallaxInstruction(const string& inputSpriteID, const string& inputBaseTextureID, const Vec2& inputDistance, const Vec2& inputApparentSize, const Vec2& inputActualPosition, const bool& loopDirectionX, const bool& loopDirectionY)
			: spriteID(inputSpriteID), baseTextureID(inputBaseTextureID), distance(inputDistance), apparentSize(inputApparentSize), actualPosition(inputActualPosition), loopDirection({loopDirectionX, loopDirectionY})
		{
			gridSize = {loopDirection[0] ? 2 : 1, loopDirection[1] ? 2 : 1};
		}
		~ParallaxInstruction() {
			if (gridTextureID != "" && baseTextureID != "" && spriteID != "" && textures.exists(gridTextureID) && textures.exists(baseTextureID) && sprites.exists(spriteID)) {
				sprites[spriteID].setTexture(textures[baseTextureID]);
				textures.erase(gridTextureID);
			}
		}	
};