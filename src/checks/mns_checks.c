/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:35 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/14 16:00:36 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int		mns_check_redirs(int *splitted_type, int tkn_count)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (i < tkn_count)
	{
		if (splitted_type[i] == IN_OPERATOR
			|| splitted_type[i] == OUT_OPERATOR
			|| splitted_type[i] == OUT_APPEND_OPRTR)
		{
			if (splitted_type[i + 1] != WORD)
				return (ft_putendl_fd("minishell: syntax error near unexpected token `newline\'", STDOUT_FILENO), MNS_ERROR);
		}
		i++;
	}
	return (ALL_FINE);
}

int	mns_check_quotes(char *line)
{
	int		i;
	char	in_quote;

	if (!line)
		return (MNS_ERROR);
	i = 0;
	in_quote = 0;
	while (line[i])
		mns_util_in_quote(&in_quote, line[i++]);
	if (in_quote != 0)
	{
		ft_putendl_fd
			("From subject:\nYour shell should not interpret unclosed quotes",
			STDOUT_FILENO);
		return (MNS_ERROR);
	}
	return (ALL_FINE);
}
