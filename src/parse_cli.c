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
	{MESSAGE_DIGEST, &md5, "md5", "MD5"},
	{MESSAGE_DIGEST, &sha256, "sha256", "SHA256"}
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

t_flag_warpper			parse_command_name(char *cmd_name)
{
	size_t				i;
	t_flag_warpper		fw;

	i = 0;
	fw.func_ptr = NULL;
	fw.flags = 0;
	while (i < g_num_commands)
	{
		if (ft_strcmp(cmd_name, g_command_list[i].cmd_name) == 0)
		{
			fw.func_ptr = g_command_list[i].func_ptr;
			fw.func_name = g_command_list[i].func_name;
		}
		i++;
	}
	return (fw);
}

unsigned char			flag_check(t_flag_warpper fw, unsigned char flag)
{
	return (fw.flags & flag);
}

t_flag_warpper			flag_set(t_flag_warpper fw, unsigned int flag)
{
	fw.flags = fw.flags | flag;
	return (fw);
}

void					print_description(char *func_name, t_hash_type type, char *mes)
{
	ft_putstr(func_name);
	ft_putstr(" (");
	if (type == STR)
		ft_putchar('"');
	ft_putstr(mes);
	if (type == STR)
		ft_putchar('"');
	ft_putstr(") = ");
}

t_flag_warpper			launch_fn_str(char *filename, t_flag_warpper fw, t_hash_type type)
{
	char				*md;

	if (type == FILENAME)
		md = hash_file(fw, filename);
	else
		md  = fw.func_ptr(filename);
	if (!md)
		exit(1);
	if (!flag_check(fw, FLAG_R) && !(flag_check(fw, FLAG_Q)))
		print_description(fw.func_name, type, filename);
	ft_putstr(md);
	if (!(flag_check(fw, FLAG_Q)) && flag_check(fw, FLAG_R))
	{
		ft_putchar(' ');
		if (type == STR)
			ft_putchar('"');
		ft_putstr(filename);
		if (type == STR)
			ft_putchar('"');
	}
	ft_putchar('\n');
	return (fw);
}

t_flag_warpper			launch_p(t_flag_warpper fw)
{
	char				*md;
	char				*str;

	if (!(flag_check(fw, ALRD_P)))
	{
		str = file_to_string(0);
		if ((md = fw.func_ptr(str)) == NULL)
			exit(1);
		ft_putstr(str);
		ft_putendl(md);
		fw = flag_set(fw, ALRD_P);
	}
	else
	{
		ft_putendl(fw.func_ptr(""));
	}
	return (fw);
}

int			process_arg(char *p_name, int argc, char **argv, t_flag_warpper *fw, int i)
{
	int					j;

	j = 0;
	while (argv[i][j])
	{
		if (argv[i][j] == 'q')
			*fw = flag_set(*fw, FLAG_Q);
		else if (argv[i][j] == 'r')
			*fw = flag_set(*fw, FLAG_R);
		else if (argv[i][j] == 'p')
			*fw = launch_p(*fw);
		else if (argv[i][j] == 's')
		{
			if (argv[i][j + 1])
			{
				launch_fn_str(argv[i] + j + 1, *fw, STR);
			}
			else
			{
				if (argv[i + 1])
					launch_fn_str(argv[i + 1], *fw, STR);
			}
		}
		j++;
	}
	return (i);
}

t_flag_warpper			parse_args(char *p_name, int argc, char **argv, t_flag_warpper fw)
{
	size_t				i;
	char				*md;

	i = 0;
	if (argc == 0)
	{
		if ((md = hash_file(fw, NULL)) != NULL)
			ft_putendl(md);
	}
	else
	{
		while (i < argc)
		{
			if (argv[i][0] == '-')
			{
				i = process_arg(p_name, argc, argv, &fw, i);		
			}
			else
			{
				launch_fn_str(argv[i], fw, FILENAME);
			}
			i++;
		}	
	}
	return (fw);
}

t_flag_warpper			parse_command_cli(char *p_name, int argc, char **argv)
{
	t_flag_warpper		t;
	size_t				i;
	char				*md;

	t = parse_command_name(argv[0]);
	if (t.func_ptr == NULL)
	{
		print_error(INVALID_COMMAND, p_name, argv[0]);
		print_command_list();
		exit(1);
	}
	/*if (argc > 1)
		md = hash_file(t, argv[1]);
	else
		md = hash_file(t, NULL);
	if (md)
		ft_putendl(md);*/
	t = parse_args(p_name, argc - 1, argv + 1, t);
	return (t);
}

t_flag_warpper			parse_no_command(char *p_name)
{
	char				*cli;
	char				**split;
	size_t				i;
	t_flag_warpper		t;
	char				*line;
	int					ret;

	i = 0;
	ret = get_next_line(0, &line);
	split = ft_strsplit(line, ' ');
	while (split[i] != NULL)
	{
		ft_putstr("====>");
		ft_putendl(split[i]);
		i++;
	}
	t = parse_command_cli(p_name, i, split);
	free_if((void **)&cli);
	free_null_terminated_tab((void **)split);
	return (t);
}

t_flag_warpper			parse_cli(int argc, char **argv)
{
	t_flag_warpper		fw;

	if (argc < 2)
		fw = parse_no_command(argv[0]);
	else
		fw = parse_command_cli(argv[0], argc - 1, argv + 1);

	return (fw);
}
