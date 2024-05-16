/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 13:45:09 by mmakagon          #+#    #+#             */
/*   Updated: 2024/05/16 09:11:04 by maxmakagono      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft_plus/libft.h"
# include "./mns_incs_defs.h"
# include "./mns_structs.h"
# include "./mns_enums.h"

void	mns_sigint_handler(int sig);

int		mns_init_env_copy(char **envp, t_data *data);
int		mns_init_data(t_data *data);
int		mns_init_paths(t_data *data);
int		mns_init_pipes(t_data *data);

int		mns_parse(t_data *data);
int		mns_parse_util_count_args(char **splitted,
			int *splitted_type,
			int *count);
void	mns_parse_util_assign_args(t_parsed *parsed,
			char **splitted,
			int *splitted_type);

int		mns_check_quotes(char *line);
int		mns_check_redirs(int *spltd_type, int tkn_count);

int		mns_split(char ***splitted, int **splitted_type, char *line);
int		mns_split_util_type(char *line);

int		mns_env_add(t_data *data, char *to_add);
int		mns_env_delete(t_data *data, char *to_delete);
int		mns_env_change(t_data *data, char *key, char *value);
char	**mns_env_find(char **envp, char *key);
char	*mns_getenv(char **envp, char *key);
int		mns_env_util_malloc_check(char **tab, int i);

int		mns_execute(t_data *data);
int		mns_exec_process(t_parsed *parsed, t_data *data);
int		mns_exec_pipe(t_data *data, int count);
void	mns_exec_redir_set(t_parsed *parsed, int *save_fileno);
void	mns_exec_redir_restore(int *std_fileno);
void	mns_exec_util_file_to_output( char *filename, int unlink_or_not);
int		mns_exec_util_pipe_dup(t_parsed *parsed, int std_fileno);
int		mns_exec_util_file_dup(char *filename, int open_flag, int std_fileno);
int		mns_exec_util_restore_stdfileno(int saved_fileno, int std_fileno);
char	*mns_exec_util_file_to_str(char *filename);

int		mns_com_pwd(void);
int		mns_com_cd(char **envp, char *arg);
int		mns_com_env(char **envp);
int		mns_com_echo(char **args);
void	mns_com_exit(t_data *data, char *str_code);

void	mns_free_data(t_data *data);
void	mns_free_tab(char **tab);

int		mns_util_in_quote(char *in_quote, char c);
int		mns_util_is_space(const char c);
int		mns_util_tablen(char **tab);
void	mns_util_free_tab(char **tab);

#endif
