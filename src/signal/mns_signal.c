/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:44 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/23 13:32:54 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Handles ctrl-c signal. */
void	mns_sigint_handler(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	mns_sigint_exec(int sig)
{
	if (sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
}

void	mns_sigquit_exec(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putendl_fd("Quit (core dumped)", STDERR_FILENO);
	}
}
