/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:34 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int mns_init_pipes(t_data *data)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
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
			count++;
		}
		i++;
	}
	return (count * 2);
}

int	mns_init_paths(t_data *data)
{
	data->paths = ft_split(getenv("PATH"), ':');
	if (!data->paths)
		return (MNS_ERROR);
	return (ALL_FINE);
}

/* Sets data elements to zero */
int	mns_init_data(t_data *data)
{
	data->line = NULL;
	data->splitted = NULL;
	data->parsed = NULL;
	data->splitted_type = NULL;
	data->paths = NULL;
	data->tkn_count = 0;
	data->pipes_count = 0;
	return (ALL_FINE);
}
