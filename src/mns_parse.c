/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:56:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/22 14:42:07 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	mns_parse_init(t_data *data)
{
	int	i;

	data->parsed = malloc((data->tkn_count + 1) * sizeof(t_parsed));
	if (!data->parsed)
		return (MNS_ERROR);
	i = 0;
	while (i <= data->tkn_count)
	{
		data->parsed[i].args = NULL;
		data->parsed[i].command = NULL;
		data->parsed[i].type = 0;
		i++;
	}

	return (ALL_FINE);
}

int	mns_parse_process(t_data *data)
{
	if (mns_parse_init(data) == MNS_ERROR)
		return (MNS_ERROR);
	data->parsed[0].command = data->splitted[0];
	data->parsed[0].args = data->splitted;
	return (ALL_FINE);
}

/* Calls mns_split and parses tokens.
	Returns -1 (MNS_ERROR) if no tokens were found
	or if there's an uncloused quote. */
int	mns_parse(t_data *data)
{
	int	token_count;

	token_count = mns_split(&data->splitted, data->line);
	if (mns_check_line(data->line) == MNS_ERROR || !token_count)
		return (MNS_ERROR);
	data->tkn_count = token_count;
	return (mns_parse_process(data));
}
