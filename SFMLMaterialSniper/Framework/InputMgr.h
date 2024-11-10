#pragma once

enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	Axis axis;
	std::list<int> positives;
	std::list<int> negatives;

	float sensi = 1.f;
	float value = 0.f;

	void AddKey(bool isPositive, int key)
	{
		if (isPositive)
		{
			positives.push_back(key);
		}
		else
		{
			negatives.push_back(key);
		}
	}
};

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
	static sf::Vector2i mousePosition;
	static std::unordered_map<Axis, AxisInfo> axisInfoMap;

public:
	static void Init();
	static void Clear();
	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(const sf::Keyboard::Key& key);
	static bool GetKeyPressing(const sf::Keyboard::Key& key);
	static bool GetKeyUp(const sf::Keyboard::Key& key);

	static bool GetMouseButtonDown(const sf::Mouse::Button& btn);
	static bool GetMouseButtonPressing(const sf::Mouse::Button& btn);
	static bool GetMouseButtonUp(const sf::Mouse::Button& btn);

	static sf::Vector2i GetMousePosition();
	static sf::Vector2f GetMousePositionf();

	static float GetAxisRaw(Axis axis);
	static float GetAxis(Axis axis);
	static void ResetAxis(Axis axis);
	static void SetAxisSensitivity(Axis axis,float sensi);
};