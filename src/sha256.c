/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sha256.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:46:52 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/18 11:39:45 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static void		init_h_values(uint32_t v[8])
{
	v[0] = 0x6a09e667;
	v[1] = 0xbb67ae85;
	v[2] = 0x3c6ef372;
	v[3] = 0xa54ff53a;
	v[4] = 0x510e527f;
	v[5] = 0x9b05688c;
	v[6] = 0x1f83d9ab;
	v[7] = 0x5be0cd19;
}

void			sha256_main_loop(uint32_t *chunk, uint32_t v[8])
{
	uint32_t	i;
	uint32_t	temp1;
	uint32_t	temp2;
}

char			*sha256(char *message)
{
	t_md		md;
	uint32_t	v[8];
	uint32_t	*chunk;
	uint32_t	offset;
	uint32_t	temp[8];

	md = padding_md5_sha2(message);
	init_h_values(v);
	offset = 0;
	while (offset < md.md_lenght)
	{
		chunk = (uint32_t *)(md.str + offset);
		ft_memcpy(temp, v, 8 * sizeof(uint32_t));
		sha256_main_loop(chunk, temp);
		add_tab_values(v, temp, 8);
		offset += 512 / 8;
	}
	return (h_values_hexstr(v, 8));
}
