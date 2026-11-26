#◉────▣───▢◇▢───▣────◉•◉───▣───▢   Colors:   ▢───▣───◉•◉───▣────▢◇▢───▣───◉#

BLACK   := \033[0;30m
RED     := \033[0;31m
GREEN   := \033[0;32m
YELLOW  := \033[0;33m
BLUE    := \033[0;34m
MAGENTA := \033[0;35m
CYAN    := \033[0;36m

CURRENT_COLOR := \033[0;34m
RESET   := \033[0m

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Variables:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

CC          := cc
CFLAGS      := -Wall -Werror -Wextra 
THREAD_FLAGS := -pthread
RM          := rm -rf

ifeq ($(OS),Windows_NT)
	EXE := .exe
else
	EXE :=
endif

NAME := philo$(EXE)
MALLOC_NAME := philo_malloc$(EXE)

#◉───▣───▢◇▢───▣───◉•◉───▣───▢    philo srcs:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

PHILO_SRCS  := main.c parce.c utils.c exit.c init.c routines.c forks.c forks_utils.c
PHILO_OBJS  := $(PHILO_SRCS:.c=.o)
MALLOC_DIR  := ../malloc
MALLOC_LIB  := $(MALLOC_DIR)/libft_malloc.a
LIBFT_LIB   := $(MALLOC_DIR)/libft/libft.a

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: banner $(NAME)

$(NAME): $(PHILO_OBJS)
	@$(CC) $(CFLAGS) $(THREAD_FLAGS) $(PHILO_OBJS) -o $(NAME)
	@echo "$(CURRENT_COLOR) ✅ $(NAME) created.\n$(RESET)"

%.o: %.c
	$(CC) $(CFLAGS) $(THREAD_FLAGS) -c $< -o $@

allocator:
	$(MAKE) -C $(MALLOC_DIR) static

$(MALLOC_NAME): $(PHILO_SRCS) allocator
	$(CC) $(CFLAGS) $(THREAD_FLAGS) \
		$(PHILO_SRCS) $(MALLOC_LIB) $(LIBFT_LIB) -o $@

malloc: $(MALLOC_NAME)

malloc-test: $(MALLOC_NAME)
	./$(MALLOC_NAME) 5 800 200 200 2 | grep -q "no one died today"
	./$(MALLOC_NAME) 1 100 100 100 | grep -Eq '^[0-9]+ [0-9]+ .*died'

clean:
	$(RM) $(PHILO_OBJS)
	@echo "$(CURRENT_COLOR)🧹 Object files cleaned.\n$(RESET)"

fclean: clean
	$(RM) $(NAME) $(MALLOC_NAME)
	@echo "$(CURRENT_COLOR) 🧹 $(NAME) binary cleaned.\n$(RESET)"

re: fclean all

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     banner      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

banner:
	@echo "$(CURRENT_COLOR)"
	@echo " ██▓███   ██░ ██  ██▓ ██▓     ▒█████    ██████  ▒█████   ██▓███   ██░ ██ ▓█████  ██▀███    ██████ "
	@echo "▓██░  ██▒▓██░ ██▒▓██▒▓██▒    ▒██▒  ██▒▒██    ▒ ▒██▒  ██▒▓██░  ██▒▓██░ ██▒▓█   ▀ ▓██ ▒ ██▒▒██    ▒ "
	@echo "▓██░ ██▓▒▒██▀▀██░▒██▒▒██░    ▒██░  ██▒░ ▓██▄   ▒██░  ██▒▓██░ ██▓▒▒██▀▀██░▒███   ▓██ ░▄█ ▒░ ▓██▄   "
	@echo "▒██▄█▓▒ ▒░▓█ ░██ ░██░▒██░    ▒██   ██░  ▒   ██▒▒██   ██░▒██▄█▓▒ ▒░▓█ ░██ ▒▓█  ▄ ▒██▀▀█▄    ▒   ██▒"
	@echo "▒██▒ ░  ░░▓█▒░██▓░██░░██████▒░ ████▓▒░▒██████▒▒░ ████▓▒░▒██▒ ░  ░░▓█▒░██▓░▒████▒░██▓ ▒██▒▒██████▒▒"
	@echo "▒▓▒░ ░  ░ ▒ ░░▒░▒░▓  ░ ▒░▓  ░░ ▒░▒░▒░ ▒ ▒▓▒ ▒ ░░ ▒░▒░▒░ ▒▓▒░ ░  ░ ▒ ░░▒░▒░░ ▒░ ░░ ▒▓ ░▒▓░▒ ▒▓▒ ▒ ░"
	@echo "░▒ ░      ▒ ░▒░ ░ ▒ ░░ ░ ▒  ░  ░ ▒ ▒░ ░ ░▒  ░ ░  ░ ▒ ▒░ ░▒ ░      ▒ ░▒░ ░ ░ ░  ░  ░▒ ░ ▒░░ ░▒  ░ ░"
	@echo "░░        ░  ░░ ░ ▒ ░  ░ ░   ░ ░ ░ ▒  ░  ░  ░  ░ ░ ░ ▒  ░░        ░  ░░ ░   ░     ░░   ░ ░  ░  ░  "
	@echo "          ░  ░  ░ ░      ░  ░    ░ ░        ░      ░ ░            ░  ░  ░   ░  ░   ░           ░  "
	@echo "$(RESET)"

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Sanitizer   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

sani: 
	gcc -fsanitize=thread -g -O1 -pthread $(PHILO_SRCS) -o philo_tsan
	./philo_tsan 5 800 200 200 7
#	./philo_tsan 5 400 200 200 7

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Norminette ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

norm:
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Checking Norminette: ──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔$(RESET)"
	@norminette $(PHILO_SRCS) philo.h
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Norminette completed. Check your output for details. ─╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣╌╌─$(RESET)"


#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re norm sani malloc malloc-test allocator