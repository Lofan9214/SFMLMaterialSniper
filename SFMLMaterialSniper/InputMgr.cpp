#include "stdafx.h"

std::vector<std::bitset<3>> InputMgr::vecInput(sf::Keyboard::KeyCount + sf::Mouse::ButtonCount, 0);

void InputMgr::clear()
{
	std::bitset<3> remover = 0;
	remover[(int)State::Pressing] = true;

	for (auto& it : vecInput)
	{
		it &= remover;
	}

	remover[(int)State::Pressing] = true;

}

void InputMgr::updateEvent(const sf::Event& ev)
{
	int idx = 0;
	std::bitset<3> setter = 0;
	
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		idx = ev.key.code;
		if (idx < 0 || idx >= sf::Keyboard::KeyCount)
		{
			return;
		}
		setter[(int)State::Down] = !vecInput[idx][(int)State::Pressing];
		setter[(int)State::Pressing] = true;
		break;
	case sf::Event::KeyReleased:
		idx = ev.key.code;
		if (idx < 0 || idx >= sf::Keyboard::KeyCount)
		{
			return;
		}
		setter[(int)State::Release] = true;
		break;
	case sf::Event::MouseButtonPressed:
		idx = sf::Keyboard::KeyCount + ev.mouseButton.button;
		setter[(int)State::Down] = !vecInput[idx][(int)State::Pressing];
		setter[(int)State::Pressing] = true;
		break;
	case sf::Event::MouseButtonReleased:
		idx = sf::Keyboard::KeyCount + ev.mouseButton.button;
		setter[(int)State::Release] = true;
		break;
	default:
		return;
	}
	vecInput[idx] = setter;
}

bool InputMgr::isKeyDown(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Down];
}

bool InputMgr::isKeyPressing(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Pressing];
}

bool InputMgr::isKeyUp(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Release];
}

bool InputMgr::isMouseButtonDown(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Down];
}

bool InputMgr::isMouseButtonPressing(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Pressing];
}

bool InputMgr::isMouseButtonUp(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Release];
}

sf::Vector2i InputMgr::getMousePosition(const sf::RenderWindow& curWindow)
{
	return sf::Mouse::getPosition(curWindow);
}


