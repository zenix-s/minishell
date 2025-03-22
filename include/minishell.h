/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:01:06 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 17:25:16 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
// No eliminar comentario impiede
// que el formater base stdio.h por debajo de readline
# include "errors.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

# define READ_END 0
# define WRITE_END 1
# define MAX_INPUT_LENGTH 1024

# include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum e_quote
{
	NONE,   // Outside of quotes
	DOUBLE, // Inside double quotes "" $var is expanded
	SINGLE  // Inside single quotes '' $var is not expanded
}						t_quote;

typedef enum e_cmd_type
{
	BUILT_IN,
	REDIRECT,
	PIPE,
	EXE
}						t_cmd_type;

typedef enum e_built_in_type
{
	UNDEFINED,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}						t_built_in_type;

typedef struct s_token
{
	char				*content;
	t_cmd_type			type;
	t_built_in_type		built_in;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env_token
{
	char				*key;
	char				*value;
	struct s_env_token	*next;
}						t_env_token;

typedef struct s_shell
{
	t_bool				is_done;
	void				(*execute)(struct s_shell *);
	char				*input;
	t_token				*tokens;
	t_env_token			*env;
	// redirect
	char				*read;
	char				*write;
	int					mode;
	// Error handling
	char				*error_message;
	char				*unexpected_token;
	t_bool				exit_of_failure;
}						t_shell;

typedef struct s_splitter
{
	char				**result;
	uint64_t			result_idx;
	int64_t				start;
	t_quote				q_state;

	int64_t				i;
}						t_splitter;

//----------------------------------------------------------------------------//
//                                    SHELL
//----------------------------------------------------------------------------//
t_shell					*shell_factory(char **env);

//----------------------------------------------------------------------------//
//									CLEAN
//----------------------------------------------------------------------------//
void					free_tokens(t_token *tokens);
void					free_env_tokens(t_env_token *env);
void					free_shell(t_shell *shell);
void					ft_free(char **lst);
void					ft_error(char *texto);
//----------------------------------------------------------------------------//
//                                   PARSER
//----------------------------------------------------------------------------//

void					segurity_state(t_shell *shell);
void					parse_line(t_shell *shell);
int						get_quote_type(t_quote quote_state, char c);
void					print_tokens(t_token *tokens);
void					free_tokens(t_token *tokens);

void					main_loop(t_shell *shell);
void					use_build(char *line, t_token *list_env);
void					head(void);

void					parser_end_state(t_shell *shell);

int						count_tokens(char *input, const char **split,
							const char **s_split);
char					**special_split(char *input, const char **split,
							const char **s_split);

u_int64_t				is_string_redirect(const char *str);
u_int64_t				is_string_pipe(const char *str);
uint64_t				is_special_token(const char *str);

char					*remove_outer_quotes(char *str);

//----------------------------------------------------------------------------//
//                                state
//----------------------------------------------------------------------------//
void					clean_end_state(t_shell *shell);
void					error_state(int mod);
void					fail_state(t_shell *shell);
void					exit_state(t_shell *shell);
// Builds
void					create_files_state(t_shell *shell);
//  select
void					select_all(t_shell *shell);
// int						select_build(t_shell **shell, char **line_arraid);
int						s_build(t_shell *shell, char **line_arraid);
void					execute_cmd(char **l_arraid, t_env_token *list_env);

void					check_redirect_error_state(t_shell *shell);

//----------------------------------------------------------------------------//
//                                Redirect
//----------------------------------------------------------------------------//
void					redirect_state(t_shell *shell);
void					prepare_in_loop(t_shell *shell);
int						prepare(t_shell *shell, t_token *aux_token);
int						ft_read_open(t_token *aux_token, t_shell *shell,
							char *s);
int						ft_write_open(t_token *aux_token, t_shell *shell,
							char *name);
int						ft_open(t_shell *shell, int file, char *name, int mode);
int						use_redirect(t_shell *shell);
// int						little_redirect(t_shell *shell);
int	follow_mode(t_token *env_aux); //
void					all_heredoc(t_shell *shell);
void					her_d(char **line_arraid);
void					stnd_out(t_token *env_aux, t_shell *aux, int mode);
int						stnd_in(t_token *env_aux, t_shell *aux, int mode);
int						new_stnd_in(t_shell *shell);
void					new_new_stdn_in(t_shell *shell, t_token *aux_token);
int	finish_redirect(t_shell *shell, t_token *aux_shell); //
void					read_alone(t_shell *shell, char **cmd);
void					write_alone(t_shell *shell, char **cmd);
int						new_open(t_shell *shell);
void					full_redirect(t_shell *shell, char **cmd);
void					redirect_error(t_token *list, int mode);

// expecific comand
void					use_unset(t_shell *shell, char **line_arraid);
void					use_pwd(void);
void					use_export(t_shell **shell, char **line_arraid);
void					use_echo(char **line_arraid);
void					use_cd(t_env_token *l_env, char **line_arraid,
							t_shell *shell);

// except
void					exe_all(char **command, t_env_token *list_env);
char					*search(char *object, char **command);

// utils_build
t_token					*new_env(t_token *list_env, char **env);
char					**obtain_env(t_env_token *list_env);
int						env_is_absolute(char **cmd);

char					*obtain_content(char *search, t_env_token *list_env);
void					change_content(t_env_token *list_env, char *oldcont,
							char *newcont);
//----------------------------------------------------------------------------//
//                                 pipex part
//----------------------------------------------------------------------------//
int						pipex_redirect(t_shell *shell, t_token *aux_token);
void					pipex_state(t_shell *shell);
void					select_pipex(t_shell *shell, int mode);
void					pipex(t_shell *shell);
void					big_pipex(t_shell *shell);
void					f_child(int *fd, int pid1, char **l_arraid,
							t_shell *shell);
void					s_child(int *fd, int pid2, char **l_arraid,
							t_shell *shell);
void					middle_child(int use_fd[4], t_token *list_aux, t_shell *shell, pid_t child_pids);
void					change_fd(int use_fd[4]);
char					**postline(t_shell *shell);
//---------------------waitpid-------------------------------------//
int						cont_pids(t_shell *shell);

// ENV
char					*get_env_value(const t_env_token *env, const char *key);
t_bool					env_list_add_back(t_env_token **head,
							t_env_token *new_env);
char					**split_env(char *env);
t_env_token				*new_env_token(char *content);
t_bool					create_list_env(char **env, t_env_token **list_env);
void					print_env(t_env_token *list_env, t_bool is_export);

// library
t_token					*ft_lstnew(void *content);
int						newcmp(const char *s1, const char *s2);
void					*ft_calloc(size_t count, size_t size);
void					ft_bzero(void *s, unsigned int n);
t_token					*ft_lstlast(t_token *lst);
char					*ft_strdup(char *src);
size_t					ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
char					**ft_split(char const *s, char c);
char					*ft_substr(char const *s, unsigned int start,
							size_t len);
void					ft_lstdelone(t_token *lst, void (*del)(void *));
int						ft_lstsize(t_env_token *lst);
char					*ft_strtrim(char const *s1, char const *set);
char					*ft_strjoin(char const *s1, char const *s2);
int						ft_atoi(const char *str);
char					*ft_itoa(int n);
int						ft_strrint(const char *s, int c);
char					*ft_strncpy(char *dst, const char *src, size_t len);
char					*ft_strduptrim(char *src);
int						ft_strcat(char *dest, const char *src);
int						ft_strcpy(char *dest, const char *src);
char					*ft_strndup(const char *s, size_t n);
int						ft_isalnum(int c);
int						ft_isalpha(int c);
int						lstsizetoken(t_token *lst);
uint64_t				is_string_in_array(const char *str, const char *arr[]);
int						ft_super_strcat(char **dest, const char *src);
char					**delete_string_on_array(char *arr[], int pos);
char					**insert_string_on_array(char *arr[], char *str,
							int pos);
t_bool					string_is_null_or_whitespace(const char *str);
t_bool					is_space(char c);

#endif
