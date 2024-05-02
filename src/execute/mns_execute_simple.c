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

/* TODO: put it to parse section,
	so if the command is a global exec - change it to tthe path */
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
	ft_putstr_fd("minishell: command not found: ", STDOUT_FILENO);
	ft_putendl_fd(cmd, STDOUT_FILENO);
	return (NULL);
}

void	mns_exec_builtin_call(t_data *data, char **envp, t_parsed parsed)
{
	if (parsed.type & COM_PWD)
		mns_com_pwd();
	else if (parsed.type & COM_EXIT)
		mns_com_exit(data, 0);
	else if (parsed.type & COM_CD)
		mns_com_cd(parsed.args[1]);
	else if (parsed.type & COM_ENV)
		mns_com_env(envp);
	else if (parsed.type & COM_ECHO)
		mns_com_echo(parsed.args);
}

char *mns_exec_simple_setup(t_data *data, char **envp, t_parsed parsed)
{
	char *exec;

	exec = NULL;
	if (parsed.type & BUILTIN_EXEC)
		mns_exec_builtin_call(data, envp, parsed);
	else if (parsed.type & GLOBAL_EXEC)
		return (exec = mns_exec_path(data->paths, parsed.command));
	else
		exec = ft_strdup(parsed.command);
	return (exec);
}

// int	mns_execute_simple(t_parsed parsed, char **paths, char **envp)
int	mns_execute_simple(t_parsed parsed, t_data *data, char **envp)
{
	char	*exec;
	pid_t	pid;

	exec = mns_exec_simple_setup(data, envp, parsed);
	if (exec)
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
	return (ALL_FINE);
}
