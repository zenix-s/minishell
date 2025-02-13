
#include "../include/minishell.h"

char	**preline(t_shell **shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	aux = (*shell)->tokens;
	prev = aux;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0)
		{
			result = (ft_split(prev->content, ' '));
			return (result);
		}
		prev = aux;
		aux = aux->next;
	}
	return (NULL);
}

char	**postline(t_shell **shell)
{
	t_token	*aux;
	t_token	*prev;
	char	**result;

	aux = (*shell)->tokens;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0)
		{
			prev = aux->next;
			result = (ft_split(prev->content, ' '));
			return (result);
		}
		aux = aux->next;
	}
	return (NULL);
}

int	pre_line_int(t_shell **shell)
{
	t_token	*aux;

	aux = (*shell)->tokens;
	while (aux)
	{
		if (ft_strcmp(aux->next->content, "|") == 0)
			return (1);
		aux = aux->next;
	}
	return (-1);
}

int	post_line_int(t_shell **shell)
{
	t_token	*aux;

	aux = (*shell)->tokens;
	while (aux)
	{
		if (ft_strcmp(aux->content, "|") == 0 && aux->next != NULL)
			return (1);
		aux = aux->next;
	}
	return (-1);
}