/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 11:49:14 by mmakagon         ###   ########.fr       */
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

char	*mns_init_prompt(t_data *data)
{
	char	dir[PATH_MAX];
	char	*temp;
	char	*home;
	int		len;

	temp = getcwd(dir, PATH_MAX);
	if (!temp)
		return (NULL);
	home = mns_getenv(data->env_copy, "HOME");
	len = ft_strlen(home);
	if (home && ft_strncmp(home, dir, len) == 0)
		temp = ft_strjoin("~", dir + len);
	else
		temp = ft_strdup(dir);
	if (!temp)
		return (NULL);
	home = ft_strjoin(PROMPT_START, temp);
	free (temp);
	if (!home)
		return (NULL);
	temp = ft_strjoin(home, PROMPT_END);
	free (home);
	return (temp);
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
	data->prompt = mns_init_prompt(data);
	return (ALL_FINE);
}
