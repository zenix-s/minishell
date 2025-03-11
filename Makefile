DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m

NAME = minishell

HEADERS	= -I ./include

CC = cc

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3
CCLANG = -lreadline

SOURCE = $(shell find . -iname "*.c")

%.o: %.c
				@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(GREEN)$< $(DEF_COLOR)"
				@ ${CC} ${CFLAGS} -c $< -o $@ ${HEADERS}


OBJS = ${SOURCE:.c=.o}

all: ${NAME}

${NAME}: ${OBJS}
				@ $(CC) ${CFLAGS} $^ -o  $@ ${CCLANG}
				@echo "\n$(GREEN) Created $(NAME) ✓$(DEF_COLOR)\n"
				@echo "$(YELLOW)    _       _       _$(DEF_COLOR)"
				@echo "$(YELLOW) __(.)<  __(.)>  __(.)=    $(DEF_COLOR)Cuak!"
				@echo "$(YELLOW) \___)   \___)   \___)$(DEF_COLOR)"

clean:
				@${RM} ${OBJS}
				@echo -e "\n${GRAY} ◎ $(RED)All objects cleaned successfully ${GRAY}◎$(DEF_COLOR)\n"

fclean:
				@${RM} ${NAME}
				@${RM} ${OBJS}
				@echo "\n${GRAY} ◎ $(RED)All objects and executable cleaned successfully${GRAY} ◎$(DEF_COLOR)\n"

re: fclean all

.PHONY: all clean fclean re