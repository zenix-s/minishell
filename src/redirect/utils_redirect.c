
#include "../../include/minishell.h"

int	little_redirect(t_shell *shell)
{
	t_token	*env_aux;
	int		mod;

	env_aux = shell->tokens;
	mod = follow_mode(env_aux);
	if (mod == 1 || mod == 5)
		her_d(ft_split(env_aux->next->next->content, ' '), env_aux, shell, mod);
	if (mod == 2 || mod == 3)
		stnd_out(env_aux, shell, mod);
	if (mod == 4)
		stnd_in(env_aux, shell, mod);
	return (mod);
}

int	finish_redirect(t_shell *shell, t_token *aux_shell)
{
	t_token	*env_aux;
	int		mod;

	env_aux = aux_shell;
	mod = follow_mode(env_aux);
	if (mod == 1 || mod == 5)
		her_d(ft_split(env_aux->next->next->content, ' '), env_aux, shell, mod);
	if (mod == 2 || mod == 3)
		stnd_out(env_aux, shell, mod);
	if (mod == 4)
		stnd_in(env_aux, shell, mod);
	return (mod);
}