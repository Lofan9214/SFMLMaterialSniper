#include "stdafx.h"
#include "CircleView.h"

CircleView::CircleView(float radius, float zoom)
{
	this->zoom = zoom;
	SetCircleRadius(radius);
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
}

void CircleView::SetZoom(float zoom)
{
	this->zoom = zoom;

	float zoomfactor = 2.f * rendermask.getRadius() / renderView.getSize().x / this->zoom;
	renderView.zoom(zoomfactor);
}

void CircleView::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	rendermask.setPosition(position);
	renderView.setCenter(pos);
}

void CircleView::Draw(sf::RenderWindow& window,const std::list<GameObject*>& lstobject)
{
	renderTexture.clear();
	renderTexture.setView(renderView);
	for (auto obj : lstobject)
	{
		if (!obj->IsActive())
		{
			continue;
		}
		obj->Draw(renderTexture);
	}
	renderTexture.display();
	rendermask.setTexture(&renderTexture.getTexture());
	window.draw(rendermask);
}
