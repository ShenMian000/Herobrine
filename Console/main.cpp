
#include "Console.h"
#include "Color.h"
#include "print.h"

int main()
{
	Color::set(Color::Fore::cyan);
	Color::set(Color::Mode::fore_bold);
	Color::set(Color::Mode::underline);
	puts("Hello HIM");

	Console console;
	console.setPrompt("him> ");
	console.run();

	return 0;
}
