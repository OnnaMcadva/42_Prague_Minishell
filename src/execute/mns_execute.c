/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_execute.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 15:04:23 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/23 14:48:34 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

/* Right now just calls mns_execute_simple
	TODO: call functions needed depending on context
	(pipes, internal commands etc) */
void	mns_execute(t_data *data, char **envp)
{
	mns_execute_simple(data->parsed[0], data->paths, envp);
}
