# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tabadawi <tabadawi@student.42abudhabi.a    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/19 16:39:10 by tabadawi          #+#    #+#              #
#    Updated: 2024/04/29 21:22:48 by tabadawi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex

LIBFT = ./libft/libft.a

SRCS = pipex.c duping.c utils.c error_handling.c heredoc.c 

BONUS_SRCS = pipex_bonus.c heredoc.c duping.c utils.c error_handling.c

CC = cc

CFLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3

OBJ = $(SRCS:.c=.o)

BONUS_OBJS = $(BONUS_SRCS:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT):
	@$(MAKE)	-C libft

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

bonus : $(LIBFT) $(BONUS_OBJS)
	@$(CC) $(CFLAGS) $(BONUS_OBJS) $(LIBFT) -o $(NAME)

clean :
	@rm -rf $(OBJ)
	@rm -rf $(BONUS_OBJS)
	@$(MAKE)	-C libft clean

fclean : clean
	@rm -rf $(NAME)
	@$(MAKE)	-C libft fclean

re : fclean all

.PHONY	:	all bonus re clean fclean