DEF_COLOR =		\033[0;39m
GREEN =			\033[1;32m
BLUE =			\033[0;94m
YELLOW =		\033[0;93m

NAME = libft.a

CC = cc

CFLAGS = -Wall -Wextra -Werror

# # DIRECTORIES
SRC =	./ft_isalnum.c \
		./ft_isalpha.c \
		./ft_split.c \
		./ft_strcat.c \
		./ft_strcmp.c \
		./ft_strncmp.c \
		./is_space.c \
		./ft_strcpy.c \
		./ft_strduptrim.c \
		./ft_strncpy.c \
		./delete_string_on_array.c \
		./ft_strjoin.c \
		./insert_string_on_array.c \
		./ft_substr.c \
		./ft_strrint.c \
		./is_string_in_array.c \
		./ft_atoi.c \
		./ft_bzero.c \
		./ft_itoa.c \
		./ft_lstnew.c \
		./ft_strlen.c \
		./ft_strdup.c \
		./ft_strtrim.c \
		./get_array_string_size.c \
		./is_string_numeric.c \
		./ft_lstlast.c \
		./ft_lstsize.c \
		./ft_strndup.c \
		./string_is_null_or_whitespace.c \
		./ft_calloc.c \


# RULES
%.o: %.c
	@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(GREEN)$< $(DEF_COLOR)"
	@ ${CC} ${CFLAGS} -c $< -o $@

OBJ = $(SRC:.c=.o)

# VARIABLES
AR = ar rcs
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "\n$(GREEN) "libft.a created" ✓$(DEF_COLOR)\n"
	@echo "$(GREEN)       .___,   $(DEF_COLOR)"
	@echo "$(GREEN)    ___('v')___$(DEF_COLOR)"
	@echo "$(GREEN)    \`\"-\\._./-'$(DEF_COLOR)"
	@echo "$(GREEN)        ^ ^  $(DEF_COLOR)"

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL = all
