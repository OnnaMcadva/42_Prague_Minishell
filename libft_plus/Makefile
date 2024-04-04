# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmakagon <mmakagon@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/18 12:43:00 by mmakagon          #+#    #+#              #
#    Updated: 2024/04/04 13:00:20 by mmakagon         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft_plus.a
CC = @clang
CFLAGS = -Wall -Wextra -Werror
AR = @ar rc
RM = @rm -rf

FILES = ft_printf \
		print_hex \
		print_integer \
		print_pointer \
		print_string \
		print_unsigned \
		ft_atoi \
		ft_isalnum \
		ft_isalpha \
		ft_isascii \
		ft_isdigit \
		ft_isprint \
		ft_tolower \
		ft_toupper \
		ft_memcmp \
		ft_strncmp \
		ft_strcmp \
		ft_bzero \
		ft_putnbr_fd \
		ft_putstr_fd \
		ft_putchar_fd \
		ft_putendl_fd \
		ft_calloc \
		ft_memchr \
		ft_memcpy \
		ft_memmove \
		ft_memset \
		ft_striteri \
		ft_itoa \
		ft_split \
		ft_strchr \
		ft_strdup \
		ft_strjoin \
		ft_strmapi \
		ft_strnstr \
		ft_strrchr \
		ft_strtrim \
		ft_substr \
		ft_strlcat \
		ft_strcat \
		ft_strlcpy \
		ft_strcpy \
		ft_strlen \
		ft_lstadd_back \
		ft_lstadd_front \
		ft_lstclear \
		ft_lstdelone \
		ft_lstiter \
		ft_lstlast \
		ft_lstmap \
		ft_lstnew \
		ft_lstsize \
		ft_get_next_line \

SRCS_DIR = ./
SRCS = $(addprefix $(SRCS_DIR), $(addsuffix .c, $(FILES)))

OBJS_DIR = ./obj/
OBJS = $(addprefix $(OBJS_DIR), $(addsuffix .o, $(FILES)))

$(OBJS_DIR)%.o: $(SRCS_DIR)%.c
	@mkdir -p obj
	$(CC) -c $(CFLAGS) -o $@ $<
	@printf "*"

all: $(NAME)
	@echo "\nLIBFT done!"

$(NAME): libft.h $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_DIR)
	@echo "LIBFT objects cleaned!"

fclean: clean
	$(RM) $(NAME)
	@echo "AND THE LIBFT LIBRARY FILE!!!"

re: clean all
	@echo "Dej pokoj!"

.PHONY: all clean fclean re
