#include "stdafx.h"
#include "CircleView.h"
#include "Scene.h"

CircleView::CircleView(const std::string& name)
	:GameObject(name)
{
}

void CircleView::SetCircleRadius(float radius)
{
	maskRadius = radius;
	rendermask.setRadius(maskRadius);
	Utils::SetOrigin(rendermask, Origins::MC);
	float diameter = maskRadius * 2.f;
	renderTexture.create(diameter, diameter);
	renderView.reset({ 0.f,0.f ,diameter,diameter });
	renderView.zoom(1.f / zoom);

	bodytube.setScale({ diameter / 150.f ,diameter / 150.f });
	Utils::SetOrigin(bodytube, Origins::MC);

	crosshairh.setSize({ diameter * 0.8f,3.f });
	Utils::SetOrigin(crosshairh, Origins::MC);

	crosshairv.setSize({ 3.f,diameter * 0.8f });
	Utils::SetOrigin(crosshairv, Origins::MC);
}

void CircleView::SetZoom(float zoom)
{
	this->zoom = zoom;

	float zoomfactor = 1.f / this->zoom;
	renderView.zoom(zoomfactor);

	crosshairh.setFillColor(sf::Color::Black);
	crosshairv.setFillColor(sf::Color::Black);
}

void CircleView::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	renderView.setCenter(position);
}

void CircleView::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = -300;
}

void CircleView::Release()
{
}

void CircleView::Reset()
{
	bodytube.setTexture(TEXTURE_MGR.Get("graphics/scopes/bodytube.png"));


}

void CircleView::Update(float dt)
{
}

void CircleView::LateUpdate(float dt)
{
	rendermask.setPosition((sf::Vector2f)SCENE_MGR.GetCurrentScene()->WorldToScreen(position));
	bodytube.setPosition((sf::Vector2f)SCENE_MGR.GetCurrentScene()->WorldToScreen(position));
	crosshairh.setPosition((sf::Vector2f)SCENE_MGR.GetCurrentScene()->WorldToScreen(position));
	crosshairv.setPosition((sf::Vector2f)SCENE_MGR.GetCurrentScene()->WorldToScreen(position));
}

void CircleView::Draw(sf::RenderTarget& window)
{
	renderTexture.clear();
	renderTexture.setView(renderView);
	std::list<GameObject*> lstobject = SCENE_MGR.GetCurrentScene()->GetWorldGameObjects();
	for (auto obj : lstobject)
	{
		if (!obj->IsActive() || obj->GetSortingOrder() > 0)
		{
			continue;
		}
		obj->Draw(renderTexture);
	}
	renderTexture.display();
	rendermask.setTexture(&renderTexture.getTexture());

	window.draw(rendermask);

	window.draw(crosshairv);
	window.draw(crosshairh);
	window.draw(bodytube);
}
