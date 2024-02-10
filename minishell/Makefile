# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 20:09:25 by zelhajou          #+#    #+#              #
#    Updated: 2024/02/10 21:46:59 by zelhajou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I includes -I lib/libft
LDFLAGS = -L lib/libft -lft -lreadline

LIBFT_DIR = lib/libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJS = obj/main.o \


all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

obj/%.o: src/%.c includes/minishell.h
	@mkdir -p obj
	@mkdir -p obj/builtins
	@mkdir -p obj/utils
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
# Clean workspace
clean:
	rm -rf obj
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild
re: fclean all

.PHONY: all clean fclean re
