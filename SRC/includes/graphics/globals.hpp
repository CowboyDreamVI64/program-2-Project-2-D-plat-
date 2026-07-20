//  This is a global texture object that we can use to store a screenshot of the window for special transition effects.
sf::Texture lastFrameScreenshot;

//  This creates the actual game window as an ExtendedWindow container.
//  - The first argument is the window name.
//  - The second argument is the resolution.
//  - The third argument is the framerate.
//  - The fourth argument is a boolean for whether to start in fullscreen (this can be modified at runtime).
//  - The fifth argument is a boolean for whether to use Vsync.
//  - The sixth argument is a multiplier for how large the window should be compared to the monitor when opened.
ExtendedWindow game = ExtendedWindow("Platformer", {1280, 720}, 60, false, false, 0.67);	

//  This creates a container of ExtendedSounds to use globally.
SoundContainer sounds = SoundContainer();

//  This creates a container of ExtendedMusics to use globally.
MusicContainer musics = MusicContainer();

//  This creates a container of ExtendedSprites to use globally.
SpriteContainer sprites = SpriteContainer();

//  This creates a container of ExtendedTexts to use globally.
TextContainer texts = TextContainer();

//  These create two containers of Stopwatches: one for integral (frame-by-frame) timers and one for floating-point (seconds-based) timers.
StopwatchContainer istopwatches = StopwatchContainer<long long>();
StopwatchContainer fstopwatches = StopwatchContainer<float>();

//  This creates a container of ExtendedTextures to use globally.
TextureContainer textures = TextureContainer();

//  This creates a container of ExtendedSoundBuffers to use globally.
SoundBufferContainer sound_buffers = SoundBufferContainer();

//  This creates a container of ExtendedFonts to use globally.
FontContainer fonts = FontContainer();

//  This creates a container of TextureFlipbooks to use globally.
TextureFlipbookContainer texture_flipbooks = TextureFlipbookContainer();

//  This creates a container of TextureFlipbooks to use globally.
SoundListContainer sound_lists = SoundListContainer();

//  When the program switches from one state to another, you may want to erase all sprites and texts but not all sounds or textures.
//  These helper constants and helper functions controls this.

//  These constants are passed through clearall; whatever one of these constants are passed through will make it so that clearall does NOT
//  clear the corresponding global container.
namespace Omit {
	const short Screenshot = 1;
	const short Sounds = 2;
	const short Musics = 3;
	const short Sprites = 4;
	const short Texts = 5;
	const short IStopwatches = 6;
	const short FStopwatches = 7;
	const short Textures = 8;
	const short SoundBuffers = 9;
	const short Fonts = 10;
	const short TextureFlipbooks = 11;
	const short SoundLists = 12;
}
bool clearcondition(const vector<short>& omitValues, const short& inputCondition) {
	return !count(omitValues.begin(), omitValues.end(), inputCondition) > 0;
}

//  This clears all the contents of all the containers EXCEPT for the containers specified in omitValues.
void clearall(const vector<short>& omitValues = vector<short>(0)) {
	if (clearcondition(omitValues, Omit::Screenshot)) {
		lastFrameScreenshot = game.screenshot();
	}
	if (clearcondition(omitValues, Omit::Sounds)) {
		sounds.clear();
	}
	if (clearcondition(omitValues, Omit::Musics)) {
		musics.clear();
	}
	if (clearcondition(omitValues, Omit::Sprites)) {
		sprites.clear();
	}
	if (clearcondition(omitValues, Omit::Texts)) {
		texts.clear();
	}
	if (clearcondition(omitValues, Omit::IStopwatches)) {
		istopwatches.clear();
	}
	if (clearcondition(omitValues, Omit::FStopwatches)) {
		fstopwatches.clear();
	}
	if (clearcondition(omitValues, Omit::Textures)) {
		textures.clear();
	}
	if (clearcondition(omitValues, Omit::SoundBuffers)) {
		sound_buffers.clear();
	}
	if (clearcondition(omitValues, Omit::Fonts)) {
		fonts.clear();
	}
	if (clearcondition(omitValues, Omit::TextureFlipbooks)) {
		texture_flipbooks.clear();
	}
	if (clearcondition(omitValues, Omit::SoundLists)) {
		sound_lists.clear();
	}
	return;
}

//  This loads all inputted textures into the textures container given the key string of the texture within the global assets variable.
TextureContainer& loadAllTextures(TextureContainer& inputTextureContainer, const vector<vector<string>>& inputTextures) {
	for (size_t i = 0; i < inputTextures.size(); ++i) {
		inputTextureContainer.loadFromMemory(inputTextures[i][0], assets[inputTextures[i][1]].data(), assets[inputTextures[i][1]].size());
	}
	return inputTextureContainer;
}

//  This loads all inputted textures into the sounds buffer container given the key string of the sound buffer within the global assets variable.
SoundBufferContainer& loadAllSoundBuffers(SoundBufferContainer& inputSoundBufferContainer, const vector<vector<string>>& inputSoundBuffers) {
	for (size_t i = 0; i < inputSoundBuffers.size(); ++i) {
		inputSoundBufferContainer.loadFromMemory(inputSoundBuffers[i][0], assets[inputSoundBuffers[i][1]].data(), assets[inputSoundBuffers[i][1]].size());
	}
	return inputSoundBufferContainer;
}

//  This loads all inputted textures into the fonts container given the key string of the font within the global assets variable.
FontContainer& loadAllFonts(FontContainer& inputFontContainer, const vector<vector<string>>& inputFonts) {
	for (size_t i = 0; i < inputFonts.size(); ++i) {
		inputFontContainer.openFromMemory(inputFonts[i][0], assets[inputFonts[i][1]].data(), assets[inputFonts[i][1]].size());
	}
	return inputFontContainer;
}