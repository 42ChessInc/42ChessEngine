NAME= autoMate

UNIT = unit_test

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -g

SRCS_DIR = srcs
OBJS_DIR = objs

MAIN = srcs/main.c
TESTER = srcs/tester_board.c
SRC = ft_strtok.c helpers.c errors.c parser.c
OBJ = $(SRC:.c=.o)

OBJ_PATH = $(patsubst %,$(OBJS_DIR)/%,$(OBJ))

all: $(NAME)

$(NAME): $(OBJ_PATH)
	$(CC) $(CFLAGS) $(MAIN) $^ -o $(NAME)
	@echo "Compiled program."

$(UNIT): $(OBJ_PATH)
	$(CC) $(CFLAGS) $(TESTER) $^ -o $@
	@echo "Compiled tester."

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir -p $@

clean:
	@rm -f $(OBJ_PATH)
	@echo "Cleaned objects..."

fclean: clean
	@rm -f $(UNIT)
	@rm -f $(NAME)
	@echo "Finished full clean."

re: fclean all
