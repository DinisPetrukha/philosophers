NAME = philo

SRC = main.c check_errors.c create_threads.c init_data.c \
	philosophers_utils.c routine.c dead_utils.c routine_utils.c

OBJ = $(SRC:.c=.o)

CC = cc

CFLAGS = -Wall -Werror -Wextra #-g -fsanitize=thread

GREEN = \033[0;32m
CYAN = \033[0;36m
RED = \033[0;31m
NC = \033[0;33m

all: $(OBJ) $(NAME)

$(OBJ): %.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@echo "$(CYAN)Linking object files...\n$(NC)"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "$(GREEN)\n---------------------------------$(NC)"
	@echo "$(GREEN)$(NAME) is ready!$(NC)"
	@echo "$(GREEN)Usage: ./$(NAME) n_philos t_die t_eat t_sleep [n_times_to_eat]$(NC)"
	@echo "$(GREEN)---------------------------------\n$(NC)"
clean:
	@echo "$(CYAN)\nCleaning object file...\n$(NC)"
	@rm -f $(OBJ)
	@echo "$(GREEN)$(NAME) object files cleaned!\n$(NC)"

fclean: clean
	@echo "$(CYAN)\n-Cleaning $(NAME)...\n$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(NAME) cleaned!$(NC)"

re: clean fclean all

.PHONY: all clean fclean re
