/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/12 16:02:56 by trecomps          #+#    #+#             */
/*   Updated: 2018/01/22 12:34:35 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dst, char *src, size_t size)
{
	char	*d;
	char	*s;
	int		n;
	int		dest_length;

	d = dst;
	s = src;
	n = size;
	while (*d != '\0' && n-- != 0)
		d++;
	dest_length = d - dst;
	n = size - dest_length;
	if (n == 0)
		return (dest_length + ft_strlen(s));
	while (*s != '\0')
	{
		if (n != 1)
		{
			*d++ = *s;
			n--;
		}
		s++;
	}
	*d = '\0';
	return (dest_length + (s - src));
}
