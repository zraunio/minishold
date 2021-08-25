# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/08/24 17:41:49 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main.c read_input.c lexer.c built_in.c echo_functions.c \
	help_functions.c check_if_something_functions.c setenv_functions.c \
	unsetenv_functions.c

OBJS_DIR = objs

OBJS = $(OBJS_DIR)/main.o $(OBJS_DIR)/read_input.o $(OBJS_DIR)/lexer.o \
	$(OBJS_DIR)/built_in.o $(OBJS_DIR)/echo_functions.o \
	$(OBJS_DIR)/help_functions.o $(OBJS_DIR)/check_if_something_functions.o \
	$(OBJS_DIR)/setenv_functions.o $(OBJS_DIR)/unsetenv_functions.o
	

INCLUDES = includes/minishell.h

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	make -C libft/
	@echo "Sources to objects done"
	gcc $(CFLAGS) -o $@ $(OBJS) -I $(INCLUDES) libft/libft.a
	@echo "Compiling 21sh done"

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