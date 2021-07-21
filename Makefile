NAME	= philo
NAME_B	= philo_bonus
SRCS	= philo.c
SRCS_B	= philo_bonus.c
OBJS	= $(SRCS:.c=.o)
OBJS_B	= $(SRCS_B:.c=.o)
HEADER	= philo.h
HEADER_B = philo_bonus.h
CC		= gcc
FLAGS	= -g3 -Wall -Werror -Wextra -pthread
RM		= rm -rf

all:	$(HEADER) $(NAME)

bonus:	$(HEADER_B) $(NAME_B)

$(NAME):	$(OBJS) PHILO
			@$(CC) $(OBJS) -o $(NAME)

$(NAME_B):	$(OBJS_B) PHILO_B
			@$(CC) $(OBJS_B) -o $(NAME_B)		

$(OBJS):	$(SRCS)
			@$(CC) -c $(SRCS) -o $(OBJS)

$(OBJS_B):	$(SRCS_B)
			@$(CC) -c $(SRCS_B) -o $(OBJS_B)

clean:		CLEAN
			@$(RM) $(OBJS)
			@$(RM) $(OBJS_B)

fclean:		clean FCLEAN
			@$(RM) $(NAME)
			@$(RM) $(NAME_B)

re:			fclean all

leaks:
			valgrind --leak-check=full --show-leak-kinds=definite $(NAME) 5 800 200 200 7

git:
			make fclean
			git add .
			git commit -m "commit"
			git push

space:
			@$(RM) ~/Library/Caches/█
			@$(RM) ~/Library/█42_cache█
			@$(RM) ~/Library/Application\ Support/Slack/Service\ Worker/CacheStorage/
			@$(RM) ~/Library/Application\ Support/Slack/Cache/
			@$(RM) ~/Library/Application\ Support/Slack/Code\ Cache/
			@$(RM) ~/Library/Application\ Support/Code/Cache/█
			@$(RM) ~/Library/Application\ Support/Code/CachedData/█
			@$(RM) ~/Library/Application Support/Spotify/PersistentCache
			@$(RM) ~/Library/Application\ Support/Code/User/workspaceStorage

.PHONY:		all clean fclean re leaks git space
.SILENT:

