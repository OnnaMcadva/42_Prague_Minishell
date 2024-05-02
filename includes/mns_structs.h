/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_structs.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:12:54 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 14:18:21 by mmakagon         ###   ########.fr       */
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
	int		type;

}				t_parsed;

typedef struct s_data
{
	char		**paths;
	char		*line;
	char		**splitted;
	int			*splitted_type;
	t_parsed	*parsed;
	int			tkn_count;
	int			pipes_count;
}				t_data;

#endif
