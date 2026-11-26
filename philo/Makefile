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

SRC_DIR     := src
OBJ_DIR     := obj
INC_DIR     := inc
INCLUDES    := -I$(INC_DIR)
PHILO_SRCS  := main.c parce.c utils.c exit.c init.c routines.c forks.c forks_utils.c
PHILO_SRC_PATHS := $(addprefix $(SRC_DIR)/,$(PHILO_SRCS))
PHILO_OBJS  := $(addprefix $(OBJ_DIR)/,$(PHILO_SRCS:.c=.o))
MALLOC_DIR  := ../malloc
MALLOC_LIB  := $(MALLOC_DIR)/libft_malloc.a
LIBFT_LIB   := $(MALLOC_DIR)/libft/libft.a
SANITIZER_BIN := $(OBJ_DIR)/philo_tsan

#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

all: $(NAME)

$(NAME): $(PHILO_OBJS)
	@$(CC) $(CFLAGS) $(THREAD_FLAGS) $(PHILO_OBJS) -o $(NAME)
	@echo "$(CURRENT_COLOR) ✅ $(NAME) created.\n$(RESET)"

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(INC_DIR)/philo.h | $(OBJ_DIR)
	$(CC) $(CFLAGS) $(THREAD_FLAGS) $(INCLUDES) -c $< -o $@

allocator:
	$(MAKE) -C $(MALLOC_DIR) static

$(MALLOC_NAME): $(PHILO_SRC_PATHS) $(INC_DIR)/philo.h allocator
	$(CC) $(CFLAGS) $(THREAD_FLAGS) \
		$(INCLUDES) $(PHILO_SRC_PATHS) $(MALLOC_LIB) $(LIBFT_LIB) -o $@

malloc: $(MALLOC_NAME)

malloc-test: $(MALLOC_NAME)
	./$(MALLOC_NAME) 25 800 200 200 2 | grep -q "no one died today"
	./$(MALLOC_NAME) 15 100 100 100 | grep -Eq '^[0-9]+ [0-9]+ .*died'

clean:
	$(RM) $(OBJ_DIR) $(PHILO_SRCS:.c=.o) philo_tsan
	@echo "$(CURRENT_COLOR)🧹 Object files cleaned.\n$(RESET)"

fclean: clean
	$(RM) $(NAME) $(MALLOC_NAME)
	@echo "$(CURRENT_COLOR) 🧹 $(NAME) binary cleaned.\n$(RESET)"

re: fclean all

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Sanitizer   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

sani: | $(OBJ_DIR)
	$(CC) $(CFLAGS) -fsanitize=thread -g -O1 $(THREAD_FLAGS) $(INCLUDES) \
		$(PHILO_SRC_PATHS) -o $(SANITIZER_BIN)
	ulimit -c 0 && ./$(SANITIZER_BIN) 5 5000 200 200 2

valgrind: $(NAME)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes \
		--error-exitcode=99 ./$(NAME) 17 250 250 250

strace: $(MALLOC_NAME) | $(OBJ_DIR)
	strace -f -e trace=mmap,munmap -o $(OBJ_DIR)/philo_malloc.strace \
		./$(MALLOC_NAME) 5 800 200 200 2
	@echo "Memory mapping trace saved to $(OBJ_DIR)/philo_malloc.strace:"
	@cat $(OBJ_DIR)/philo_malloc.strace

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Norminette ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

norm:
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Checking Norminette: ──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌➔$(RESET)"
	@norminette $(PHILO_SRC_PATHS) $(INC_DIR)/philo.h
	@echo "$(CURRENT_COLOR)➵⤐──╌╌➣⋆➣╌╌──⤏➵•➵⤐──╌╌➣⋆➣╌╌── Norminette completed. Check your output for details. ─╌➣⋆➣╌─⤏➵•➵⤐─╌╌➣⋆➣╌╌─$(RESET)"


#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all clean fclean re norm sani valgrind strace malloc malloc-test allocator