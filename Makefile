NAME    = libasm.a

SRCS    = ft_strlen.s ft_strcpy.s ft_strcmp.s ft_write.s ft_read.s ft_strdup.s
OBJS    = $(SRCS:.s=.o)

BONUS_SRC   = ft_atoi_base_bonus.s ft_list_push_front_bonus.s ft_list_size_bonus.s ft_list_remove_if_bonus.s ft_list_sort_bonus.s
BONUS_OBJ   = $(BONUS_SRC:.s=.o)

NASM    = nasm
NASMFLAGS = -f elf64

CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

TEST    = main
TESTSRC = main.c
TESTBIN = test
TESTFLAGS = -no-pie

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

bonus: $(OBJS) $(BONUS_OBJ)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJ)

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

test: all $(TESTSRC)
	$(CC) $(CFLAGS) $(TESTSRC) $(NAME) -o $(TESTBIN) $(TESTFLAGS)

test_bonus: bonus
	$(CC) $(CFLAGS) main_bonus.c $(NAME) -o test_bonus $(TESTFLAGS)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME) $(TESTBIN) test_bonus

re: fclean all

.PHONY: all clean fclean re test test_bonus bonus
