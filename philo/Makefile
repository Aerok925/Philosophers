NAME = philo

SRCS = source/action.c source/philo.c source/chekers.c source/create_list.c source/free_list.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

INCLUDES = philo.h

OBJS = ${SRCS:.c=.o}

.PHONY: all fclean clean re

.c.o: $(INCLUDES)
	$(CC) -Wall -Wextra -Werror -I$(INCLUDES) -c $< -o $@

$(NAME): $(SRCS) $(OBJS) $(INCLUDES)
	$(CC) $(FLAGC) $(OBJS) -I$(INCLUDES) -o $(NAME)

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all

