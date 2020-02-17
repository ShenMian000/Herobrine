
#include "Console.h"

int main()
{
	Console& console = Console::getInstance();
	console.setPrompt("him> ");
	console.run();

	return 0;
}
