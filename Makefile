# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/08/04 16:59:13 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main.c read_input.c lexer.c

OBJS = main.o read_input.o lexer.o

CFLAGS = -g -Wall -Wextra -Werror

all: $(NAME)

$(NAME):
	make -C libft/
	@gcc $(CFLAGS) -c $(SRCS) -I includes
	@echo "Sources to objects done"
	gcc $(CFLAGS) -o 21sh $(OBJS) libft/libft.a
	@echo "Compiling 21sh done"

clean:
	make clean -C libft/
	@echo "Removing .o files"
	@rm -f $(OBJS)

fclean: clean
	make -C libft/ fclean
	@echo "Removing .a files"
	@rm -f $(NAME)

re: fclean all