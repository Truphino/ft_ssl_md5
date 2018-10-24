/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:57:27 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/19 12:25:22 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

#include "libft.h"
#include <errno.h>

typedef enum		e_errors_type
{
	NO_COMMAND,
	INVALID_COMMAND,
}					t_errors_type;

typedef struct		s_dispatch_error
{
	t_errors_type	er_type;
	void			(*func_ptr)(char *p_name, char* message);
}					t_dispatch_error;

void				print_error(t_errors_type er_type, char *p_name, char *mes);

#endif
