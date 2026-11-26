# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: KarmaFaber <github.com/KarmaFaber>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/11/26 12:22:37 by KarmaFaber        #+#    #+#              #
#    Updated: 2026/11/26 12:22:39 by KarmaFaber       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#◉───▣───▢◇▢───▣───◉•◉───▣───▢   Variables:   ▢───▣───◉•◉───▣───▢◇▢───▣───◉#
PHILO_DIR := philo
MALLOC_DIR := malloc


#◉───▣───▢◇▢───▣───◉•◉───▣───▢     rules      ▢───▣───◉•◉───▣───▢◇▢───▣───◉#
all: philo

philo:
	$(MAKE) -C $(PHILO_DIR)

malloc:
	$(MAKE) -C $(MALLOC_DIR) static

philo-malloc:
	$(MAKE) -C $(PHILO_DIR) malloc

philo-test:
	$(MAKE) -C $(PHILO_DIR) malloc-test

allocator-test:
	$(MAKE) -C $(MALLOC_DIR) test

test: philo-test

clean:
	$(MAKE) -C $(PHILO_DIR) clean
	$(MAKE) -C $(MALLOC_DIR) clean

fclean:
	$(MAKE) -C $(PHILO_DIR) fclean
	$(MAKE) -C $(MALLOC_DIR) fclean

re: fclean all


#◉───▣───▢◇▢───▣───◉•◉───▣───▢ Phony targets ▢───▣───◉•◉───▣───▢◇▢───▣───◉#

.PHONY: all philo malloc philo-malloc philo-test allocator-test test clean fclean re