/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_execute_simple.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:39:48 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 15:26:11 by mmakagon         ###   ########.fr       */
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
