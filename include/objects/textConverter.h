#pragma once

// Converts int and floats into const char*

class TextConverter
{
public:

	const char* SetString(int value);
	const char* SetString(float value);

private:
	static const int BUFFERSIZE = 20;
	char buffer[BUFFERSIZE];

};