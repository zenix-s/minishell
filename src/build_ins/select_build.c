
#include "../../include/minishell.h"

/*
void	first_children(int *fd, int pid1, char **arriad, t_token list_env)
{
	int	texto;

	if (pid < 0)
		ft_error("fork:");
	if (pid1 == 0)
	{
		close(fd[READ_END]);
		texto = ft_open(argv[1], 1);


	}
}
*/

/**
 @ fd[2] ->contiene dos enteros ( READ_END and WRITE_END)
 @ pidx  ->almacena identificadores de proceso PID
*/
/*
void	pipex(char **line_arraid, t_token *list_env)
{
	int		fd[2];
	pid_t	pid1;
	pid_t	pid2;

	if (pipe(fd) == -1)
		ft_error("pipe");
	pid1 = fork();
	ft_first_children(fd, pid1, argv, envp);
	pid2 = fork();
	//ft_second_children(fd, pid2, argv, envp);
	close(fd[READ_END]);
	close(fd[WRITE_END]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	//exit(1);
	exe(line_arraid[0], list_env);
}
*/

/*
*used to parse a command line and execute the corresponding built-in function.
*"echo", "pwd", "export", "unset", "env", and "exit" commands.
*it attempts to execute the command as an external program.
*/

void	execute_command(char **line_arraid, t_token *list_env)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("fork failed");
		return ;
	}
	if (pid == 0)
		exe_all(line_arraid, list_env);
	else
		waitpid(pid, NULL, 0);
}


void	select_build(char *line, t_token *list_env)
{
	char	**line_arraid;

	line_arraid = ft_split(line, ' ');
	if (line && ft_strcmp(line_arraid[0], "echo") == 0)
		use_echo(list_env, line_arraid);
	if (line && ft_strcmp(line, "cd") == 0)
		use_cd(&list_env, line_arraid);
	else if (line && ft_strcmp(line_arraid[0], "pwd") == 0)
		use_pwd(list_env);
	else if (line && ft_strcmp(line_arraid[0], "export") == 0)
	{
		if (!line_arraid[1])
			use_env(list_env);
		else
			use_export(&list_env, line_arraid);
	}
	else if (line && ft_strcmp(line_arraid[0], "unset") == 0)
		use_unset(&list_env, line_arraid);
	else if (line && ft_strcmp(line_arraid[0], "env") == 0)
		use_env(list_env);
	else if (line && ft_strcmp(line_arraid[0], "exit") == 0)
		exit(0); //no sea tan facil...
	else
		execute_command(line_arraid, list_env);
	ft_free(line_arraid);
}


//TO DO

// crear la lista de funciones de sistema (?) distinta al env cuando se usa export A (sin igual)