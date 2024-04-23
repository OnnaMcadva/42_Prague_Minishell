/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:42:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:34 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Frees line, paths and splitted. */
void	mns_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->splitted)
		while (data->splitted[i])
			free(data->splitted[i++]);
	i = 0;
	if (data->paths)
		while (data->paths[i])
			free(data->paths[i++]);
	free (data->parsed);
	free (data->paths);
	free (data->splitted);
	free (data->line);
}
