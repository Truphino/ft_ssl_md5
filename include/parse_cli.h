/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cli.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:53:25 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/19 12:47:26 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_CLI_H
# define PARSE_CLI_H

# include "flag_warpper.h"

typedef enum			e_command_type
{
	STANDARD,
	MESSAGE_DIGEST,
	CIPHER,
}						t_command_type;

typedef struct			e_commands
{
	t_command_type		cmd_type;
	char				*(*func_ptr)(char *message);
	char				*cmd_name;
}						t_command;

t_flag_warpper			parse_cli(int argc, char **argv);

#endif
