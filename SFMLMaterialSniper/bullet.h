#pragma once

// F = -C*rho*A*abs(V-W)*(V-W)/2
// C : �׷� ��� (�Ϲ����� ��Ȳ���� 0.295)
// rho : ���� ����
// A : ź���� �ܸ���
// V : ź���� �ӵ�
// W : �ٶ��� �ӵ�

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

	const float coeff = 0.295f; // �׷� ��� (0.295�� �Ϲ����� ��ġ)
	const float rho = 1.2f; // ���� ���� (���� ��� �� �µ����� 1.2kg/m^3)

	float weight = 11.3f; // ź���߷� (mg)
	float diameter = 7.82f; // ź������ (mm)
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
