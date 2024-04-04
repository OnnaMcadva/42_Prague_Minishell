/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:47 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/04 12:53:28 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mns_init_paths(t_data *data)
{
	data->paths = ft_split(getenv("PATH"), ':');
	if (!data->paths)
		return (ERROR);
	return (ALL_FINE);
}

int	mns_init(t_data *data)
{
	data->line = NULL;
	data->parsed = NULL;
	if (mns_init_paths(data) == ERROR)
		return (mns_free_data(data), ERROR);
	return (ALL_FINE);
}
