/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:42:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 09:45:12 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}

void	mns_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->parsed)
		while (i < data->tkn_count)
			free(data->parsed[i++].args);
	free (data->parsed);
	mns_free_tab(data->splitted);
	free (data->spltd_type);
	mns_free_tab(data->paths);
	free (data->line);
	free (data->prompt);
}
