#pragma once

// F = -C*rho*A*abs(V-W)*(V-W)/2
// C : 항력 계수 (일반적인 상황에서 0.295)
// rho : 공기 저항
// A : 탄두의 단면적
// V : 탄두의 속도
// W : 바람의 속도

class Bullet : public GameObject
{
protected:

	bool fired = false;

	const float coeff = 0.295f; // 항력 계수 (0.295가 일반적인 수치)
	const float rho = 1.2f; // 공기 저항 (정상 기압 및 온도에서 1.2kg/m^3)

	float weight = 11.3f; // 탄두중량 (mg)
	float diameter = 7.82f; // 탄두지름 (mm)

	sf::Sprite body;
	Animator animator;

	sf::Vector3f pos3d;
	sf::Vector3f vel3d;
	sf::Vector3f acc3d;
	sf::Vector3f wind;
	sf::Vector3f gravity = {0.f,49.f,0.f};

public:
	Bullet(const std::string& name = "");
	~Bullet() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void UpdateDragAccelation();
	void SetWind(const sf::Vector3f& wind) { this->wind = wind; }
	void SetPosition(const sf::Vector3f& pos) { pos3d = pos; }
	void SetGravity(const sf::Vector3f& gravity) { this->gravity = gravity; }

	void Fire(const sf::Vector3f& startpos, const sf::Vector3f& vel);

	sf::Vector3f GetPosition3() { return pos3d; }
	sf::Vector3f GetVelocity3() { return vel3d; }
};
