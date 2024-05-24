/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:56:17 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/24 01:21:19 by maxmakagono      ###   ########.fr       */
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
		data->parsed[i].command = NULL;
		data->parsed[i].args = NULL;
		data->parsed[i].redir_in = NULL;
		data->parsed[i].redir_out = NULL;
		data->parsed[i].type = NULL_TOKEN;
		data->parsed[i].fd[0] = STDIN_FILENO;
		data->parsed[i].fd[1] = STDOUT_FILENO;
		i++;
	}
	return (ALL_FINE);
}

int	mns_parse_command(char **splitted,
			int *spltd_type, t_parsed *parsed)
{
	int	args_count;
	int	step;

	args_count = 0;
	step = mns_parse_util_count_args(splitted, spltd_type, &args_count);
	parsed->args = malloc((args_count + 1) * sizeof(char *));
	if (!parsed->args)
		return (perror("Malloc error"), MNS_ERROR);
	mns_parse_util_assign_args(parsed, splitted, spltd_type);
	return (step);
}

/* TODO: split into smaller functions */
int	mns_parse_process(t_data *data, t_parsed *parsed)
{
	int	i;
	int	step;

	i = 0;
	while (data->splitted[i])
	{
		if (data->spltd_type[i] != PIPE)
		{
			step = mns_parse_command(data->splitted + i,
					data->spltd_type + i, parsed);
			if (step == MNS_ERROR)
				return (MNS_ERROR);
			i += step;
		}
		else
		{
			parsed->type = PIPE;
			i++;
		}
		parsed++;
	}
	return (ALL_FINE);
}

/* Calls mns_split and parses tokens.
	Returns -1 (MNS_ERROR) if no tokens were found
	or if there's an unclosed quote. */
int	mns_parse(t_data *data)
{
	mns_split_util_copy_line(&data->line);
	data->tkn_count = mns_split(data, data->line);
	if (mns_check_quotes(data->line) == MNS_ERROR
		|| !data->tkn_count
		|| mns_check_redirs(data) == MNS_ERROR)
		return (MNS_ERROR);
	if (mns_parse_init(data) == MNS_ERROR)
		return (MNS_ERROR);
	return (mns_parse_process(data, data->parsed));
}
