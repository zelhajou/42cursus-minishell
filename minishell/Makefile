# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 20:09:25 by zelhajou          #+#    #+#              #
#    Updated: 2024/02/27 10:23:52 by beddinao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address
# Update these paths according to your Readline installation
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
INCLUDES = -I./includes -I./lib/libft -I./lib/get_next_line -I$(READLINE_INCLUDE)
SRCDIR = ./src
OBJDIR = ./obj
LIBFTDIR = ./lib/libft
READLINEDIR = ./lib/readline

SRCS = $(SRCDIR)/main.c \
       $(SRCDIR)/parser/parser.c \
       $(SRCDIR)/parser/tokenizer.c \
       $(SRCDIR)/parser/syntax_checker.c \
       $(SRCDIR)/utils/tokenizer_utils.c \
       $(SRCDIR)/utils/parser_utils.c \
       $(SRCDIR)/utils/env_managment.c \
       $(SRCDIR)/utils/expand.c \
       $(SRCDIR)/utils/termination.c \
       $(SRCDIR)/utils/executer_utils.c \
       $(SRCDIR)/utils/general.c \
       $(SRCDIR)/utils/executer_utils_2.c \
	   $(SRCDIR)/utils/executer_utils_3.c \
       $(SRCDIR)/utils/general_2.c \
       $(SRCDIR)/utils/specific_task.c \
	   $(SRCDIR)/utils/specific_task_2.c \
       $(SRCDIR)/exec/exec_builtins.c \
       $(SRCDIR)/exec/executer.c \
       $(SRCDIR)/exec/formation.c \
       $(SRCDIR)/exec/exec_one.c \
       $(SRCDIR)/exec/fds_managment.c \
       $(SRCDIR)/exec/formation_2.c \
       $(SRCDIR)/_init/_init.c \
       $(SRCDIR)/_init/exec_init.c \
	   $(SRCDIR)/builtins/builtins.c \
	   $(SRCDIR)/builtins/builtins_utils.c \
	   ./lib/get_next_line/get_next_line.c \
	   ./lib/get_next_line/get_next_line_utils.c \
	   
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LDFLAGS = -L$(LIBFTDIR) -lft -L$(READLINE_LIB) -lreadline
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
