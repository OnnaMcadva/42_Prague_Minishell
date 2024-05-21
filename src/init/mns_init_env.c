/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 09:25:24 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/21 13:01:08 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_init_shell(t_data *data)
{
	char	dir[PATH_MAX];
	char	*temp;
	int		shlvl;

	temp = getcwd(dir, PATH_MAX);
	if (!temp)
		return (MNS_ERROR);
	temp = ft_strjoin(dir, "/minishell");
	if (!temp)
		return (MNS_ERROR);
	mns_env_change(data, "SHELL", temp);
	free (temp);
	shlvl = 1;
	temp = mns_getenv(data->env_copy, "SHLVL");
	if (!temp)
		return (mns_env_add(data, "SHLVL=1"));
	else
		shlvl += ft_atoi(temp);
	temp = ft_itoa(shlvl);
	if (!temp)
		return (perror("init_itoa"), MNS_ERROR);
	if (mns_env_change(data, "SHLVL", temp) == MNS_ERROR)
		return (free(temp), MNS_ERROR);
	free(temp);
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
	if (mns_init_shell(data) == MNS_ERROR)
		return (MNS_ERROR);
	return (ALL_FINE);
}
