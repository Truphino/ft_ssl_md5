/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   h_values_hexstr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 17:58:09 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/18 14:44:01 by trecomps         ###   ########.fr       */
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
		tmp = (dec >> ((32 - i * 4))) & 0xF;
		if (tmp < 10)
			buf[i - 1] = '0' + tmp;
		else
			buf[i - 1] = 'a' + tmp - 10;
	}
}

char			*h_values_hexstr(uint32_t *v, uint32_t size)
{
	char		*md;
	uint32_t	i;

	i = 0;
	md = (char *)ft_memalloc(8 * size + 1);
	while (i < size)
	{
		printf("%x\n", v[i]);
		dec_to_hex(swap_uint32(v[i]), md + (i * 8));
		i++;
	}
	return (md);
}
