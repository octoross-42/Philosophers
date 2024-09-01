NAME = philo

SRCS = src/philo.c \
		src/parsing/parsing.c \
		src/utils/utils.c \
		src/utils/time.c \
		src/philo/actions.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) -pthread -Iinclude/ -c $< -o ${<:.c=.o}	

$(NAME): ${OBJS}
	$(CC) $(OBJS) -o $(NAME)

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all