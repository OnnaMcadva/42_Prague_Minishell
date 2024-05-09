/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mns_incs_defs.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:53:16 by mmakagon          #+#    #+#             */
/*   Updated: 2024/04/24 13:55:50 by mmakagon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MNS_INCS_DEFS_H
# define MNS_INCS_DEFS_H

// # include <stdlib.h>
// # include <string.h>
// # include <sys/types.h>
// # include <unistd.h>
// # include <termios.h>
// # include <term.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <sys/ioctl.h>
# include <sys/param.h>

# define PROMPT "\x1B[36m[minishell] \x1B[35m[ =) ] \x1B[36m~> \x1B[0m"
// the lenght is 42 =)

# define MNS_ERROR          -1
# define CHILD              0
# define ALL_FINE           42

# define NULL_TOKEN         0x0
# define GLOBAL_EXEC        0x00001
# define LOCAL_EXEC         0x00002
# define BUILTIN_EXEC       0x00004
# define IN_OPERATOR        0x00008
# define HERE_DOC           0x00010
# define OUT_OPERATOR       0x00020
# define OUT_APPEND_OPRTR   0x00040
# define COM_CD             0x00080
# define COM_ECHO           0x00100
# define COM_ENV            0x00200
# define COM_EXIT           0x00400
# define COM_EXPORT         0x00800
# define COM_PWD            0x01000
# define COM_UNSET          0x02000
# define WORD               0x04000
# define PIPE               0x08000
# define ENV                0x10000

# define META_CHARACTERS "|&;()<>"

# ifdef MACOS
#  include </usr/local/Homebrew/Cellar/readline/8.2.10/include/readline/readline.h>
# endif

#endif
