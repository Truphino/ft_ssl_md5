/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_fg_values.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 16:28:06 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/17 17:13:41 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md5.h"

t_f_g_values		calc_fg_i_16(uint32_t i, t_h_values v)
{
	t_f_g_values	val;

	if (i < 16)
	{
		val.f = (v.h1 & v.h2) | ((~v.h1) & v.h3);
		val.g = i;
	}
	else
	{
		val.f = 0;
		val.g = 0;
	}
	return (val);
}

t_f_g_values		calc_fg_i_32(uint32_t i, t_h_values v)
{
	t_f_g_values	val;

	if (i < 32)
	{
		val.f = (v.h3 & v.h1) | ((~v.h3) & v.h2);
		val.g = (5*i + 1) % 16;
	}
	else
	{
		val.f = 0;
		val.g = 0;
	}
	return (val);
}

t_f_g_values		calc_fg_i_48(uint32_t i, t_h_values v)
{
	t_f_g_values	val;

	if (i < 48)
	{
		val.f = v.h1 ^ v.h2 ^ v.h3;
		val.g = (3*i + 5) % 16;
	}
	else
	{
		val.f = 0;
		val.g = 0;
	}
	return (val);
}

t_f_g_values		calc_fg_i_64(uint32_t i, t_h_values v)
{
	t_f_g_values	val;

	if (i < 64)
	{
		val.f = v.h2 ^ (v.h1 | (~v.h3));
		val.g = (7*i) % 16;
	}
	else
	{
		val.f = 0;
		val.g = 0;
	}
	return (val);
}
