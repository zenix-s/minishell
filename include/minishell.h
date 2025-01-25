
#ifndef MINISHELL_H

# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <sys/wait.h>

# define READ_END	0
# define WRITE_END	1
#define MAX_INPUT_LENGTH 1024

typedef struct s_token
{
	void			*content;
	struct s_token	*next;
}					t_token;

//EnvStruckt
//  head
typedef struct s_env
{
	void			*data;
	struct s_env	*next;
}					t_env;

//  data
typedef struct s_data
{
	char			*key;
	char			*value;
}					t_data;

//not today
void				ft_init(char *line);

//commond ()
void				main_loop(t_token *list_env);

//Builds 
//  select
void				select_build(char *line, t_token *list_env);
void				execute_comman(char **line_arraid, t_token *list_env);

//expecific comand
void				use_unset(t_token **list_env, char **line_arraid);
void				use_env(t_token *list_env);
void				use_pwd(t_token *list_env);
void				use_export(t_token **list_env, char **line_arraid);
void				use_echo(t_token *list_env, char **line_arraid);
void				use_cd(t_token **list_env, char **line_arraid);

//except
void				exe_all(char **command, t_token *list_env);

//utils
void				ft_free(char **lst);
void				ft_error(char *texto);
void				head(void);

//utils_build
t_token				*new_env(t_token *list_env, char **env);
char				**obtain_env(t_token *list_env);
int					size_env(char *line_env);
int					env_is_absolute(char **cmd);

//pipex part
void				pipex(char **line_arraid, t_token *list_env);
void				first_children(int *fd, int pid1, char **arriad, t_token list_env);

//library
t_token				*ft_lstnew(void *content);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, unsigned int n);
void				ft_lstadd_back(t_token **lst, t_token *new);
t_token				*ft_lstlast(t_token *lst);
char				*ft_strdup(char *src);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_substr(char const *s, unsigned int start, size_t len);
void				ft_lstdelone(t_token *lst, void (*del)(void*));
int					ft_lstsize(t_token *lst);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strjoin(char const *s1, char const *s2);

#endif
