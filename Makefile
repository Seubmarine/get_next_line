NAME = get_next_file

SRCS = get_next_line.c  get_next_line_utils.c

OBJS = get_next_line.o  get_next_line_utils.o

CFLAGS = -Wall -Werror -Wextra

all: $(NAME)

$(NAME):	$(OBJS)
	$(CC) $(CFLAGS) $(OBJS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all re clean fclean