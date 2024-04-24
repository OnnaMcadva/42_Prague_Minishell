/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 10:49:05 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 11:29:19 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_tknlen(const char *line, int *tkn_len)
{
	char	in_quote;
	int		pos;

	in_quote = 0;
	pos = 0;
	while (line[pos])
	{
		if (mns_util_in_quote(&in_quote, line[pos]))
			pos++;
		else
		{
			if (!in_quote && line[pos] == WHITESPACE)
				break ;
			(*tkn_len)++;
			pos++;
		}
	}
	while (line[pos] == WHITESPACE)
		pos++;
	return (pos);
}

char	*mns_tkncpy(const char *line, char *token, int tkn_len, int next_pos)
{
	int		i;
	int		j;
	char	in_quote;

	in_quote = 0;
	i = 0;
	j = 0;
	while (line[i] && i < next_pos)
	{
		if (mns_util_in_quote(&in_quote, line[i]))
			i++;
		else
		{
			if (!in_quote && line[i] == WHITESPACE)
				break ;
			else if (j < tkn_len)
				token[j++] = line[i];
			i++;
		}
	}
	token[j] = '\0';
	return (token);
}

int	mns_split_process(char **splitted, int *spltd_type,
						const char *line, int tokens)
{
	int	i;
	int	tkn_len;
	int	next_pos;

	i = 0;
	tkn_len = 0;
	while (i < tokens)
	{
		next_pos = mns_tknlen(line, &tkn_len);
		splitted[i] = (char *)malloc((tkn_len + 1) * sizeof(char));
		if (!splitted[i])
			return (MNS_ERROR);
		spltd_type[i] = mns_split_util_type(line);
		splitted[i] = mns_tkncpy(line, splitted[i], tkn_len, next_pos);
		line += next_pos;
		i++;
	}
	splitted[i] = NULL;
	spltd_type[i] = NULL_TOKEN;
	return (ALL_FINE);
}

/* Counts a number of tokens to allocate */
int	mns_count_tokens(const char *line)
{
	int		i;
	int		count;
	char	in_quote;

	i = 0;
	count = 1;
	in_quote = 0;
	while (line[i])
	{
		mns_util_in_quote(&in_quote, line[i]);
		if (!in_quote && line[i] == WHITESPACE)
		{
			while (line[i] == WHITESPACE)
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
int	mns_split(char ***splitted, int **spltd_type, const char *line)
{
	int	tokens;

	while (*line == WHITESPACE)
		line++;
	if (!*line)
		return (0);
	tokens = mns_count_tokens(line);
	*splitted = malloc((tokens + 1) * sizeof(char *));
	*spltd_type = malloc((tokens + 1) * sizeof(int));
	if (!*splitted || !*spltd_type)
		return (MNS_ERROR);
	if (mns_split_process(*splitted, *spltd_type, line, tokens) == MNS_ERROR)
		return (MNS_ERROR);
	return (tokens);
}
