# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ehelmine <ehelmine@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/17 12:59:07 by ehelmine          #+#    #+#              #
#    Updated: 2021/09/30 14:26:58 by ehelmine         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS = main.c read_input.c lexer.c built_in.c echo_functions.c \
	help_functions.c check_if_something_functions.c setenv_functions.c \
	unsetenv_functions.c cd_start.c check_quotes.c \
	cd_input_check.c cd_finish.c check_input.c fork.c free_or_null.c \
	cd_dir_name.c echo_output.c echo_start.c setenv_help.c \
	cd_flags_errors.c change_directory.c check_dir_rights.c \
	error_message_for_exec.c

OBJS_DIR = objs

OBJS = $(addprefix $(OBJS_DIR)/, main.o read_input.o lexer.o built_in.o \
	echo_functions.o help_functions.o check_if_something_functions.o \
	setenv_functions.o unsetenv_functions.o cd_start.o check_quotes.o \
	cd_input_check.o cd_finish.o check_input.o fork.o free_or_null.o \
	cd_dir_name.o echo_output.o echo_start.o setenv_help.o cd_flags_errors.o \
	change_directory.o check_dir_rights.o error_message_for_exec.o)

LIBFT_OBJS = $(addprefix libft/, ft_putchar.o ft_putstr.o ft_atoi.o \
	ft_strlen.o ft_strcmp.o ft_putnbr.o ft_strdup.o ft_strcpy.o ft_strncpy.o \
	ft_strclr.o ft_strcat.o ft_strncmp.o ft_putendl.o ft_strlcat.o ft_bzero.o \
	ft_strncat.o ft_strchr.o ft_strrchr.o ft_isalpha.o ft_isdigit.o \
	ft_isascii.o ft_isprint.o ft_strstr.o ft_strnstr.o ft_tolower.o \
	ft_toupper.o ft_isalnum.o ft_memset.o ft_memcpy.o ft_memccpy.o \
	ft_memchr.o ft_memcmp.o ft_memmove.o ft_strequ.o ft_strnequ.o \
	ft_memalloc.o ft_memdel.o ft_strnew.o ft_strdel.o ft_strtrim.o \
	ft_strjoin.o ft_striter.o ft_striteri.o ft_strsplit.o ft_strsub.o \
	ft_strmap.o ft_strmapi.o ft_itoa.o ft_putchar_fd.o ft_putstr_fd.o \
	ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o ft_lstadd.o ft_lstdelone.o \
	ft_lstdel.o ft_lstiter.o ft_lstmap.o ft_check_int_len.o ft_islower.o \
	ft_isupper.o ft_isspace.o ft_strndup.o get_next_line.o major_bit.o \
	minor_bit.o free_two.o ft_putarr.o ft_arrdup.o ft_arrnew.o \
	ft_strstr_after.o ft_strjoin_three.o free_arr.o ft_return_char_index.o)

INCLUDES = includes/minishell.h

CFLAGS = -g -Wall -Wextra -Werror 

all: $(NAME)

$(NAME): $(OBJS_DIR) $(OBJS)
	make -C libft/
	@echo "Sources to objects done"
	gcc $(CFLAGS) -o $@ $(OBJS) -I $(INCLUDES) libft/libft.a
	@echo "Compiling minishell done"

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