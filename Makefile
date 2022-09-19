# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: cpost <cpost@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2022/07/11 13:49:40 by cpost         #+#    #+#                  #
#    Updated: 2022/09/19 16:07:18 by cpost         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SRC_PATH = ./src/
#SHR_PATH = ./shared/
OBJ_PATH = ./obj/
#BON_PATH = ./bonus/
INC_PATH = ./include/

NAME = philo
#BONUS_NAME = philo_bonus
CC = gcc
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g

SRC_NAME = $(shell ls $(SRC_PATH))
#SHR_NAME = $(shell ls $(SHR_PATH))
#BON_NAME = $(shell ls $(BON_PATH))

OBJ_NAME = $(SRC_NAME:.c=.o) $(SHR_NAME:.c=.o)
#BON_OBJ_NAME = $(BON_NAME:.c=.o) $(SHR_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
#SHR = $(addprefix $(SHR_PATH), $(SHR_NAME))
#BON = $(addprefix $(BON_PATH), $(BON_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))
#BON_OBJ = $(addprefix $(OBJ_PATH), $(BON_OBJ_NAME))
INC = $(addprefix -I,$(INC_PATH))

BOLD = \033[1m
GREEN = \033[32;1m
RED	= \033[31;1m
YELLOW	= \033[33;1m
RESET = \033[0m

all: $(NAME)

bonus: $(BONUS_NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(INC) $(OBJ) -o $(NAME) && printf "$(YELLOW)$(BOLD)\rBuilt $(NAME)\r\e[35C[OK]\n$(RESET)"

#$(BONUS_NAME): $(BON_OBJ)
#	@make -C $(LIBFT_PATH)
#	@make -C $(LIBPRINTF_PATH)
#	@$(CC) $(CFLAGS) $(LIB) $(INC) $(BON_OBJ) -o $(BONUS_NAME) && printf "$(YELLOW)$(BOLD)\rBuilt $(BONUS_NAME)\r\e[35C[OK]\n$(RESET)"

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

#$(OBJ_PATH)%.o: $(SHR_PATH)%.c
#	@mkdir -p $(OBJ_PATH)
#	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

#$(OBJ_PATH)%.o: $(BON_PATH)%.c
#	@mkdir -p $(OBJ_PATH)
#	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< && printf "$(GREEN)$(BOLD)\rCompiling: $(notdir $<)\r\e[35C[OK]\n$(RESET)"

clean:
	@echo "$(RED)Cleaning$(RESET)"
	@rm -f $(OBJ)
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)
	@rm -f $(BONUS_NAME)

re: fclean all

.PHONY: clean, fclean, re, all