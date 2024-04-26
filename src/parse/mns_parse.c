/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:56:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 14:18:16 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
		data->parsed[i].type = NULL_TOKEN;
		i++;
	}
	return (ALL_FINE);
}

int	mns_parse_count_args(char **splitted, int *splitted_type)
{
	int	i;

	i = 0;
	while (splitted[i] && splitted_type[i] != PIPE)
		i++;
	return (i);
}

void	mns_parse_assign_args(t_data *data, int i, int j, int args_count)
{
	int	k;

	k = 0;
	while(k < args_count && data->splitted[i])
	{
		data->parsed[j].args[k] = data->splitted[i];
		k++;
		i++;
	}
	data->parsed[j].args[k] = NULL;
}

int	mns_parse_process(t_data *data)
{
	int	i;
	int	j;
	int	args_count;

	if (mns_parse_init(data) == MNS_ERROR)
		return (MNS_ERROR);
	i = 0;
	j = 0;
	args_count = 0;
	while (data->splitted[i])
	{
		if (data->splitted_type[i] == WORD)
		{
			args_count = mns_parse_count_args(data->splitted + i, data->splitted_type + i);
			data->parsed[j].args = malloc((args_count + 1) * sizeof(char *));
			if (!data->parsed[j].args)
				return (perror("Malloc error"), MNS_ERROR);
			data->parsed[j].command = data->splitted[i];
			mns_parse_assign_args(data, i, j, args_count);
			j++;
			i += args_count;
		}
		else
			i++;
	}
	return (ALL_FINE);
}

/* Calls mns_split and parses tokens.
	Returns -1 (MNS_ERROR) if no tokens were found
	or if there's an unclosed quote. */
int	mns_parse(t_data *data)
{
	data->tkn_count = mns_split(&data->splitted, &data->splitted_type, data->line);
	if (mns_check_line(data->line) == MNS_ERROR || !data->tkn_count)
		return (MNS_ERROR);
	return (mns_parse_process(data));
}
