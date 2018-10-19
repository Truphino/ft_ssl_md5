/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_warpper.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trecomps <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 16:14:18 by trecomps          #+#    #+#             */
/*   Updated: 2018/10/19 10:07:24 by trecomps         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAG_WARPPER_H
# define FLAG_WARPPER_H

# define			FLAG_P 1 << 0
# define			FLAG_Q 1 << 1
# define			FLAG_R 1 << 2
# define			FLAG_S 1 << 3

typedef struct		s_flag_warpper
{
	char			*(*func_ptr)(char *);
	unsigned char	flags;
}					t_flag_warpper;

#endif
