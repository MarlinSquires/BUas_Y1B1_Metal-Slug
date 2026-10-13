#include "precomp.h"
#include "jsonParser.h"



json JsonParser::Load(const char* address)
{
	std::ifstream file(address);
	return json::parse(file);
}