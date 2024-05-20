/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:49:05 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/20 11:13:20 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_tknlen(char *line, int *tkn_len)
{
	unsigned char	in_quote;
	int				pos;

	in_quote = 0;
	pos = 0;
	while (line[pos])
	{
		if (mns_util_in_quote(&in_quote, line[pos]))
			pos++;
		else
		{
			if (!in_quote && mns_util_is_space(line[pos]))
				break ;
			(*tkn_len)++;
			pos++;
		}
	}
	while (mns_util_is_space(line[pos]))
		pos++;
	return (pos);
}

char	*mns_tkncpy(char *line, char *token, int tkn_len, int next_pos)
{
	int				i;
	int				j;
	unsigned char	in_quote;

	in_quote = 0;
	i = 0;
	j = 0;
	while (line[i] && i < next_pos)
	{
		if (mns_util_in_quote(&in_quote, line[i]))
			i++;
		else
		{
			if (!in_quote && mns_util_is_space(line[i]))
				break ;
			else if (j < tkn_len)
				token[j++] = line[i];
			i++;
		}
	}
	token[j] = '\0';
	return (token);
}

int	mns_split_process(t_data *data, char *line, int tokens)
{
	int	i;
	int	tkn_len;
	int	next_pos;

	i = 0;
	tkn_len = 0;
	while (i < tokens)
	{
		next_pos = mns_tknlen(line, &tkn_len);
		data->splitted[i] = (char *)malloc((tkn_len + 1) * sizeof(char));
		if (!data->splitted[i])
			return (MNS_ERROR);
		data->splitted[i] = mns_tkncpy(line, data->splitted[i],
				tkn_len, next_pos);
		data->spltd_type[i] = mns_split_util_type(line);
		if (data->spltd_type[i] == ENV)
			mns_split_util_read_env(data, &data->splitted[i]);
		line += next_pos;
		i++;
	}
	data->splitted[i] = NULL;
	data->spltd_type[i] = NULL_TOKEN;
	return (ALL_FINE);
}

/* Counts a number of tokens to allocate */
int	mns_count_tokens(char *line)
{
	int				i;
	int				count;
	unsigned char	in_quote;

	i = 0;
	count = 1;
	in_quote = 0;
	while (line[i])
	{
		mns_util_in_quote(&in_quote, line[i]);
		if (!in_quote && mns_util_is_space(line[i]))
		{
			while (mns_util_is_space(line[i]))
				i++;
			if (!line[i])
				break ;
			count++;
			continue ;
		}
		i++;
	}
	return (count);
}

/* Splits line to an array of strings (splitted)
	and returns a number of parsed tokens.
	Also makes an array of token types,
	to make parsing easier.
	Returns 0 in case of empty line.
	Returns -1 (MNS_ERROR) in case of malloc error. */
int	mns_split(t_data *data, char *line)
{
	int	tokens;

	while (mns_util_is_space(*line))
		line++;
	if (!*line)
		return (0);
	tokens = mns_count_tokens(line);
	data->splitted = malloc((tokens + 1) * sizeof(char *));
	if (!data->splitted)
		return (perror("malloc"), MNS_ERROR);
	data->spltd_type = malloc((tokens + 1) * sizeof(int));
	if (!data->spltd_type)
		return (perror("malloc"), MNS_ERROR);
	if (mns_split_process(data, line, tokens) == MNS_ERROR)
		return (MNS_ERROR);
	return (tokens);
}
