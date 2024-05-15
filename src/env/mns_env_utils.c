/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_env_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 01:14:48 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/15 14:55:38 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_env_util_malloc_check(char **tab, int i)
{
	if (!tab[i])
	{
		while (tab[++i])
			free(tab[i]);
		free (tab);
		return (MNS_ERROR);
	}
	return (ALL_FINE);
}

char	*mns_env_util_join(char *key, char *value)
{
	char	*temp;
	char	*new_entry;

	temp = ft_strjoin(key, "=");
	if (!temp)
		return (perror("malloc"), NULL);
	new_entry = ft_strjoin(temp, value);
	free (temp);
	return (new_entry);
}


