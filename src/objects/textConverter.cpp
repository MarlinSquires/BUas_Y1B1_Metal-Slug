#include "precomp.h"
#include "textConverter.h"


const char* TextConverter::SetString(int value)
{
	snprintf(buffer, sizeof(buffer), "%d", value);
	return buffer;
}

const char* TextConverter::SetString(float value)
{
	snprintf(buffer, sizeof(buffer), "%f", value);
	return buffer;
}