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

char	*mns_exec_path(char **paths, char *cmd)
{
	int		i;
	char	*possible_path;
	char	*possible_exec;

	i = 0;
	while (paths[i])
	{
		possible_path = ft_strjoin(paths[i], "/");
		possible_exec = ft_strjoin(possible_path, cmd);
		free(possible_path);
		if (access(possible_exec, F_OK | X_OK) == 0)
			return (possible_exec);
		free(possible_exec);
		i++;
	}
	return (NULL);
}

/* Simple execute for cases without pipes and redirections. */
void	mns_execute_simple(t_parsed parsed, char **paths, char **envp)
{
	char	*exec;
	pid_t	pid;

	exec = mns_exec_path(paths, parsed.command);
	if (!exec)
		printf ("minishell: command not found: %s\n", parsed.command);
	else
	{
		pid = fork();
		if (pid == MNS_ERROR)
			printf ("Fork error");
		else if (pid == CHILD)
		{
			if (execve(exec, parsed.args, envp) == MNS_ERROR)
			{
				ft_putendl_fd("minishell: permission denied: ", STDOUT_FILENO);
				exit (MNS_ERROR);
			}
		}
		else
			wait(NULL);
	}
	free (exec);
}

int	mns_execute_redirect(t_parsed parsed, char **envp, char **paths)
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
    mns_execute_simple(parsed, paths, envp);
    if (dup2(save_stdout, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to restore STDOUT file descriptor");
		code = MNS_ERROR;
    }
    close(fd);
    close(save_stdout);
    return (code);
}

int mns_execute_last(void)
{
	int		fd;
	char	*output;

	fd = open("./temp", O_RDONLY);
	if (fd == MNS_ERROR)
        return (perror("Failed to open temporary file"), MNS_ERROR);
	while (1)
	{
		output = get_next_line(fd, 1);
		ft_putstr_fd(output, STDOUT_FILENO);
		if (!output)
			break ;
		free(output);
	}
	close (fd);
	unlink ("./temp");
	return (ALL_FINE);
}


void	mns_execute(t_data *data, char **envp)
{
	int	i;

	mns_execute_redirect(data->parsed[0], envp, data->paths);
	i = 1;
	while (data->parsed[i].type != NULL_TOKEN)
	{
		i++;
	}
	mns_execute_last();
}
