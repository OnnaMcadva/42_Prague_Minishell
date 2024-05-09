/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:45:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 13:58:03 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_plus/libft.h"
# include "./mns_incs_defs.h"
# include "./mns_structs.h"
# include "./mns_enums.h"

void	mns_sigint_handler(int sig);

int		mns_init_data(t_data *data);
int		mns_init_paths(t_data *data);

int		mns_parse(t_data *data);
int		mns_parse_util_count_args(const char **splitted, const int *splitted_type, int *count);
void	mns_parse_util_assign_args(t_parsed *parsed, const char **splitted, const int *splitted_type);

int		mns_check_line(const char *line);

int		mns_split(char ***splitted, int **splitted_type, const char *line);
int		mns_split_util_type(const char *line);

int		mns_execute(t_data *data, char **envp);
int		mns_execute_simple(t_parsed *parsed, t_data *data, char **envp);
int		mns_exec_pipe(t_data *data, char **envp, int count);
void	mns_exec_redir_set(t_parsed *parsed, int *save_fileno);
void    mns_exec_redir_restore(int *std_fileno);
void	mns_exec_util_file_to_output(const char *filename, int unlink_or_not);
int		mns_exec_util_dup(char *filename, int open_flag, int std_fileno);
int		mns_exec_util_restore_stdfileno(int saved_fileno, int std_fileno);
char	*mns_exec_util_file_to_str(const char *filename);

void    mns_com_pwd(void);
void	mns_com_cd(char *arg);
void    mns_com_env(char **envp);
void    mns_com_echo(char **args);

void	mns_free_data(t_data *data);

int		mns_util_in_quote(char *in_quote, char c);
int		mns_util_is_metachar(char c);

void	mns_com_exit(t_data *data, int code);

#endif
