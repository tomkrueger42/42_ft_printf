# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tkruger <tkruger@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/07/19 10:42:27 by tkruger           #+#    #+#              #
#    Updated: 2022/01/06 00:50:34 by tkruger          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
FLAGS = -Wall -Wextra -Werror -c
SRC = ./src/ft_printf.c ./src/ft_printf_2.c ./src/ft_printf_3.c

$(NAME):
	@gcc $(FLAGS) $(SRC)
	@ar -crs $(NAME) ft_*.o

all: $(NAME)

clean:
	@rm -rf *.o *~

fclean: clean
	@rm -rf $(NAME)

re: fclean all