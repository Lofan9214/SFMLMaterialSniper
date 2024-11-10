#include "stdafx.h"

int main()
{
	Framework::Instance().init(1920,1080,"게임 제목");
	Framework::Instance().dothis();
	Framework::Instance().release();
	return 0;
}