/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:04:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/23 13:25:44 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_exec_pipe_exit(t_data *data, int count)
{
	int	status;
	int	i;

	i = 0;
	while (i <= count)
	{
		waitpid(data->parsed[i].pid, &status, 0);
		i += 2;
	}
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_status = WTERMSIG(status);
		if (data->exit_status != SIGTRAP + 128)
			data->exit_status += 128;
	}
}

int	mns_exec_pipe(t_data *data, int count)
{
	int		saved_out;
	int		saved_in;
	int		i;

	saved_out = mns_exec_util_pipe_dup(&data->parsed[1], STDOUT_FILENO);
	if (mns_exec_process(&data->parsed[0], data) == MNS_ERROR)
		return (MNS_ERROR);
	mns_exec_util_restore_stdfileno(saved_out, STDOUT_FILENO);
	i = 2;
	while (i < count)
	{
		saved_in = mns_exec_util_pipe_dup(&data->parsed[i - 1], STDIN_FILENO);
		saved_out = mns_exec_util_pipe_dup(&data->parsed[i + 1], STDOUT_FILENO);
		mns_exec_process(&data->parsed[i], data);
		mns_exec_util_restore_stdfileno(saved_in, STDIN_FILENO);
		mns_exec_util_restore_stdfileno(saved_out, STDOUT_FILENO);
		i += 2;
	}
	saved_in = mns_exec_util_pipe_dup(&data->parsed[count - 1], STDIN_FILENO);
	mns_exec_process(&data->parsed[count], data);
	mns_exec_util_restore_stdfileno(saved_in, STDIN_FILENO);
	mns_exec_pipe_exit(data, count);
	return (ALL_FINE);
}
