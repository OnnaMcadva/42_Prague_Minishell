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

int	mns_exec_pipe_dup(t_parsed *parsed, int std_fileno)
{
	int	saved;

	saved = dup(std_fileno);
	dup2(parsed->fd[std_fileno], std_fileno);
	close(parsed->fd[std_fileno]);
	return (saved);
}

int mns_exec_pipe(t_data *data, char **envp, int count)
{
	int		saved_out;
	int		saved_in;
	int		i;
	
	saved_out = mns_exec_pipe_dup(&data->parsed[1], STDOUT_FILENO);
	mns_execute_simple(&data->parsed[0], data, envp);
	mns_exec_util_restore_stdfileno(saved_out, STDOUT_FILENO);
	i = 2;
	while (i < count)
	{
		saved_in = mns_exec_pipe_dup(&data->parsed[i - 1], STDIN_FILENO);
		saved_out = mns_exec_pipe_dup(&data->parsed[i + 1], STDOUT_FILENO);
		mns_execute_simple(&data->parsed[i], data, envp);
		mns_exec_util_restore_stdfileno(saved_in, STDIN_FILENO);
		mns_exec_util_restore_stdfileno(saved_out, STDOUT_FILENO);
		i += 2;
	}
	saved_in = mns_exec_pipe_dup(&data->parsed[count - 1], STDIN_FILENO);
	mns_execute_simple(&data->parsed[count], data, envp);
	mns_exec_util_restore_stdfileno(saved_in, STDIN_FILENO);
	return (ALL_FINE);
}