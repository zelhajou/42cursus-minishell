# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 20:09:25 by zelhajou          #+#    #+#              #
#    Updated: 2024/02/15 14:27:57 by zelhajou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = gcc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./includes -I./lib/libft


SRCDIR = ./src
OBJDIR = ./obj
LIBFTDIR = ./lib/libft
READLINEDIR = ./lib/readline

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/parser/parser.c \
	   $(SRCDIR)/parser/tokenizer.c \
	   $(SRCDIR)/parser/syntax_checker.c \


OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

LDFLAGS = -L$(LIBFTDIR) -lft -lreadline


LIBFT = $(LIBFTDIR)/libft.a

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	$(MAKE) -C $(LIBFTDIR)

clean:
	rm -rf $(OBJDIR)
	$(MAKE) -C $(LIBFTDIR) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFTDIR) fclean

re: fclean all

.PHONY: all clean fclean re