# include <stdio.h>
# include <unistd.h>
# include <sys/wait.h>

#define CHILD 0
#define FORK_ERROR -1
#define MNS_ERROR -1


void myfunc(char **argv, char **envp, int pid)
{
	printf ("03 This is the first child before the second fork, id = %d\n", pid);
	pid = fork();
	if (pid == FORK_ERROR)
		return ;
	else if (pid == CHILD)
	{
		printf ("05 This is the second child and you'll see it, next will be the test text, id = %d\n", pid);
		if (execve("./test_executable", argv, envp) == MNS_ERROR)
		{
			printf ("minishell: permission denied: \nid = %d\n", pid);
			exit(MNS_ERROR);
		}
	}
	else
	{
		printf ("04 This is the first child that became the second parent and you'll see it before child, id = %d\n", pid);
		wait (NULL);
		printf ("06 This is the second parent and you'll see it after child, next will be the test text, id = %d\n", pid);
		if (execve("./test_executable", argv, envp) == MNS_ERROR)
		{
			printf ("minishell: permission denied: \nid = %d\n", pid);
			exit(MNS_ERROR);
		}
	}
}

int main(int argc, char **argv, char **envp)
{
	pid_t pid;

	pid = fork();
	if (pid == FORK_ERROR)
		return (perror("ERROR"), pid);
	else if (pid == CHILD)
	{
		printf ("02 Child from main starts, id = %d\n", pid);
		myfunc(argv, envp, pid);
		printf ("This you'll never see, id = %d\n", pid);
	}
	else
	{
		printf ("01 This is the first parent and you'll see it at the very beginning, id = %d\n", pid);
		wait(NULL);
		printf ("07 This is the first parent and you'll see it at the very end, id = %d\n", pid);
	}

}
