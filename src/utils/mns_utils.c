/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:37:49 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/16 10:50:53 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Toggles the in_quote switch and returns either it was toggled or not */
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

int	mns_util_is_space(const char c)
{
	if (c == WHITESPACE
		|| c == TAB_SYMBOL
		|| c == NEW_LINE)
		return (1);
	return (0);
}

int	mns_util_tablen(char **tab)
{
	int	i;

	i = 0;
	if (tab)
		while (tab[i])
			i++;
	return (i);
}

void	mns_util_free_tab(char **tab)
{
	int	i;

	if (tab)
	{
		i = 0;
		while (tab[i])
			free(tab[i++]);
		free(tab);
	}
}
