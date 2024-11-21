#pragma once

namespace GameDefine
{
	enum class BreathStatus
	{
		Normal,
		Hold,
		Over,
	};
	enum class ReloadStatus
	{
		Normal,
		MagazineEjecting,
		MagazineInserted,
	};
	enum class BoltStatus
	{
		Ready,
		Fire,
		BoltPulling,
		Recovery,
	};
	enum class SortingOrders
	{
		CircleView = 140,
		Player = 150,
		BulletShell = 190,
		Gun = 200,
	};
	enum class UiSortingOrders
	{
		UiHud = 300,
		UiResult = 500,
	};
}