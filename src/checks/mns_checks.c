/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:35 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/13 14:23:28 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_check_line( char *line)
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
