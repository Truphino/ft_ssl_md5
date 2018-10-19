/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:56:53 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/19 13:07:29 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "errors.h"

void			no_command_error(char *p_name, char *message)
{
	(void)message;
	ft_putstr("usage: ");
	ft_putstr(p_name);
	ft_putstr(" command [command opts] [command args]\n");
}

void			invalid_command_error(char *p_name, char *message)
{
	ft_putstr(p_name);
	ft_putstr(": Error: \'");
	ft_putstr(message);
	ft_putstr("\' is an invalid command.\n");
}

static const	t_dispatch_error g_error_list[] =
{
	{NO_COMMAND, &no_command_error},
	{INVALID_COMMAND, &invalid_command_error}
};

static const size_t	g_num_errors = sizeof(g_error_list) / sizeof(t_dispatch_error);

void			print_error(t_errors_type er_type, char *p_name, char *message)
{
	size_t		i;

	i = 0;
	while (i < g_num_errors)
	{
		if (er_type == g_error_list[i].er_type)
			g_error_list[i].func_ptr(p_name, message);
		i++;
	}
}
