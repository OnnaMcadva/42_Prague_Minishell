/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 12:46:44 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/17 15:45:54 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mns_sigint_handler(int sig)
{
	mns_util_do_nothing(&sig);
	ft_putchar_fd('\n', STDOUT_FILENO);
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
}
