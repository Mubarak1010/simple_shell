#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	char *token;
	int track;
	size_t size;
	char *buf = NULL;
	char *args[64];

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
		{
			continue;
		}
		if (strcmp(args[0], "exit") == 0)
		{
			break;
		}
		pid = fork();
		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("./shell");
				exit(1);
			}
		}
		else if (pid < 0)
		{
			perror("fork");
		}
		else
		{
			wait(NULL);
		}
	}
	free(buf);
	return (0);
}