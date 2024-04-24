# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 16:39:10 by tabadawi          #+#    #+#              #
#    Updated: 2024/04/24 13:22:40 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SRCS = pipex.c duping.c utils.c error_handling.c

CC = cc

CFLAGS = -Wall -Werror -Wextra -fsanitize=address -g3

OBJ = $(SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT):
	@$(MAKE)	-C libft

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(LIBFT) $(OBJ) -o $(NAME)

clean :
	@rm -rf $(OBJ)
	@$(MAKE)	-C libft clean

fclean : clean
	@rm -rf $(NAME)
	@rm -rf $(LIBFT)

re : fclean all