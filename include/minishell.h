
#ifndef MINISHELL_H

# define MINISHELL_H

# include <limits.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_token
{
	char			*content;
	struct s_token	*next;
}					t_token;

typedef enum e_bool
{
	FALSE,
	TRUE
}					t_bool;

// Parser in the middle of the header
//----------------------------------------------------------------------------//
//                                   PARSER                                   //
//----------------------------------------------------------------------------//
void				ft_init(char *line);

t_token				*create_token(char *content);
t_token				*add_token(t_token **head, char *content);
int					is_separator(const char *line, size_t *sep_len);
t_token				*tokenize_line(char *line);

void				main_loop(t_token *list_env);
void				use_build(char *line, t_token *list_env);
// void				use_unset(char **env, char *line);

t_token				*new_env(t_token *list_env, char **env);
void				use_env(t_token *list_env);
void				use_pwd(t_token *list_env);

t_token				*ft_lstnew(void *content);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_calloc(size_t count, size_t size);
void				ft_bzero(void *s, unsigned int n);
void				ft_lstadd_back(t_token **lst, t_token *new);
t_token				*ft_lstlast(t_token *lst);
char				*ft_strdup(char *src);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strncpy(char *dst, const char *src, size_t len);
char				*ft_strduptrim(char *src);

#endif
