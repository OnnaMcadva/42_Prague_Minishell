/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:46 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:47:52 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int mns_com_echo_check(char *str)
{
    int i;

    i = 0;
    while (str[++i])
        if (str[i] != 'n')
            return (0);
    return (1);
}

void    mns_com_echo(char **args)
{
    int i;
    int no_nl_flag;

    no_nl_flag = 0;
    if (args[1])
    {    
        i = 1;
        if (ft_strncmp(args[1], "-n", 2) == 0 && mns_com_echo_check(args[1]))
        {
            i++;
            no_nl_flag = 1;
        }
        while (args[i])
        {
            ft_putstr_fd(args[i++], STDOUT_FILENO);
            if (args[i])
                ft_putchar_fd(WHITESPACE, STDOUT_FILENO);
        }
    }
    if (no_nl_flag == 0)
        ft_putchar_fd(NEW_LINE, STDOUT_FILENO);
}