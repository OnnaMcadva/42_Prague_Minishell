/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:13:47 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/15 14:57:37 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*mns_env_find(char **envp, char *key)
{
	int		i;
	int		len;
	char	*tf_equals;

	tf_equals = ft_strjoin(key, "=");
	len = ft_strlen(tf_equals);
	if (!len)
		return (free(tf_equals), NULL);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], tf_equals, len) == 0)
			break ;
		i++;
	}
	free(tf_equals);
	return (envp[i]);
}

int	mns_env_add(t_data *data, char *to_add)
{
	int		i;
	char	**temp_envp;

	i = mns_util_tablen(data->env_copy);
	if (i <= 0)
		return (MNS_ERROR);
	temp_envp = malloc((i + 2) * sizeof(char *));
	if (!temp_envp)
		return (perror("malloc"), MNS_ERROR);
	temp_envp[i + 1] = NULL;
	temp_envp[i] = ft_strdup(data->env_copy[i - 1]);
	temp_envp[--i] = ft_strdup(to_add);
	if (mns_env_util_malloc_check(temp_envp, i) == MNS_ERROR
		|| mns_env_util_malloc_check(temp_envp, i + 1) == MNS_ERROR)
		return (MNS_ERROR);
	while (--i >= 0)
	{
		temp_envp[i] = ft_strdup(data->env_copy[i]);
		if (mns_env_util_malloc_check(temp_envp, i) == MNS_ERROR)
			return (MNS_ERROR);
	}
	mns_free_tab(data->env_copy);
	data->env_copy = temp_envp;
	return (ALL_FINE);
}

int	mns_env_delete(t_data *data, char *to_delete)
{
	char	**temp_envp;
	char	*pointer;
	int		i;
	int		flag;

	pointer = mns_env_find(data->env_copy, to_delete);
	i = mns_util_tablen(data->env_copy);
	temp_envp = malloc(i * sizeof(char *));
	if (!temp_envp || !pointer || i <= 0)
		return (free(temp_envp), MNS_ERROR);
	temp_envp[i - 1] = NULL;
	flag = 1;
	while (--i >= 0)
	{
		if (data->env_copy[i] == pointer)
		{
			flag = 0;
			i--;
		}
		temp_envp[i - flag] = ft_strdup(data->env_copy[i]);
		if (mns_env_util_malloc_check(temp_envp, i - flag) == MNS_ERROR)
			return (MNS_ERROR);
	}
	mns_free_tab(data->env_copy);
	return (data->env_copy = temp_envp, ALL_FINE);
}

int	mns_env_change(t_data *data, char *key, char *value)
{
	char	*pointer;
	char	*new_entry;
	int		i;

	pointer = mns_env_find(data->env_copy, key);
	if (!pointer)
		return (MNS_ERROR);
	new_entry = mns_env_util_join(key, value);
	if (!new_entry)
		return (perror("malloc"), MNS_ERROR);
	i = 0;
	while (data->env_copy[i])
	{
		if (data->env_copy[i] == pointer)
		{
			free(data->env_copy[i]);
			data->env_copy[i] = new_entry;
			break ;
		}
		i++;
	}
	return (ALL_FINE);
}
