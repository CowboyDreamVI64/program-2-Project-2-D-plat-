class AnimationFrame {
	public:
	    string TextureID;
	    double length;
	    Vec2 size;
	    Vec2 offset;
	    
	    AnimationFrame(const string& TextureID, double length = 1.0, Vec2 size = 1.0, Vec2 offset = 0.0) {
	        this->TextureID = TextureID;
	        if (length < 0) {
	            this->length = 0;
	        }
	        else {
	            this->length = length;
	        }
	        this->offset = offset;
	        this->size = size;
	    }
};

class Animation {
	public:
	    vector<AnimationFrame> frames;
	    bool loop;
	    double loopStart;
	
	    inline Animation& append(const AnimationFrame& frame) {
	        frames.push_back(frame);
	        return *this;
	    }
	
	    size_t getIndexAtLength(double length) const {
	        if (length < 0) {
	            length = 0;
	        }
	        
	        double accumulator = length;
	        size_t finalIndex = 0;
	
	        for (size_t i = 0; i < frames.size();) {
	            finalIndex = i;
	            
	            if (accumulator < frames[i].length) {
	                break;
	            } else {
	                accumulator -= frames[i].length;
	            }
	
	            if (i == frames.size() - 1 && loop == true) {
	                i = 0;
	                accumulator += loopStart;
	                continue;
	            }
	
	            ++i;
	        }
	
	        return finalIndex;
	    }
	
	    inline bool is_empty() const {
	        return frames.size() == 0;
	    }
	
	    inline Animation& insert(size_t index, const AnimationFrame& frame) {
	        frames.insert(frames.begin() + index, frame);
	        return *this;
	    }
	
	    inline Animation& erase(size_t index) {
	        frames.erase(frames.begin() + index);
	        return *this;
	    }
	    
	    inline AnimationFrame& getFrame(size_t index) {
	        return frames.at(index);
	    }
	    inline const AnimationFrame& getFrame(size_t index) const {
	        return frames.at(index);
	    }
	    
	    Animation(const vector<AnimationFrame>& frames, bool loop = false, double loopStart = 0.0) {
	        this->frames = frames;
	        this->loop = loop;
	        if (loopStart < 0) {
	            this->loopStart = 0;
	        }
	        else {
	            this->loopStart = loopStart;
	        }
	    }
};

class AnimationState {
    private:
	    unordered_map<string, Animation> animations;
	    string currentAnimationID;
	    double animationTime = 0;
    
    public:
	    bool paused;
	    
	    inline AnimationState& add(const string& ID, const Animation& animation) {
	        animations.insert_or_assign(ID, animation);
	        return *this;
	    }
	    
	    inline AnimationState& remove(const string& currentAnimationID) {
	        animations.erase(currentAnimationID);
	        return *this;
	    }
	    
	    inline string getAnimationID() const {
	        return currentAnimationID;
	    }
	    
	    AnimationState& setAnimationID(string currentAnimationID) {
	        if (animations.count(currentAnimationID) != 0) {
	            this->currentAnimationID = currentAnimationID;
	            animationTime = 0;
	        }
	        return *this;
	    }
	    
	    inline double getTime() const {
	        return animationTime;
	    }
	    
	    AnimationState& setTime(double animationTime) {
	        if (animationTime < 0) {
	            animationTime = 0;
	        }
	        else {
	            this->animationTime = animationTime;
	        }
	        return *this;
	    }
	    
	    inline AnimationState& tick(double input_time) {
	        if (!paused) {
	            animationTime += input_time;
	        }
	        return *this;
	    }
	    
	    inline AnimationFrame& getAnimationFrame() {
	        Animation& currentAnimation = animations.at(currentAnimationID);	
	        return currentAnimation.getFrame(currentAnimation.getIndexAtLength(animationTime));
	    }
	    inline const AnimationFrame& getAnimationFrame() const {
	        const Animation& currentAnimation = animations.at(currentAnimationID);	
	        return currentAnimation.getFrame(currentAnimation.getIndexAtLength(animationTime));
	    }
	    
	    inline AnimationState(const unordered_map<string, Animation>& inputAnimations, const string& inputAnimationID)
			: animations(inputAnimations), currentAnimationID(inputAnimationID) {}
	    inline AnimationState() {}
};