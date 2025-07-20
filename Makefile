
test: all

NAME = libasm.a
BONUS_NAME = libasm_bonus.a
SRC = src/*.s
BONUS_SRC = src/bonus/*.s
WRAPPERS = wrappers/*.c
WRAPPERS_BONUS = wrappers/wrappers_bonus/*.c
INCLUDE = -Iinclude
OBJ_DIR = obj
OBJS = $(patsubst src/%.s,$(OBJ_DIR)/%.o,$(wildcard src/*.s))
BONUS_OBJS = $(patsubst src/bonus/%.s,$(OBJ_DIR)/%.o,$(wildcard src/bonus/*.s))

NASM = nasm
NASMFLAGS = -f elf64
CC = gcc
CFLAGS = -Wall -Wextra -Werror $(INCLUDE)

all: $(NAME)

bonus: $(BONUS_NAME) $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

$(BONUS_NAME): $(BONUS_OBJS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: src/%.s | $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR)/%.o: src/bonus/%.s | $(OBJ_DIR)
	$(NASM) $(NASMFLAGS) $< -o $@

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

test: all
	$(CC) $(CFLAGS) tester/main.c $(WRAPPERS) $(NAME) -L. -lasm -o test

test_bonus: bonus
	$(CC) $(CFLAGS) tester/main_bonus.c $(WRAPPERS_BONUS) -L. -lasm_bonus -lasm -o test_bonus

clean:
	rm -f $(OBJ_DIR)/*.o

fclean: clean
	rm -f $(NAME) $(BONUS_NAME) test test_bonus
	rm -rf $(OBJ_DIR)

re: fclean all

.PHONY: all bonus clean fclean re test test_bonus

