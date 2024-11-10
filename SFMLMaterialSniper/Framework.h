#pragma once

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:

	Framework() = default;
	virtual ~Framework() = default;

	Framework(const Framework&) = delete;
	Framework& operator=(const Framework&) = delete;

	sf::RenderWindow window;

	sf::Clock clock;
	float fTimeScale = 1.f;

	float fGameTime = 0.f;
	float fGameDT = 0.f;
	float fRealTime = 0.f;
	float fRealDT = 0.f;

public:

	float getGameTime() const { return fGameTime; }
	float getGameDeltaTime() const { return fGameDT; }
	float getRealTime() const { return fRealTime; }
	float getRealDeltaTime() const { return fRealDT; }

	void setTimeScale(float iTimeScale) { fTimeScale = iTimeScale; }
	float getTimeScale() const { return fTimeScale; }

	virtual void init(int iWidth, int iHeight, const std::string& strTitle);
	virtual void dothis();
	virtual void release();
};