
#ifndef MINISHELL_H

# define MINISHELL_H

//
# include <stdio.h>
//
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
	BUILT_IN
}						t_cmd_type;

typedef struct s_token
{
	char				*content;
	t_cmd_type			type;
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
	t_token *tokens;  // line
	t_env_token *env; // enviroment
}						t_shell;

//----------------------------------------------------------------------------//
//                                   PARSER                                   //
//----------------------------------------------------------------------------//
void					ft_init(char *line);

t_token					*create_token(char *content);
t_bool					add_token(t_token **head, char *content);
int						is_separator(const char *line, size_t *sep_len);
t_token					*tokenize_line(char *line, t_shell *shell);
t_quote					get_quote_type(t_quote quote_state, char c);
void					print_tokens(t_token *tokens);

void					main_loop(t_shell *shell);
void					use_build(char *line, t_token *list_env);
// void				use_unset(char **env, char *line);

// Builds
//  select
void					select_all(t_shell **shell);
void					select_build(t_shell **shell, char **line_arraid);

void					execute_command(char **line_arraid, t_token *list_env);

// redirect
void					foo_here_doc(char **line_arraid);
// expecific comand
void					use_unset(t_token **list_env, char **line_arraid);
void					use_pwd(void);
void					use_export(t_shell **shell, char **line_arraid);
void					use_echo(char **line_arraid);
void					use_cd(t_token **list_env, char **line_arraid);

// except
void					exe_all(char **command, t_token *list_env);

// utils
void					ft_free(char **lst);
void					ft_error(char *texto);
void					head(void);

// utils_build
t_token					*new_env(t_token *list_env, char **env);
char					**obtain_env(t_token *list_env);
// int					size_env(char *line_env);
int						env_is_absolute(char **cmd);

char					*obtain_content(char *search, t_token *list_env);
void					change_content(t_token **list_env, char *oldcont,
							char *newcont);
// pipex part
void					pipex(char **line_arraid, t_token *l_env);
void					f_child(int *fd, int pid1, char **l_arriad,
							t_token *l_env);
void					s_child(int *fd, int pid2, char **l_arraid,
							t_token *l_env);
// ENV
char					*get_env_value(const t_env_token *env, const char *key);
t_bool					env_list_add_back(t_env_token **head, t_env_token *new);
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
int						ft_lstsize(t_token *lst);
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

#endif
