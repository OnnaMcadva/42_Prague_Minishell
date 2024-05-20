#include "../includes/minishell.h"

char *mns_exec_util_file_to_str(char *filename)
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

#if 0
char *mns_exec_util_file_to_str(char *filename)
{
    char    *buffer;
    char    *result = NULL;
    char    *temp;
    int     fd;

    fd = open(filename, O_RDONLY);
    if (fd == MNS_ERROR)
    {
        perror("Failed to open file");
        return (NULL);
    }
    while ((buffer = get_next_line(fd, 1)))
    {
        if (result)
        {
            temp = ft_strjoin(result, buffer);
            free(result);
            free(buffer);
            result = temp;
        }
        else
        {
            result = buffer;
        }
    }
    close(fd);
    return (result);
}
#endif

char *mns_parse_util_heredoc(char *stop_word)
{
    char    *buffer;
    char    *input = NULL;
    char    *temp;
    int     fd;

    fd = open(HEREDOC_FILENAME, O_CREAT | O_TRUNC | O_RDWR, 0777);
    if (fd == MNS_ERROR)
    {
        perror("Failed to create temp file for heredoc");
        return (NULL);
    }

    while ((buffer = readline("> ")) && ft_strcmp(buffer, stop_word) != 0)
    {
        ft_putendl_fd(buffer, fd);
        free(buffer);
    }
    free(buffer);
    close(fd);

    input = mns_exec_util_file_to_str(HEREDOC_FILENAME);
    unlink(HEREDOC_FILENAME);
    return (input);
}

int main()
{
    char *str = mns_parse_util_heredoc("END");
    if (str)
    {
        printf("%s\n", str);
        free(str);
    }
    return 0;
}
