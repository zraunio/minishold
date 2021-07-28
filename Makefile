# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/07/28 14:16:32 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh

SRCS = main.c

OBJS = main.o

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