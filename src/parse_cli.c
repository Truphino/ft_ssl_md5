/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cli.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/19 11:52:27 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/19 13:08:15 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parse_cli.h"
#include "errors.h"
#include "ft_ssl_md5.h"

static const			t_command g_command_list[] =
{
	{MESSAGE_DIGEST, &md5, "md5"},
	{MESSAGE_DIGEST, &sha256, "sha256"}
};

static const size_t			g_num_commands = sizeof(g_command_list) / sizeof(t_command);

static void					print_command_type(t_command_type cmd_type)
{
	ft_putchar('\n');
	if (cmd_type == STANDARD)
		ft_putstr("Standard");
	else if (cmd_type == MESSAGE_DIGEST)
		ft_putstr("Message Digest");
	else if (cmd_type == CIPHER)
		ft_putstr("Cipher");
	else
		ft_putstr("ERROR");
	ft_putendl(" commands:");
}

static void				print_command_list_type(t_command_type cmd_type)
{
	size_t				i;

	i = 0;
	print_command_type(cmd_type);
	while (i < g_num_commands)
	{
		if (cmd_type == g_command_list[i].cmd_type)
			ft_putendl(g_command_list[i].cmd_name);
		i++;
	}
}

void					print_command_list(void)
{
	size_t				i;

	i = 0;
	print_command_list_type(STANDARD);
	print_command_list_type(MESSAGE_DIGEST);
	print_command_list_type(CIPHER);
}

t_flag_warpper			parse_cli(int argc, char **argv)
{
	t_flag_warpper		t;

	if (argc < 2)
		print_error(NO_COMMAND, argv[0], NULL);
	else
	{
		print_error(INVALID_COMMAND, argv[0], argv[1]);
		print_command_list();
	}
	t.func_ptr = &md5;
	t.flags = 0;
	return (t);
}
