#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - check the code
 *
 * Return: Nothing.
 */

int main(void)
{
	pid_t pid;
	char *token, *buf = NULL, *args[64];
	size_t size, track;
	extern char **environ;

	while (1)
	{
		if (getline(&buf, &size, stdin) == -1)
		{
			break;
		}
		buf[strcspn(buf, "\n")] = '\0';
		token = strtok(buf, " ");
		track = 0;
		while (token != NULL && track < 63)
		{
			args[track] = token;
			track++;
			token = strtok(NULL, " ");
		}
		args[track] = NULL;
		if (track == 0)
			continue;
		if (strcmp(args[0], "exit") == 0)
			exit(1);
		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, environ) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else if (pid < 0)
			perror("fork");
		else
			wait(NULL);
	}
	free(buf);
	return (0);
}
