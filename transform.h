#pragma once
#include "component.h"


class Transform : public Component
{
public:

	Tmpl8::float2 pos;
	Tmpl8::float2 scale;

	Transform();

	void Translate(); // 

	Transform* parent;


private:



};

