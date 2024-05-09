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

int	mns_parse_command(const char **splitted, const int *splitted_type, t_parsed *parsed)
{
	int	args_count;
	int	step;

	args_count = 0;
	step = mns_parse_util_count_args(splitted, splitted_type, &args_count);
	parsed->args = malloc((args_count + 1) * sizeof(char *));
	if (!parsed->args)
		return (perror("Malloc error"), MNS_ERROR);
	mns_parse_util_assign_args(parsed, splitted, splitted_type);
	return (step);
}

/* TODO: split into smaller functions */
int	mns_parse_process(const char **splitted, const int *splitted_type, t_parsed	*parsed)
{
	int	i;
	int	step;

	i = 0;
	while (splitted[i])
	{
		if (splitted_type[i] != PIPE)
		{
			step = mns_parse_command(splitted + i, splitted_type + i, parsed);
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
	data->tkn_count = mns_split(&data->splitted, &data->splitted_type, data->line);
	if (mns_check_line(data->line) == MNS_ERROR || !data->tkn_count)
		return (MNS_ERROR);
	if (mns_parse_init(data) == MNS_ERROR)
		return (MNS_ERROR);
	return (mns_parse_process((const char **) data->splitted, data->splitted_type, data->parsed));
}
