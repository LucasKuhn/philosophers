# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lalex-ku <lalex-ku@42sp.org.br>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/09 13:40:15 by lalex-ku          #+#    #+#              #
#    Updated: 2022/11/09 15:00:03 by lalex-ku         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	philo
CFLAGS	=	-pthread -Wall -Wextra -Werror # -g3 -fsanitize=thread
OBJ_DIR	=	obj
OBJS	=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
SRCS	=	main.c print_state.c create_philosophers.c philo_eat_utils.c \
simulate_philosophers.c fork_utils.c philo_state_utils.c update_state.c \
ft_atoi.c get_timestamp.c pick_a_fork.c invalid_args.c

all: $(NAME)

run: $(NAME)
	./$(NAME) 4 410 200 200 8

clean:
	@rm -rf obj
	@echo "removed obj folder"

fclean: clean
	@rm -rf $(NAME)
	@echo "removed executable"

re: fclean all

$(NAME): $(LIBFT_A) $(OBJ_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LDLIBS) $(LDFLAGS)

$(OBJ_DIR)/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDE)

$(OBJ_DIR):
	mkdir -p $@
