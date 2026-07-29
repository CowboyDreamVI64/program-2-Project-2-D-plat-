//  --- HUD (player stat UI) ---
//  
//  This class creates and refreshes the on-screen elements (sprites + text) that show the player
//  their current health, coins, points, and lives. It draws directly in screen-pixel space (using
//  game.resolution), NOT through the world camera/viewport, since it's a UI overlay rather than
//  something that exists in the level.
//  
//  REQUIRES (make sure these are loaded before calling hud.build()/hud.update()):
//  	- A texture loaded under the ID stored in heartTextureID (default "ui.heart")
//  	- A texture loaded under the ID stored in coinTextureID (default "ui.coin")
//  	- A font loaded under the ID stored in fontID (default "main")
//  
//  USAGE:
//  	hud.build();                 //  call once, after textures/fonts are loaded and the sprite/
//  	                              //  text containers have been cleared for the current state
//  	...
//  	hud.update(playerStats);     //  call once per rendered frame, after playerStats has been
//  	                              //  updated for that frame
//  	...
//  	//  When rendering, make sure to pass "texts" into the refresh call as well as "sprites":
//  	game.refresh(true, sprites, texts);
//  -------------------------------------------------------------------------------------------------------
class HUD {
	public:
		string heartTextureID = "ui.heart";
		string coinTextureID = "ui.coin";
		string livesTextureID = "ui.player";
		string fontID = "main";
		
		//  Pixel padding from the top-left corner of the window.
		float paddingX = 16.0f;
		float paddingY = 16.0f;
		
		//  Pixel size/spacing of each heart icon in the health row.
		float heartIconSize = 28.0f;
		float heartIconSpacing = 6.0f;
		
		//  Pixel size of the coin/lives icons.
		float iconSize = 32.0f;
		
		//  The z-value every HUD element is drawn at (should be higher than anything else on screen
		//  so the HUD is never obscured).
		double z = 1000.0;
		
		bool built = false;
		
		//  Creates every sprite/text element the HUD needs. Safe to call again later (e.g. after a
		//  clearall() wipes the sprite/text containers between game states) to rebuild everything.
		HUD& build() {
			sprites.add("hud.coin_icon", textures[coinTextureID], z)
				.resizeToFit(sf::Vector2f({iconSize, iconSize}))
				.setPosition(sf::Vector2f({paddingX, paddingY}));
			
			texts.add("hud.coin_text", fonts[fontID], z)
				.setCharacterSize(22)
				.setFillColor(sf::Color::White);
			
			sprites.add("hud.lives_icon", textures[livesTextureID], z)
				.resizeToFit(sf::Vector2f({iconSize, iconSize}))
				.setPosition(sf::Vector2f({paddingX, paddingY + iconSize + 8.0f}));
			
			texts.add("hud.lives_text", fonts[fontID], z)
				.setCharacterSize(22)
				.setFillColor(sf::Color::White);
			
			texts.add("hud.points_text", fonts[fontID], z)
				.setCharacterSize(22)
				.setFillColor(sf::Color::White);
			
			built = true;
			return *this;
		}
		
		//  Removes every heart-icon sprite currently on screen so update() can rebuild the row from
		//  scratch to match the player's current health/maxHealth.
		HUD& clearHearts() {
			for (const string& heartSpriteID : sprites.get_ids_with_tag("hud.heart")) {
				sprites.erase(heartSpriteID);
			}
			return *this;
		}
		
		//  Refreshes every HUD element to match the passed stats. Call this once per rendered frame
		//  (not once per physics tick) after playerStats has potentially changed.
		HUD& update() {
			if (!built) {
				build();
			}
			
			//  --- Coins ---
			texts["hud.coin_text"]
				.setString("x" + to_string(TOTAL_COINS))
				.setPosition(sf::Vector2f({paddingX + iconSize + 8.0f, paddingY + 4.0f}));
			
			//  --- Lives ---
			texts["hud.lives_text"]
				.setString("x" + to_string(TOTAL_LIVES))
				.setPosition(sf::Vector2f({paddingX + iconSize + 8.0f, paddingY + iconSize + 12.0f}));
			
			//  --- Points (top-right corner) ---
			const string pointsString = string(to_string(TOTAL_SCORE).size() < SCORE_DISPLAY_PADDING ? SCORE_DISPLAY_PADDING - to_string(TOTAL_SCORE).size() : 0, '0') + to_string(TOTAL_SCORE);
			ExtendedText& pointsText = texts["hud.points_text"].setString(pointsString);
			pointsText.setPosition(sf::Vector2f({
				static_cast<float>(game.resolution.x) - pointsText.getGlobalBounds().size.x - paddingX,
				paddingY
			}));
			
			//  --- Health (heart row) ---
			clearHearts();
			for (int i = 0; i < TOTAL_HEALTH; ++i) {
				sprites.add("hud.heart." + to_string(i), textures[heartTextureID], z)
					.add_tag("hud.heart")
					.resizeToFit(sf::Vector2f({heartIconSize, heartIconSize}))
					.setPosition(sf::Vector2f({
						paddingX + i*(heartIconSize + heartIconSpacing),
						paddingY + 2*(iconSize + 8.0f)
					}))
					.setOpacity(i < TOTAL_HEALTH ? 1.0f : 0.25f);
			}
			
			return *this;
		}
};

//  The single global HUD instance.
HUD hud;
