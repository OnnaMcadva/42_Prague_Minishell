#include "../../includes/minishell.h"

/* Reads from with get_next_line and makes a string with strjoin,
	returns NULL in case of error.
    Return needs to be freed. */
char *mns_exec_util_file_to_str(const char *filename)
{
	char	*buffer;
	char	*result;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == MNS_ERROR)
	{
		perror("Failed to open file");
        return (NULL);
	}
	result = get_next_line(fd, 1);
	while (result)
	{
		buffer = get_next_line(fd, 1);
		if (!buffer)
			break ;
		result = ft_strjoin(result, buffer);
		free(buffer);
	}
	close(fd);
	return (result);
}

/* Outputs the contents of a file to STDOUT,
	bassically like bash's cat command */
void mns_exec_util_file_to_output(const char *filename, int unlink_or_not)
{
	char *output;

	output = mns_exec_util_file_to_str(filename);
	if (output)
		ft_putstr_fd(output, STDOUT_FILENO);
	free(output);
	if (unlink_or_not == 1)
		unlink (filename);
}

int	mns_exec_util_restore_stdout(int save_stdout)
{
	if (dup2(save_stdout, STDOUT_FILENO) == MNS_ERROR)
	{
        perror("Failed to restore STDOUT file descriptor");
		return (MNS_ERROR);
    }
    close(save_stdout);
	return (ALL_FINE);
}

/* Saves STDOUT_FILENO to save_stdout veariable,
	opens a file, duplicates its FD to STDOUT_FILENO
	and returns save_stdout if all went smoothly
	or -1 (MNS_ERROR) in case of any error. */
int	mns_exec_util_dup(char *filename, int open_flag, int std_fileno)
{
	int	fd;
	int save_stdout;

	fd = open(filename, open_flag, 0777);
    if (fd == MNS_ERROR)
	{
		perror("Failed to open temporary file");
        return (MNS_ERROR);
	}
    save_stdout = dup(std_fileno);
    if (save_stdout == MNS_ERROR)
	{
        perror("Failed to save STDOUT file descriptor");
        close(fd);
        return (MNS_ERROR);
    }
    if (dup2(fd, std_fileno) == MNS_ERROR)
	{
        perror("Failed to redirect STDOUT to temporary file");
        close (fd);
		return (MNS_ERROR);
    }
    close(fd);
	return (save_stdout);
}

/* Checks if the called global exec is in the folders,
	saved in PATH env variable.
	If so - returns the exec with its full path (needs to be freed),
	if not - writes an error and returns NULL. */
char	*mns_exec_path(char **paths, char *cmd)
{
	int		i;
	char	*possible_path;
	char	*possible_exec;

	i = 0;
	while (paths[i])
	{
		possible_path = ft_strjoin(paths[i], "/");
		possible_exec = ft_strjoin(possible_path, cmd);
		free(possible_path);
		if (access(possible_exec, F_OK | X_OK) == 0)
			return (possible_exec);
		free(possible_exec);
		i++;
	}
	ft_putstr_fd("minishell: command not found: ", STDOUT_FILENO);
	ft_putendl_fd(cmd, STDOUT_FILENO);
	return (NULL);
}

/* Calls built-in functions */
void	mns_exec_builtin_call(t_data *data, char **envp, t_parsed parsed)
{
	if (parsed.type & COM_PWD)
		mns_com_pwd();
	else if (parsed.type & COM_EXIT)
		mns_com_exit(data, 0);
	else if (parsed.type & COM_CD)
		mns_com_cd(parsed.args[1]);
	else if (parsed.type & COM_ENV)
		mns_com_env(envp);
	else if (parsed.type & COM_ECHO)
		mns_com_echo(parsed.args);
}

char *mns_exec_simple_setup(t_data *data, char **envp, t_parsed parsed)
{
	char	*exec;
	int		save_stdout;

	exec = NULL;
	if (parsed.type & OUT_OPERATOR)
		save_stdout = mns_exec_util_dup(parsed.redir_out, O_CREAT | O_WRONLY | O_TRUNC, STDOUT_FILENO);
	if (parsed.type & BUILTIN_EXEC)
		mns_exec_builtin_call(data, envp, parsed);
	else if (parsed.type & GLOBAL_EXEC)
	{
		if (mns_init_paths(data) != MNS_ERROR)
			exec = mns_exec_path(data->paths, parsed.command);
	}
	else
		exec = ft_strdup(parsed.command);
	if (parsed.type & OUT_OPERATOR)
		save_stdout = mns_exec_util_restore_stdout(save_stdout);
	return (exec);
}

int	mns_execute_simple(t_parsed parsed, t_data *data, char **envp)
{
	char	*exec;
	pid_t	pid;

	exec = mns_exec_simple_setup(data, envp, parsed);
	if (exec)
	{
		pid = fork();
		if (pid == MNS_ERROR)
			printf ("Fork error");
		else if (pid == CHILD)
		{
			if (execve(exec, parsed.args, envp) == MNS_ERROR)
			{
				ft_putendl_fd("minishell: permission denied: ", STDOUT_FILENO);
				exit (MNS_ERROR);
			}
		}
		else
			wait(NULL);
	}
	free (exec);
	return (ALL_FINE);
}
