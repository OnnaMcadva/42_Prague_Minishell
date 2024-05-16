/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:30:40 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/16 14:44:22 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_STRUCTS_H
# define MNS_STRUCTS_H

typedef struct s_parsed
{
	char	*command;
	char	**args;
	char	*redir_in;
	char	*redir_out;
	int		fd[2];
	int		type;

}				t_parsed;

typedef struct s_data
{
	char		**env_copy;
	char		**paths;
	char		*line;
	char		**splitted;
	int			*splitted_type;
	t_parsed	*parsed;
	int			tkn_count;
	int			pipes_count;
	int			exit_status;
}				t_data;

#endif
