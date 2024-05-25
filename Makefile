CC 			= cc
CFLAGS		= -Wall -Werror -Wextra -g3
INCLUDES	= -I./incs/
SRCS 		=	srcs/main.c srcs/utils.c srcs/create_config.c \
				srcs/ft_ltoa.c srcs/ft_itoa.c srcs/create_philos.c \
				srcs/create_forks.c
OBJS 		= $(SRCS:.c=.o)
NAME 		= philo

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $^ $(INCLUDES)

$(NAME): $(OBJS)
	@clear
	@echo "$(NAME)  ❌"
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(INCLUDES)
	@clear
	@echo "$(NAME)  ✅"

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)
	@echo "$(NAME)  ❌"

push:
	@make fclean
	@git add .
	@git commit -m "Utilisation de push : ptetre plus d'infos dans le README"
	@git push
	@echo "✅ Le dossier a bien ete push ✅"

re: fclean $(NAME)

.PHONY: all clean fclean re push