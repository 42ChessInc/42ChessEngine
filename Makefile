NAME= autoMate

NQ = n_queens

RECUR = fib

CC = cc

CFLAGS = -Wall -Werror -Wextra -Iinclude -g

SRCS_DIR = ./srcs/main.c

NQ_PATH = ./srcs/nqueens.c #./srcs/nqueens_utils.c

RECUR_PATH = ./srcs/recursion.c

INC_DIR = include

all: $(NAME)

$(NQ):
	$(CC) $(CFLAGS) -o $(NQ) $(NQ_PATH)

$(RECUR):
	$(CC) $(CFLAGS) -o $(RECUR) $(RECUR_PATH)

$(NAME): $(SRCS_DIR)
	$(CC) $(CFLAGS) -o $(NAME) $(SRCS_DIR)

clean:
	@rm -f $(NQ)
	@rm -f $(RECUR)
	@rm -f $(NAME)

.PHONY: all n_queens clean
