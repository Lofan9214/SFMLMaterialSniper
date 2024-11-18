#include "stdafx.h"
#include "RoundBoard.h"
#include "SceneGame.h"
#include "Bullet.h"

RoundBoard::RoundBoard(const std::string& name)
	: GameObject(name)
{
}

void RoundBoard::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
	internalHitBox.setPosition(position);
	bulletMark.setPosition(position);
}

void RoundBoard::SetPosition(const sf::Vector3f& pos)
{
	position3 = pos;
	SetPosition({ position3.x ,position3.y });
	sf::Vector2f apparent = { 1.f,1.f };
	apparent *= defaultdistance / position3.z;
	sortingOrder = position3.z * -1.f;
	SetScale(apparent);
}

void RoundBoard::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
	internalHitBox.setRotation(rotation);
	bulletMark.setRotation(rotation);
}

void RoundBoard::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
	internalHitBox.setScale(scale);
	bulletMark.setScale(scale);
}

void RoundBoard::SetAnimationScale(const sf::Vector2f& scale)
{
	body.setScale(Utils::ElementProduct(this->scale, scale));
	internalHitBox.setScale(Utils::ElementProduct(this->scale, scale));
	bulletMark.setScale(Utils::ElementProduct(this->scale, scale));
}

void RoundBoard::SetDisplacement(const sf::Vector2f& disp)
{
	displacement = disp;
	body.setOrigin(origin + displacement);
	internalHitBox.setOrigin(origin + displacement - offsetHitBox);
	bulletMark.setOrigin(origin + displacement - positionHit);
}

void RoundBoard::SetColor(const sf::Color& color)
{
	this->color = color;
	body.setColor(this->color);
}

void RoundBoard::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
		internalHitBox.setOrigin(origin - offsetHitBox);
		bulletMark.setOrigin(origin - positionHit);
	}
}

void RoundBoard::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
	internalHitBox.setOrigin(origin - offsetHitBox);
	bulletMark.setOrigin(origin - positionHit);
}

void RoundBoard::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 5;

	bullet = nullptr;

	internalHitBox.setRadius(240);
	internalHitBox.setFillColor(sf::Color::Transparent);
	internalHitBox.setOutlineColor(sf::Color::Red);
	internalHitBox.setOutlineThickness(3);

	positionHit.x = 0.f;
	positionHit.y = 0.f;
	hit = false;

	animator.SetSprite(&body);
	animator.BindFunction(this);
	animator.AddEvent("roundboardspawn", 18, []() {SOUND_MGR.PlaySfx("sounds/targets/roundboardspawn.mp3"); });
	animator.AddEvent("roundboardhit", 45,
		[this]()
		{
			active = false;
		});
}

void RoundBoard::Release()
{
}

void RoundBoard::Reset()
{
	active = true;
	hit = false;

	if (bullet == nullptr)
	{
		SceneGame* scene = dynamic_cast<SceneGame*>(SCENE_MGR.GetCurrentScene());
		if (scene != nullptr)
		{
			bullet = dynamic_cast<Bullet*>(scene->FindGo("bullet"));
			TargetHit = [scene]() {scene->TargetHit();};
		}
	}

	bulletMark.setTexture(TEXTURE_MGR.Get("graphics/targets/bulletmark.png"));

	animator.Play("animations/targets/roundboardspawn.csv");
	animator.PlayQueue("animations/targets/roundboardidle.csv");

	SetOrigin(Origins::BC);
}

void RoundBoard::Update(float dt)
{
	animator.Update(dt);

	if (InputMgr::GetMouseButtonDown(sf::Mouse::XButton1))
	{
		SetPosition({ position3.x,position3.y,position3.z - 100.f });
	}
	if (InputMgr::GetMouseButtonDown(sf::Mouse::XButton2))
	{
		SetPosition({ position3.x,position3.y,position3.z + 100.f });
	}
}

void RoundBoard::FixedUpdate(float dt)
{
	if (bullet == nullptr)
	{
		return;
	}

	sf::FloatRect bodyRect = GetGlobalBounds();
	if (bullet->GetPosition3().z > position3.z
		&& bullet->GetPosition3Previous().z < position3.z)
	{
		sf::Image collisionImage = body.getTexture()->copyToImage();
		sf::Vector2f point = body.getInverseTransform().transformPoint(bullet->GetPosition());

		if (bodyRect.contains(bullet->GetPosition())
			&& collisionImage.getPixel(point.x, point.y).a != 0)
		{
			sf::Vector2f hitboxCenter(240.f, 240.f);
			hitboxCenter += offsetHitBox;
			float distance = Utils::Distance(point, hitboxCenter);
			if (distance < 15)
			{
				animator.Play("animations/targets/roundboardcrit.csv");
				SOUND_MGR.PlaySfx("sounds/targets/roundboardhit.mp3");
				bullet->Hit();
				std::cout << "critboard" << std::endl;
				TargetHit();
			}
			else if (distance < internalHitBox.getRadius())
			{
				hit = true;
				animator.Play("animations/targets/roundboardhit.csv");
				SOUND_MGR.PlaySfx("sounds/targets/roundboardhit.mp3");
				positionHit = point - bulletMark.getLocalBounds().getSize() * 0.5f;
				bulletMark.setOrigin(origin - positionHit);
				std::cout << "hitboard" << std::endl;
				bullet->Hit();
				TargetHit();
			}
			else
			{
				bullet->SetRotation(Utils::RandomRange(0.f, 360.f));
				bullet->Hit(Bullet::Result::Ricochet);
			}
		}
	}

}

void RoundBoard::Draw(sf::RenderTarget& window)
{
	window.draw(body);
	if (hit)
	{
		window.draw(bulletMark);
	}
	if (Variables::isDrawHitBox)
	{
		window.draw(internalHitBox);
	}
}
