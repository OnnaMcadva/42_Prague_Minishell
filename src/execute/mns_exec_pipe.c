/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exec_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:04:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/23 02:06:35 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#if 0
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
	return (ALL_FINE);
}
#endif

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
	return (ALL_FINE);
}
