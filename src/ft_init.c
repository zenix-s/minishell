
#include "../include/minishell.h"

void	ft_init(char *line)
{
    t_token *token;
    t_token *tokenaux = NULL;
	char	*aux;
	int	    cont;
	int	    auxcont;

	cont = 0;
	auxcont = 0;
    aux = calloc(1, sizeof(char ));
	while(line[cont])
	{
	    aux[auxcont] = line[cont];
	    cont++;
	    auxcont++;
	    if (line[cont] == ' ' || line[cont] == '\0')
		    {
                if (token)
                {
                    ft_lstnew(tokenaux);
                    ft_lstadd_back(&token, tokenaux);
                }
                if (!token)
                    token = ft_lstnew(aux);
			    cont++;
			    printf("%s\n", aux);
			    auxcont = 0;
                aux = calloc(1, sizeof(char ));
		    }
	    }
        free(aux);
}
