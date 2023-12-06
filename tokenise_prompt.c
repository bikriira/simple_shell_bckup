#include "main.h"


/**
 * tokenise_prompt - Turn string into groups based on delimeter argument.
 * @str: The string to be tokenised.
 * @delimeter: The character ot be based on when slicing the string.
 *
 * Return: Pointer to pointer to tokenised data.
 */
char **tokenise_prompt(char *str, char *delimeter)
{
	int i = 0, i_copy = 0;
	char **argv, *str_copy = str, *token, *str_copy_token;

	str_copy_token = strtok(str_copy, delimeter);

	while (str_copy_token)
	{
		str_copy_token = strtok(NULL, delimeter);
		i_copy++;
	}

	argv = malloc(sizeof(char *) * (i_copy + 1));
	token = strtok(str, delimeter);

	while (token)
	{
		argv[i] = malloc(strlen(token) + 1);
		strcpy(argv[i], token);
		token = strtok(NULL, delimeter);
		i++;
	}
	argv[i] = NULL;

	return (argv);
}
