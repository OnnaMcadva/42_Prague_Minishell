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

int mns_exec_redir_out(t_parsed *parsed)
{
	if (parsed->type & OUT_OPERATOR)
		return (mns_exec_util_dup(parsed->redir_out, O_CREAT | O_WRONLY | O_TRUNC, STDOUT_FILENO));
	else if (parsed->type & OUT_APPEND_OPRTR)
		return (mns_exec_util_dup(parsed->redir_out, O_CREAT | O_WRONLY | O_APPEND, STDOUT_FILENO));
	else
		return (MNS_ERROR);
}

/* Calls built-in functions */
void	mns_exec_builtin_call(t_data *data, char **envp, t_parsed parsed)
{
	int	save_stdout;

	save_stdout = mns_exec_redir_out(&parsed);
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
	if (save_stdout != MNS_ERROR)
		mns_exec_util_restore_stdfileno(save_stdout, STDOUT_FILENO);
}

char *mns_exec_simple_setup(t_data *data, char **envp, t_parsed parsed)
{
	char	*exec;

	exec = NULL;
	if (parsed.type & BUILTIN_EXEC)
		mns_exec_builtin_call(data, envp, parsed);
	else if (parsed.type & GLOBAL_EXEC)
	{
		if (mns_init_paths(data) != MNS_ERROR)
			exec = mns_exec_path(data->paths, parsed.command);
	}
	else
		exec = ft_strdup(parsed.command);
	return (exec);
}

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
			mns_exec_redir_out(&parsed);
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
