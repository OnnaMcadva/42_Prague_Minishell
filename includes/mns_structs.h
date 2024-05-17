/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 22:30:40 by maxmakagono       #+#    #+#             */
/*   Updated: 2024/05/16 17:13:26 by maxmakagono      ###   ########.fr       */
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
