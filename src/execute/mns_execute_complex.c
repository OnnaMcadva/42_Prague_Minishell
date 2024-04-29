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

/* Saves STDOUT_FILENO to save_stdout veariable,
	opens a file, duplicates its FD to STDOUT_FILENO
	and returns save_stdout or -1 (MNS_ERROR) in case of any error. */
int	mns_exec_dup_stdout_to_file(char *filename, int open_flag)
{
	int	fd;
	int save_stdout;

	fd = open(filename, open_flag, 0777);
    if (fd == MNS_ERROR)
	{
		perror("Failed to open temporary file");
        return (MNS_ERROR);
	}
    save_stdout = dup(STDOUT_FILENO);
    if (save_stdout == MNS_ERROR)
	{
        perror("Failed to save STDOUT file descriptor");
        close(fd);
        return (MNS_ERROR);
    }
    if (dup2(fd, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to redirect STDOUT to temporary file");
		return (MNS_ERROR);
    }
    close(fd);
	return (save_stdout);
}

int	mns_exec_restore_stdout(int save_stdout)
{
	if (dup2(save_stdout, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to restore STDOUT file descriptor");
		return (MNS_ERROR);
    }
    close(save_stdout);
	return (ALL_FINE);
}

/* Creates a temp file, writes the command output there,
	then outputs the contents to STDOUT 
	TODO: cleanup, split into smaller functions 
	and make exec_middle or something... */
int	mns_execute_complex(t_data *data, char **envp)
{
	int	i;
	int	save_stdout;

	save_stdout = mns_exec_dup_stdout_to_file("./temp", O_CREAT | O_RDWR | O_TRUNC);
	if (save_stdout == MNS_ERROR)
		return (MNS_ERROR);
	mns_execute_simple(data->parsed[0], data->paths, envp);
	if (mns_exec_restore_stdout(save_stdout) == MNS_ERROR)
		return (MNS_ERROR);
	i = 1;
	while (data->parsed[i].type != NULL_TOKEN)
	{
		i++;
	}
	mns_exec_util_file_to_output("./temp", 1);
	return (ALL_FINE);
}
