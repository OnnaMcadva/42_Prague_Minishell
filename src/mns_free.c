/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:42:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/04 12:43:43 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mns_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->parsed)
		while (data->parsed[i])
			free(data->parsed[i++]);
	i = 0;
	if (data->paths)
		while (data->paths[i])
			free(data->paths[i++]);
	free (data->paths);
	free (data->parsed);
	free (data->line);
}
