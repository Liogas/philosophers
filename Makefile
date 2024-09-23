#==PROGRAM==#
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g3

NAME	= philo

#==TEST==#
NB_PHILO	= 3
TTD			= 605
TTE			= 200
TTS			= 200
LIMIT		= 10

#==SRC & OBJ==##
SRCS		= supervisor.c fork_utils.c print.c routine.c utils.c time.c ft_itoa.c fork.c philo.c mutex.c free.c main.c
OBJS		= $(SRCS:.c=.o)

#==RULES==#

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $^

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@ -lpthread -D_REENTRANT
	@clear
	@echo "Try : ./philo [nb_philo] [time to died] [time to eat] [time to sleep] [limit (optional)]"

clean:
	@rm -rf $(OBJS)
	@echo "objets : 🗑️"

fclean: clean
	@rm -rf $(NAME)
	@echo "./philo: 🗑️"

re: fclean all

run_test: $(NAME)
	@clear
	@./philo $(NB_PHILO) $(TTD) $(TTE) $(TTS)

run_test_limit: $(NAME)
	@clear
	@./philo $(NB_PHILO) $(TTD) $(TTE) $(TTS) $(LIMIT)

run_test_v: $(NAME)
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./philo $(NB_PHILO) $(TTD) $(TTE) $(TTS)

run_test_limit_v: $(NAME)
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes ./philo $(NB_PHILO) $(TTD) $(TTE) $(TTS) $(LIMIT)

run_test_h: $(NAME)
	@clear
	@valgrind --tool=helgrind --error-limit=no ./philo $(NB_PHILO) $(TTD) $(TTE) $(TTS)

run_test_limit_h: $(NAME)
	@clear
	@valgrind --tool=helgrind --error-limit=no ./philo $(NB_PHILO) $(TTD) $(TTE) $(TTS) $(LIMIT)

push: fclean
	@git add .
	@git commit -m "use make push"
	@git push

.PHONY: all clean fclean re run_test tun_test_v run_test_h push