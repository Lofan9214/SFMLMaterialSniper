#pragma once
class SoundObject
{
protected:
	std::string soundBufferId;
	std::string name;

	sf::Sound sfx;

	float time;
	float targetTime;
	bool setEnd;

public:
	SoundObject(const std::string& sbId = "", const std::string& name = "");
	virtual ~SoundObject() = default;

	std::string getName() const { return name; }
	void setName(const std::string& iname) { name = iname; }

	virtual float GetVolume() { return sfx.getVolume(); }
	virtual void SetVolume(float vol) { sfx.setVolume(vol); }

	virtual void Play(bool isLoop);
	virtual void Play(float targetTime);
	virtual void Pause();
	virtual void Stop();

	virtual void init();
	virtual void release();

	virtual void reset();

	virtual void update(float dt);

};

