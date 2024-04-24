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
	DOLLAR_SIGN = '$',
	PIPE_LINE = '|',
	REDIR_IN = '<',
	REDIR_OUT = '>',
};

enum e_tkn_type
{
	NULL_TOKEN = 0,
	WORD,
	ENV,
	PIPE,
	IN_OPERATOR,
	HERE_DOC,
	OUT_OPERATOR,
	OUT_APPEND_OPRTR,
	GLOBAL_EXEC,
	LOCAL_EXEC,
	COM_CD,
	COM_ECHO,
	COM_ENV,
	COM_EXIT,
	COM_EXPORT,
	COM_PWD,
	COM_UNSET,
};

enum e_state
{
	MNS_ERROR = -1,
	CHILD = 0,
	ALL_FINE,
};

#endif
