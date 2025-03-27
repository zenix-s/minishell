DEF_COLOR =		\033[0;39m
GRAY =			\033[0;90m
RED =			\033[0;91m
GREEN =			\033[0;92m
YELLOW =		\033[0;93m
BLUE =			\033[0;94m

NAME = minishell

HEADERS	= -I ./include

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3
CCLANG = -lreadline

SOURCE = ./src/build_ins/use_export.c \
			./src/build_ins/utils_b_content.c \
			./src/build_ins/alone_baskwards.c \
			./src/build_ins/env_is_absolute.c \
			./src/build_ins/use_unset.c \
			./src/build_ins/execute_command.c \
			./src/build_ins/ft_use_pwd.c \
			./src/build_ins/print_env.c \
			./src/build_ins/use_echo.c \
			./src/build_ins/use_exit.c \
			./src/build_ins/use_cd.c \
			./src/env/split_env.c \
			./src/env/env_list_add_back.c \
			./src/env/get_env_value.c \
			./src/env/create_list_env.c \
			./src/env/new_env_token.c \
			./src/handle_signal.c \
			./src/exe_all.c \
			./src/redirect/redirect_utils.c \
			./src/redirect/standard_out.c \
			./src/redirect/redirect_state.c \
			./src/redirect/here_doc.c \
			./src/redirect/standard_in.c \
			./src/main.c \
			./src/clean/free_env.c \
			./src/clean/free_tokens.c \
			./src/clean/free_shell.c \
			./src/pipex/middle_child.c \
			./src/pipex/prepare_redirect.c \
			./src/pipex/ft_waitpid.c \
			./src/pipex/pipex_redirect.c \
			./src/pipex/utils_pipex.c \
			./src/pipex/pipex.c \
			./src/pipex/big_pipex.c \
			./src/state/transition_states/parser_end_state.c \
			./src/state/parser_states/assign_type_state/assign_type_state.c \
			./src/state/parser_states/expand_env_state/expand_variable.c \
			./src/state/parser_states/expand_env_state/expand_env_state.c \
			./src/state/parser_states/expand_env_state/get_varriable_name.c \
			./src/state/parser_states/expand_env_state/is_valid_init_char.c \
			./src/state/parser_states/tokenize_state/add_token.c \
			./src/state/parser_states/tokenize_state/create_token.c \
			./src/state/parser_states/tokenize_state/pre_process_input.c \
			./src/state/parser_states/tokenize_state/tokenize_state.c \
			./src/state/parser_states/trim_nodes_state.c \
			./src/state/post_parser_checks_states/check_redirect_newline_error_state.c \
			./src/state/select_state.c \
			./src/state/segurity_state.c \
			./src/state/readline_states/readline_state.c \
			./src/state/readline_states/valid_input.c \
			./src/state/clean_state.c \
			./src/state/pipex_state.c \
			./src/state/create_files_state.c \
			./src/state/error_state.c \
			./src/state/exit_state.c \
			./src/handle_signal_heredoc.c \
			./src/shared/get_quote_type.c \
			./src/shared/is_separator.c \
			./src/shared/special_split_aux.c \
			./src/shared/remove_outer_quotes.c \
			./src/shared/special_split.c \
			./src/shared/generate_here_doc_file_name.c \
			./src/shell_factory.c \
			./src/utils.c \

LIBFT_SRC = ./libft
LIBS = $(LIBFT_SRC)/libft.a

%.o: %.c
				@echo "${BLUE} ◎ $(YELLOW)Compiling   ${RED}→   $(GREEN)$< $(DEF_COLOR)"
				@ ${CC} ${CFLAGS} -c $< -o $@ ${HEADERS}


OBJS = ${SOURCE:.c=.o}

all: libft ${NAME}

libft:
	@$(MAKE) -s all -C $(LIBFT_SRC)

${NAME}: ${OBJS}
				@ $(CC) ${CFLAGS} $^ -o $@ ${LIBS} ${CCLANG}
				@echo "\n$(GREEN) Created $(NAME) ✓$(DEF_COLOR)\n"
				@echo "$(YELLOW)    _       _       _$(DEF_COLOR)"
				@echo "$(YELLOW) __(.)<  __(.)>  __(.)=    $(DEF_COLOR)Cuak!"
				@echo "$(YELLOW) \___)   \___)   \___)$(DEF_COLOR)"

clean:
	@$(MAKE) -s clean -C $(LIBFT_SRC)
	@${RM} ${OBJS}
	@echo -e "\n${GRAY} ◎ $(RED)All objects cleaned successfully ${GRAY}◎$(DEF_COLOR)\n"

fclean:
				@${RM} ${NAME}
				@${RM} ${OBJS}
				@$(MAKE) -s fclean -C $(LIBFT_SRC)
				@echo "\n${GRAY} ◎ $(RED)All objects and executable cleaned successfully${GRAY} ◎$(DEF_COLOR)\n"

re: fclean all

.PHONY: all, clean, fclean, re, libft
.DEFAULT_GOAL = all
