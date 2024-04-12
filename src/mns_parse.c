/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:56:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/04 15:19:27 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mns_parse(t_data *data)
{
	// data->parsed = ft_split(data->line, WHITESPACE);
	// printf("\n%s\n", data->parsed[0]);
	mns_split(&data->parsed, data->line);
	if (!data->parsed || !data->parsed[0])
		return (MNS_ERROR);
	return (ALL_FINE);
}
