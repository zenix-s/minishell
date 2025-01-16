
#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <limits.h>


typedef struct s_token
{
	void			*content;
	struct s_token	*next;
}					t_token;

void	main_loop(char **env);
void	ft_init(char *line);

t_token	*ft_lstnew(void *content);
int		ft_strcmp(const char *s1, const char *s2);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, unsigned int n);
void	ft_lstadd_back(t_token **lst, t_token *new);
t_token	*ft_lstlast(t_token *lst);

#endif