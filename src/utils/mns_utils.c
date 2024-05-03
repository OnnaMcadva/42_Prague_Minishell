/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:37:49 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 10:49:34 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Toggles in_quote switch and returns either it was toggled or not */
int	mns_util_in_quote(char *in_quote, char c)
{
	int	toggle;

	if (!*in_quote && (c == DOUBLE_QUOTE || c == SINGLE_QUOTE))
	{
		*in_quote = c;
		toggle = 1;
	}
	else if (c == *in_quote)
	{
		*in_quote = 0;
		toggle = 1;
	}
	else
		toggle = 0;
	return (toggle);
}

/* !!! A candidate for deletion !!! */
int	mns_util_is_metachar(char c)
{
	int	i;

	i = 0;
	while (META_CHARACTERS[i])
	{
		if (c == META_CHARACTERS[i])
			return (1);
		i++;
	}
	return (0);
}
