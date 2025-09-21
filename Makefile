NAME= autoMate

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -g

SRCS_DIR = srcs
OBJS_DIR = objs

MAIN = srcs/main.c
SRC = ft_strtok.c helpers.c
OBJ = $(SRC:.c=.o)

OBJ_PATH = $(patsubst %,$(OBJS_DIR)/%,$(OBJ))

all: $(NAME)

$(NAME): $(OBJ_PATH)
	$(CC) $(CFLAGS) $(MAIN) $^ -o $(NAME)
	@echo "Compiled program."

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ_PATH)
	@echo "Cleaned objects..."

fclean: clean
	@rm -f $(NAME)
	@echo "Finished full clean."

re: fclean all
