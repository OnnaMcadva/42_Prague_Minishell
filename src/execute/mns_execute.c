/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exec_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 10:39:48 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 15:26:11 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Checks if the called global exec is in the folders,
	saved in PATH env variable.
	If so - returns the exec with its full path (needs to be freed),
	if not - writes an error and returns NULL. */
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

/* Calls built-in functions */
void	mns_exec_builtin_call(t_data *data,
								char **envp,
								t_parsed *parsed,
								int *save_stdfileno)
{
	mns_exec_redir_set(parsed, save_stdfileno);
	if (parsed->type & COM_PWD)
		mns_com_pwd();
	else if (parsed->type & COM_EXIT)
		mns_com_exit(data, ft_atoi(parsed->args[1]));
	else if (parsed->type & COM_CD)
		mns_com_cd(parsed->args[1]);
	else if (parsed->type & COM_ENV)
		mns_com_env(envp);
	else if (parsed->type & COM_ECHO)
		mns_com_echo(parsed->args);
	mns_exec_redir_restore(save_stdfileno);
}

char	*mns_exec_setup(t_data *data,
						char **envp,
						t_parsed *parsed,
						int *save_stdfileno)
{
	char	*exec;

	exec = NULL;
	save_stdfileno[0] = -1;
	save_stdfileno[1] = -1;
	if (parsed->type & BUILTIN_EXEC)
		mns_exec_builtin_call(data, envp, parsed, save_stdfileno);
	else if (parsed->type & GLOBAL_EXEC)
			exec = mns_exec_path(data->paths, parsed->command);
	else
		exec = ft_strdup(parsed->command);
	return (exec);
}

int	mns_exec_process(t_parsed *parsed, t_data *data, char **envp)
{
	char	*exec;
	pid_t	pid;
	int		save_stdfileno[2];

	exec = mns_exec_setup(data, envp, parsed, save_stdfileno);
	if (exec)
	{
		pid = fork();
		if (pid == MNS_ERROR)
			printf ("Fork error");
		else if (pid == CHILD)
		{
			mns_exec_redir_set(parsed, save_stdfileno);
			if (execve(exec, parsed->args, envp) == MNS_ERROR)
			{
				ft_putendl_fd("minishell: permission denied: ", STDOUT_FILENO);
				mns_exec_redir_restore(save_stdfileno);
				exit (MNS_ERROR);
			}
		}
		else
			wait(NULL);
	}
	free (exec);
	return (ALL_FINE);
}

int	mns_execute(t_data *data, char **envp)
{
	int	i;

	i = mns_init_pipes(data);
	if (i > 0)
		return (mns_exec_pipe(data, envp, i));
	return (mns_exec_process(&data->parsed[0], data, envp));
}
