#pragma once

#include "json.hpp"

using nlohmann::json;

class JsonParser
{
public:
	static json Load(const char* address);

};



