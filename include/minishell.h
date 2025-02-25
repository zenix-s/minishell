
#ifndef MINISHELL_H

# define MINISHELL_H

//
# include <stdio.h>
//
# include "state_machine.h"
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
}						t_token;

typedef struct s_env_token
{
	char				*key;
	char				*value;
	struct s_env_token	*next;
}						t_env_token;

typedef struct s_shell
{
	char				*input;
	t_token				*tokens;
	t_env_token			*env;
}						t_shell;

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
void					ft_init(char *line);
void					parse_line(t_shell *shell);
t_quote					get_quote_type(t_quote quote_state, char c);
void					print_tokens(t_token *tokens);
void					free_tokens(t_token *tokens);
char					*echo_parser(char *line);

void					main_loop(t_shell *shell);
void					use_build(char *line, t_token *list_env);
void					head(void);
// void				use_unset(char **env, char *line);

// Builds
//  select
void					select_all(t_shell **shell);
int						select_build(t_shell **shell, char **line_arraid);
void					execute_command(char **line_arraid, t_env_token *list_env);

//----------------------------------------------------------------------------//
//                                Redirect
//----------------------------------------------------------------------------//
void					her_d(char **line_arraid, t_token *env_aux, t_shell **aux, int mode);
void					stnd_out(t_token *env_aux, t_shell **aux, int mode);
void					stnd_in(t_token *env_aux, t_shell **aux, int mode);
//expecific comand
void				use_unset(t_shell **shell, char **line_arraid);
void				use_pwd(void);
void				use_export(t_shell **shell, char **line_arraid);
void				use_echo(char **line_arraid);
void				use_cd(t_env_token **l_env, char **line_arraid, t_shell **shell);

// except
void					exe_all(char **command, t_env_token *list_env);

// utils_build
t_token					*new_env(t_token *list_env, char **env);
char					**obtain_env(t_env_token *list_env);
int						env_is_absolute(char **cmd);

char					*obtain_content(char *search, t_env_token *list_env);
void					change_content(t_env_token **list_env, char *oldcont,
							char *newcont);
//----------------------------------------------------------------------------//
//                                 pipex part
//----------------------------------------------------------------------------//
void					select_pipex(t_shell **shell, int mode);
void					pipex(t_shell **shell);
void					big_pipex(t_shell **shell);
void					f_child(int *fd, int pid1, char **l_arraid,
							t_shell **shell);
void					s_child(int *fd, int pid2, char **l_arraid,
							t_shell **shell);
char					**preline(t_shell **shell);
char					**postline(t_shell **shell);
int						pre_line_int(t_shell **shell);
int						post_line_int(t_shell **shell);

// ENV
char					*get_env_value(const t_env_token *env, const char *key);
t_bool					env_list_add_back(t_env_token **head,
							t_env_token *new_env);
char					**split_env(char *env);
t_env_token				*new_env_token(char *content);
t_bool					create_list_env(char **env, t_env_token **list_env);
void					print_env(t_env_token *list_env);

// library
t_token					*ft_lstnew(void *content);
int						ft_strcmp(const char *s1, const char *s2);
void					*ft_calloc(size_t count, size_t size);
void					ft_bzero(void *s, unsigned int n);
void					ft_lstadd_back(t_token **lst, t_token *new);
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
int				    	lstsizetoken(t_token *lst);

#endif
