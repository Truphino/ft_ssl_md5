/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:34:37 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/18 11:38:28 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint32_t		circle_leftrotate(uint32_t x, uint32_t c)
{
	return ((x << c) | (x >> (32 - c)));
}

void			add_tab_values(uint32_t *a, uint32_t *b, uint32_t size)
{
	uint32_t		i;

	i = 0;
	while (i < size)
	{
		a[i] += b[i];
		i++;
	}
}
