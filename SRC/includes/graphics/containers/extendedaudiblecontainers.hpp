class SoundEvent : public AudibleElement<sf::Sound, SoundContainer, SoundEvent> {
	friend AudibleElement<sf::Sound, SoundContainer, SoundEvent>;
	friend SoundContainer;
	
	public:
		sf::Sound* sound;
	protected:
		inline sf::Sound& audible() {
			return *sound;
		}
		inline const sf::Sound& audible() const {
			return *sound;
		}
		inline bool audibleValid() const {
			return sound != nullptr;  //  false if nullptr, true otherwise.
		}
	
	public:
		SoundContainer*& parentSoundContainer;

		SoundEvent& update() {
			update_loop();
			update_volume();
			update_pause();
			update_pan();
			return *this;
		}
		const sf::SoundBuffer& getBuffer() const {
			if (!audibleValid()) {
				throw runtime_error("Manual (std::runtime_error) from (!sound == true); sound buffer get failed");
			}
			return audible().getBuffer();
		}
		sf::Time getDuration() const {
			if (audibleValid()) {
				return audible().getBuffer().getDuration();
			}
			return sf::Time();
		}
		SoundEvent& setBuffer(const sf::SoundBuffer& inputBuffer) {
			delete sound;
			sound = new sf::Sound(inputBuffer);
			update();
			return *this;
		}
		SoundEvent(SoundContainer* inputParentContainer, const sf::SoundBuffer& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false)
			: parentSoundContainer(parentContainer), AudibleElement(inputParentContainer, inputLocalVolume, playNow, loopNow, inputBypassPanShift)
		{
			sound = new sf::Sound(inputBuffer);
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		~SoundEvent() {
			delete sound;
			sound = nullptr;
			return;
		}
		SoundEvent(const SoundEvent& other)
			: parentSoundContainer(parentContainer), AudibleElement(other.parentContainer, other.localVolume, other.paused, other.loop, other.bypassPanShift)
		{
			if (this != &other) {
				localPan = other.localPan;
				if (other.sound) {
					sound = new sf::Sound(*other.sound);
				} else {
					sound = nullptr;
				}
				update();
			}
		}
		SoundEvent(SoundEvent&& other) noexcept
			: parentSoundContainer(parentContainer), AudibleElement(other.parentContainer, other.localVolume, other.paused, other.loop, other.bypassPanShift)
		{
			if (this != &other) {
				if (other.sound) {
					sound = other.sound;
					other.sound = nullptr;
				} else {
					sound = nullptr;
				}
				
				update();
			}
		}
		SoundEvent& operator=(const SoundEvent& other) {
			parentSoundContainer = parentContainer;
			if (this != &other) {
				AudibleElement::operator=(other);
				if (other.sound) {
					sound = new sf::Sound(*other.sound);
				} else {
					sound = nullptr;
				}
				
				update();
			}
			return *this;
		}
		SoundEvent& operator=(SoundEvent&& other) {
			parentSoundContainer = parentContainer;
			if (this != &other) {
				AudibleElement::operator=(other);
				if (other.sound) {
					sound = other.sound;
					other.sound = nullptr;
				} else {
					sound = nullptr;
				}
				
				update();
			}
			return *this;
		}
};
class SoundContainer : public AudibleContainer<sf::Sound, SoundContainer, SoundEvent> {
	friend AudibleContainer<sf::Sound, SoundContainer, SoundEvent>;
	friend SoundEvent;
	
	public:
		inline SoundEvent& play(const string& inputID, sf::SoundBuffer& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, SoundEvent(this, inputBuffer, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return event.at(inputID);
		}
		SoundContainer(const float& inputMasterVolume = 1.0) : AudibleContainer(inputMasterVolume) {}
};

class MusicEvent : public AudibleElement<sf::Music, MusicContainer, MusicEvent> {
	friend AudibleElement<sf::Music, MusicContainer, MusicEvent>;
	friend MusicContainer;
	
	public:
		sf::Music music;
	protected:
		inline sf::Music& audible() {
			return music;
		}
		inline const sf::Music& audible() const {
			return music;
		}
		inline bool audibleValid() const {
			return true;
		}
		
		sf::Time loopStart = sf::Time::Zero;
		sf::Time loopEnd = sf::Time::Zero;
	public:
		MusicContainer*& parentMusicContainer;
		
		MusicEvent& update_loop_points() {
			sf::Time musicDuration = music.getDuration();
			if (loopStart < sf::Time::Zero) {
				loopStart = sf::Time::Zero;
			} else if (loopEnd > musicDuration) {
				loopEnd = musicDuration;
			}
			if (loopEnd < sf::Time::Zero) {
				loopStart = sf::Time::Zero;
			} else if (loopEnd > musicDuration) {
				loopEnd = musicDuration;
			}
			music.setLoopPoints(sf::Music::TimeSpan({loopStart, loopEnd}));
			return *this;
		}
		MusicEvent& update() {
			update_loop();
			update_volume();
			update_pause();
			update_pan();
			update_loop_points();
			return *this;
		}
		inline sf::Music::TimeSpan getLoopPoints() const {
			return music.getLoopPoints();
		}
		inline sf::Time getLoopPointStart() const {
			return loopStart;
		}
		sf::Time getLoopPointDuration(const bool& useEndAsDuration = true) const {
			if (useEndAsDuration) {
				return loopEnd - loopStart;
			} else {
				return loopEnd;
			}
		}
		MusicEvent& setLoopPoints(const sf::Time& startDuration, const sf::Time& endDuration, const bool& useEndAsDuration = true) {
			loopStart = startDuration;
			loopEnd = endDuration;
			if (useEndAsDuration) {
				loopEnd += startDuration;
			}
			update_loop_points();
			return *this;
		}
		MusicEvent& resetLoopPoints() {
			loopStart = sf::Time::Zero;
			loopEnd = music.getDuration();
			update_loop_points();
			return *this;
		}
		inline MusicEvent& setLoopPoints_sec(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::seconds(startDuration), sf::seconds(endDuration), useEndAsDuration);
			return *this;
		}
		inline MusicEvent& setLoopPoints_ms(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::milliseconds(startDuration), sf::milliseconds(endDuration), useEndAsDuration);
			return *this;
		}
		inline MusicEvent& setLoopPoints_us(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::microseconds(startDuration), sf::microseconds(endDuration), useEndAsDuration);
			return *this;
		}
		inline sf::Time loop_begin() const {
			return loopStart;
		}
		inline sf::Time loop_end() const {
			return loopEnd;
		}
		inline sf::Time loop_duration() const {
			return loopEnd - loopStart;
		}
		inline sf::Time getDuration() const {
			return music.getDuration();
		}
		inline float getLoopPointStart_sec() const {
			return getLoopPointStart().asSeconds();
		}
		inline float getLoopPointStart_ms() const {
			return getLoopPointStart().asMilliseconds();
		}
		inline float getLoopPointStart_us() const {
			return getLoopPointStart().asMicroseconds();
		}
		inline float getLoopPointDuration_sec(const bool& useEndAsDuration = true) const {
			return getLoopPointDuration(useEndAsDuration).asSeconds();
		}
		inline float getLoopPointDuration_ms(const bool& useEndAsDuration = true) const {
			return getLoopPointDuration(useEndAsDuration).asMilliseconds();
		}
		inline float getLoopPointDuration_us(const bool& useEndAsDuration = true) const {
			return getLoopPointDuration(useEndAsDuration).asMicroseconds();
		}
		MusicEvent& openFromFile(const string& inputPath) {
			if (!music.openFromFile(inputPath)) {
				throw runtime_error("Manual (std::runtime_error) from (!music.openFromFile(inputPath) == true); music buffer load failed");
			}
			resetLoopPoints();
			return *this;
		}
		MusicEvent& openFromMemory(const char* inputData, size_t inputSize) {
			if (!music.openFromMemory(inputData, inputSize)) {
				throw runtime_error("Manual (std::runtime_error) from (!music.openFromMemory(inputData, inputSize) == true); music buffer load failed");
			}
			loopStart = sf::Time::Zero;
			loopEnd = getDuration();
			return *this;
		}
		inline MusicEvent& openFromMemory(const vector<char>& inputBuffer) {
			openFromMemory(inputBuffer.data(), inputBuffer.size());
			return *this;
		}
		inline MusicEvent& loadFromFile(const string& inputPath) {
			openFromFile(inputPath);
			return *this;
		}
		inline MusicEvent& loadFromMemory(const char* inputData, size_t inputSize) {
			openFromMemory(inputData, inputSize);
			return *this;
		}
		inline MusicEvent& loadFromMemory(const vector<char>& inputBuffer) {
			openFromMemory(inputBuffer);
			return *this;
		}
		MusicEvent(MusicContainer* inputParentContainer, const string& inputPath, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false)
			: music(inputPath), parentMusicContainer(parentContainer), AudibleElement(inputParentContainer, inputLocalVolume, playNow, loopNow, inputBypassPanShift)
		{
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		
		MusicEvent(MusicContainer* inputParentContainer, const char* inputData, const size_t& inputSize, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false)
			: music(inputData, inputSize), parentMusicContainer(parentContainer), AudibleElement(inputParentContainer, inputLocalVolume, playNow, loopNow, inputBypassPanShift)
		{
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		
		MusicEvent(MusicContainer* inputParentContainer, const vector<char>& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false)
			: music(inputBuffer.data(), inputBuffer.size()), parentMusicContainer(parentContainer), AudibleElement(inputParentContainer, inputLocalVolume, playNow, loopNow, inputBypassPanShift)
		{
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		
		//  Copy constructors removed because sf::Music is non-copyable
		//MusicEvent(const MusicEvent& other)
		//	: music(other.music), parentMusicContainer(parentContainer), AudibleElement(other.parentContainer, other.localVolume, other.paused, other.loop, other.bypassPanShift) {}
		
		MusicEvent(MusicEvent&& other) noexcept
			: music(static_cast<sf::Music&&>(other.music)), parentMusicContainer(parentContainer), AudibleElement(other.parentContainer, other.localVolume, !other.paused, other.loop, other.bypassPanShift)
		{
		
		}
		
		//MusicEvent& operator=(const MusicEvent& other) {
		//	parentMusicContainer = parentContainer;
		//	music = other.music;
		//	AudibleElement::operator=(other);
		//	return *this;
		//}
		
		MusicEvent& operator=(MusicEvent&& other) {
			parentMusicContainer = parentContainer;
			music = static_cast<sf::Music&&>(other.music);
			AudibleElement::operator=(other);
			return *this;
		}
};
class MusicContainer : public AudibleContainer<sf::Music, MusicContainer, MusicEvent> {
	friend AudibleContainer<sf::Music, MusicContainer, MusicEvent>;
	friend MusicEvent;
	
	public:
		inline MusicContainer& play(const string& inputID, const string& inputPath, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputPath, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		inline MusicContainer& play(const string& inputID, const char* inputData, const size_t& inputSize, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputData, inputSize, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		inline MusicContainer& play(const string& inputID, const vector<char>& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputBuffer, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer(const float& inputMasterVolume = 1.0) : AudibleContainer(inputMasterVolume) {}
};
