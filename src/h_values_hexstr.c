/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_values_hexstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:58:09 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/17 19:22:34 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

void		dec_to_hex(uint32_t dec, char *buf)
{
	unsigned int	i;
	unsigned int	tmp;

	i = 0;
	while (++i <= 32 / 4)
	{
		tmp = (dec >> ((i * 4))) & 0xF;
		if (tmp < 10)
			buf[i - 1] = '0' + tmp;
		else
			buf[i - 1] = 'a' + tmp - 10;
	}
}

char		*h_values_hexstr(t_h_values v)
{
	char	*md;

	md = (char *)ft_memalloc(33);
	dec_to_hex(v.h0, md + 0);
	dec_to_hex(v.h1, md + 8);
	dec_to_hex(v.h2, md + 16);
	dec_to_hex(v.h3, md + 24);
	return (md);
}
