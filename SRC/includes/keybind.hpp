//  Contains a list of keybinds that attribute to certain entity actions
struct KeyBind {
	sf::Keyboard::Key up;
	sf::Keyboard::Key left;
	sf::Keyboard::Key down;
	sf::Keyboard::Key right;
	sf::Keyboard::Key jump;
	sf::Keyboard::Key sprint;
	
	//  This returns a list of boolean that are true depending on if the corresponding key WAS pressed
	array<bool, 6> getInputBool(ExtendedWindow& window) const {
		return {
			game.pollForKey(up),
			game.pollForKey(left),
			game.pollForKey(down),
			game.pollForKey(right),
			game.pollForKey(jump),
			game.pollForKey(sprint)
		};
	}
};
//  This is a default set of keybinds (WASD, space to jump, shift to sprint)
KeyBind defaultKeyBinds{sf::Keyboard::Key::W, sf::Keyboard::Key::A, sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::Space, sf::Keyboard::Key::LShift};