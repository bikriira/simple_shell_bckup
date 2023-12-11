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
	char **path_value = malloc(sizeof(char*));
	pid_t child;

	
	path_value = tokenise_env_val("PATH");
	if (pather(path_value ,argv[0]) == NULL)
	{
		perror("Command doesn’t exist");
		free_ptr2ptr(path_value);
		return (NULL);
	}
	child = fork();

	if (child == 0)
	{
		argv[0] = pather(path_value ,argv[0]);
		printf("%s", argv[0]);
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
		free_ptr2ptr(path_value);
	}

	return (argv);
}

char **tokenise_env_val(char *wanted_key)
{
	int i, count = 0;
	char *key, *wanted_part, *wanted_part_cpy, *token, **token_array,
	**environ_copy;

	while (environ[count])
		count++;
	environ_copy = malloc(sizeof(char*) * (count + 1));
	for (i = 0; environ[i]; i++)
		environ_copy[i] = strdup(environ[i]);
	environ_copy[i] = NULL;

	i = 0;
	count = 0;

	while(environ_copy[i])
	{
		key = strtok(environ_copy[i], "=");
		if (strcmp(key, wanted_key) == 0)
		{
			free_ptr2ptr(environ_copy);
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
	printf("donee witht tokenise_envvl\n");
	return (token_array);
}

char *pather(char **token_array, char *prompt_input)
{
	int i = 0;
	char *path;
	struct stat stat_storage;

	while(token_array[i] != NULL)
	{
		path = malloc(strlen(token_array[i]) + strlen(prompt_input) + 2);
		strcat(path, token_array[i]);
		strcat(path, "/");
		strcat(path, prompt_input);
		printf("token %d: %s",i, token_array[i]);
		if (stat(path, &stat_storage) == 0)
			return (path);
		free(path);
		i++;
	}
	if (stat(prompt_input, &stat_storage) == 0)
		return (prompt_input);

	return (NULL);
}














