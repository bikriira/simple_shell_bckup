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
	pid_t child;
	char **path_value;

	printf("right above **path_value");
	path_value = tokenise_env_val("PATH");

	printf("under char **path_value = tokenise_env_val('PATH');");
	if (pather(path_value ,argv[0]) == NULL)
	{
		perror("Command doesn’t exist");
		return (NULL);
	}
	printf("above fork()");
	child = fork();

	if (child == 0)
	{
		printf("child created");
		execve(pather(path_value ,argv[0]), argv, environ);
		perror("Failed to execute");
	}
	else if (child == -1)
	{
		perror("Failed to create child");
	}
	else
	{
		printf("above wait()");
		wait(&status);
	}

	printf("above return(argv)");
	return (argv);
}

char **tokenise_env_val(char *wanted_key)
{
	int i = 0, count = 0;
	char *key, *wanted_part, *wanted_part_cpy, *token, **token_array;

	while(environ[i])
	{
		key = strtok(environ[i], "=");
		if (strcmp(key, wanted_key) == 0)
		{
			wanted_part = strtok(NULL, "\n");
			break;
		}
		i++;
	}

	wanted_part_cpy = strdup(wanted_part);
	token = strtok(wanted_part_cpy, ":");
	while(token)
	{
		token = strtok(NULL, ":");
		count++;
	}

	token_array = malloc(sizeof(char*) * (count + 2));
	token = strtok(wanted_part, ":");
	i = 0;
	while(token)
	{
		token_array[i] = malloc((sizeof(char) * strlen(token)) + 1);
		strcpy(token_array[i], token);
		token = strtok(NULL, ":");
		i++;
	}
	token_array[i] = NULL;
	free(wanted_part_cpy);
	return (token_array);
}

char *pather(char **token_array, char *prompt_input)
{
	int i = 0;
	char *path;
	struct stat stat_storage;

	while(token_array[i] != NULL)
	{
		path = token_array[i];
		strcat(path, "/");
		strcat(path, prompt_input);
		if (stat(path, &stat_storage) == 0)
			return (path);
		i++;
	}
	if (stat(prompt_input, &stat_storage) == 0)
		return (prompt_input);

	return (NULL);
}














