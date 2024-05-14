/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/14 23:20:19 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_com_exit(t_data *data, char *str_code)
{
	int	code;
	int	i;

	code = ft_atoi(str_code);
	ft_putendl_fd("exit", STDOUT_FILENO);
	i = 0;
	if (str_code)
	{
		while (str_code[i])
		{
			if (!ft_isdigit(str_code[i]))
			{
				code = 255;
				ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
				ft_putstr_fd(str_code, STDOUT_FILENO);
				ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
				break ;
			}
			i++;
		}
	}
	mns_free_data(data);
	mns_free_tab(data->env_copy);
	exit (code);
}
