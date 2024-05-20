/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:13:47 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/20 23:55:43 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**mns_env_find(char **envp, char *to_find)
{
	int		i;
	int		len;
	char	*tf_equals;

	if (!envp || !to_find || !*to_find)
		return (NULL);
	tf_equals = ft_strjoin(to_find, "=");
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
	return (envp + i);
}

int	mns_env_add(t_data *data, char *to_add)
{
	char	**temp_env;
	char	**pointer;
	int		tab_len;

	tab_len = mns_util_tablen(data->env_copy);
	if (tab_len <= 0)
		return (MNS_ERROR);
	temp_env = malloc((tab_len + 2) * sizeof(char *));
	if (!temp_env)
		return (perror("malloc"), MNS_ERROR);
	if (tab_len > 1)
	{
		pointer = data->env_copy + tab_len - 1;
		if (mns_util_tabcpy(temp_env, data->env_copy, *pointer) == MNS_ERROR)
			return (MNS_ERROR);
	}
	temp_env[tab_len - 1] = ft_strdup(to_add);
	if (!temp_env[tab_len - 1])
		return (mns_free_tab(temp_env), MNS_ERROR);
	pointer = data->env_copy + tab_len - 1;
	if (mns_util_tabcpy(temp_env + tab_len, pointer, NULL) == MNS_ERROR)
			return (MNS_ERROR);
	mns_free_tab(data->env_copy);
	data->env_copy = temp_env;
	return (ALL_FINE);
}

int	mns_env_delete(t_data *data, char *to_delete)
{
	char	**temp_envp;
	char	**pointer;
	int		env_len;

	env_len = mns_util_tablen(data->env_copy);
	if (env_len <= 0)
		return (MNS_ERROR);
	pointer = mns_env_find(data->env_copy, to_delete);
	if (!pointer || !*pointer)
		return (MNS_ERROR);
	temp_envp = malloc(env_len * sizeof(char *));
	if (!temp_envp)
		return (perror("malloc"), MNS_ERROR);
	if (mns_util_tabcpy(temp_envp, data->env_copy, *pointer) == MNS_ERROR)
		return (MNS_ERROR);
	env_len = mns_util_tablen(temp_envp);
	if (mns_util_tabcpy(temp_envp + env_len, pointer + 1, NULL) == MNS_ERROR)
		return (MNS_ERROR);
	mns_free_tab(data->env_copy);
	data->env_copy = temp_envp;
	return (ALL_FINE);
}

int	mns_env_change(t_data *data, char *key, char *value)
{
	char	**pointer;
	char	*temp;
	char	*new_entry;

	pointer = mns_env_find(data->env_copy, key);
	if (!pointer || !*pointer)
		return (MNS_ERROR);
	temp = ft_strjoin(key, "=");
	if (!temp)
		return (perror("malloc"), MNS_ERROR);
	new_entry = ft_strjoin(temp, value);
	free (temp);
	if (!new_entry)
		return (perror("malloc"), MNS_ERROR);
	free(*pointer);
	*pointer = new_entry;
	return (ALL_FINE);
}

char	*mns_getenv(char **envp, char *key)
{
	char	**pointer;
	int		i;

	if (key && envp)
	{
		if (key[0] == DOLLAR_SIGN)
			key++;
		pointer = mns_env_find(envp, key);
		if (!pointer || !*pointer)
			return (NULL);
		i = 0;
		while ((*pointer)[i])
		{
			if ((*pointer)[i] == '=')
				return (*pointer + i + 1);
			i++;
		}
	}
	return (NULL);
}
