# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zelhajou <zelhajou@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/10 20:09:25 by zelhajou          #+#    #+#              #
#    Updated: 2024/03/08 22:41:53 by beddinao         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address
READLINE_INCLUDE = $(shell brew --prefix readline)/include
READLINE_LIB = $(shell brew --prefix readline)/lib
INCLUDES = -I./includes -I./lib/libft -I./lib/get_next_line -I$(READLINE_INCLUDE)
SRCDIR = ./src
OBJDIR = ./obj
LIBFTDIR = ./lib/libft
LIBGNTLDIR = ./lib/get_next_line
READLINEDIR = ./lib/readline

SRCS = $(SRCDIR)/main.c \
	$(SRCDIR)/01_input_validation/syntax_checker.c \
	$(SRCDIR)/01_input_validation/syntax_checker_utils.c \
	$(SRCDIR)/02_tokenization/tokenizer.c \
	$(SRCDIR)/02_tokenization/tokenizer_utils.c \
	$(SRCDIR)/02_tokenization/print_tokens.c \
	$(SRCDIR)/03_parsing/parser.c \
	$(SRCDIR)/03_parsing/parser_utils.c \
	$(SRCDIR)/04_execution/initialization/command_execution_init.c \
	$(SRCDIR)/04_execution/initialization/environment_init.c \
	$(SRCDIR)/04_execution/builtin_command_execution.c \
	$(SRCDIR)/04_execution/builtin_command_execution2.c \
	$(SRCDIR)/04_execution/command_execution_adv.c \
	$(SRCDIR)/04_execution/executor.c \
	$(SRCDIR)/04_execution/path_utilities.c \
	$(SRCDIR)/04_execution/path_utilities2.c \
	$(SRCDIR)/04_execution/process_pipeline_management.c \
	$(SRCDIR)/04_execution/command_execution_control.c \
	$(SRCDIR)/04_execution/command_input_preprocessing.c \
	$(SRCDIR)/04_execution/heredoc_handling.c \
	$(SRCDIR)/05_builtin/builtin_commands.c \
	$(SRCDIR)/05_builtin/builtin_commands_utils.c \
	$(SRCDIR)/05_builtin/builtin_commands_utils2.c \
	$(SRCDIR)/05_builtin/builtin_commands_utils3.c \
	$(SRCDIR)/06_signals/signal_handlers.c \
	$(SRCDIR)/07_env_var_expansion/env_handling.c \
	$(SRCDIR)/07_env_var_expansion/env_managment.c \
	$(SRCDIR)/07_env_var_expansion/env_managment2.c \
	$(SRCDIR)/07_env_var_expansion/variable_expansion.c \
	$(SRCDIR)/07_env_var_expansion/variable_expansion_utils.c \
	$(SRCDIR)/utils/string_utilities/string_utils.c \
	$(SRCDIR)/utils/string_utilities/string_utils2.c \
	$(SRCDIR)/utils/shell_utilities.c \

OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
LDFLAGS = -L$(LIBFTDIR) -lft -L$(READLINE_LIB) -lreadline
LIBFT = $(LIBFTDIR)/libft.a

# setup:
# 	@stty -ctlecho

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(OBJDIR)/%.o: $(SRCDIR)/%.c ./includes/minishell.h
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
