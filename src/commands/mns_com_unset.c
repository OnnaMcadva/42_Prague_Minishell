/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:49:16 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 12:11:48 by mmakagon         ###   ########.fr       */
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
