/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:01:06 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 17:25:16 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H

# define MINISHELL_H

# include <stdio.h>
# include "errors.h"
# include "libft.h"
# include "structs.h"
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdint.h>
# include <stdlib.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# include <stdlib.h>
# include <dirent.h>

# define READ_END 0
# define WRITE_END 1
# define MAX_INPUT_LENGTH 1024

//----------------------------------------------------------------------------//
//                                    SHELL
//----------------------------------------------------------------------------//
t_shell		*shell_factory(char **env);

//----------------------------------------------------------------------------//
//									CLEAN
//----------------------------------------------------------------------------//
void		free_tokens(t_token *tokens);
void		free_env_tokens(t_env_token *env);
void		free_shell(t_shell *shell);
void		ft_free(char **lst);
void		ft_error(char *texto);
void		ft_pipe(int fd[2], char *text);

//----------------------------------------------------------------------------//
//                                   PARSER
//----------------------------------------------------------------------------//
void		segurity_state(t_shell *shell);
int			get_quote_type(t_quote quote_state, char c);
void		print_tokens(t_token *tokens);
void		free_tokens(t_token *tokens);
void		main_loop(t_shell *shell);
void		head(void);
void		parser_end_state(t_shell *shell);
int			count_tokens(char *input, const char **split, const char **s_split);
char		**special_split(char *input, const char **split,
				const char **s_split);
u_int64_t	is_string_redirect(const char *str);
u_int64_t	is_string_pipe(const char *str);
uint64_t	is_special_token(const char *str);
char		*remove_outer_quotes(char *str);
t_bool		add_quotes(char *value, char **new_value);

//----------------------------------------------------------------------------//
//                               signal
//----------------------------------------------------------------------------//
void		init_sigaction(void);
void		set_sigaction_for_child(void);
void		set_signal_interactive_child(void);
void		set_signal_for_heredoc(void);

//----------------------------------------------------------------------------//
//                                state
//----------------------------------------------------------------------------//
void		readline_state(t_shell *shell);
t_bool		is_valid_input(t_shell *shell);
void		clean_end_state(t_shell *shell);
void		error_state(int mod);
void		fail_state(t_shell *shell);
void		exit_state(t_shell *shell);
void		create_files_state(t_shell *shell);
void		select_all(t_shell *shell);
int			s_build(t_shell *shell, char **line_arraid);
void		execute_cmd(char **l_arraid, t_env_token *list_env);
void		check_redirect_error_state(t_shell *shell);

//----------------------------------------------------------------------------//
//                                Redirect
//----------------------------------------------------------------------------//
void		redirect_state(t_shell *shell);
int			prepare(t_shell *shell, t_token *aux_token);
int			ft_read_open(t_token *aux_token, t_shell *shell);
int			ft_write_open(t_token *aux_token, t_shell *shell, char *name);
int			ft_open(t_shell *shell, int file, char *name, int mode);
void		all_heredoc(t_shell *shell);
void		stnd_out(t_token *env_aux, t_shell *aux, int mode);
int			stnd_in(t_token *env_aux, t_shell *aux, int mode);
int			new_stnd_in(t_shell *shell);
void		read_alone(t_shell *shell, char **cmd);
void		write_alone(t_shell *shell, char **cmd);
int			new_open(t_shell *shell);
void		full_redirect(t_shell *shell, char **cmd);
void		redirect_error(t_token *list, int mode);
char		*generate_here_doc_file_name(int64_t n_pipe);

// expecific comand
void		use_unset(t_shell *shell, char **line_arraid);
void		use_pwd(char **line_arraid);
void		use_exit(t_shell *shell, char **line_arraid);
void		use_export(t_shell **shell, char **line_arraid, int count);
void		use_echo(char **line_arraid);
void		use_cd(t_env_token *l_env, char **line_arraid, t_shell *shell);
void		use_env(t_env_token *list_env, char **line_arraid,
				t_bool is_export);

// except
void		exe_all(char **command, t_env_token *list_env);
char		*search(char *object, char **command);

// utils_build
char		**obtain_env(t_env_token *list_env);
int			env_is_absolute(char **cmd, char **env_now);
char		*obtain_content(char *search, t_env_token *list_env);
void		change_content(t_env_token *list_env, char *oldcont, char *newcont);
int			verify_backwards_rute(char *line_arraid);
void		go_back(char **steps);
int			use_slash(char **big_arraid, char *line_arraid);
int			create_new_rute(char *rute, char *step);
//----------------------------------------------------------------------------//
//                                 pipex part
//----------------------------------------------------------------------------//
int			pipex_redirect(t_shell *shell, t_token *aux_token);
void		pipex_state(t_shell *shell);
void		select_pipex(t_shell *shell, int mode);
void		pipex(t_shell *shell);
void		big_pipex(t_shell *shell);
void		f_child(int *fd, int pid1, char **l_arraid, t_shell *shell);
void		s_child(int *fd, int pid2, char **l_arraid, t_shell *shell);
void		m_child(int use_fd[4], t_token *t_aux, t_shell *shell,
				pid_t child_pids);
void		change_fd(int use_fd[4]);
int			contpipex(t_token *list_aux);
t_token		*next_pipex(t_token *list_token);
t_token		*prepare_next_time(t_token *token_aux, int aux[2], int fd[2]);
void		ft_waitpid(t_token *token_aux, pid_t *child_pids);
char		**postline(t_shell *shell);

//---------------------waitpid-------------------------------------//
void		ft_status(int status);
char		*get_env_value(const t_env_token *env, const char *key);
t_bool		env_list_add_back(t_env_token **head, t_env_token *new_env);
char		**split_env(char *env);
t_env_token	*new_env_token(char *content);
t_bool		create_list_env(char **env, t_env_token **list_env);
void		print_env(t_env_token *list_env, t_bool is_export);
t_bool		is_valid_env_key(char *key);

//--------------------------------g_global-------------------------//
extern int	g_exit_status;

#endif
