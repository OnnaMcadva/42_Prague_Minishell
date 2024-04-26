/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_execute_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:04:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 15:32:12 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_exec_complex_first(t_parsed parsed, char **envp, char **paths)
{
    int	fd;
    int	save_stdout;
	int	code;

	code = ALL_FINE;
    fd = open("./temp", O_CREAT | O_RDWR | O_TRUNC, 0777);
    if (fd == MNS_ERROR)
        return (perror("Failed to open temporary file"), MNS_ERROR);
    save_stdout = dup(STDOUT_FILENO);
    if (save_stdout == MNS_ERROR)
	{
        perror("Failed to save STDOUT file descriptor");
        close(fd);
        return (MNS_ERROR);
    }
    if (dup2(fd, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to redirect STDOUT to temporary file");
		code = MNS_ERROR;
    }
    close(fd);
    mns_execute_simple(parsed, paths, envp);
    if (dup2(save_stdout, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to restore STDOUT file descriptor");
		code = MNS_ERROR;
    }
    close(save_stdout);
    return (code);
}

/* Outputs the result of previous commands (saved in temp file) to STDOUT */
int mns_exec_complex_last(void)
{
	int		fd;
	char	*output;

	fd = open("./temp", O_RDONLY);
	if (fd == MNS_ERROR)
	{
		perror("Failed to open temporary file");
        return (MNS_ERROR);
	}
	while (1)
	{
		output = get_next_line(fd, 1);
		if (!output)
			break ;
		ft_putstr_fd(output, STDOUT_FILENO);
		free(output);
	}
	close (fd);
	unlink ("./temp");
	return (ALL_FINE);
}

/* Creates a temp file, writes the command output there,
	then outputs the contents to STDOUT 
	TODO: cleanup, split into smaller functions 
	and make exec_middle or something... */
int	mns_execute_complex(t_data *data, char **envp)
{
	int	i;

	mns_exec_complex_first(data->parsed[0], envp, data->paths);
	i = 1;
	while (data->parsed[i].type != NULL_TOKEN)
	{
		i++;
	}
	mns_exec_complex_last();
	return (ALL_FINE);
}
