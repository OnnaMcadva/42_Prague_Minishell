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

/* Creates a temp file, writes the command output there,
	then outputs the contents to STDOUT 
	TODO: cleanup, split into smaller functions 
	and make exec_middle or something... */
int	mns_execute_complex(t_data *data, char **envp)
{
	int	i;
	int	save_stdout;

	save_stdout = mns_exec_util_dup("./temp", O_CREAT | O_RDWR | O_TRUNC, STDOUT_FILENO);
	if (save_stdout == MNS_ERROR)
		return (MNS_ERROR);
	mns_execute_simple(data->parsed[0], data, envp);
	if (mns_exec_util_restore_stdout(save_stdout) == MNS_ERROR)
		return (MNS_ERROR);
	i = 1;
	while (data->parsed[i].type != NULL_TOKEN)
	{
		i++;
	}
	mns_exec_util_file_to_output("./temp", 0);
	return (ALL_FINE);
}
