/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_enums.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:12:55 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 13:55:40 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_ENUMS_H
# define MNS_ENUMS_H

enum e_delimiter
{
	WHITESPACE = ' ',
	TAB_SYMBOL = '\t',
	NEW_LINE = '\n',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	ESCAPE = '\\',
	SLASH = '/',
	DOLLAR_SIGN = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
};

#endif
