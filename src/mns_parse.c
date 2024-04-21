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

#include "../includes/minishell.h"

/* Calls mns_split and parses tokens.
	Returns -1 (MNS_ERROR) if no tokens were found
	or if there's an uncloused quote. */
int	mns_parse(t_data *data)
{
	data->tkn_count = mns_split(&data->splitted, data->line);
	if (mns_check_line(data->line) == MNS_ERROR || !data->tkn_count)
		return (MNS_ERROR);
	return (ALL_FINE);
}
