template <typename T>
class Stopwatch : public TaggableElement<Stopwatch<T>> {
	public:
		StopwatchContainer<T>* parentStopwatchContainer;
		T frame;
		T maxFrame;
		bool localPause;
		bool loop;
		bool tickBackwards;
		bool useMax;
		bool setBackState = false;
		Stopwatch& elapse(const T& elapseAmount = 1);
		Stopwatch& clamp() {
			if (useMax) {
				if (frame > maxFrame) {
					if (loop) {
						frame = 0;
					} else {
						frame = maxFrame;
					}
				} else if (frame < 0) {
					if (loop) {
						frame = maxFrame;
					} else {
						frame = 0;
					}
				}
			} else if (frame < 0) {
				frame = 0;
			}
			return *this;
		}
		Stopwatch& add(const T& frames = 1) {
			frame += frames;
			clamp();
			return *this;
		}
		Stopwatch& subtract(const T& frames = 1) {
			if (frame > frames) {
				frame -= frames;
			} else {
				frame = 0;
			}
			clamp();
			return *this;
		}
		Stopwatch& offset(const T& frames = 0, const bool& reverseDirection = false) {
			short multiplier = reverseDirection ? -1 : 1;
			if (frames*multiplier >= 0) {
				add(frames*multiplier);
			} else {
				subtract(-frames*multiplier);
			}
			return *this;
		}
		Stopwatch& set(const T& frames = 0) {
			frame = frames;
			clamp();
			return *this;
		}
		Stopwatch& setTickDirection(const bool& inputTickBackwards = false) {
			tickBackwards = inputTickBackwards;
			return *this;
		}
		bool getTickDirection() {
			return tickBackwards;
		}
		Stopwatch& setBack(const T& frames = 0) {
			frame = frames;
			clamp();
			setBackState = true;
			return *this;
		}
		Stopwatch& reset() {
			frame = 0;
			clamp();
			return *this;
		}
		Stopwatch& pause() {
			localPause = true;
			return *this;
		}
		Stopwatch& unpause() {
			localPause = false;
			return *this;
		}
		Stopwatch& resume() {
			localPause = false;
			return *this;
		}
		Stopwatch& setLoop(const bool& inputLoop) {
			loop = inputLoop;
			clamp();
			return *this;
		}
		bool isPaused() {
			return localPause;
		}
		bool isLooping() {
			return loop;
		}
		Stopwatch& setMax(const T& inputMaxFrame) {
			maxFrame = inputMaxFrame;
			useMax = true;
			clamp();
			return *this;
		}
		Stopwatch& resetMax() {
			maxFrame = 0;
			useMax = false;
			clamp();
			return *this;
		}
		T getMax() {
			return maxFrame;
		}
		float invlerp(const double& intervalStart, const double& intervalEnd) {
			if (intervalStart == intervalEnd) {
				return nan("");
			}
			float invLerpValue = (frame - intervalStart)/(intervalEnd - intervalStart);
			invLerpValue *= invLerpValue >= 0.0;
			invLerpValue = invLerpValue >= 1.0 ? 1.0 : invLerpValue;
			return static_cast<float>(invLerpValue);
		}
		Stopwatch(StopwatchContainer<T>* StopwatchContainerObject, const T& startingFrame = 0, const bool& inputPause = false, const bool& inputLoop = false, const bool& inputUseMax = false, const T& inputMaxFrame = 0, const bool& inputTickBackwards = false) : frame(startingFrame), localPause(inputPause), loop(inputLoop), useMax(inputUseMax), maxFrame(inputMaxFrame), parentStopwatchContainer(StopwatchContainerObject), tickBackwards(inputTickBackwards) {};
};
template <typename T>
class StopwatchContainer : public TaggableContainer<Stopwatch<T>> {
	public:
		bool masterPause;
		unordered_map<string, Stopwatch<T>> stopwatch;
		Stopwatch<T>& start(const string& inputID, const T& startingFrame = 0, const bool& inputPause = false, const bool& inputLoop = false, const bool& inputUseMax = false, const T& inputMaxFrame = 0, const bool& inputTickBackwards = false) {
			stopwatch.insert_or_assign(inputID, Stopwatch(this, startingFrame, inputPause, inputLoop, inputUseMax, inputMaxFrame, inputTickBackwards));
			return stopwatch.at(inputID);
		}
		StopwatchContainer& stop(const string& inputID) {
			stopwatch.erase(inputID);
			return *this;
		}
		StopwatchContainer& add(const T& frames = 1) {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).add(frames);
			}
			return *this;
		}
		StopwatchContainer& subtract(const T& frames = 1) {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).subtract(frames);
			}
			return *this;
		}
		StopwatchContainer& offset(const T& frames = 0, const bool& reverseDirection = false) {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).offset(frames, reverseDirection);
			}
			return *this;
		}
		StopwatchContainer& reset() {
			for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
				stopwatch.at(currentWatch.first).reset();
			}
			return *this;
		}
		StopwatchContainer& elapse(const T& elapseAmount = 1) {
			if (!masterPause) {
				for (pair<string, Stopwatch<T>> currentWatch : stopwatch) {
					stopwatch.at(currentWatch.first).elapse(elapseAmount);
				}
			}
			return *this;
		}
		bool exists(const string& inputID) {
			return stopwatch.count(inputID) != 0;
		}
		StopwatchContainer& pause() {
			masterPause = true;
			return *this;
		}
		StopwatchContainer& unpause() {
			masterPause = false;
			return *this;
		}
		StopwatchContainer& resume() {
			masterPause = false;
			return *this;
		}
		bool isPaused() {
			return masterPause;
		}
		StopwatchContainer& clear() {
			stopwatch = unordered_map<string, Stopwatch<T>>();
			return *this;
		}
		Stopwatch<T>& operator[](const string& inputID) {
			return stopwatch.at(inputID);
		}
		const Stopwatch<T>& operator[](const string& inputID) const {
			return stopwatch.at(inputID);
		}
		StopwatchContainer(const bool& inputPause = false) : masterPause(inputPause) {
			this->taggables = &stopwatch;
		}
};
template <typename T>
Stopwatch<T>& Stopwatch<T>::elapse(const T& elapseAmount) {
	if (parentStopwatchContainer) {
		if (!parentStopwatchContainer->masterPause && !localPause) {
			if (!setBackState) {
				if (!tickBackwards) {
					add(elapseAmount);
				} else {
					subtract(elapseAmount);
				}
			} else {
				setBackState = false;
			}
		}
	}
	clamp();
	return *this;
}