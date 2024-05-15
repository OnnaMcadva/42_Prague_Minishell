/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 00:13:47 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/15 01:29:03 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_env_add(t_data *data, char *to_add)
{
	int		i;
	char	**temp_envp;

	i = mns_util_tablen(data->env_copy);
	temp_envp = malloc((i + 2) * sizeof(char *));
	if (!temp_envp)
		return (MNS_ERROR);
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
	int		i;
	int		len;
	char	**temp_envp;

	i = mns_util_tablen(data->env_copy);
	len = ft_strlen(to_delete);
	temp_envp = malloc(i * sizeof(char *));
	if (!temp_envp)
		return (MNS_ERROR);
	temp_envp[i] = NULL;
	while (--i >= 0)
	{
		if (ft_strncmp(to_delete, temp_envp[i], len))
			break ;
		temp_envp[i] = ft_strdup(data->env_copy[i]);
		if (mns_env_util_malloc_check(temp_envp, i) == MNS_ERROR)
			return (MNS_ERROR);
	}
}
