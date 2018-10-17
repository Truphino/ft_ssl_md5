/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 19:39:51 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/17 19:55:19 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

static const uint32_t r[] = {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
	5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
	4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
	6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static const uint32_t k[] = {
	0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
	0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
	0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
	0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
	0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
	0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
	0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
	0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
	0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
	0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
	0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
	0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
	0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
	0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
	0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
	0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

static t_h_values	add_h_values(t_h_values a, t_h_values b)
{
	a.h0 += b.h0;
	a.h1 += b.h1;
	a.h2 += b.h2;
	a.h3 += b.h3;
	return (a);
}

static t_h_values	init_h_values(void)
{
	t_h_values		v;

	v.h0 = 0x67452301;
	v.h1 = 0xefcdab89;
	v.h2 = 0x98badcfe;
	v.h3 = 0x10325476;
	return (v);
}

static uint32_t		circle_leftrotate(uint32_t x, uint32_t c)
{
	return ((x << c) | (x >> (32 - c)));
}

t_h_values	md5_main_loop(uint32_t *chunk, t_h_values v)
{
	uint32_t		i;
	t_f_g_values	val;
	uint32_t		temp;

	i = 0;
	while (i < 64)
	{
		if (i < 16)
			val = calc_fg_i_16(i, v);
		else if (i < 32)
			val = calc_fg_i_32(i, v);
		else if (i < 48)
			val = calc_fg_i_48(i, v);
		else
			val = calc_fg_i_64(i, v);
		temp = v.h3;
		v.h3 = v.h2;
		v.h1 = v.h1 + circle_leftrotate(v.h0 + val.f + k[i] + chunk[val.g],
											r[i]);
		v.h0 = temp;
		i++;
	}
	return (v);
}

char		*md5(char *message)
{
	t_md		md;
	int			offset;
	uint32_t	*chunk;
	t_h_values	v;

	md = padding_md5(message);
	v = init_h_values();
	offset = 0;
	while (offset < md.md_lenght)
	{
		chunk = (uint32_t *)(md.str + offset);
		v = add_h_values(md5_main_loop(chunk, v), v);
		offset += 512 / 8;
	}
	return (h_values_hexstr(v));
}
