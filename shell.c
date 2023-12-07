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
		int i;
		char **argv;

		print_prompt();
		argv = execute_prompt(read_and_tokenise());

		for (i = 0; argv[i] != NULL; i++)
			free(argv[i]);
		free(argv);
	}

	return (0);
}
