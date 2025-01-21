
#ifndef MINISHELL_H

# define MINISHELL_H

# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_token
{
	void			*content;
	struct s_token	*next;
}					t_token;


void				ft_init(char *line);

void				main_loop(t_token *list_env);
void				use_build(char *line, t_token *list_env);
void				use_unset(t_token **list_env, char **line_arraid);
t_token				*new_env(t_token *list_env, char **env);
int					size_env(char *line_env);
void				use_env(t_token *list_env);
void				use_pwd(t_token *list_env);
void				use_export(t_token **list_env, char **line_arraid);
void				use_echo(t_token *list_env, char **line_arraid);
void				exe(char *line, t_token *list_env);
void				exe(char *command, t_token *list_env);


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
