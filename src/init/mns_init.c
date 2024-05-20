/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/20 21:39:47 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_init_pipes(t_data *data)
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
			data->pipes_count++;
		}
		i++;
	}
	return (data->pipes_count * 2);
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
	data->spltd_type = NULL;
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
		shlvl += ft_atoi(temp);
	temp = ft_itoa(shlvl);
	if (!temp)
		return (perror("init_atoi"), MNS_ERROR);
	else
	{
		if (mns_env_change(data, "SHLVL", temp) == MNS_ERROR)
			return (free(temp), MNS_ERROR);
		free(temp);
	}
	temp = mns_getenv(data->env_copy, "PWD");
	if (temp)
	{
		temp = ft_strjoin(temp, "/minishell");
		if (temp)
			mns_env_change(data, "SHELL", temp);
		free (temp);
	}
	return (ALL_FINE);
}

int	mns_init_env(char **envp, t_data *data)
{
	int	tab_len;

	data->exit_status = 0;
	tab_len = mns_util_tablen(envp);
	if (tab_len <= 0)
		return (MNS_ERROR);
	data->env_copy = malloc((tab_len + 1) * sizeof(char *));
	if (!data->env_copy)
		return (perror("malloc"), MNS_ERROR);
	if (mns_util_tabcpy(data->env_copy, envp, NULL) == MNS_ERROR)
		return (MNS_ERROR);
	return (mns_init_shell(data));
}
