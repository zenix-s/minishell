/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:01:06 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 17:25:16 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H

# define STRUCTS_H

# include <stdint.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum e_quote
{
	NONE,
	DOUBLE,
	SINGLE
}						t_quote;

typedef enum e_cmd_type
{
	BUILT_IN,
	REDIRECT,
	PIPE,
	EXE
}						t_cmd_type;

typedef enum e_built_in_type
{
	UNDEFINED,
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}						t_built_in_type;

typedef struct s_token
{
	char				*content;
	t_cmd_type			type;
	t_built_in_type		built_in;
	struct s_token		*next;
	struct s_token		*prev;
}						t_token;

typedef struct s_env_token
{
	char				*key;
	char				*value;
	struct s_env_token	*next;
}						t_env_token;

typedef struct s_shell
{
	t_bool				is_done;
	void				(*execute)(struct s_shell *);
	char				*input;
	t_token				*tokens;
	t_env_token			*env;
	char				**pending_inputs;
	t_bool				is_here_doc;
	int					exit_status;
	char				*read;
	char				*write;
	int					mode;
	int					n_pipex;
	char				**heredoc_files;
	char				*error_message;
	char				*unexpected_token;
	t_bool				exit_of_failure;
}						t_shell;

typedef struct s_splitter
{
	char				**result;
	uint64_t			result_idx;
	int64_t				start;
	t_quote				q_state;
	int64_t				i;
}						t_splitter;

#endif
