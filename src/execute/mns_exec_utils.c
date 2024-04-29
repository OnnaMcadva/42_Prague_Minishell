#include "../../includes/minishell.h"

/* Reads from with get_next_line and make a string with strjoin,
	returns NULL in case*/
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

/* Outputs the result of previous commands (saved in temp file) to STDOUT */
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