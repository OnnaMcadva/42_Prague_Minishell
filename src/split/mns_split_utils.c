/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:14:05 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 15:43:18 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_split_util_type(char *line)
{
	char	in_quote;

	in_quote = 0;
	while (*line && mns_util_in_quote(&in_quote, *line))
		line++;
	if (!line)
		return (NULL_TOKEN);
	else if (in_quote != SINGLE_QUOTE && line[0] == DOLLAR_SIGN)
		return (ENV);
	else if (!in_quote && line[0] == PIPE_LINE)
		return (PIPE);
	else if (!in_quote && line[0] == REDIR_IN)
	{
		if (line[1] == REDIR_IN)
			return (HERE_DOC);
		return (IN_OPERATOR);
	}
	else if (!in_quote && line[0] == REDIR_OUT)
	{
		if (line[1] == REDIR_OUT)
			return (OUT_APPEND_OPRTR);
		return (OUT_OPERATOR);
	}
	else
		return (WORD);
}
