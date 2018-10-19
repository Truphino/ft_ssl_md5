/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 11:22:38 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/19 12:27:59 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"
#include "parse_cli.h"

int			main(int argc, char **argv)
{
	int				fd;
	t_flag_warpper	fw;

	fw.func_ptr = &(md5);
	//ft_putendl(hash_file(fw, FILE_COMMAND_LINE));
	//ft_putendl(hash_file(fw, "hash_test.txt"));
	fw = parse_cli(argc, argv);
}
