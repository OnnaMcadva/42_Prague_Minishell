/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 10:37:49 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 15:55:11 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/* To mute 'unused parameter' error */
void	*mns_util_do_nothing(void *arg)
{
	return (arg);
}

/* Toggles in_quote switch and returns either it was toggled or not */
int mns_util_in_quote(char c, int *in_quote)
{
    int toggled;

    if (!*in_quote && (c == DOUBLE_QUOTE || c == SINGLE_QUOTE))
    {
        *in_quote = c;
        toggled = 1;
    }
    else if (c == *in_quote)
    {
        *in_quote = 0;
        toggled = 1;
    }
    else
        toggled = 0;
    return (toggled);
}
