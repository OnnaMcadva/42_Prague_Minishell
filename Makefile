# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 10:26:38 by mmakagon          #+#    #+#              #
#    Updated: 2024/04/17 14:55:43 by mmakagon         ###   ########.fr        #
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
else
LIBFLAGS = -lreadline -L./libft_plus -lft_plus
endif

FILES = minishell \
		mns_checks \
		mns_com_cd \
		mns_com_echo \
		mns_com_env \
		mns_com_exit \
		mns_com_export \
		mns_com_pwd \
		mns_com_unset \
		mns_execute_simple \
		mns_free \
		mns_init \
		mns_parse \
		mns_signal \
		mns_split \
		mns_utils \


SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $< $(INCFLAGS)

all: $(NAME)

$(NAME): ./includes/minishell.h $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFLAGS)
	@echo "minishell compiled"

$(LIBFT_LIB):
	@make -s -C $(LIBFT_DIR)

clean:
	$(RM) $(NAME)

fclean:
	$(RM) $(OBJS) $(NAME) $(OBJS_DIR)
	@make fclean -C $(LIBFT_DIR)

re: clean all

fre: fclean all

.PHONY: all clean fclean re fre
