# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/04 10:26:38 by mmakagon          #+#    #+#              #
#    Updated: 2024/04/04 13:53:43 by mmakagon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = @clang
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
LIBFLAGS = -lreadline -L./libft_plus -lft_plus
LIBFT_DIR = ./libft_plus
LIBFT_LIB = $(LIBFT_DIR)/libft_plus.a
RM = @rm -rf


FILES = minishell \
		mns_execute \
		mns_free \
		mns_init \
		mns_parse \
		mns_utils \


SRCS_DIR = ./src/
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p obj
	$(CC) $(CFLAGS) -c -o $@ $<

all: $(NAME)

$(NAME): $(SRCS_DIR)minishell.h $(LIBFT_LIB) $(OBJS)
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
