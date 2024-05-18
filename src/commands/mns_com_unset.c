/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:16 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/18 09:36:11 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_unset(t_data *data, char **args)
{
	int		i;

	if (args)
	{
		i = 1;
		while (args[i])
		{
			mns_env_delete(data, args[i]);
			i++;
		}
	}
	return (EXIT_SUCCESS);
}