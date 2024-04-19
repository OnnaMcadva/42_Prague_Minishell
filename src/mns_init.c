/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 14:57:47 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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
int	mns_init(t_data *data)
{
	data->line = NULL;
	data->splitted = NULL;
	data->tkn_count = 0;
	if (mns_init_paths(data) == MNS_ERROR)
		return (mns_free_data(data), MNS_ERROR);
	return (ALL_FINE);
}
