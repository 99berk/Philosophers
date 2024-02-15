NAME := philo

FLAGS := -Wall -Wextra -Werror -pthread -fsanitize=thread -g

CC := gcc
GREEN := \033[0;32m
RED := \033[0;31m
RESET := \033[0m

SRC := main.c \
    philo_init.c \
    death.c \
    eat_sleep_repeat.c \
    utils.c

OBJ = $(SRC:c=o)

BUILD_PRINT = $(GREEN)Building $<$(RESET)
DELETE_PRINT = $(RED)Deleting ./philo$(RESET)
DELETE_OBJ = $(RED)Deleting Objects $(RESET)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(SRC) -o $(NAME)

%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@
	@echo "$(BUILD_PRINT)"

clean :
		@rm -rf $(OBJ)
		@echo "$(DELETE_OBJ)"

fclean : clean
	@rm -f $(NAME)
	@echo "$(DELETE_PRINT)"

re :    fclean all
