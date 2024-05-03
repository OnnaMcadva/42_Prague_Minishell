/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:52 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:47:57 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    mns_com_env(char **envp)
{
    int i;

    i = 0;
    if (envp)
        while (envp[i])
            ft_putendl_fd(envp[i++], STDOUT_FILENO);
}