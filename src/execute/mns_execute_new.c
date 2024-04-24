/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_execute_new.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:04:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 15:32:12 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_execute(t_data *data, char **envp)
{
	int	i;

	mns_execute_first(data->parsed[0], envp);
	i = 1;
	while (data->parsed[i].type != NULL_TOKEN)
	{
		i++;
	}
	mns_execute_last(data->parsed[i], envp);
}
