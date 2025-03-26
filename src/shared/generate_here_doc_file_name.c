/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generate_here_doc_file_name.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*generate_here_doc_file_name(int64_t n_pipe)
{
	char	*file_name;
	char	*n_pipestr;

	file_name = ft_strdup("hdocfilesave000");
	n_pipestr = ft_itoa(n_pipe);
	ft_super_strcat(&file_name, n_pipestr);
	ft_super_strcat(&file_name, ".log");
	free(n_pipestr);
	return (file_name);
}
