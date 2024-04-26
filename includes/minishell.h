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

int		mns_init(t_data *data);

int		mns_parse(t_data *data);

int		mns_check_line(const char *line);

int		mns_split(char ***splitted,
			int **splitted_type, const char *line);
int		mns_split_util_type(const char *line);

int		mns_execute(t_data *data, char **envp);
int		mns_execute_simple(t_parsed parsed, char **paths, char **envp);
int		mns_execute_complex(t_data *data, char **envp);

void	mns_free_data(t_data *data);

int		mns_util_in_quote(char *in_quote, char c);
int		mns_util_is_metachar(char c);

void	mns_com_exit(t_data *data, int code);

#endif