CYAN = \033[1;36m
GREEN = \033[1;32m
YELLOW = \033[1;33m
RED = \033[1;31m
WHITE = \033[1;37m
BLUE = \033[1;34m
PURPLE = \033[1;35m
GREY = \033[1;90m
DEFAULT = \033[0m
C1 = \033[38;5;160m
C2 = \033[38;5;161m
C3 = \033[38;5;162m
C4 = \033[38;5;163m
C5 = \033[38;5;164m
C6 = \033[38;5;165m
C7 = \033[38;5;166m
C8 = \033[38;5;167m
C9 = \033[38;5;168m
C10 = \033[38;5;169m
C11 = \033[38;5;170m
C12 = \033[38;5;171m
B1 = \033[38;5;148m
B2 = \033[38;5;149m
B3 = \033[38;5;150m
B4 = \033[38;5;151m
B5 = \033[38;5;152m
D1 = \033[38;5;47m
D2 = \033[38;5;48m
D3 = \033[38;5;49m
D4 = \033[38;5;50m
D5 = \033[38;5;51m
E1 = \033[38;5;52m
E2 = \033[38;5;53m
E3 = \033[38;5;54m
E4 = \033[38;5;55m
E5 = \033[38;5;56m
E6 = \033[38;5;57m


PHILO:
		printf "\n\n"
		printf " $(C1)████   $(C2)█   █  $(C3)███  $(C4)█    $(C5)  ███   $(C6) ████ $(C7)  ███   $(C8)████   $(C9)█   █  $(C10)█████  $(C11)████   $(C12) ████\n"
		printf " $(C1)█   █  $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █  $(C6)█     $(C7) █   █  $(C8)█   █  $(C9)█   █  $(C10)█      $(C11)█   █  $(C12)█\n"
		printf " $(C1)█   █  $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █  $(C6)█     $(C7) █   █  $(C8)█   █  $(C9)█   █  $(C10)█      $(C11)█   █  $(C12)█\n"
		printf " $(C1)████   $(C2)█████  $(C3) █   $(C4)█    $(C5) █   █  $(C6) ███  $(C7) █   █  $(C8)████   $(C9)█████  $(C10)████   $(C11)████   $(C12) ███\n"
		printf " $(C1)█      $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █  $(C6)    █ $(C7) █   █  $(C8)█      $(C9)█   █  $(C10)█      $(C11)█ █    $(C12)    █\n"
		printf " $(C1)█      $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █  $(C6)    █ $(C7) █   █  $(C8)█      $(C9)█   █  $(C10)█      $(C11)█  █   $(C12)    █\n"
		printf " $(C1)█      $(C2)█   █  $(C3)███  $(C4)████ $(C5)  ███   $(C6)████  $(C7)  ███   $(C8)█      $(C9)█   █  $(C10)█████  $(C11)█   █  $(C12)████\n\n"

PHILO_B:
		printf "\n\n"
		printf " $(C1)████   $(C2)█   █  $(C3)███  $(C4)█    $(C5)  ███          $(B1)████   $(B2) ███   $(B3)█     █ $(B4)█   █ $(B5)  ████ \n"
		printf " $(C1)█   █  $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █         $(B1)█   █  $(B2)█   █  $(B3)██    █ $(B4)█   █ $(B5) █     \n"
		printf " $(C1)█   █  $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █         $(B1)█   █  $(B2)█   █  $(B3)█ █   █ $(B4)█   █ $(B5) █     \n"
		printf " $(C1)████   $(C2)█████  $(C3) █   $(C4)█    $(C5) █   █         $(B1)████   $(B2)█   █  $(B3)█  █  █ $(B4)█   █ $(B5)  ███  \n"
		printf " $(C1)█      $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █         $(B1)█   █  $(B2)█   █  $(B3)█   █ █ $(B4)█   █ $(B5)     █ \n"
		printf " $(C1)█      $(C2)█   █  $(C3) █   $(C4)█    $(C5) █   █         $(B1)█   █  $(B2)█   █  $(B3)█    ██ $(B4)█   █ $(B5)     █ \n"
		printf " $(C1)█      $(C2)█   █  $(C3)███  $(C4)████ $(C5)  ███          $(B1)████   $(B2) ███   $(B3)█     █ $(B4) ███  $(B5) ████  \n\n"

CLEAN:
		printf "\n\n"
		printf " $(D1)  ███  $(D2)█      $(D3)█████  $(D4) ███  $(D5) █     █ \n"
		printf " $(D1) █     $(D2)█      $(D3)█      $(D4)█   █ $(D5) ██    █ \n"
		printf " $(D1)█      $(D2)█      $(D3)█      $(D4)█   █ $(D5) █ █   █ \n"
		printf " $(D1)█      $(D2)█      $(D3)███    $(D4)█   █ $(D5) █  █  █ \n"
		printf " $(D1)█      $(D2)█      $(D3)█      $(D4)█████ $(D5) █   █ █ \n"
		printf " $(D1) █     $(D2)█      $(D3)█      $(D4)█   █ $(D5) █    ██ \n"
		printf " $(D1)  ███  $(D2)█████  $(D3)█████  $(D4)█   █ $(D5) █     █ \n\n"

FCLEAN:
		printf "\n\n"
		printf " $(E1)█████ $(E2)  ███  $(E3)█      $(E4)█████  $(E5) ███  $(E6) █     █ \n"
		printf " $(E1)█     $(E2) █     $(E3)█      $(E4)█      $(E5)█   █ $(E6) ██    █ \n"
		printf " $(E1)█     $(E2)█      $(E3)█      $(E4)█      $(E5)█   █ $(E6) █ █   █ \n"
		printf " $(E1)████  $(E2)█      $(E3)█      $(E4)███    $(E5)█   █ $(E6) █  █  █ \n"
		printf " $(E1)█     $(E2)█      $(E3)█      $(E4)█      $(E5)█████ $(E6) █   █ █ \n"
		printf " $(E1)█     $(E2) █     $(E3)█      $(E4)█      $(E5)█   █ $(E6) █    ██ \n"
		printf " $(E1)█     $(E2)  ███  $(E3)█████  $(E4)█████  $(E5)█   █ $(E6) █     █ \n\n"

