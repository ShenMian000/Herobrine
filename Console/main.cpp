#include "console.h"
#include "color.h"
#include "print.h"

int main()
{
	Console console;
	console.setPrompt("him> ");
	console.run();

	return 0;
}
