#pragma once

class InputMgr
{
private:
	enum class State
	{
		Release,
		Down,
		Pressing,
	};
	
	static std::vector<std::bitset<3>> vecInput;
public:
	static void clear();
	static void updateEvent(const sf::Event& ev);

	static bool isKeyDown(const sf::Keyboard::Key& key);
	static bool isKeyPressing(const sf::Keyboard::Key& key);
	static bool isKeyUp(const sf::Keyboard::Key& key);

	static bool isMouseButtonDown(const sf::Mouse::Button& btn);
	static bool isMouseButtonPressing(const sf::Mouse::Button& btn);
	static bool isMouseButtonUp(const sf::Mouse::Button& btn);

	static sf::Vector2i getMousePosition(const sf::RenderWindow& curWindow);
};
