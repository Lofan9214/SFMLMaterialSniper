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
}