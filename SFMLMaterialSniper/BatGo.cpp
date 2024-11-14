#include "stdafx.h"
#include "BatGo.h"

BatGo::BatGo(const std::string& name)
	:GameObject(name)
{
}

void BatGo::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(position);
}

void BatGo::SetScale(const sf::Vector2f& scale)
{
	GameObject::SetScale(scale);
	body.setScale(this->scale);
}

void BatGo::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset < Origins::Custom)
	{
		origin = Utils::SetOrigin(body, originPreset);
	}
}

void BatGo::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = newOrigin;
	body.setOrigin(origin);
}

void BatGo::Init()
{
	body.setSize({ 100.f,10.f });
	body.setFillColor(sf::Color::White);

	SetOrigin(Origins::TC);

	auto windowSize = FRAMEWORK.GetWindowSizef();

	initPos.x = windowSize.x * 0.5f;
	initPos.y = windowSize.y - 50.f;

	minX = body.getSize().x * 0.5f;
	maxX = windowSize.x - minX;
}

void BatGo::Reset()
{

	SetPosition(initPos);
}

void BatGo::Release()
{
}

void BatGo::LateUpdate(float dt)
{
}

void BatGo::Update(float dt)
{

	direction.x = InputMgr::GetAxis(Axis::Horizontal);
	sf::Vector2f newpos = position + direction * speed * dt;
	if (newpos.x<minX || newpos.x>maxX)
	{
		InputMgr::ResetAxis(Axis::Horizontal);
	}
	newpos.x = Utils::Clamp(newpos.x, minX, maxX);

	SetPosition(newpos);
}

void BatGo::FixedUpdate(float dt)
{
}

void BatGo::Draw(sf::RenderTarget& renderTarget)
{
	renderTarget.draw(body);
}

