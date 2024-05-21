/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:35 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 12:15:51 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_check_redirs_err(t_data *data)
{
	ft_putstr_fd("minishell: ", STDOUT_FILENO);
	ft_putstr_fd("syntax error near unexpected token ", STDOUT_FILENO);
	if (data->spltd_type[data->tkn_count - 1] == PIPE)
		ft_putendl_fd("`|\'", STDOUT_FILENO);
	else
		ft_putendl_fd("`newline\'", STDOUT_FILENO);
	data->exit_status = 2;
}

int	mns_check_redirs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->tkn_count)
	{
		if (((data->spltd_type[i] == IN_OPERATOR
					|| data->spltd_type[i] == HERE_DOC
					|| data->spltd_type[i] == OUT_OPERATOR
					|| data->spltd_type[i] == OUT_APPEND_OPRTR)
				&& data->spltd_type[i + 1] != WORD)
			|| (data->spltd_type[i] == PIPE
				&& data->spltd_type[i + 1] == PIPE))
			break ;
		i++;
	}
	if (i < data->tkn_count)
		return (mns_check_redirs_err(data), MNS_ERROR);
	return (ALL_FINE);
}

int	mns_check_quotes(char *line)
{
	int				i;
	unsigned char	in_quote;

	if (!line)
		return (MNS_ERROR);
	i = 0;
	in_quote = 0;
	while (line[i])
		mns_util_in_quote(&in_quote, line[i++]);
	if (in_quote != 0)
	{
		ft_putendl_fd("From the subject: ", STDOUT_FILENO);
		ft_putendl_fd("Your shell should not interpret unclosed quotes",
			STDOUT_FILENO);
		return (MNS_ERROR);
	}
	return (ALL_FINE);
}
