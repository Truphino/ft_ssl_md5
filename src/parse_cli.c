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
	{MESSAGE_DIGEST, &md5, "md5", "MD5", "usage: md5 [-pqr] [-s string] [files ...]"},
	{MESSAGE_DIGEST, &sha256, "sha256", "SHA256", "usage: sha256 [-pqr] [-s string] [files ...]"}
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

void				parse_command_name(char *cmd_name, t_flag_warpper *fw)
{
	size_t				i;

	i = 0;
	fw->func_ptr = NULL;
	fw->flags = 0;
	while (i < g_num_commands)
	{
		if (ft_strcmp(cmd_name, g_command_list[i].cmd_name) == 0)
		{
			fw->func_ptr = g_command_list[i].func_ptr;
			fw->func_name = g_command_list[i].func_name;
		}
		i++;
	}
}

unsigned char			flag_check(t_flag_warpper fw, unsigned char flag)
{
	return (fw.flags & flag);
}

t_flag_warpper			flag_set(t_flag_warpper *fw, unsigned int flag)
{
	fw->flags = fw->flags | flag;
	return (*fw);
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

void			launch_fn_str(char *filename, t_flag_warpper *fw, t_hash_type type)
{
	char				*md;

	flag_set(fw, LAUNCH);
	if (type == FILENAME)
		md = hash_file(*fw, filename);
	else
		md  = fw->func_ptr(filename);
	if (!md)
		exit(1);
	if (filename && !flag_check(*fw, FLAG_R) && !(flag_check(*fw, FLAG_Q)))
		print_description(fw->func_name, type, filename);
	ft_putstr(md);
	if (filename && !(flag_check(*fw, FLAG_Q)) && flag_check(*fw, FLAG_R))
	{
		ft_putchar(' ');
		if (type == STR)
			ft_putchar('"');
		ft_putstr(filename);
		if (type == STR)
			ft_putchar('"');
	}
	ft_putchar('\n');
}

void				launch_p(t_flag_warpper *fw)
{
	char				*md;
	char				*str;

	if (!(flag_check(*fw, ALRD_P)))
	{
		str = file_to_string(0);
		if ((md = fw->func_ptr(str)) == NULL)
			exit(1);
		ft_putstr(str);
		ft_putendl(md);
		flag_set(fw, ALRD_P);
	}
	else
	{
		ft_putendl(fw->func_ptr(""));
	}
}

void		print_usage(t_flag_warpper fw)
{
	int		i;

	i = 0;
	while (i < g_num_commands)
	{
		if (fw.func_ptr == g_command_list[i].func_ptr)
		{
			ft_putendl(g_command_list[i].func_usage);
		}
		i++;
	}
}

int			process_arg(int argc, char **argv, t_flag_warpper *fw, int i)
{
	int					j;

	j = 0;
	if (argv[i][j] == '-')
		j++;
	while (argv[i][j])
	{
		if (argv[i][j] == 'q')
			flag_set(fw, FLAG_Q);
		else if (argv[i][j] == 'r')
			flag_set(fw, FLAG_R);
		else if (argv[i][j] == 'p')
			launch_p(fw);
		else if (argv[i][j] == 's')
		{
			if (argv[i][j + 1])
			{
				launch_fn_str(argv[i] + j + 1, fw, STR);
			}
			else
			{
				if (argv[i + 1])
					launch_fn_str(argv[i + 1], fw, STR);
				i++;
			}
		}
		else
		{
			argv[i][j + 1] = '\0';
			print_error(ILLEGAL_OPTION, (*fw).p_name, &(argv[i][j]));
			print_usage(*fw);
			exit(1);
		}
		j++;
	}
	return (i);
}

void				parse_args(int argc, char **argv, t_flag_warpper *fw)
{
	size_t				i;
	char				*md;

	i = 0;
	if (argc == 0)
	{
		if ((md = hash_file(*fw, NULL)) != NULL)
		{
			ft_putendl(md);
			flag_set(fw, L_CMDL | LAUNCH);
		}
	}
	else
	{
		while (i < argc)
		{
			if (argv[i][0] == '-')
				i = process_arg(argc, argv, fw, i);		
			else
				launch_fn_str(argv[i], fw, FILENAME);
			i++;
		}	
	}
	if (!(flag_check(*fw, ALRD_P)) && !(flag_check(*fw, LAUNCH)))
	{
		launch_fn_str(NULL, fw, FILENAME);
	}
}

void				parse_command_cli(int argc, char **argv, t_flag_warpper *fw)
{
	size_t				i;
	char				*md;

	parse_command_name(argv[0], fw);
	if (fw->func_ptr == NULL)
	{
		print_error(INVALID_COMMAND, fw->p_name, argv[0]);
		print_command_list();
	}
	else
		parse_args(argc - 1, argv + 1, fw);
}

void			parse_no_command(t_flag_warpper *fw)
{
	char				**split;
	size_t				i;
	char				*line;
	int					ret;

	i = 0;
	ret = 1;
	while (ret && !flag_check(*fw, L_CMDL))
	{
		ft_putstr("ft_openssl => ");
		ret = get_next_line(0, &line);
		if (ret && line[0] != '\0')
		{
			split = ft_strsplit(line, ' ');
			while (split[i] != NULL)
				i++;
			parse_command_cli(i, split, fw);
			free_null_terminated_tab((void **)split);
		}
	}
}

t_flag_warpper			init_flag_warpper(char *p_name)
{
	t_flag_warpper		fw;

	fw.p_name = p_name;
	fw.func_ptr = NULL;
	fw.func_name = NULL;
	fw.flags = 0;
	return (fw);
}

t_flag_warpper			parse_cli(int argc, char **argv)
{
	t_flag_warpper		fw;

	fw = init_flag_warpper(argv[0]);
	if (argc < 2)
		parse_no_command(&fw);
	else
		parse_command_cli(argc - 1, argv + 1, &fw);

	return (fw);
}
