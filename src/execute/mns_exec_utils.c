/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_exec_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:28:40 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/23 11:37:38 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	mns_exec_util_restore_stdfileno(int saved_fileno, int std_fileno)
{
	if (dup2(saved_fileno, std_fileno) == MNS_ERROR)
	{
		perror("Failed to restore STD file descriptor");
		return (MNS_ERROR);
	}
	close(saved_fileno);
	return (ALL_FINE);
}

int	mns_exec_util_pipe_dup(t_parsed *parsed, int std_fileno)
{
	int	saved_std_fileno;

	saved_std_fileno = dup(std_fileno);
	if (saved_std_fileno == MNS_ERROR)
	{
		perror("Failed to save STD file descriptor");
		close(parsed->fd[std_fileno]);
		return (MNS_ERROR);
	}
	if (dup2(parsed->fd[std_fileno], std_fileno) == MNS_ERROR)
	{
		perror("Failed to redirect STD to a pipe");
		close (parsed->fd[std_fileno]);
		return (MNS_ERROR);
	}
	close(parsed->fd[std_fileno]);
	return (saved_std_fileno);
}

/* Saves STDOUT_FILENO to	saved_std_fileno veariable,
	opens a file, duplicates its FD to STDOUT_FILENO
	and returns	saved_std_fileno if all went smoothly
	or -1 (MNS_ERROR) in case of any error. */
int	mns_exec_util_file_dup(char *filename, int open_flag, int std_fileno)
{
	int	fd;
	int	saved_std_fileno;

	fd = open(filename, open_flag, 0777);
	if (fd == MNS_ERROR)
	{
		perror("Failed to open a file");
		return (MNS_ERROR);
	}
	saved_std_fileno = dup(std_fileno);
	if (saved_std_fileno == MNS_ERROR)
	{
		perror("Failed to save STD file descriptor");
		close(fd);
		return (MNS_ERROR);
	}
	if (dup2(fd, std_fileno) == MNS_ERROR)
	{
		perror("Failed to redirect STD to a file");
		close (fd);
		return (MNS_ERROR);
	}
	close(fd);
	return (saved_std_fileno);
}

void	mns_exec_util_exit(t_data *data, t_parsed *parsed)
{
	int status;

	status = 0;
	if (data->pipes_count <= 0)
		wait (&status);
	if (parsed->type & HERE_DOC)
			unlink (HEREDOC_FILENAME);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		data->exit_status = WTERMSIG(status);
		if (data->exit_status != SIGTRAP + 128)
			data->exit_status += 128;
	}
}
