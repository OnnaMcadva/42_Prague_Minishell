/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:56:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 15:44:47 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	mns_parse(t_data *data)
{
	data->tkn_count = mns_split(&data->splitted, data->line);
	if (!data->tkn_count)
		return (MNS_ERROR);
	return (ALL_FINE);
}
