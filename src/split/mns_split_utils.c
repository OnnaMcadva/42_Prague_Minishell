/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_split_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:14:05 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/17 13:41:09 by mmakagon         ###   ########.fr       */
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

void	mns_split_util_read_env(t_data *data, char **splitted_i)
{
	char	*temp;

	if (splitted_i && *splitted_i)
	{
		if (ft_strcmp(*splitted_i, "$?") == 0)
			temp = ft_itoa(data->exit_status);
		else
			temp = ft_strdup(mns_getenv(data->env_copy, *splitted_i));
		if (temp)
		{
			free(*splitted_i);
			*splitted_i = temp;
		}
		else
			perror("read_env error");
	}
}
