class ExtendedTexture : public TaggableElement<ExtendedTexture> {
	public:
		TextureContainer* parentTextureContainer;
		sf::Texture* texture;
		ExtendedTexture& setSmooth(const bool& inputSmooth) {
			if (texture) {
				texture->setSmooth(inputSmooth);
			}
			return *this;
		}
		ExtendedTexture& load(const sf::Texture& inputTexture) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture(inputTexture);
			return *this;
		}
		ExtendedTexture& loadFromImage(const sf::Image& inputImage) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture();
			if (texture->loadFromImage(inputImage));
			return *this;
		}
		ExtendedTexture& loadFromFile(const string& fileDirectory) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture();
			if(!texture->loadFromFile(fileDirectory)) {
				texture = nullptr;
			}
			return *this;
		}
		ExtendedTexture& loadFromMemory(const unsigned char* data, const size_t& size) {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			texture = new sf::Texture();
			if(!texture->loadFromMemory(data, size)) {
				texture = nullptr;
			}
			return *this;
		}
		ExtendedTexture& unload() {
			if (texture) {
				delete texture;
				texture = nullptr;
			}
			return *this;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const sf::Texture& inputTexture) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture(inputTexture);
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const sf::Image& inputImage) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture();
			if (texture->loadFromImage(inputImage));
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const string& fileDirectory) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture(fileDirectory);
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject, const unsigned char* data, const size_t& size) : parentTextureContainer(TextureContainerObject) {
			texture = new sf::Texture(data, size);
			return;
		}
		ExtendedTexture(TextureContainer* TextureContainerObject) : parentTextureContainer(TextureContainerObject) {
			texture = nullptr;
			return;
		}
		~ExtendedTexture() {
			delete texture;
			texture = nullptr;
			return;
		}
		ExtendedTexture(ExtendedTexture& originalObject) {
			if (originalObject.texture) {
				texture = new sf::Texture(*originalObject.texture);
			} else {
				texture = nullptr;
			}
			parentTextureContainer = originalObject.parentTextureContainer;
			return;
		}
		ExtendedTexture& operator=(ExtendedTexture& rObject) {
			if (this != &rObject) {
				delete texture;
				if (rObject.texture) {
					texture = new sf::Texture(*rObject.texture);
				} else {
					texture = nullptr;
				}
				parentTextureContainer = rObject.parentTextureContainer;
			}
			return *this;
		}
		ExtendedTexture(ExtendedTexture&& originalObject) noexcept : texture(originalObject.texture) {
			parentTextureContainer = originalObject.parentTextureContainer;
			originalObject.texture = nullptr;
			return;
		}
		ExtendedTexture& operator=(ExtendedTexture&& rObject) noexcept {
			if (this != &rObject) {
				texture = rObject.texture;
				parentTextureContainer = rObject.parentTextureContainer;
				rObject.texture = nullptr;
			}
			return *this;
		}
};
class TextureContainer : public TaggableContainer<TextureContainer, ExtendedTexture> {
	public:
		bool defaultTextureSmoothness = false;
		unordered_map<string, ExtendedTexture>& extended_texture;
		TextureContainer& update_smoothness() {
			for (pair<const string, ExtendedTexture>& currentExtendedTexture : extended_texture) {
				extended_texture.at(currentExtendedTexture.first).setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& load(string inputID, const sf::Texture& inputTexture) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).load(inputTexture);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, inputTexture));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& loadFromImage(string inputID, const sf::Image& inputImage) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).loadFromImage(inputImage);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, inputImage));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& loadFromFile(string inputID, const string& fileDirectory) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).loadFromFile(fileDirectory);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, fileDirectory));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& loadFromMemory(string inputID, const unsigned char* data, const size_t size) {
			if (extended_texture.count(inputID) != 0) {
				extended_texture.at(inputID).loadFromMemory(data, size);
			} else {
				extended_texture.insert_or_assign(inputID, ExtendedTexture(this, data, size));
			}
			if (extended_texture.at(inputID).texture) {
				extended_texture.at(inputID).texture->setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		bool exists(const string& inputID) {
			return extended_texture.count(inputID) != 0;
		}
		TextureContainer& erase(const string& inputID) {
			extended_texture.erase(inputID);
			return *this;
		}
		TextureContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		TextureContainer& clear() {
			extended_texture = unordered_map<string, ExtendedTexture>();
			return *this;
		}
		TextureContainer& clean() {
			for (pair<const string, ExtendedTexture>& currentExtendedTexture : extended_texture) {
				if (!extended_texture.at(currentExtendedTexture.first).texture) {
					erase(currentExtendedTexture.first);
				}
			}
			return *this;
		}
		TextureContainer& setSmooth(const bool& inputSmooth = true) {
			defaultTextureSmoothness = inputSmooth;
			update_smoothness();
			return *this;
		}
		sf::Texture& operator[](const string& inputID) {
			return *extended_texture.at(inputID).texture;
		}
		const sf::Texture& operator[](const string& inputID) const {
			return *extended_texture.at(inputID).texture;
		}
		TextureContainer() : extended_texture(taggables) {}
};

class ExtendedSoundBuffer : public TaggableElement<ExtendedSoundBuffer> {
	public:
		SoundBufferContainer* parentSoundBufferContainer;
		sf::SoundBuffer* buffer;
		ExtendedSoundBuffer& load(const sf::SoundBuffer& inputSoundBuffer) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			buffer = new sf::SoundBuffer(inputSoundBuffer);
			return *this;
		}
		ExtendedSoundBuffer& loadFromFile(const string& fileDirectory) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			buffer = new sf::SoundBuffer();
			if(!buffer->loadFromFile(fileDirectory)) {
				buffer = nullptr;
			}
			return *this;
		}
		ExtendedSoundBuffer& loadFromMemory(const unsigned char* data, const size_t& size) {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			buffer = new sf::SoundBuffer();
			if(!buffer->loadFromMemory(data, size)) {
				buffer = nullptr;
			}
			return *this;
		}
		ExtendedSoundBuffer& unload() {
			if (buffer) {
				delete buffer;
				buffer = nullptr;
			}
			return *this;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject, const sf::SoundBuffer& inputSoundBuffer) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = new sf::SoundBuffer(inputSoundBuffer);
			return;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject, const string& fileDirectory) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = new sf::SoundBuffer(fileDirectory);
			return;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject, const unsigned char* data, const size_t& size) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = new sf::SoundBuffer(data, size);
			return;
		}
		ExtendedSoundBuffer(SoundBufferContainer* SoundBufferContainerObject) : parentSoundBufferContainer(SoundBufferContainerObject) {
			buffer = nullptr;
			return;
		}
		~ExtendedSoundBuffer() {
			delete buffer;
			buffer = nullptr;
			return;
		}
		ExtendedSoundBuffer(ExtendedSoundBuffer& originalObject) {
			if (originalObject.buffer) {
				buffer = new sf::SoundBuffer(*originalObject.buffer);
			} else {
				buffer = nullptr;
			}
			parentSoundBufferContainer = originalObject.parentSoundBufferContainer;
			return;
		}
		ExtendedSoundBuffer& operator=(ExtendedSoundBuffer& rObject) {
			if (this != &rObject) {
				delete buffer;
				if (rObject.buffer) {
					buffer = new sf::SoundBuffer(*rObject.buffer);
				} else {
					buffer = nullptr;
				}
				parentSoundBufferContainer = rObject.parentSoundBufferContainer;
			}
			return *this;
		}
		ExtendedSoundBuffer(ExtendedSoundBuffer&& originalObject) noexcept : buffer(originalObject.buffer) {
			parentSoundBufferContainer = originalObject.parentSoundBufferContainer;
			originalObject.buffer = nullptr;
			return;
		}
		ExtendedSoundBuffer& operator=(ExtendedSoundBuffer&& rObject) noexcept {
			if (this != &rObject) {
				buffer = rObject.buffer;
				parentSoundBufferContainer = rObject.parentSoundBufferContainer;
				rObject.buffer = nullptr;
			}
			return *this;
		}
};
class SoundBufferContainer : public TaggableContainer<SoundBufferContainer, ExtendedSoundBuffer> {
	public:
		unordered_map<string, ExtendedSoundBuffer>& extended_buffer;
		SoundBufferContainer& load(const string& inputID, const sf::SoundBuffer& inputSoundBuffer) {
			extended_buffer.insert_or_assign(inputID, ExtendedSoundBuffer(this, inputSoundBuffer));
			return *this;
		}
		SoundBufferContainer& loadFromFile(const string& inputID, const string& fileDirectory) {
			extended_buffer.insert_or_assign(inputID, ExtendedSoundBuffer(this, fileDirectory));
			return *this;
		}
		SoundBufferContainer& loadFromMemory(const string& inputID, const unsigned char* data, const size_t& size) {
			extended_buffer.insert_or_assign(inputID, ExtendedSoundBuffer(this, data, size));
			return *this;
		}
		bool exists(const string& inputID) {
			return extended_buffer.count(inputID) != 0;
		}
		SoundBufferContainer& erase(const string& inputID) {
			extended_buffer.erase(inputID);
			return *this;
		}
		SoundBufferContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		SoundBufferContainer& clear() {
			extended_buffer = unordered_map<string, ExtendedSoundBuffer>();
			return *this;
		}
		SoundBufferContainer& clean() {
			for (pair<const string, ExtendedSoundBuffer>& currentExtendedSoundBuffer : extended_buffer) {
				if (!extended_buffer.at(currentExtendedSoundBuffer.first).buffer) {
					erase(currentExtendedSoundBuffer.first);
				}
			}
			return *this;
		}
		sf::SoundBuffer& operator[](const string& inputID) {
			return *extended_buffer.at(inputID).buffer;
		}
		const sf::SoundBuffer& operator[](const string& inputID) const {
			return *extended_buffer.at(inputID).buffer;
		}
		SoundBufferContainer() : extended_buffer(taggables) {}
};

