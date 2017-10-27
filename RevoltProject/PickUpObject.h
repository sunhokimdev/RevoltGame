#pragma once

#include "Thing.h"

class PickUpObject : public Thing
{
public:
	PickUpObject();
	virtual ~PickUpObject();

	/*   기본 루프 메서드   */
	void Setup();
	void Update();
	void Render();
};

