#include "main.h"



/**
 * main - The entry point of the simple shell programm.
 *
 * Return: 0 on success.
 */
int main(void)
{
	while (1)
	{
		print_prompt();
		read_and_tokenise();
		/*execute_prompt();*/
	}

	return (0);
}
