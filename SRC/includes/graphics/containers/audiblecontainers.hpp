class SoundEvent : public TaggableElement<SoundEvent> {
	public:
		SoundContainer* parentSoundContainer;
		sf::Sound* sound;
		float localVolume = 1.0;
		float localPan = 0.0;
		bool loop = false;
		bool paused = false;
		bool bypassPanShift = false;
		SoundEvent& update_volume();
		SoundEvent& update_pan();
		SoundEvent& update_pause();
		SoundEvent& update_loop() {
			if (sound) {
				sound->setLooping(loop);
			}
			return *this;
		}
		SoundEvent& update() {
			update_loop();
			update_volume();
			update_pause();
			update_pan();
			return *this;
		}
		float getVolume() const {
			return localVolume;
		}
		float getPan() const {
			if (sound) {
				return localPan;
			}
			return nan("");
		}
		bool getBypassPanShift() const {
			return bypassPanShift;
		}
		SoundEvent& setBypassPanShift(const bool& inputBypassPanShift = false) {
			bypassPanShift = inputBypassPanShift;
			update_pan();
			return *this;
		}
		float getPitch() const {
			if (sound) {
				return sound->getPitch();
			}
			return nan("");
		}
		bool isPlaying() const {
			if (sound) {
				return (sound->getStatus() == sf::Sound::Status::Playing);
			}
			return false;
		}
		bool isPaused() const {
			return paused;
		}
		bool isStopped() const {
			if (sound) {
				return sound->getStatus() == sf::Sound::Status::Stopped;
			}
			return false;
		}
		bool isLooping() const {
			return loop;
		}
		const sf::SoundBuffer& getBuffer() const {
			if (!sound) {
				throw runtime_error("Manual (std::runtime_error) from (!sound == true); sound buffer get failed");
			}
			return sound->getBuffer();
		}
		sf::Time getTimestamp() const {
			if (sound) {
				return sound->getPlayingOffset();
			}
			return sf::Time();
		}
		sf::Time getDuration() const {
			if (sound) {
				return sound->getBuffer().getDuration();
			}
			return sf::Time();
		}
		SoundEvent& setTimestamp(const sf::Time& inputTime) {
			if (sound) {
				sound->setPlayingOffset(inputTime);
			}
			return *this;
		}
		float getTimestamp_sec() const {
			return getTimestamp().asSeconds();
		}
		float getTimestamp_ms() const {
			return getTimestamp().asMilliseconds();
		}
		float getTimestamp_us() const {
			return getTimestamp().asMicroseconds();
		}
		float getDuration_sec() const {
			return getDuration().asSeconds();
		}
		float getDuration_ms() const {
			return getDuration().asMilliseconds();
		}
		float getDuration_us() const {
			return getDuration().asMicroseconds();
		}
		SoundEvent& setTimestamp_sec(const float& inputTimestamp) {
			setTimestamp(sf::seconds(inputTimestamp));
			return *this;
		}
		SoundEvent& setTimestamp_ms(const float& inputTimestamp) {
			setTimestamp(sf::milliseconds(inputTimestamp));
			return *this;
		}
		SoundEvent& setTimestamp_us(const float& inputTimestamp) {
			setTimestamp(sf::microseconds(inputTimestamp));
			return *this;
		}
		SoundEvent& setBuffer(const sf::SoundBuffer& inputBuffer) {
			delete sound;
			sound = new sf::Sound(inputBuffer);
			update();
			return *this;
		}
		SoundEvent& setVolume(const float inputLocalVolume = 1.0) {
			localVolume = inputLocalVolume;
			update_volume();
			return *this;
		}
		SoundEvent& setPan(float inputPan = 0.0) {
			inputPan = inputPan >= 1.0 ? 1.0 : inputPan;
			inputPan = inputPan <= -1.0 ? -1.0 : inputPan;
			localPan = inputPan;
			update_pan();
			return *this;
		}
		SoundEvent& setPitch(float inputPitch = 1.0) {
			inputPitch *= inputPitch >= 0.0;
			if (sound) {
				sound->setPitch(inputPitch);
			}
			return *this;
		}
		SoundEvent& setPause(const bool& pauseNow) {
			paused = pauseNow;
			update_pause();
			return *this;
		}
		SoundEvent& setLooping(const bool& loopNow) {
			loop = loopNow;
			update_loop();
			return *this;
		}
		SoundEvent& pause() {
			paused = true;
			update_pause();
			return *this;
		}
		SoundEvent& unpause() {
			paused = false;
			update_pause();
			return *this;
		}
		SoundEvent& resume() {
			unpause();
			return *this;
		}
		SoundEvent& reset() {
			if (sound) {
				sound->stop();
			}
			setTimestamp_sec(0.0);
			pause();
			return *this;
		}
		SoundEvent& stop() {
			if (sound) {
				sound->stop();
			}
			return *this;
		}
		SoundEvent& replay() {
			reset();
			unpause();
			if (sound) {
				sound->play();
			}
			return *this;
		}
		SoundEvent(SoundContainer* SoundContainerObject, const sf::SoundBuffer& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentSoundContainer(SoundContainerObject), bypassPanShift(inputBypassPanShift) {
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
		SoundEvent(const SoundEvent& originalObject) {
			if (originalObject.sound) {
				sound = new sf::Sound(*originalObject.sound);
			} else {
				sound = nullptr;
			}
			localVolume = originalObject.localVolume,
			paused = originalObject.paused,
			loop = originalObject.loop;
			parentSoundContainer = originalObject.parentSoundContainer;
			update();
			return;
		}
		SoundEvent& operator=(const SoundEvent& rObject) {
			if (this != &rObject) {
				delete sound;
				if (rObject.sound) {
					sound = new sf::Sound(*rObject.sound);
				} else {
					sound = nullptr;
				}
				localVolume = rObject.localVolume,
				paused = rObject.paused,
				loop = rObject.loop;
				parentSoundContainer = rObject.parentSoundContainer;
				update();
			}
			return *this;
		}
		SoundEvent(SoundEvent&& originalObject) noexcept : sound(originalObject.sound) {
			localVolume = originalObject.localVolume,
			paused = originalObject.paused,
			loop = originalObject.loop;
			parentSoundContainer = originalObject.parentSoundContainer;
			update_volume();
			update_loop();
			update_pause();
			originalObject.sound = nullptr;
			return;
		}
		SoundEvent& operator=(SoundEvent&& rObject) noexcept {
			if (this != &rObject) {
				sound = rObject.sound;
				localVolume = rObject.localVolume,
				paused = rObject.paused,
				loop = rObject.loop;
				parentSoundContainer = rObject.parentSoundContainer;
				update_volume();
				update_loop();
				update_pause();
				rObject.sound = nullptr;
			}
			return *this;
		}
};
class SoundContainer : public TaggableContainer<SoundContainer, SoundEvent> {
	friend SoundEvent;
	
	private:
		float masterVolume = 1.0;
		float panShift = 0.0;
		bool masterPaused = false;
	public:
		unordered_map<string, SoundEvent>& event;
		SoundEvent& play(const string& inputID, sf::SoundBuffer& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, SoundEvent(this, inputBuffer, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return event.at(inputID);
		}
		SoundContainer& update_volume() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_volume();
			}
			return *this;
		}
		SoundContainer& update_loop() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_loop();
			}
			return *this;
		}
		SoundContainer& update_pause() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pause();
			}
			return *this;
		}
		SoundContainer& update() {
			update_loop();
			update_volume();
			update_pause();
			return *this;
		}
		float getVolume() const {
			return masterVolume;
		}
		bool isPlaying() const {
			return !masterPaused;
		}
		bool isPaused() const {
			return masterPaused;
		}
		bool exists(const string& inputID) const {
			return event.count(inputID) != 0;
		}
		SoundContainer& update_pan() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pan();
			}
			return *this;
		}
		float getPanShift(const bool& deg = true) const {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		SoundContainer& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return *this;
		}
		SoundContainer& setVolume(const float& inputMasterVolume) {
			masterVolume = inputMasterVolume;
			update_volume();
			return *this;
		}
		SoundContainer& setPause(const bool& pauseNow) {
			masterPaused = pauseNow;
			update_pause();
			return *this;
		}
		SoundContainer& pause() {
			masterPaused = true;
			return *this;
		}
		SoundContainer& unpause() {
			masterPaused = false;
			update_pause();
			return *this;
		}
		SoundContainer& resume() {
			unpause();
			return *this;
		}
		SoundContainer& erase(const string& inputID) {
			event.erase(inputID);
			return *this;
		}
		SoundContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		SoundContainer& clear() {
			event = unordered_map<string, SoundEvent>();
			return *this;
		}
		SoundContainer& clean() {
			for (pair<const string, SoundEvent>& currentEvent : event) {
				if (event.at(currentEvent.first).isStopped()) {
					erase(currentEvent.first);
				}
			}
			return *this;
		}
		SoundEvent& operator[](const string& inputID) {
			return event.at(inputID);
		}
		const SoundEvent& operator[](const string& inputID) const {
			return event.at(inputID);
		}
		SoundContainer(const float& inputMasterVolume = 1.0) : masterVolume(inputMasterVolume), event(taggables) {
			masterVolume = masterVolume >= 1.0 ? 1.0 : masterVolume;
			masterVolume *= masterVolume >= 0.0;
			return;
		}
};
SoundEvent& SoundEvent::update_volume() {
	if (sound && parentSoundContainer) {
		if (parentSoundContainer) {
			sound->setVolume(localVolume*parentSoundContainer->masterVolume*100.0f);
		} else {
			sound->setVolume(localVolume*100.0f);
		}
	}
	return *this;
}
SoundEvent& SoundEvent::update_pan() {
	if (sound){
		if (!bypassPanShift && parentSoundContainer && parentSoundContainer->panShift != 0.0) {
			sound->setPan(cos(acos(localPan) + parentSoundContainer->panShift));
		} else {
			sound->setPan(localPan);
		}
	}
	return *this;
}
SoundEvent& SoundEvent::update_pause() {
	if (sound) {
		if (paused || (parentSoundContainer && parentSoundContainer->masterPaused)) {
			sound->pause();
		} else {
			sound->play();
		}
	}
	return *this;
}

