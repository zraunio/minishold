# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/08/10 16:07:15 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main.c read_input.c lexer.c built_in.c

OBJS_DIR = objs

OBJS = $(OBJS_DIR)/main.o $(OBJS_DIR)/read_input.o $(OBJS_DIR)/lexer.o $(OBJS_DIR)/built_in.o

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