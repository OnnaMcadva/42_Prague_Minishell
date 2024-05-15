/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/15 14:50:59 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_init_pipes(t_data *data)
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

int	mns_init_data(t_data *data)
{
	data->line = NULL;
	data->splitted = NULL;
	data->parsed = NULL;
	data->splitted_type = NULL;
	data->paths = NULL;
	data->tkn_count = 0;
	data->pipes_count = 0;
	if (mns_init_paths(data) == MNS_ERROR)
		return (MNS_ERROR);
	return (ALL_FINE);
}

int	mns_init_env_copy(char **envp, t_data *data)
{
	int	i;

	i = 0;
	if (envp)
		while(envp[i])
			i++;
	if (!i)
		return (MNS_ERROR);
	data->env_copy = malloc((i + 1) * sizeof(char *));
	if (!data->env_copy)
		return (perror("malloc"), MNS_ERROR);
	data->env_copy[i] = NULL;
	while (--i >= 0)
	{
		data->env_copy[i] = ft_strdup(envp[i]);
		if (mns_env_util_malloc_check(data->env_copy, i) == MNS_ERROR)
			return (MNS_ERROR);
	}
	return (ALL_FINE);
}
