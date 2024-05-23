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

# Colors
DEF_COLOR	= \033[0;39m
GRAY		= \033[0;90m
RED		= \033[0;91m
GREEN		= \033[0;92m
BLUE		= \033[0;94m
MAGENTA		= \033[0;95m
CYAN		= \033[0;96m
WHITE		= \033[0;97m
ORANGE		= \033[38;5;220m
GREEN_BR	= \033[38;5;118m
BLUE_BR		= \033[38;5;219m
YELLOW_BR	= \033[38;5;227m
PINK_BR		= \033[38;5;206m
PINK_POKOJ	= \033[38;5;160m

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
	@printf "$(YELLOW_BR)*$(DEF_COLOR)"

all: $(NAME)
	@echo "$(GREEN_BR)\nLIBFT done!$(DEF_COLOR)"

$(NAME): libft.h $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@ranlib $(NAME)

clean:
	$(RM) $(OBJS) $(OBJS_DIR)
	@echo "$(CYAN)LIBFT objects cleaned!$(DEF_COLOR)"

fclean: clean
	$(RM) $(NAME)
	@echo "$(MAGENTA)AND THE LIBFT LIBRARY FILE!!!$(DEF_COLOR)"

re: clean all
	@echo "$(PINK_POKOJ)Dej pokoj!$(DEF_COLOR)"

.PHONY: all clean fclean re
