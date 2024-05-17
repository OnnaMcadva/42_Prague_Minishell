/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/16 17:08:22 by maxmakagono      ###   ########.fr       */
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
	char	*temp;

	temp = mns_getenv(data->env_copy, "PATH");
	if (temp)
	{
		data->paths = ft_split(temp, ':');
		if (!data->paths)
			return (perror("ft_split: malloc"), MNS_ERROR);
	}
	else
		data->paths = NULL;
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

int	mns_init_shell(t_data *data)
{
	int		shlvl;
	char	*temp;

	shlvl = 1;
	temp = mns_getenv(data->env_copy, "SHLVL");
	if (temp)
		shlvl += (ft_atoi(temp));
	temp = ft_itoa(shlvl);
	if (temp)
	{
		if (mns_env_change(data, "SHLVL", temp) == MNS_ERROR)
			return (free(temp), MNS_ERROR);
		free(temp);
	}
	temp = mns_getenv(data->env_copy, "_");
	if (temp)
		if (mns_env_change(data, "SHELL", temp) == MNS_ERROR)
			return (MNS_ERROR);
	return (ALL_FINE);
}

int	mns_init_env(char **envp, t_data *data)
{
	int	i;

	i = 0;
	data->exit_status = 0;
	if (envp)
		while (envp[i])
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
	return (mns_init_shell(data));
}
