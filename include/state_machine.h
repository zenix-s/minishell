/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: serferna <serferna@student.42madrid.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 11:13:15 by serferna          #+#    #+#             */
/*   Updated: 2025/01/26 11:13:15 by serferna         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STATE_MACHINE_H

# define STATE_MACHINE_H

# include <stdlib.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}				t_bool;

typedef struct s_state_machine
{
	t_bool		is_done;
	void		*context;
	void		(*execute)(struct s_state_machine *);
}				t_state_machine;

t_state_machine	*create_state_machine(void);

#endif
