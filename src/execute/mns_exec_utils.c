#include "../../includes/minishell.h"

/* Reads from with get_next_line and makes a string with strjoin,
	returns NULL in case of error.
    Return needs to be freed. */
char *mns_exec_util_file_to_str(const char *filename)
{
	char	*buffer;
	char	*result;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == MNS_ERROR)
	{
		perror("Failed to open file");
        return (NULL);
	}
	result = get_next_line(fd, 1);
	while (result)
	{
		buffer = get_next_line(fd, 1);
		if (!buffer)
			break ;
		result = ft_strjoin(result, buffer);
		free(buffer);
	}
	close(fd);
	return (result);
}

/* Outputs the contents of a file to STDOUT,
	bassically like bash's cat command */
void mns_exec_util_file_to_output(const char *filename, int unlink_or_not)
{
	char *output;

	output = mns_exec_util_file_to_str(filename);
	if (output)
		ft_putstr_fd(output, STDOUT_FILENO);
	free(output);
	if (unlink_or_not == 1)
		unlink (filename);
}

int	mns_exec_util_restore_stdout(int save_stdout)
{
	if (dup2(save_stdout, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to restore STDOUT file descriptor");
		return (MNS_ERROR);
    }
    close(save_stdout);
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
		perror("Failed to open temporary file");
        return (MNS_ERROR);
	}
    save_stdout = dup(std_fileno);
    if (save_stdout == MNS_ERROR)
	{
        perror("Failed to save STDOUT file descriptor");
        close(fd);
        return (MNS_ERROR);
    }
    if (dup2(fd, std_fileno) == MNS_ERROR)
	{
        perror("Failed to redirect STDOUT to temporary file");
        close (fd);
		return (MNS_ERROR);
    }
    close(fd);
	return (save_stdout);
}