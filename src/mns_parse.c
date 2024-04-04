/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:56:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/04 14:59:57 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mns_parse(t_data *data)
{
	data->parsed = ft_split(data->line, WHITE_SPACE);
	if (!data->parsed[0])
		return(ERROR);
	return (ALL_FINE);
}
