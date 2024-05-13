/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_free.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 09:42:14 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 13:16:56 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->splitted)
		while (data->splitted[i])
			free(data->splitted[i++]);
	free (data->splitted);
	free (data->splitted_type);
	i = 0;
	if (data->paths)
		while (data->paths[i])
			free(data->paths[i++]);
	free (data->paths);
	i = 0;
	if (data->parsed)
		while (i < data->tkn_count)
			free(data->parsed[i++].args);
	free (data->parsed);
	free (data->line);
}
