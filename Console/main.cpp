
#include "Console.h"
#include "Color.h"
#include "print.h"

int main()
{
	Console console;
	console.setPrompt("him> ");
	console.run();

	return 0;
}
