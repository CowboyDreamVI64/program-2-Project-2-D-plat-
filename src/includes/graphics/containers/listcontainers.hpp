class TexturePage {
	public:
		sf::Texture* texture;
		size_t length = 0;
		double weight = 0.0;
		TexturePage(sf::Texture& inputTexture, const size_t& inputLength = 1, const double& inputWeight = 1.0) : texture(&inputTexture), length(inputLength), weight(inputWeight) {
			weight *= weight > 0.0;
			return;
		}
		TexturePage() {
			return;
		}
};
class TextureFlipbook {
	public:
		bool looping;
		size_t loop_starting_frame;
		vector<TexturePage> texture_pages;
		TextureFlipbook& add(const vector<TexturePage>& inputTexturePages) {
			for (const TexturePage& texturePage : inputTexturePages) {
				texture_pages.push_back(texturePage);
			}
			return *this;
		}
		TextureFlipbook& add(vector<sf::Texture>& inputTextures) {
			for (sf::Texture& inputTexture : inputTextures) {
				texture_pages.push_back(TexturePage(inputTexture));
			}
			return *this;
		}
		size_t getFrameTotal() {
			size_t totalFrames = 0;
			for (const TexturePage& texturePage : texture_pages) {
				totalFrames += texturePage.length;
			}
			return totalFrames;
		}
		double getWeightTotal() {
			double totalWeight = 0;
			for (const TexturePage& texturePage : texture_pages) {
				totalWeight += texturePage.weight;
			}
			return totalWeight;
		}
		sf::Texture& getAtIndex(const size_t& inputIndex) {
			return *texture_pages.at(inputIndex).texture;
		}
		TextureFlipbook& removeAtIndex(const size_t& inputIndex) {
			texture_pages.erase(texture_pages.begin() + inputIndex);
			return *this;
		}
		TexturePage& insertAtIndex(const size_t& inputIndex, const TexturePage& inputTexturePage) {
			texture_pages.insert(texture_pages.begin() + inputIndex, inputTexturePage);
			return texture_pages.at(inputIndex);
		}
		long long getIndex(long long inputFrame = 0) {
			long long maxFrame = getFrameTotal() - 1;
			long long targetFrame = inputFrame;
			if (looping) {
				if (inputFrame > maxFrame) {
					inputFrame -= maxFrame + 1;
					targetFrame %= maxFrame + 1 - loop_starting_frame;
					targetFrame += loop_starting_frame;
				}
			} else if (inputFrame >= maxFrame) {
				targetFrame = maxFrame;
			} else if (inputFrame < 0) {
				targetFrame = 0;
			}
			for (size_t i = 0; i < texture_pages.size(); ++i) {
				if (targetFrame < texture_pages[i].length) {
					return i;
				} else {
					targetFrame -= texture_pages[i].length;
				}
			}
			return texture_pages.size() - 1;
		}
		long long getIndex(const double& inputLerpValue = 0.0) {
			return getIndex(static_cast<long long>(getFrameTotal() * inputLerpValue));
		}
		sf::Texture& get(const long long& inputFrame = 0) {
			return *texture_pages.at(getIndex(inputFrame)).texture;
		}
		sf::Texture& get(const double& inputLerpValue = 0.0) {
			return *texture_pages.at(getIndex(inputLerpValue)).texture;
		}
		sf::Texture& getRandom() {
			double targetWeight = getWeightTotal() * drandom();
			for (size_t i = 0; i < texture_pages.size(); ++i) {
				if (targetWeight < texture_pages[i].weight) {
					return *texture_pages.at(i).texture;
				} else {
					targetWeight -= texture_pages[i].weight;
				}
			}
			return *texture_pages.at(0).texture;
		}
		TextureFlipbook& remove(const long long& inputFrame = 0) {
			texture_pages.erase(texture_pages.begin() + getIndex(inputFrame));
			return *this;
		}
		TextureFlipbook& remove(const double& inputLerpValue = 0.0) {
			texture_pages.erase(texture_pages.begin() + getIndex(inputLerpValue));
			return *this;
		}
		bool getLoop() {
			return looping;
		}
		TextureFlipbook& setLoop(const bool& inputLoop) {
			looping = inputLoop;
			return *this;
		}
		TextureFlipbook& clear() {
			texture_pages = vector<TexturePage>();
			return *this;
		}
		TextureFlipbook& create(const vector<TexturePage>& inputTexturePages) {
			texture_pages = inputTexturePages;
			return *this;
		}
		TextureFlipbook& create(vector<sf::Texture>& inputTextures) {
			for (sf::Texture& inputTexture : inputTextures) {
				texture_pages.push_back(TexturePage(inputTexture, 1, 1.0));
			}
			return *this;
		}
		TextureFlipbook& safeAssignAtIndex(const size_t& inputIndex, const TexturePage& inputTexturePage) {
			if (texture_pages.size() <= inputIndex) {
				texture_pages.resize(inputIndex + 1, TexturePage());
			}
			texture_pages[inputIndex] = inputTexturePage;
			return *this;
		}
		TextureFlipbook& safeAssignAtIndex(const size_t& inputIndex, sf::Texture& inputTexture) {
			if (texture_pages.size() <= inputIndex) {
				texture_pages.resize(inputIndex + 1, TexturePage());
			}
			texture_pages[inputIndex] = TexturePage(inputTexture);
			return *this;
		}
		sf::Texture& operator[](const long long& inputFrame) {
			return get(inputFrame);
		}
		TextureFlipbook(const vector<TexturePage>& inputTexturePages, const bool& inputLoop = false, const size_t& inputLoopStartingFrame = 0) : looping(inputLoop), loop_starting_frame(inputLoopStartingFrame) {
			texture_pages = inputTexturePages;
			return;
		}
		TextureFlipbook(vector<sf::Texture>& inputTextures, const bool& inputLoop = false, const size_t& inputLoopStartingFrame = 0) : looping(inputLoop), loop_starting_frame(inputLoopStartingFrame) {
			for (sf::Texture& inputTexture : inputTextures) {
				texture_pages.push_back(TexturePage(inputTexture, 1, 1.0));
			}
			return;
		}
		TextureFlipbook() {
			return;
		}
};
class TextureFlipbookContainer {
	public:
		unordered_map<string, TextureFlipbook> texture_flipbooks;
		TextureFlipbook& add(const string& inputID, const TextureFlipbook& inputTextureFlipbook) {
			texture_flipbooks.insert_or_assign(inputID, inputTextureFlipbook);
			return texture_flipbooks.at(inputID);
		}
		TextureFlipbookContainer& remove(const string& inputID) {
			texture_flipbooks.erase(inputID);
			return *this;
		}
		TextureFlipbookContainer& clear() {
			texture_flipbooks = unordered_map<string, TextureFlipbook>();
			return *this;
		}
		TextureFlipbook& at(const string& inputID) {
			return texture_flipbooks.at(inputID);
		}
		bool exists(const string& inputID) {
			return texture_flipbooks.count(inputID) != 0;
		}
		TextureFlipbook& operator[](const string& inputID) {
			return texture_flipbooks.at(inputID);
		}
		const TextureFlipbook& operator[](const string& inputID) const {
			return texture_flipbooks.at(inputID);
		}
};

