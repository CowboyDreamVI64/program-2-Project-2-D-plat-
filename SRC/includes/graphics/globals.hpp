sf::Texture lastFrameScreenshot;
ExtendedWindow game = ExtendedWindow("Platformer", {1920, 1080}, 60, false, false, 0.67);	
SoundContainer sounds = SoundContainer();
MusicContainer musics = MusicContainer();
SpriteContainer sprites = SpriteContainer();
TextContainer texts = TextContainer();
StopwatchContainer istopwatches = StopwatchContainer<long long>();
StopwatchContainer fstopwatches = StopwatchContainer<float>();
TextureContainer textures = TextureContainer();
SoundBufferContainer sound_buffers = SoundBufferContainer();
FontContainer fonts = FontContainer();
TextureFlipbookContainer texture_flipbooks = TextureFlipbookContainer();
SoundListContainer sound_lists = SoundListContainer();

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

TextureContainer& loadAllTextures(TextureContainer& inputTextureContainer, const vector<vector<string>>& inputTextures) {
	for (size_t i = 0; i < inputTextures.size(); ++i) {
		inputTextureContainer.loadFromMemory(inputTextures[i][0], assets[inputTextures[i][1]].data(), assets[inputTextures[i][1]].size());
	}
	return inputTextureContainer;
}
SoundBufferContainer& loadAllSoundBuffers(SoundBufferContainer& inputSoundBufferContainer, const vector<vector<string>>& inputSoundBuffers) {
	for (size_t i = 0; i < inputSoundBuffers.size(); ++i) {
		inputSoundBufferContainer.loadFromMemory(inputSoundBuffers[i][0], assets[inputSoundBuffers[i][1]].data(), assets[inputSoundBuffers[i][1]].size());
	}
	return inputSoundBufferContainer;
}
FontContainer& loadAllFonts(FontContainer& inputFontContainer, const vector<vector<string>>& inputFonts) {
	for (size_t i = 0; i < inputFonts.size(); ++i) {
		inputFontContainer.openFromMemory(inputFonts[i][0], assets[inputFonts[i][1]].data(), assets[inputFonts[i][1]].size());
	}
	return inputFontContainer;
}