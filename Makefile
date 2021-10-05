NAME = push_swap

CC = gcc

CFLAGS = -Wall -Wextra -Werror

SRC = main.c swap.c push.c rotate.c reverse.c sort_below_five.c buffer.c algo_100.c

OBJS = $(SRC:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean :
			@rm -f $(OBJS)

fclean :	clean
			@rm -f $(NAME)

re: fclean all

.PHONY : all clean fclean re .o