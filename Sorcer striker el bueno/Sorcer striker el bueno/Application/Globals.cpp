#include <windows.h>
#include <stdio.h>
#include <iostream>

void log(const char file[], int line, const char* format, ...)
{
	static char tmp_string[4096];
	static char tmp_string2[4096];
	static va_list  ap;

	// Construct the string from variable arguments
	va_start(ap, format);
	vsprintf_s(tmp_string, 4096, format, ap);
	va_end(ap);
	sprintf_s(tmp_string2, 4096, "\n%s(%d) : %s", file, line, tmp_string);

	// TODO: esbrinar perque peta en aquest projecte
	//OutputDebugString(tmp_string2);

	std::cout << tmp_string2 << std::endl;
}