class SoundEntry {
	public:
		sf::Sound sound;
		float localVolume;
		float localPan;
		double weight;
		SoundEntry(const sf::SoundBuffer& inputSoundBuffer = sf::SoundBuffer(), const float& inputLocalVolume = 1.0, float inputPanning = 0.0, float inputPitch = 1.0, double inputWeight = 1.0) : sound(sf::Sound(inputSoundBuffer)), localVolume(inputLocalVolume) {
			inputPanning = inputPanning >= 1.0 ? 1.0 : inputPanning;
			inputPanning = inputPanning <= -1.0 ? -1.0 : inputPanning;
			localPan = inputPanning;
			inputPitch *= inputPitch >= 0.0;
			inputWeight *= inputWeight > 0.0;
			weight = inputWeight;
			sound.setPan(localPan);
			sound.setPitch(inputPitch);
		}
};
class SoundList {
	public:
		float masterVolume = 1.0;
		bool masterPaused = false;
		float panShift = 0.0;
		vector<SoundEntry> sound_entries;
		SoundList& update_volume() {
			for (SoundEntry& inputSoundEntry : sound_entries) {
				inputSoundEntry.sound.setVolume(masterVolume * inputSoundEntry.localVolume * 100.0f);
			}
			return *this;
		}
		SoundList& update_pause() {
			if (masterPaused) {
				for (SoundEntry& inputSoundEntry : sound_entries) {
					inputSoundEntry.sound.pause();
				}
			} else {
				for (SoundEntry& inputSoundEntry : sound_entries) {
					inputSoundEntry.sound.play();
				}
			}
			return *this;
		}
		SoundList& update_pan() {
			for (SoundEntry& inputSoundEntry : sound_entries) {
				if (panShift == 0.0) {
					inputSoundEntry.sound.setPan(inputSoundEntry.localPan);
				} else {
					inputSoundEntry.sound.setPan(cos(acos(inputSoundEntry.localPan) + panShift));
				}
			}
			return *this;
		}
		bool getVolume() {
			return masterVolume;
		}
		SoundList& setVolume(float inputMasterVolume) {
			inputMasterVolume *= inputMasterVolume > 0.0;
			inputMasterVolume = inputMasterVolume > 1.0 ? 1.0 : inputMasterVolume;
			masterVolume = inputMasterVolume;
			update_volume();
			return *this;
		}
		SoundList& setPause(const bool& inputPause) {
			masterPaused = inputPause;
			update_pause();
			return *this;
		}
		SoundList& pause() {
			masterPaused = true;
			update_pause();
			return *this;
		}
		SoundList& unpause() {
			masterPaused = false;
			update_pause();
			return *this;
		}
		SoundList& resume() {
			unpause();
			return *this;
		}
		bool inactive() {
			for (size_t i = 0; i < sound_entries.size(); ++i) {
				if (sound_entries[i].sound.getStatus() != sf::Sound::Status::Stopped) {
					return false;
				}
			}
			return true;
		}
		SoundList& clean() {
			for (size_t i = 0; i < sound_entries.size(); ++i) {
				if (sound_entries[i].sound.getStatus() == sf::Sound::Status::Stopped) {
					sound_entries.erase(sound_entries.begin() + i);
					--i;
				}
			}
			return *this;
		}
		SoundList& clear() {
			sound_entries = vector<SoundEntry>();
			return *this;
		}
		float getPanShift(const bool& deg = true) {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		SoundList& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return *this;
		}
		SoundList& add(const sf::SoundBuffer& inputSoundBuffer, float inputLocalVolume = 1.0, float inputPanning = 0.0, float inputPitch = 1.0, double inputWeight = 1.0, const bool& forcePlay = false) {
			sound_entries.push_back(SoundEntry(inputSoundBuffer, inputLocalVolume, inputPanning, inputPitch, inputWeight));
			if (!forcePlay && masterPaused) {
				sound_entries[sound_entries.size() - 1].sound.pause();
			} else {
				sound_entries[sound_entries.size() - 1].sound.play();
			}
			update_volume();
			return *this;
		}
		SoundList& add(const vector<SoundEntry>& inputSoundEntries, const bool& forcePlay = false) {
			size_t oldSize = sound_entries.size();
			sound_entries.insert(sound_entries.begin(), inputSoundEntries.begin(), inputSoundEntries.end());
			if (!forcePlay && masterPaused) {
				for (size_t i = oldSize - 1;  i < sound_entries.size(); ++i) {
					sound_entries[i].sound.pause();
				}
			} else {
				for (size_t i = oldSize - 1;  i < sound_entries.size(); ++i) {
					sound_entries[i].sound.play();
				}
			}
			update_volume();
			return *this;
		}
		SoundList& insert(const SoundEntry& inputSoundEntry, const size_t& inputIndex) {
			sound_entries.insert(sound_entries.begin() + inputIndex, inputSoundEntry);
			return *this;
		}
		SoundList& remove(const size_t& inputIndex) {
			sound_entries.erase(sound_entries.begin() + inputIndex);
			return *this;
		}
		SoundEntry& get(const size_t& inputIndex) {
			return sound_entries[inputIndex];
		}
		SoundList& play(const size_t& inputIndex) {
			get(inputIndex).sound.play();
			return *this;
		}
		SoundEntry& getRandom() {
			return sound_entries[size_t_random(0, sound_entries.size() - 1)];
		}
		SoundList& playRandom() {
			getRandom().sound.play();
			return *this;
		}
		SoundList(const vector<SoundEntry>& inputSoundEntries = vector<SoundEntry>(), float inputMasterVolume = 1.0, const bool inputMasterPaused = false, const float& inputPanShift = 0.0) : masterVolume(inputMasterVolume), masterPaused(inputMasterPaused), panShift(inputPanShift) {
			sound_entries = inputSoundEntries;
			update_volume();
			update_pause();
			return;
		}
		SoundList(vector<sf::SoundBuffer>& inputSoundBuffers, float inputMasterVolume = 1.0, const bool inputMasterPaused = false, const float& inputPanShift = 0.0) : masterVolume(inputMasterVolume), masterPaused(inputMasterPaused), panShift(inputPanShift) {
			for (sf::SoundBuffer& inputSoundBuffer : inputSoundBuffers) {
				sound_entries.push_back(SoundEntry(inputSoundBuffer));
			}
			update_volume();
			update_pause();
			return;
		}
};
class SoundListContainer {
	public:
		unordered_map<string, SoundList> sound_flipbooks;
		SoundList& add(const string& inputID, const SoundList& inputSoundList = SoundList()) {
			sound_flipbooks.insert_or_assign(inputID, inputSoundList);
			return sound_flipbooks.at(inputID);
		}
		SoundListContainer& remove(const string& inputID) {
			sound_flipbooks.erase(inputID);
			return *this;
		}
		SoundListContainer& clear() {
			sound_flipbooks = unordered_map<string, SoundList>();
			return *this;
		}
		SoundList& at(const string& inputID) {
			return sound_flipbooks.at(inputID);
		}
		bool exists(const string& inputID) {
			return sound_flipbooks.count(inputID) != 0;
		}
		SoundList& operator[](const string& inputID) {
			return sound_flipbooks.at(inputID);
		}
		const SoundList& operator[](const string& inputID) const {
			return sound_flipbooks.at(inputID);
		}
};