class ExtendedTexture : public ResourceElement<sf::Texture, TextureContainer, ExtendedTexture> {
	friend ResourceElement<sf::Texture, TextureContainer, ExtendedTexture>;
	
	public:
		TextureContainer*& parentTextureContainer;
		sf::Texture*& texture;
		ExtendedTexture& setSmooth(const bool& inputSmooth) {
			if (texture) {
				texture->setSmooth(inputSmooth);
			}
			return *this;
		}
		ExtendedTexture& loadFromImage(const sf::Image& inputImage) {
			if (texture && texture->loadFromImage(inputImage)) {}
			
			return *this;
		}
		
		template <typename dConstructorT>
		ExtendedTexture(TextureContainer* inputParentContainer, const dConstructorT& inputDConstructor)
			: parentTextureContainer(parentContainer), texture(r), ResourceElement(inputParentContainer, inputDConstructor)
		{}
		ExtendedTexture(TextureContainer* inputParentContainer, const unsigned char* data, const size_t& size)
			: parentTextureContainer(parentContainer), texture(r), ResourceElement(inputParentContainer, data, size)
		{}
		ExtendedTexture(TextureContainer* inputParentContainer)
			: parentTextureContainer(parentContainer), texture(r), ResourceElement(inputParentContainer)
		{}
		ExtendedTexture(const ExtendedTexture& other)
			: parentTextureContainer(parentContainer), texture(r), ResourceElement(other)
		{}
		ExtendedTexture(ExtendedTexture&& other) noexcept
			: parentTextureContainer(parentContainer), texture(r), ResourceElement(static_cast<ExtendedTexture&&>(other))
		{}
		ExtendedTexture operator=(const ExtendedTexture& other) {
			ResourceElement::operator=(other);
			parentTextureContainer = parentContainer;
			texture = r;
			
			return *this;
		}
		ExtendedTexture operator=(ExtendedTexture&& other) noexcept {
			ResourceElement::operator=(static_cast<ExtendedTexture&&>(other));
			parentTextureContainer = parentContainer;
			texture = r;
			
			return *this;
		}
};
class TextureContainer : public ResourceContainer<sf::Texture, TextureContainer, ExtendedTexture> {
	public:
		bool defaultTextureSmoothness;
		unordered_map<string, ExtendedTexture>& extended_texture;
		TextureContainer& update_smoothness() {
			for (pair<const string, ExtendedTexture>& currentExtendedTexture : extended_texture) {
				extended_texture.at(currentExtendedTexture.first).setSmooth(defaultTextureSmoothness);
			}
			return *this;
		}
		TextureContainer& setSmooth(const bool& inputSmooth = true) {
			defaultTextureSmoothness = inputSmooth;
			update_smoothness();
			return *this;
		}
		
		TextureContainer(const bool& inputDefaultTextureSmoothness = false) : defaultTextureSmoothness(inputDefaultTextureSmoothness), extended_texture(taggables) {}
};

class ExtendedSoundBuffer : public ResourceElement<sf::SoundBuffer, SoundBufferContainer, ExtendedSoundBuffer> {
	friend ResourceElement<sf::SoundBuffer, SoundBufferContainer, ExtendedSoundBuffer>;
	
	public:
		SoundBufferContainer*& parentSoundBufferContainer;
		sf::SoundBuffer*& buffer;

