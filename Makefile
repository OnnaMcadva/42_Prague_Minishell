# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maxmakagonov <maxmakagonov@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 10:26:38 by mmakagon          #+#    #+#              #
#    Updated: 2024/05/23 10:13:57 by maxmakagono      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
UNAME = $(shell uname -s)
CC = @clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFT_DIR = ./libft_plus
LIBFT_LIB = $(LIBFT_DIR)/libft_plus.a
RM = @rm -rf

ifeq ($(UNAME),Darwin)
LIBFLAGS = -L/usr/local/opt/readline/lib -lreadline -L./libft_plus -lft_plus
INCFLAGS = -I/usr/local/opt/readline/include
CFLAGS += -DMACOS
else
LIBFLAGS = -lreadline -L./libft_plus -lft_plus
endif

FILES = minishell \
		checks/mns_checks \
		commands/mns_com_cd \
		commands/mns_com_echo \
		commands/mns_com_env \
		commands/mns_com_exit \
		commands/mns_com_export_utils \
		commands/mns_com_export \
		commands/mns_com_pwd \
		commands/mns_com_unset \
		env/mns_env \
		execute/mns_exec_pipe \
		execute/mns_exec_redirections \
		execute/mns_exec_utils \
		execute/mns_execute \
		free/mns_free \
		init/mns_init \
		init/mns_init_env \
		parse/mns_parse_utils \
		parse/mns_parse \
		signal/mns_signal \
		split/mns_split_utils \
		split/mns_split \
		utils/mns_utils \


SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS_SUBDIRS = obj/checks obj/commands obj/execute obj/free obj/init obj/parse obj/signal obj/split obj/utils obj/env
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p $(OBJS_DIR) $(OBJS_SUBDIRS)
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

all: $(NAME)

$(NAME): $(LIBFT_LIB) $(OBJS) ./includes/minishell.h
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFLAGS)
	@echo "minishell compiled"

$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(NAME) $(OBJS_DIR) env_with* export.txt
	@echo "ALL minishell binaries cleaned!"
	@make fclean -C $(LIBFT_DIR)

re: clean all

fre: fclean all

.PHONY: all clean fclean re fre
