/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exec_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:29:45 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/21 12:16:50 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	mns_exec_redir_set(t_parsed *parsed, int *save_fileno)
{
	if (parsed->type & IN_OPERATOR || parsed->type & HERE_DOC)
		save_fileno[0] = mns_exec_util_file_dup(
				parsed->redir_in,
				O_RDONLY,
				STDIN_FILENO);
	if (parsed->type & OUT_OPERATOR)
		save_fileno[1] = mns_exec_util_file_dup(
				parsed->redir_out,
				O_CREAT | O_WRONLY | O_TRUNC,
				STDOUT_FILENO);
	else if (parsed->type & OUT_APPEND_OPRTR)
		save_fileno[1] = mns_exec_util_file_dup(
				parsed->redir_out,
				O_CREAT | O_WRONLY | O_APPEND,
				STDOUT_FILENO);
}

void	mns_exec_redir_restore(int *std_fileno)
{
	if (std_fileno[0] != MNS_ERROR)
		mns_exec_util_restore_stdfileno(std_fileno[0], STDIN_FILENO);
	if (std_fileno[1] != MNS_ERROR)
		mns_exec_util_restore_stdfileno(std_fileno[1], STDOUT_FILENO);
}
