/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:04:23 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:34 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int mns_exec_count_set_pipes(t_data *data)
{
	int	i;

	i = 0;
	while (data->parsed[i].type != NULL_TOKEN)
	{
		if (data->parsed[i].type == PIPE)
		{
			if (pipe(data->parsed[i].fd) == MNS_ERROR)
			{
				while (--i >= 0)
				{
					close(data->parsed[i].fd[0]);
					close(data->parsed[i].fd[1]);
				}
				return (perror("pipe"), MNS_ERROR);
			}
		}
		i++;
	}
	return (i - 1);
}

/* Right now looks for pipe and calls execute_complex,
	otherwise calls mns_execute_simple.
	TODO: call functions needed depending on context
	(pipes, internal commands etc) */
int	mns_execute(t_data *data, char **envp)
{
	int	i;

	i = mns_exec_count_set_pipes(data);
	if (i > 0)
		return (mns_exec_pipe(data, envp, i));
	return (mns_execute_simple(&data->parsed[0], data, envp));
}
