NAME = philo

SRCS = src/main.c \
		src/parsing/parsing.c \
		src/parsing/init.c \
		src/utils/utils.c \
		src/utils/time.c \
		src/routine/actions.c \
		src/routine/routine.c

OBJS = ${SRCS:.c=.o}

CC = cc
CFLAGS = -Wall -Wextra -Werror

%.o: %.c
	$(CC) $(CFLAGS) -pthread -Iinclude/ -c $< -o ${<:.c=.o}	

$(NAME): ${OBJS}
	$(CC) $(OBJS) -o $(NAME)

all : ${NAME}

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}

re: fclean all