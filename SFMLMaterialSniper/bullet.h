#pragma once

// F = -C*rho*A*abs(V-W)*(V-W)/2
// C : 항력 계수 (일반적인 상황에서 0.295)
// rho : 공기 저항
// A : 탄두의 단면적
// V : 탄두의 속도
// W : 바람의 속도

class Bullet : public GameObject
{
public:
	enum class Status
	{
		Ready,
		Fired,
		Hit,
	};

	enum class Result
	{
		Hit1,
		Hit2,
		Ricochet,
	};

protected:

	Status status = Status::Ready;

	const float coeff = 0.295f; // 항력 계수 (0.295가 일반적인 수치)
	const float rho = 1.2f; // 공기 저항 (정상 기압 및 온도에서 1.2kg/m^3)

	float weight = 11.3f; // 탄두중량 (mg)
	float diameter = 7.82f; // 탄두지름 (mm)
	float muzzleSpeed = 980.f;

	sf::Sprite body;
	Animator animator;

	sf::Vector3f position3Previous;
	sf::Vector3f position3;
	sf::Vector3f positionStarted;
	sf::Vector3f velocity3d;
	sf::Vector3f acc3d;
	sf::Vector3f wind;
	sf::Vector3f gravity = { 0.f,9.8f,0.f };

	float gravityMultiplier = 2.f;
	float windMultiplier = 8.f;

public:
	Bullet(const std::string& name = "");
	~Bullet() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetPosition(const sf::Vector3f& pos);
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;
	void SetAnimationScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void UpdateFired(float dt);
	void Draw(sf::RenderTarget& renderTarget) override;

	void UpdateAccelation();
	void SetWind(const sf::Vector3f& wind) { this->wind = wind; }
	void SetGravity(const sf::Vector3f& gravity) { this->gravity = gravity; }

	void Fire(const sf::Vector3f& startpos, const sf::Vector3f& dir = { 0.f,0.f,1.f });
	void Hit(Result result = Result::Hit1);

	sf::Vector3f GetPosition3() { return position3; }
	sf::Vector3f GetPosition3Previous() { return position3Previous; }
	sf::Vector3f GetVelocity3() { return velocity3d; }
};