class MusicEvent : public TaggableElement<MusicEvent> {
	public:
		MusicContainer* parentMusicContainer;
		sf::Music music;
		float localVolume = 1.0;
		float localPan = 0.0;
		bool loop = false;
		bool paused = false;
		bool bypassPanShift = false;
		sf::Time loopStart = sf::Time::Zero;
		sf::Time loopEnd = sf::Time::Zero;
		MusicEvent& update_volume();
		MusicEvent& update_pan();
		MusicEvent& update_pause();
		MusicEvent& update_loop() {
			music.setLooping(loop);
			return *this;
		}
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
		sf::Music::TimeSpan getLoopPoints() const {
			return music.getLoopPoints();
		}
		sf::Time getLoopPointStart() const {
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
		MusicEvent& setLoopPoints_sec(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::seconds(startDuration), sf::seconds(endDuration), useEndAsDuration);
			return *this;
		}
		MusicEvent& setLoopPoints_ms(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::milliseconds(startDuration), sf::milliseconds(endDuration), useEndAsDuration);
			return *this;
		}
		MusicEvent& setLoopPoints_us(const float& startDuration, const float& endDuration, const bool& useEndAsDuration = true) {
			setLoopPoints(sf::microseconds(startDuration), sf::microseconds(endDuration), useEndAsDuration);
			return *this;
		}
		sf::Time loop_begin() const {
			return loopStart;
		}
		sf::Time loop_end() const {
			return loopEnd;
		}
		sf::Time loop_duration() const {
			return loopEnd - loopStart;
		}
		sf::Time duration() const {
			return music.getDuration();
		}
		float getLoopPointStart_sec() const {
			return getLoopPointStart().asSeconds();
		}
		float getLoopPointStart_ms() const {
			return getLoopPointStart().asMilliseconds();
		}
		float getLoopPointStart_us() const {
			return getLoopPointStart().asMicroseconds();
		}
		float getLoopPointDuration_sec(const bool& useEndAsDuration = true) const {
			return getLoopPointDuration(useEndAsDuration).asSeconds();
		}
		float getLoopPointDuration_ms(const bool& useEndAsDuration = true) const {
			return getLoopPointDuration(useEndAsDuration).asMilliseconds();
		}
		float getLoopPointDuration_us(const bool& useEndAsDuration = true) const {
			return getLoopPointDuration(useEndAsDuration).asMicroseconds();
		}
		float getVolume() const {
			return localVolume;
		}
		float getPan() const {
			return localPan;
		}
		bool getBypassPanShift() const {
			return bypassPanShift;
		}
		MusicEvent& setBypassPanShift(const bool& inputBypassPanShift = false) {
			bypassPanShift = inputBypassPanShift;
			update_pan();
			return *this;
		}
		float getPitch() const {
			return music.getPitch();
		}
		bool isPlaying() const {
			return (music.getStatus() == sf::Music::Status::Playing);
		}
		bool isPaused() const {
			return paused;
		}
		bool isStopped() const {
			return music.getStatus() == sf::Music::Status::Stopped;
		}
		bool isLooping() const {
			return loop;
		}
		sf::Time getTimestamp() const {
			return music.getPlayingOffset();
		}
		sf::Time getDuration() const {
			return music.getDuration();
		}
		MusicEvent& setTimestamp(const sf::Time& inputTime) {
			music.setPlayingOffset(inputTime);
			return *this;
		}
		float getTimestamp_sec() const {
			return getTimestamp().asSeconds();
		}
		float getTimestamp_ms() const {
			return getTimestamp().asMilliseconds();
		}
		float getTimestamp_us() const {
			return getTimestamp().asMicroseconds();
		}
		float getDuration_sec() const {
			return getDuration().asSeconds();
		}
		float getDuration_ms() const {
			return getDuration().asMilliseconds();
		}
		float getDuration_us() const {
			return getDuration().asMicroseconds();
		}
		MusicEvent& setTimestamp_sec(const float& inputTimestamp) {
			setTimestamp(sf::seconds(inputTimestamp));
			return *this;
		}
		MusicEvent& setTimestamp_ms(const float& inputTimestamp) {
			setTimestamp(sf::milliseconds(inputTimestamp));
			return *this;
		}
		MusicEvent& setTimestamp_us(const float& inputTimestamp) {
			setTimestamp(sf::microseconds(inputTimestamp));
			return *this;
		}
		MusicEvent& setVolume(const float inputLocalVolume = 1.0) {
			localVolume = inputLocalVolume;
			update_volume();
			return *this;
		}
		MusicEvent& setPan(float inputPan = 0.0) {
			inputPan = inputPan >= 1.0 ? 1.0 : inputPan;
			inputPan = inputPan <= -1.0 ? -1.0 : inputPan;
			localPan = inputPan;
			update_pan();
			return *this;
		}
		MusicEvent& setPitch(float inputPitch = 1.0) {
			inputPitch *= inputPitch >= 0.0;
			music.setPitch(inputPitch);
			return *this;
		}
		MusicEvent& setPause(const bool& pauseNow) {
			paused = pauseNow;
			update_pause();
			return *this;
		}
		MusicEvent& setLooping(const bool& loopNow) {
			loop = loopNow;
			update_loop();
			return *this;
		}
		MusicEvent& pause() {
			paused = true;
			update_pause();
			return *this;
		}
		MusicEvent& unpause() {
			paused = false;
			update_pause();
			return *this;
		}
		MusicEvent& resume() {
			unpause();
			return *this;
		}
		MusicEvent& reset() {
			music.stop();
			setTimestamp_sec(0.0);
			pause();
			return *this;
		}
		MusicEvent& stop() {
			music.stop();
			return *this;
		}
		MusicEvent& replay() {
			reset();
			unpause();
			music.play();
			return *this;
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
		MusicEvent& openFromMemory(const vector<char>& inputBuffer) {
			openFromMemory(inputBuffer.data(), inputBuffer.size());
			return *this;
		}
		MusicEvent& loadFromFile(const string& inputPath) {
			openFromFile(inputPath);
			return *this;
		}
		MusicEvent& loadFromMemory(const char* inputData, size_t inputSize) {
			openFromMemory(inputData, inputSize);
			return *this;
		}
		MusicEvent& loadFromMemory(const vector<char>& inputBuffer) {
			openFromMemory(inputBuffer);
			return *this;
		}
		MusicEvent(MusicContainer* MusicContainerObject, const string& inputPath, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentMusicContainer(MusicContainerObject), bypassPanShift(inputBypassPanShift) {
			music = sf::Music(inputPath);
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		MusicEvent(MusicContainer* MusicContainerObject, const char* inputData, const size_t& inputSize, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentMusicContainer(MusicContainerObject), bypassPanShift(inputBypassPanShift) {
			music = sf::Music(inputData, inputSize);
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
		MusicEvent(MusicContainer* MusicContainerObject, const vector<char>& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) : localVolume(inputLocalVolume), paused(!playNow), loop(loopNow), parentMusicContainer(MusicContainerObject), bypassPanShift(inputBypassPanShift) {
			music = sf::Music(inputBuffer.data(), inputBuffer.size());
			resetLoopPoints();
			localVolume = localVolume >= 1.0 ? 1.0 : localVolume;
			localVolume *= localVolume >= 0.0;
			update();
			return;
		}
};
class MusicContainer : public TaggableContainer<MusicContainer, MusicEvent> {
	friend MusicEvent;
	
	private:
		float masterVolume = 1.0;
		float panShift = 0.0;
		bool masterPaused = false;
	public:
		unordered_map<string, MusicEvent>& event;
		MusicContainer& play(const string& inputID, const string& inputPath, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputPath, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer& play(const string& inputID, const char* inputData, const size_t& inputSize, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputData, inputSize, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer& play(const string& inputID, const vector<char>& inputBuffer, const float& inputLocalVolume = 1.0, const bool& playNow = true, const bool& loopNow = false, const bool& inputBypassPanShift = false) {
			event.insert_or_assign(inputID, MusicEvent(this, inputBuffer, inputLocalVolume, playNow, loopNow, inputBypassPanShift));
			return *this;
		}
		MusicContainer& update_volume() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_volume();
			}
			return *this;
		}
		MusicContainer& update_loop() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_loop();
			}
			return *this;
		}
		MusicContainer& update_pause() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pause();
			}
			return *this;
		}
		MusicContainer& update() {
			update_loop();
			update_volume();
			update_pause();
			return *this;
		}
		float getVolume() const {
			return masterVolume;
		}
		bool isPlaying() const {
			return !masterPaused;
		}
		bool isPaused() const {
			return masterPaused;
		}
		bool exists(const string& inputID) const {
			return event.count(inputID) != 0;
		}
		MusicContainer& update_pan() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				event.at(currentEvent.first).update_pan();
			}
			return *this;
		}
		float getPanShift(const bool& deg = true) const {
			return panShift * (deg ? 180.0 / acos(-1.0) : 1.0);
		}
		MusicContainer& setPanShift(float inputFloat = 0.0, const bool& deg = true) {
			panShift = fmod(inputFloat*(deg ? acos(-1.0)/180.0 : 1.0), 2*acos(-1.0));
			update_pan();
			return *this;
		}
		MusicContainer& setVolume(const float& inputMasterVolume) {
			masterVolume = inputMasterVolume;
			update_volume();
			return *this;
		}
		MusicContainer& setPause(const bool& pauseNow) {
			masterPaused = pauseNow;
			update_pause();
			return *this;
		}
		MusicContainer& pause() {
			masterPaused = true;
			return *this;
		}
		MusicContainer& unpause() {
			masterPaused = false;
			update_pause();
			return *this;
		}
		MusicContainer& resume() {
			unpause();
			return *this;
		}
		MusicContainer& erase(const string& inputID) {
			event.erase(inputID);
			return *this;
		}
		MusicContainer& remove(const string& inputID) {
			erase(inputID);
			return *this;
		}
		MusicContainer& clear() {
			event = unordered_map<string, MusicEvent>();
			return *this;
		}
		MusicContainer& clean() {
			for (pair<const string, MusicEvent>& currentEvent : event) {
				if (event.at(currentEvent.first).isStopped()) {
					erase(currentEvent.first);
				}
			}
			return *this;
		}
		MusicEvent& operator[](const string& inputID) {
			return event.at(inputID);
		}
		const MusicEvent& operator[](const string& inputID) const {
			return event.at(inputID);
		}
		MusicContainer(const float& inputMasterVolume = 1.0) : masterVolume(inputMasterVolume), event(taggables) {
			masterVolume = masterVolume >= 1.0 ? 1.0 : masterVolume;
			masterVolume *= masterVolume >= 0.0;
			return;
		}
};
MusicEvent& MusicEvent::update_volume() {
	if (parentMusicContainer) {
		music.setVolume(localVolume*parentMusicContainer->masterVolume*100.0f);
	} else {
		music.setVolume(localVolume*100.0f);
	}
	return *this;
}
MusicEvent& MusicEvent::update_pan() {
	if (!bypassPanShift && parentMusicContainer && parentMusicContainer->panShift != 0.0) {
		music.setPan(cos(acos(localPan) + parentMusicContainer->panShift));
	} else {
		music.setPan(localPan);
	}
	return *this;
}
MusicEvent& MusicEvent::update_pause() {
	if (paused || (parentMusicContainer && parentMusicContainer->masterPaused)) {
		music.pause();
	} else {
		music.play();
	}
	return *this;
}