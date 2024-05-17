/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_com_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 12:48:58 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/17 11:10:29 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_com_exit_numeric_check(char *arg_one, int *code)
{
	int	i;

	if (arg_one)
	{
		i = 0;
		while (arg_one[i])
		{
			if (!ft_isdigit(arg_one[i]))
			{
				ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
				ft_putstr_fd(arg_one, STDOUT_FILENO);
				ft_putendl_fd(": numeric argument required", STDOUT_FILENO);
				*code = 2;
				return (MNS_ERROR);
			}
			i++;
		}
		*code = ft_atoi(arg_one);
	}
	return (ALL_FINE);
}

void	mns_com_exit(t_data *data, char **args)
{
	int	code;
	int	i;

	ft_putendl_fd("exit", STDOUT_FILENO);
	code = 0;
	i = 0;
	if (args)
		while (args[i])
			i++;
	if (i > 1)
	{
		if (mns_com_exit_numeric_check(args[1], &code) != MNS_ERROR && i > 2)
		{
			code = EXIT_FAILURE;
			ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
			ft_putendl_fd("too many arguments", STDOUT_FILENO);
		}
	}
	mns_free_data(data);
	mns_free_tab(data->env_copy);
	exit (code);
}
