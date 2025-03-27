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
		./ft_lstdelone.c \
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

OBJ = $(SRC:.c=.o)

# VARIABLES
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
NAME = libft.a
RM = rm -f

# RULES
%.o: %.c
	@echo "Compiling $<"
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	@$(AR) $(NAME) $(OBJ)
	@echo "libft.a created"

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
.DEFAULT_GOAL = all
