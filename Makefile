# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rshor <rshor@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/05 17:53:13 by rshor             #+#    #+#              #
#    Updated: 2022/03/05 17:53:17 by rshor            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				= 	pipex

HEADER				=	pipex.h

SRCS				=	pipex.c	parser.c	childs_process.c	free.c\
						file_operations.c	ft_exec.c\
						libft_utils.c	ft_split.c\

OBJ 				= 	$(SRCS:%.c=%.o)

CC 					= 	cc 
CFLAGS 				= 	-Wall -Wextra -Werror

RM 					= 	rm -rf

all					:	$(NAME) 

$(NAME)				:	$(OBJ)

%.o					: %.c $(HEADER)
	$(CC) $(CFLAGS)  -c  $<  -o $@ 

.PHONY				:	all clean fclean re bonus

clean:
	$(RM) $(OBJ) 

fclean				: clean
	$(RM) $(NAME)

re					: fclean all