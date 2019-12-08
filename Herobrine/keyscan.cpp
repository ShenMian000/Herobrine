
#include <windows.h>
#include <iostream>

using namespace std;

#include "include.h"



string keyscanBuf;

void keyscan()
{
	for(auto code = 1; code <= 254; code++)
	{
		auto state = GetAsyncKeyState(code);

		if(state == 0)
			return;

		keyscanBuf += to_string(code) + ";";
	}
}

int main()
{
	while(true)
	{
		keyscan();
		cout << keyscanBuf << endl;
	}

	getchar(); getchar();
}