		template <typename dConstructorT>
		ExtendedSoundBuffer(SoundBufferContainer* inputParentContainer, const dConstructorT& inputDConstructor)
			: parentSoundBufferContainer(parentContainer), buffer(r), ResourceElement(inputParentContainer, inputDConstructor)
		{}
		ExtendedSoundBuffer(SoundBufferContainer* inputParentContainer, const unsigned char* data, const size_t& size)
			: parentSoundBufferContainer(parentContainer), buffer(r), ResourceElement(inputParentContainer, data, size)
		{}
		ExtendedSoundBuffer(SoundBufferContainer* inputParentContainer)
			: parentSoundBufferContainer(parentContainer), buffer(r), ResourceElement(inputParentContainer)
		{}
		ExtendedSoundBuffer(const ExtendedSoundBuffer& other)
			: parentSoundBufferContainer(parentContainer), buffer(r), ResourceElement(other)
		{}
		ExtendedSoundBuffer(ExtendedSoundBuffer&& other) noexcept
			: parentSoundBufferContainer(parentContainer), buffer(r), ResourceElement(static_cast<ExtendedSoundBuffer&&>(other))
		{}
		ExtendedSoundBuffer operator=(const ExtendedSoundBuffer& other) {
			ResourceElement::operator=(other);
			parentSoundBufferContainer = parentContainer;
			buffer = r;
			
			return *this;
		}
		ExtendedSoundBuffer operator=(ExtendedSoundBuffer&& other) noexcept {
			ResourceElement::operator=(static_cast<ExtendedSoundBuffer&&>(other));
			parentSoundBufferContainer = parentContainer;
			buffer = r;
			
			return *this;
		}
};
class SoundBufferContainer : public ResourceContainer<sf::SoundBuffer, SoundBufferContainer, ExtendedSoundBuffer> {
	public:
		unordered_map<string, ExtendedSoundBuffer>& extended_buffer;
		
		SoundBufferContainer() : extended_buffer(taggables) {}
};

class ExtendedFont : public ResourceElement<sf::Font, FontContainer, ExtendedFont> {
	friend ResourceElement<sf::Font, FontContainer, ExtendedFont>;
	
	public:
		FontContainer*& parentFontContainer;
		sf::Font*& font;
		ExtendedFont& setSmooth(const bool& inputSmooth) {
			if (font) {
				font->setSmooth(inputSmooth);
			}
			return *this;
		}
		ExtendedFont& loadFromFile(const string& inputFileDirectory) {
			if (font && font->openFromFile(inputFileDirectory)) {}
			
			return *this;
		}
		ExtendedFont& loadFromMemory(const unsigned char* data, const size_t& size) {
			if (font && font->openFromMemory(data, size)) {}
			
			return *this;
		}
		

		template <typename dConstructorT>
		ExtendedFont(FontContainer* inputParentContainer, const dConstructorT& inputDConstructor)
			: parentFontContainer(parentContainer), font(r), ResourceElement(inputParentContainer, inputDConstructor)
		{}
		ExtendedFont(FontContainer* inputParentContainer, const unsigned char* data, const size_t& size)
			: parentFontContainer(parentContainer), font(r), ResourceElement(inputParentContainer, data, size)
		{}
		ExtendedFont(FontContainer* inputParentContainer)
			: parentFontContainer(parentContainer), font(r), ResourceElement(inputParentContainer)
		{}
		ExtendedFont(const ExtendedFont& other)
			: parentFontContainer(parentContainer), font(r), ResourceElement(other)
		{}
		ExtendedFont(ExtendedFont&& other) noexcept
			: parentFontContainer(parentContainer), font(r), ResourceElement(static_cast<ExtendedFont&&>(other))
		{}
		ExtendedFont operator=(const ExtendedFont& other) {
			ResourceElement::operator=(other);
			parentFontContainer = parentContainer;
			font = r;
			
			return *this;
		}
		ExtendedFont operator=(ExtendedFont&& other) noexcept {
			ResourceElement::operator=(static_cast<ExtendedFont&&>(other));
			parentFontContainer = parentContainer;
			font = r;
			
			return *this;
		};
};
class FontContainer : public ResourceContainer<sf::Font, FontContainer, ExtendedFont> {
	public:
		unordered_map<string, ExtendedFont>& extended_font;
		
		bool defaultFontSmoothness = false;
		FontContainer& update_smoothness() {
			for (pair<const string, ExtendedFont>& currentExtendedFont : extended_font) {
				extended_font.at(currentExtendedFont.first).setSmooth(defaultFontSmoothness);
			}
			return *this;
		}
		FontContainer& setSmooth(const bool& inputSmooth = true) {
			defaultFontSmoothness = inputSmooth;
			update_smoothness();
			return *this;
		}

		FontContainer(const bool& inputDefaultFontSmoothness = false) : defaultFontSmoothness(inputDefaultFontSmoothness), extended_font(taggables) {}
};