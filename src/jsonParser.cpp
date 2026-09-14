#include "precomp.h"
#include "jsonParser.h"

#include <fstream>




//unsigned char* LoadFile(const char* filename, size_t* outSize);
//unsigned char* file = LoadFile("data/level1.tmj", 0);

json JsonParser::Load(const char* address)
{
	std::ifstream file(address);
	return json::parse(file);
}