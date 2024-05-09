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

/* Saves STDOUT_FILENO to save_stdout veariable,
	opens a file, duplicates its FD to STDOUT_FILENO
	and returns save_stdout if all went smoothly
	or -1 (MNS_ERROR) in case of any error. */
int	mns_exec_util_dup(char *filename, int open_flag, int std_fileno)
{
	int	fd;
	int save_stdout;

	fd = open(filename, open_flag, 0777);
    if (fd == MNS_ERROR)
	{
		perror("Failed to open a file");
        return (MNS_ERROR);
	}
    save_stdout = dup(std_fileno);
    if (save_stdout == MNS_ERROR)
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
	return (save_stdout);
}