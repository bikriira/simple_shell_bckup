#include "main.h"

/**
 * execute_prompt - Executes the procesed prompt using execve
 * @argv: Tokenised input which is now in an array;
 *
 * Return: The pointer to array of pointers argv
 */
char **execute_prompt(char **argv)
{
	int status;
	pid_t child = fork();

	if (child == 0)
	{
		execve(argv[0], argv, environ);
		perror("Failed to execute");
	}
	else if (child == -1)
	{
		perror("Failed to create child");
	}
	else
	{
		wait(&status);
	}
	return (argv);
}
