/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:14:05 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/20 10:59:35 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_split_util_type(char *line)
{
	unsigned char	in_quote;

	in_quote = 0;
	while (*line && mns_util_in_quote(&in_quote, *line))
		line++;
	if (!line)
		return (NULL_TOKEN);
	else if (in_quote != SINGLE_QUOTE && line[0] == DOLLAR_SIGN && line[1])
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

void	mns_split_util_read_env(t_data *data, char **splitted_i)
{
	char	*temp;

	if (splitted_i && *splitted_i)
	{
		if (ft_strcmp(*splitted_i, "$?") == 0)
			temp = ft_itoa(data->exit_status);
		else
			temp = ft_strdup(mns_getenv(data->env_copy, *splitted_i));
		free(*splitted_i);
		if (temp)
			*splitted_i = temp;
		else
			*splitted_i = ft_strdup("\0");
	}
}
