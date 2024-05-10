#include "../../includes/minishell.h"

int	mns_exec_util_restore_stdfileno(int saved_fileno, int std_fileno)
{
	if (dup2(saved_fileno, std_fileno) == MNS_ERROR)
	{
        perror("Failed to restore STD file descriptor");
		return (MNS_ERROR);
    }
    close(saved_fileno);
	return (ALL_FINE);
}

int	mns_exec_util_pipe_dup(t_parsed *parsed, int std_fileno)
{
	int	saved_std_fileno;

	saved_std_fileno = dup(std_fileno);
	if 	(saved_std_fileno == MNS_ERROR)
	{
        perror("Failed to save STD file descriptor");
        close(parsed->fd[std_fileno]);
        return (MNS_ERROR);
    }
	if (dup2(parsed->fd[std_fileno], std_fileno) == MNS_ERROR)
	{
        perror("Failed to redirect STD to a pipe");
        close (parsed->fd[std_fileno]);
		return (MNS_ERROR);
    }
	close(parsed->fd[std_fileno]);
	return (saved_std_fileno);
}

/* Saves STDOUT_FILENO to	saved_std_fileno veariable,
	opens a file, duplicates its FD to STDOUT_FILENO
	and returns	saved_std_fileno if all went smoothly
	or -1 (MNS_ERROR) in case of any error. */
int	mns_exec_util_file_dup(char *filename, int open_flag, int std_fileno)
{
	int	fd;
	int	saved_std_fileno;

	fd = open(filename, open_flag, 0777);
    if (fd == MNS_ERROR)
	{
		perror("Failed to open a file");
        return (MNS_ERROR);
	}
	saved_std_fileno = dup(std_fileno);
    if 	(saved_std_fileno == MNS_ERROR)
	{
        perror("Failed to save STD file descriptor");
        close(fd);
        return (MNS_ERROR);
    }
    if (dup2(fd, std_fileno) == MNS_ERROR)
	{
        perror("Failed to redirect STD to a file");
        close (fd);
		return (MNS_ERROR);
    }
    close(fd);
	return 	(saved_std_fileno);
}