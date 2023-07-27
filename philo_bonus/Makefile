# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jareste- <jareste-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/11 02:37:54 by jareste-          #+#    #+#              #
#    Updated: 2023/07/27 08:28:48 by jareste-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC_PATH = ./SRC
INC_PATH = INC

SRCS = $(addprefix $(SRC_PATH)/, philo.c \
	    utils.c \
		threads.c \
		init.c \
		eat_print.c)

CC = cc -g -fsanitize=address
RM = rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c INC/philo.h Makefile
		@${CC} ${CFLAGS} -c $< -o $@	

OBJS = ${SRCS:.c=.o}

all: 
		@$(MAKE) ${NAME} --no-print-directory

${NAME}:: ${OBJS} 
	@${CC} $(CFLAGS) $(OBJS) -o ${NAME}
	@echo "EVERYTHING DONE✌️   "

clean:
			@${RM} ${OBJS} --no-print-directory
			@echo "OBJECTS REMOVED😭   "

fclean: clean 
			@${RM} ${OBJS} ${NAME} --no-print-directory
			@echo "EVERYTHING REMOVED😭 "

re: 
			@$(MAKE) fclean --no-print-directory
			@$(MAKE) all --no-print-directory

.PHONY: all clean fclean re
