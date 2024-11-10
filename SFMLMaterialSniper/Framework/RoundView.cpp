#include "stdafx.h"
#include "RoundView.h"

RoundView::RoundView()
{
	gameObjectsChanged = false;
	zoom = 1.f;
	maskRadius = 50.f;
}

void RoundView::SetZoom(float zoom)
{
	this->zoom = zoom;

	float zoomfactor = 2.f * rendermask.getRadius() / renderView.getSize().x / this->zoom;
	renderView.zoom(zoomfactor);
}

void RoundView::SetViewPort(const sf::FloatRect& ratioRect)
{
	if (ratioRect.left + ratioRect.width > 1.f
		|| ratioRect.top + ratioRect.height > 1.f)
	{
		return;
	}
	renderView.setViewport(ratioRect);
}

void RoundView::SetViewPort(const sf::Vector2f& displaySize, const sf::FloatRect& pixelRect)
{
	sf::FloatRect viewport;

	viewport.top = pixelRect.top / displaySize.y;
	viewport.height = pixelRect.height / displaySize.y;
	viewport.left = pixelRect.left / displaySize.x;
	viewport.width = pixelRect.width / displaySize.x;

	renderView.setViewport(viewport);
}

void RoundView::SetViewCenter(const sf::Vector2f& center)
{
	renderViewCenter = center;
	renderView.setCenter(renderViewCenter);
}

void RoundView::SetViewSize(const sf::Vector2f& size)
{
	renderView.setSize(size);
}

void RoundView::RemoveGo(GameObject* obj)
{
	gameObjectsChanged = true;
	removeGameObjs.push_back(obj);
}

void RoundView::Init()
{
}

void RoundView::Release()
{
}

void RoundView::Reset()
{
}

void RoundView::Update(float dt)
{
	renderTexture.clear();
	renderTexture.setView(renderView);

	for (auto sd : drawObjects)
	{
		sd->Draw(renderTexture);
	}
	renderTexture.display();
	rendermask.setTexture(&renderTexture.getTexture());
}

void RoundView::OnPreDraw()
{
	ApplyAddGo();
	ApplyRemoveGo();
}

void RoundView::Draw(sf::RenderWindow& window)
{
	window.draw(rendermask);
}

void RoundView::ApplyAddGo()
{
	for (auto go : addGameObjs)
	{
		if (std::find(drawObjects.begin(), drawObjects.end(), go) == drawObjects.end())
		{
			drawObjects.push_back(go);
		}
	}
	addGameObjs.clear();
}

void RoundView::ApplyRemoveGo()
{
	for (auto go : removeGameObjs)
	{
		drawObjects.remove(go);
	}

	removeGameObjs.clear();
}

void RoundView::SortDrawObject()
{
	if (gameObjectsChanged)
	{
		return;
	}
	gameObjectsChanged = false;

	std::stable_sort(drawObjects.begin(), drawObjects.end(), DrawOrderComparer());
}
