#pragma once

class Bullet;
class GlassShard;
class ShootMark;

class Bottle : public GameObject
{
protected:

	sf::Sprite body;
	Animator animator;
	sf::RectangleShape stand;

	sf::Vector3f position3;
	float defaultdistance = 25.f;

	ShootMark* shootMark;

	std::function<GlassShard* ()> TakeGlassShard;
	std::function<void()> TargetHit;
	std::function<const std::list<Bullet*>()> GetBulletList;
	std::function<void(Bottle*)> ReturnThis;

public:
	Bottle(const std::string& name = "");
	~Bottle() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetPosition(const sf::Vector3f& pos);
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;
	void SetOffset(const sf::Vector2f& disp) override;
	void SetColor(const sf::Color& color) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	sf::FloatRect GetLocalBounds() const override { return body.getLocalBounds(); }
	sf::FloatRect GetGlobalBounds() const override { return body.getGlobalBounds(); }

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void FixedUpdate(float dt) override;
	void Draw(sf::RenderTarget& window) override;

	void SetShootMark(ShootMark* shootMark) { this->shootMark = shootMark; }
	void SetActiveShootMark(bool active);
};

