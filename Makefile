# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bakgun <bakgun@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/01 16:25:17 by bakgun            #+#    #+#              #
#    Updated: 2024/03/22 12:17:01 by bakgun           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := philo

FLAGS := -Wall -Wextra -Werror -pthread # -fsanitize=thread -g

CC := gcc
GREEN := \033[0;32m
RED := \033[0;31m
RESET := \033[0m

SRC := philo.c \
    smell_of_death.c \
    life_of_philo.c \
    utils.c \
	ft_strjoin.c

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

re : fclean all

.PHONY: all clean fclean re