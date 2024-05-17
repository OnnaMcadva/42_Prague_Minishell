/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:52 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/17 00:16:47 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_env(char **envp)
{
	int	i;

	if (!envp)
		return (EXIT_FAILURE);
	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], STDOUT_FILENO);
	return (EXIT_SUCCESS);
}
