/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 22:01:06 by serferna          #+#    #+#             */
/*   Updated: 2025/02/27 17:25:16 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H

# define ERRORS_H

# define ERR_UNEXPECTED_TOKEN "UnexpectedTokenError"
# define ERR_UNEXPECTED_TOKEN_NEWLINE \
	"syntax error near \
unexpected token `newline'" 
# define ERR_MALLOC "Memory allocation error"
# define ERR_CWD_NOT_FOUND "cd: error retrieving current directory: \
getcwd: cannot access parent directories:"

#endif
