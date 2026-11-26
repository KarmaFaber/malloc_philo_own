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

PHILO_DIR := philo
MALLOC_DIR := malloc
PHILO_INC_DIR := $(PHILO_DIR)/inc
PHILO_SRCS := $(filter-out $(PHILO_DIR)/src/main.c,$(wildcard $(PHILO_DIR)/src/*.c))
MALLOC_DEBUG_PRINTER := $(MALLOC_DIR)/test/src/debug_printers.c
ifeq ($(OS),Windows_NT)
PHILO_MEMORY_BIN := philo_malloc_memory.exe
else
PHILO_MEMORY_BIN := philo_malloc_memory
endif
PHILO_ARGS ?= 55 800 200 200 2
TEST_DIR := test
TEST_LOGS := $(TEST_DIR)/sani.log $(TEST_DIR)/valgrind.log \
	$(TEST_DIR)/strace.log


#◉───▣───▢◇▢───▣───◉•◉───▣───▢ default target ▢───▣───◉•◉───▣───▢◇▢───▣───◉#
all: philo

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Internal helpers ▢───▣───◉•◉───▣───▢◇▢───▣#
# These targets are build dependencies; use the test targets below instead.
allocator-static:
	@$(MAKE) -s -C $(MALLOC_DIR) static

$(PHILO_MEMORY_BIN): allocator-static philo_malloc_memory.c $(PHILO_SRCS) \
		$(PHILO_INC_DIR)/philo.h $(MALLOC_DEBUG_PRINTER) \
		$(MALLOC_DIR)/test/inc/test.h
	@$(CC) -Wall -Wextra -Werror -pthread -I$(PHILO_INC_DIR) \
		-Imalloc/inc -Imalloc/libft -Imalloc/test \
		philo_malloc_memory.c $(PHILO_SRCS) $(MALLOC_DEBUG_PRINTER) \
		$(MALLOC_DIR)/libft_malloc.a $(MALLOC_DIR)/libft/libft.a -o $@

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Build targets ▢───▣───◉•◉───▣───▢◇▢───▣───◉#
philo:
	$(MAKE) -C $(PHILO_DIR)

malloc:
	$(MAKE) -C $(MALLOC_DIR) static

philo-malloc:
	$(MAKE) -C $(PHILO_DIR) malloc

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Test targets (run from terminal) ▢───▣───◉#
philo-test:
	$(MAKE) -C $(PHILO_DIR) malloc-test

philo-memory-test: $(PHILO_MEMORY_BIN)
	@./$(PHILO_MEMORY_BIN) $(PHILO_ARGS)

ifeq ($(OS),Windows_NT)
allocator-test sani valgrind strace test_gdb:
	@echo "WARNING: '$@' uses Linux-only test tools and is unavailable on Windows."
	@echo "No tests were run and no log files were created."
	@exit 1
else
allocator-test:
	$(MAKE) -C $(MALLOC_DIR) test

sani:
	@echo "$(RED)Running philo with sanitizer...$(RESET)"
	$(MAKE) -C $(PHILO_DIR) sani

valgrind:
	@echo "$(CYAN)Running philo with valgrind...$(RESET)"
	$(MAKE) -C $(PHILO_DIR) valgrind

strace:
	@echo "$(CYAN)Running philo with strace...$(RESET)"
	$(MAKE) -C $(PHILO_DIR) strace

# `test_gdb` saves each test's full output separately and reports all failures.
test_gdb:
	@mkdir -p $(TEST_DIR)
	@set +e; \
	$(MAKE) sani > $(TEST_DIR)/sani.log 2>&1; sani_status=$$?; \
	$(MAKE) valgrind > $(TEST_DIR)/valgrind.log 2>&1; valgrind_status=$$?; \
	$(MAKE) strace > $(TEST_DIR)/strace.log 2>&1; strace_status=$$?; \
	printf 'sani: exit %s (%s/sani.log)\n' "$$sani_status" "$(TEST_DIR)"; \
	printf 'valgrind: exit %s (%s/valgrind.log)\n' "$$valgrind_status" "$(TEST_DIR)"; \
	printf 'strace: exit %s (%s/strace.log)\n' "$$strace_status" "$(TEST_DIR)"; \
	if [ "$$sani_status" -ne 0 ] || [ "$$valgrind_status" -ne 0 ] \
		|| [ "$$strace_status" -ne 0 ]; then \
		printf 'One or more tests failed; inspect %s/*.log\n' "$(TEST_DIR)"; \
		exit 1; \
	fi
endif

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Cleanup targets ▢───▣───◉•◉───▣───▢◇▢───▣#
clean:
	$(MAKE) -C $(PHILO_DIR) clean
	$(MAKE) -C $(MALLOC_DIR) clean
	rm -f $(PHILO_MEMORY_BIN)

fclean:
	$(MAKE) -C $(PHILO_DIR) fclean
	$(MAKE) -C $(MALLOC_DIR) fclean
	rm -f $(PHILO_MEMORY_BIN)
	rm -f $(TEST_LOGS)

re: fclean all

#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all philo malloc philo-malloc philo-test allocator-test sani valgrind strace allocator-static philo-memory-test test_gdb clean fclean re