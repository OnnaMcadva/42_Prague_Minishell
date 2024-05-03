/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:34 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_init_paths(t_data *data)
{
	data->paths = ft_split(getenv("PATH"), ':');
	if (!data->paths)
		return (MNS_ERROR);
	return (ALL_FINE);
}

/* Sets data elements to zero */
int	mns_init_data(t_data *data)
{
	data->line = NULL;
	data->splitted = NULL;
	data->parsed = NULL;
	data->splitted_type = NULL;
	data->paths = NULL;
	data->tkn_count = 0;
	data->pipes_count = 0;
	return (ALL_FINE);
}
