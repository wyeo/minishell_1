# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wyeo <marvin@42.fr>                        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/05/18 09:56:40 by wyeo              #+#    #+#              #
#    Updated: 2015/05/18 11:27:34 by wyeo             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Delete the implicites rules

.SUFFIXES:

NAME = ft_minishell1

CC = gcc

CFLAGS = -Wall -Wextra -Werror

CFILES = ./Src/ft_builtins.c ./Src/ft_cd.c ./Src/ft_cmd.c ./Src/ft_env.c \
		 ./Src/ft_exe.c ./Src/ft_liste.c ./Src/ft_main.c ./Src/get_next_line.c

OFILES = ./ft_builtins.o ./ft_cd.o ./ft_cmd.o ./ft_env.o \
		 ./ft_exe.o ./ft_liste.o ./ft_main.o ./get_next_line.o

LIBFT = -L./Libft -lft -lncurses

.PHONY: all
all: $(NAME)

$(NAME):
	@make -C ./Libft/
	@$(CC) $(CFLAGS) -c $(CFILES)
	@$(CC) $(CFLAGS) -o $(NAME) $(OFILES) $(LIBFT)

.PHONY: clean
clean:
	@rm -rf $(OFILES)

.PHONY: fclean
fclean: clean
	@rm -rf $(NAME)

.PHONY: re
re: fclean all
