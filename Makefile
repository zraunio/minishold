# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zraunio <zraunio@student.hive.fi>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/09/01 15:46:31 by zraunio          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main.c read_input.c lexer.c built_in.c echo_functions.c \
	help_functions.c check_if_something_functions.c setenv_functions.c \
	unsetenv_functions.c check_quotes.c cd_start.c \
	cd_input_check.c

OBJS_DIR = objs

OBJS = $(OBJS_DIR)/main.o $(OBJS_DIR)/read_input.o $(OBJS_DIR)/lexer.o \
	$(OBJS_DIR)/built_in.o $(OBJS_DIR)/echo_functions.o \
	$(OBJS_DIR)/help_functions.o $(OBJS_DIR)/check_if_something_functions.o \
	$(OBJS_DIR)/setenv_functions.o $(OBJS_DIR)/unsetenv_functions.o \
	$(OBJS_DIR)/check_quotes.o $(OBJS_DIR)/cd_start.o \
	$(OBJS_DIR)/cd_input_check.o
	

INCLUDES = includes/minishell.h

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	make -C libft/
	@echo "\\n\033[32;1mOBJECT FILES CREATED\033[0m \\n""
	gcc $(CFLAGS) -o $@ $(OBJS) -I $(INCLUDES) libft/libft.a
	@echo "\\n\033[32;1mCOMPILED SHELL\033[0m \\n"

$(OBJS_DIR)/%.o: %.c
	gcc $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	mkdir objs

clean:
	make clean -C libft/
	@echo "Removing .o files"
	@rm -Rf $(OBJS_DIR)

fclean: clean
	make -C libft/ fclean
	@echo "Removing .a files"
	@rm -f $(NAME)

re: fclean all
