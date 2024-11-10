#include "stdafx.h"

std::vector<std::bitset<3>> InputMgr::vecInput(sf::Keyboard::KeyCount + sf::Mouse::ButtonCount, 0);
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;
sf::Vector2i InputMgr::mousePosition;

void InputMgr::Init()
{
	AxisInfo axisInfoH;
	axisInfoH.axis = Axis::Horizontal;
	axisInfoH.AddKey(true, sf::Keyboard::D);
	axisInfoH.AddKey(true, sf::Keyboard::Right);
	axisInfoH.AddKey(false, sf::Keyboard::A);
	axisInfoH.AddKey(false, sf::Keyboard::Left);
	axisInfoMap.insert({ Axis::Horizontal,axisInfoH });
	AxisInfo axisInfoV;
	axisInfoV.axis = Axis::Vertical;
	axisInfoV.AddKey(true, sf::Keyboard::S);
	axisInfoV.AddKey(true, sf::Keyboard::Down);
	axisInfoV.AddKey(false, sf::Keyboard::W);
	axisInfoV.AddKey(false, sf::Keyboard::Up);
	axisInfoMap.insert({ Axis::Vertical,axisInfoV });
}

void InputMgr::Clear()
{
	std::bitset<3> remover = 0x01 << (int)State::Pressing;

	for (auto& it : vecInput)
	{
		it &= remover;
	}
}

void InputMgr::UpdateEvent(const sf::Event& ev)
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
	case sf::Event::MouseMoved:
		mousePosition.x = ev.mouseMove.x;
		mousePosition.y = ev.mouseMove.y;
		return;
	default:
		return;
	}
	vecInput[idx] = setter;
}

void InputMgr::Update(float dt)
{
	for (auto& pair : axisInfoMap)
	{
		AxisInfo& axisInfo = pair.second;
		float raw = GetAxisRaw(axisInfo.axis);
		float dir = raw;

		if (raw == 0.f && axisInfo.value != 0.f)
		{
			dir = axisInfo.value > 0.f ? -1.f : 1.f;
		}

		axisInfo.value += dir * axisInfo.sensi * dt;

		axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);
		float axisTH = abs(dir * axisInfo.sensi * dt);

		if (raw == 0.f && abs(axisInfo.value) < axisTH)
		{
			axisInfo.value = 0.f;
		}
	}
}

bool InputMgr::GetKeyDown(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Down];
}

bool InputMgr::GetKeyPressing(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Pressing];
}

bool InputMgr::GetKeyUp(const sf::Keyboard::Key& key)
{
	return vecInput[key][(int)State::Release];
}

bool InputMgr::GetMouseButtonDown(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Down];
}

bool InputMgr::GetMouseButtonPressing(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Pressing];
}

bool InputMgr::GetMouseButtonUp(const sf::Mouse::Button& btn)
{
	return vecInput[sf::Keyboard::KeyCount + btn][(int)State::Release];
}

sf::Vector2i InputMgr::GetMousePosition()
{
	return mousePosition;
}

sf::Vector2f InputMgr::GetMousePositionf()
{
	return (sf::Vector2f)mousePosition;
}

float InputMgr::GetAxisRaw(Axis axis)
{
	auto foundIt = axisInfoMap.find(axis);
	if (foundIt == axisInfoMap.end())
	{
		return 0.f;
	}

	auto& axisInfo = foundIt->second;

	float axisvalue = 0.f;

	auto itInt = axisInfo.positives.begin();
	while (itInt != axisInfo.positives.end())
	{
		if (GetKeyPressing((sf::Keyboard::Key)*itInt))
		{
			axisvalue += 1.f;
			break;
		}
		++itInt;
	}
	itInt = axisInfo.negatives.begin();
	while (itInt != axisInfo.negatives.end())
	{
		if (GetKeyPressing((sf::Keyboard::Key)*itInt))
		{
			axisvalue -= 1.f;
			break;
		}

		++itInt;
	}


	return axisvalue;
}

float InputMgr::GetAxis(Axis axis)
{
	auto foundIt = axisInfoMap.find(axis);
	if (foundIt == axisInfoMap.end())
	{
		return 0.f;
	}

	return foundIt->second.value;
}

void InputMgr::ResetAxis(Axis axis)
{
	auto foundIt = axisInfoMap.find(axis);
	if (foundIt != axisInfoMap.end())
	{
		foundIt->second.value = 0.f;
	}
}

void InputMgr::SetAxisSensitivity(Axis axis,float sensi)
{
	auto foundIt = axisInfoMap.find(axis);
	if (foundIt != axisInfoMap.end())
	{
		foundIt->second.sensi = sensi;
	}
}
