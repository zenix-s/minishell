
#include "../include/minishell.h"

void	head(void)
{
	printf("\033[0;32m");
	printf("         .__         .__         .__             .__   .__   \n");
	printf("  _____  |__|  ____  |__|  ______|  |__    ____  |  |  |  |  \n");
	printf(" /     \\ |  | /    \\ |  | /  ___/");
	printf("|  |  \\ _/ __ \\ |  |  |  |  \n");
	printf("|  Y Y  \\|  ||   |  \\|  | \\___ \\ ");
	printf("|   Y  \\   ___/ |  |__|  |__\n");
	printf("|__|_|  /|__||___|  /|__|/____ / |___|  / \\___/  |____/|____/\n");
	printf("\033[0m");
	printf("                                by serferna and lortega-  ^_^ \n");
}

void	ft_free(char **lst)
{
	int	i;

	i = 0;
	while (lst[i])
		free(lst[i++]);
	free(lst);
}

void	ft_error(char *texto)
{
	perror(texto);
	exit(-1);
}
