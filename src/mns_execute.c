/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:39:48 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 16:00:52 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* TODO: use the correct parsed element depending on child */
char	*mns_exec_path(t_data *data)
{
	int		i;
	char	*possible_path;
	char	*possible_exec;

	i = 0;
	while (data->paths[i])
	{
		possible_path = ft_strjoin(data->paths[i], "/");
		possible_exec = ft_strjoin(possible_path, data->splitted[0]);
		free(possible_path);
		if (access(possible_exec, F_OK | X_OK) == 0)
			return (possible_exec);
		free(possible_exec);
		i++;
	}
	return (NULL);
}

void	mns_execute(t_data *data, char **envp)
{
	char	*exec;
	pid_t	pid;

	exec = mns_exec_path(data);
	if (!exec)
		printf ("minishell: command not found: %s\n", data->splitted[0]);
	else
	{
		pid = fork();
		if (pid == MNS_ERROR)
			printf ("fork error");
		else if (pid == CHILD)
		{
			if (execve(exec, data->splitted, envp) == MNS_ERROR)
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
