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

/* TODO: manage NULL returned from getenv */
int	mns_init_paths(t_data *data)
{
	data->paths = ft_split(getenv("PATH"), ':');
	if (!data->paths)
		return (MNS_ERROR);
	return (ALL_FINE);
}

/* Sets data elements to zero
	and gets paths for executables.
	Returns -1 (MNS_ERROR) in case of malloc error */
int	mns_init_data(t_data *data)
{
	data->line = NULL;
	data->splitted = NULL;
	data->parsed = NULL;
	data->splitted_type = NULL;
	data->tkn_count = 0;
	data->pipes_count = 0;
	if (mns_init_paths(data) == MNS_ERROR)
		return (mns_free_data(data), MNS_ERROR);
	return (ALL_FINE);
}
