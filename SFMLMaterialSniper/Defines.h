#pragma once

enum class SceneIds
{
	none = -1,
	Dev1,
	Dev2,
	Count
};

enum class Origins
{
	//Top
	//Middle
	//Bottom
	//Left Center Right
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
	Custom,
};

enum class Sides
{
	Left,
	Right,
	None,
	Rand,
};