class ExtendedFont : public TaggableElement<ExtendedFont> {
	public:
		FontContainer* parentFontContainer;
		sf::Font* font;
		ExtendedFont& setSmooth(const bool& inputSmooth) {
			if (font) {
				font->setSmooth(inputSmooth);
			}
			return *this;
		}
		ExtendedFont& open(const sf::Font& inputFont) {
			if (font) {
				delete font;
				font = nullptr;
			}
			font = new sf::Font(inputFont);
			return *this;
		}
		ExtendedFont& openFromFile(const string& fileDirectory) {
			if (font) {
				delete font;
				font = nullptr;
			}
			font = new sf::Font();
			if(!font->openFromFile(fileDirectory)) {
				font = nullptr;
			}
			return *this;
		}
		ExtendedFont& openFromMemory(const unsigned char* data, const size_t& size) {
			if (font) {
				delete font;
				font = nullptr;
			}
			font = new sf::Font();
			if(!font->openFromMemory(data, size)) {
				font = nullptr;
			}
			return *this;
		}
		ExtendedFont& load(const sf::Font& inputFont) {
			return open(inputFont);
		}
		ExtendedFont& loadFromFile(const string& fileDirectory) {
			return openFromFile(fileDirectory);
		}
		ExtendedFont& loadFromMemory(const unsigned char* data, const size_t& size) {
			return openFromMemory(data, size);
		}
		ExtendedFont& unload() {
			if (font) {
				delete font;
				font = nullptr;
			}
			return *this;
		}
		ExtendedFont(FontContainer* FontContainerObject, const sf::Font& inputFont) : parentFontContainer(FontContainerObject) {
			font = new sf::Font(inputFont);
			return;
		}
		ExtendedFont(FontContainer* FontContainerObject, const string& fileDirectory) : parentFontContainer(FontContainerObject) {
			font = new sf::Font(fileDirectory);
			return;
		}
		ExtendedFont(FontContainer* FontContainerObject, const unsigned char* data, const size_t& size) : parentFontContainer(FontContainerObject) {
			font = new sf::Font(data, size);
			return;
		}
		ExtendedFont(FontContainer* FontContainerObject) : parentFontContainer(FontContainerObject) {
			font = nullptr;
			return;
		}
		~ExtendedFont() {
			delete font;
			font = nullptr;
			return;
		}
		ExtendedFont(ExtendedFont& originalObject) {
			if (originalObject.font) {
				font = new sf::Font(*originalObject.font);
			} else {
				font = nullptr;
			}
			parentFontContainer = originalObject.parentFontContainer;
			return;
		}
		ExtendedFont& operator=(ExtendedFont& rObject) {
			if (this != &rObject) {
				delete font;
				if (rObject.font) {
					font = new sf::Font(*rObject.font);
				} else {
					font = nullptr;
				}
				parentFontContainer = rObject.parentFontContainer;
			}
			return *this;
		}
		ExtendedFont(ExtendedFont&& originalObject) noexcept : font(originalObject.font) {
			parentFontContainer = originalObject.parentFontContainer;
			originalObject.font = nullptr;
			return;
		}
		ExtendedFont& operator=(ExtendedFont&& rObject) noexcept {
			if (this != &rObject) {
				font = rObject.font;
				parentFontContainer = rObject.parentFontContainer;
				rObject.font = nullptr;
			}
			return *this;
		}
};
class FontContainer : public TaggableContainer<FontContainer, ExtendedFont> {
	public:
		bool defaultFontSmoothness = false;
		unordered_map<string, ExtendedFont>& extended_font;
		FontContainer& update_smoothness() {
			for (pair<const string, ExtendedFont>& currentExtendedFont : extended_font) {
				extended_font.at(currentExtendedFont.first).setSmooth(defaultFontSmoothness);
			}
			return *this;
		}
		FontContainer& open(const string& inputID, const sf::Font& inputFont) {
			extended_font.insert_or_assign(inputID, ExtendedFont(this, inputFont));
			return *this;
		}
		FontContainer& openFromFile(const string& inputID, const string& fileDirectory) {
			extended_font.insert_or_assign(inputID, ExtendedFont(this, fileDirectory));
			return *this;
		}
		FontContainer& openFromMemory(const string& inputID, const unsigned char* data, const size_t& size) {
			extended_font.insert_or_assign(inputID, ExtendedFont(this, data, size));
			return *this;
		}
		FontContainer& load(const string& inputID, const sf::Font& inputFont) {
			return open(inputID, inputFont);
		}
		FontContainer& loadFromFile(const string& inputID, const string& fileDirectory) {
			return openFromFile(inputID, fileDirectory);
		}
		FontContainer& loadFromMemory(const string& inputID, const unsigned char* data, const size_t& size) {
			return openFromMemory(inputID, data, size);
		}
		bool exists(const string& inputID) {
			return extended_font.count(inputID) != 0;
		}
		FontContainer& erase(const string& inputID) {
			extended_font.erase(inputID);
			return *this;
		}
		FontContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		FontContainer& clear() {
			extended_font = unordered_map<string, ExtendedFont>();
			return *this;
		}
		FontContainer& clean() {
			for (pair<const string, ExtendedFont>& currentExtendedFont : extended_font) {
				if (!extended_font.at(currentExtendedFont.first).font) {
					erase(currentExtendedFont.first);
				}
			}
			return *this;
		}
		FontContainer& setSmooth(const bool& inputSmooth = true) {
			defaultFontSmoothness = inputSmooth;
			update_smoothness();
			return *this;
		}
		sf::Font& operator[](const string& inputID) {
			return *extended_font.at(inputID).font;
		}
		const sf::Font& operator[](const string& inputID) const {
			return *extended_font.at(inputID).font;
		}
		FontContainer() : extended_font(taggables) {}
};