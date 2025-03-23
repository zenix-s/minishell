/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"

typedef struct s_parse_state
{
	char		*input;
	char		**split_input;
	int64_t		i;
	int64_t		first;
	t_bool		is_first;
	t_bool		is_next_redirect;
}				t_parse_state;

typedef struct s_expand_env_state
{
	uint64_t	len;
	char		*var_name;
	char		*value;
	uint64_t	start;
	char		new_content[1024];
	uint64_t	i;
	int			quote;
	t_bool		idiot;
}				t_expand_env_state;

t_token			*create_token(char *content);
t_bool			add_token(t_token **head, char *content);
int				is_separator(const char *line, size_t *sep_len);

void			tokenize_state(t_shell *shell);
void			expand_env_state(t_shell *shell);
void			trim_nodes_state(t_shell *shell);
void			assign_type_state(t_shell *shell);

char			*get_var_name(const char *content, uint64_t *start);
uint64_t		expand_variale(char *new_content, uint64_t i,
					const char *value);
t_bool			pre_process_input(t_parse_state *state);
t_bool			is_valid_init_char(char c);

#endif
