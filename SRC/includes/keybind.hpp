struct KeyBind {
	sf::Keyboard::Key up;
	sf::Keyboard::Key left;
	sf::Keyboard::Key down;
	sf::Keyboard::Key right;
	sf::Keyboard::Key jump;
	sf::Keyboard::Key sprint;
	
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
KeyBind defaultKeyBinds{sf::Keyboard::Key::W, sf::Keyboard::Key::A, sf::Keyboard::Key::S, sf::Keyboard::Key::D, sf::Keyboard::Key::Space, sf::Keyboard::Key::LShift};