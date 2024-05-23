/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:37:49 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/23 13:39:16 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Toggles the in_quote switch and returns either it was toggled or not */
int	mns_util_in_quote(unsigned char *in_quote, char c)
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

int	mns_util_tabcpy(char **dest, char **src, char *last_line)
{
	int	i;

	if (!src || !*src)
		return (1);
	i = 0;
	while (src[i] && src[i] != last_line)
	{
		dest[i] = ft_strdup(src[i]);
		if (!dest[i])
			return (mns_free_tab(dest), MNS_ERROR);
		i++;
	}
	dest[i] = NULL;
	return (ALL_FINE);
}

int	mns_util_isredir(int type)
{
	if (type == IN_OPERATOR
		|| type == HERE_DOC
		|| type == OUT_OPERATOR
		|| type == OUT_APPEND_OPRTR)
		return (1);
	return (0);
}
