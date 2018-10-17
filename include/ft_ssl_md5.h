/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/17 11:20:32 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/17 18:55:31 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include "externals_headers.h"
# include "libft.h"

typedef struct		s_md
{
	uint8_t			*str;
	uint64_t		md_lenght;
}					t_md;

typedef struct		s_h_values
{
	uint32_t	h0;
	uint32_t	h1;
	uint32_t	h2;
	uint32_t	h3;
}					t_h_values;

typedef struct		s_f_g_values
{
	uint32_t	f;
	uint32_t	g;
}					t_f_g_values;

t_f_g_values	calc_fg_i_16(uint32_t i, t_h_values v);
t_f_g_values	calc_fg_i_32(uint32_t i, t_h_values v);
t_f_g_values	calc_fg_i_48(uint32_t i, t_h_values v);
t_f_g_values	calc_fg_i_64(uint32_t i, t_h_values v);
char			*md5(char *message);
t_md			padding_md5(char const *message);
char			*h_values_hexstr(t_h_values v);

#endif
