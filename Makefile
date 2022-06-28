# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jshin <jshin@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/06/29 01:14:40 by jshin             #+#    #+#              #
#    Updated: 2022/06/29 05:50:29 by jshin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
BONUS = bonus
CC = gcc
FLAGS = -Wall -Wextra -Werror
SRC = ./srcs/pipex.c ./srcs/utils.c ./libft/ft_split.c ./libft/ft_putstr_fd.c \
	  ./libft/ft_strjoin.c ./libft/ft_strlcpy.c ./libft/ft_strnstr.c \
	  ./libft/ft_putchar_fd.c ./libft/ft_strlen.c

OBJ = $(SRC:.c = .o)

AR = ar
ARFLAG = -rcs

all : $(NAME)

$(NAME) : $(OBJ)
	$(AR) $(ARFLAG) $@ $^

%.o : %.c
	$(CC) $(CFLAG) -c $<

clean :
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY : all clean fclean re