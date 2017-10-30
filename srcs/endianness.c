/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianese.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 15:18:54 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 15:58:55 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		g_rev;

inline uint64_t		endian(uint64_t n, uint8_t size)
{
	if (g_rev)
	{
		if (size == 8)
			return (bswap_8(n));
		else if (size == 16)
			return (bswap_16(n));
		else if (size == 32)
			return (bswap_32(n));
		else if (size == 64)
			return (bswap_64(n));
		return (bswap_32(n));
	}
	return (n);
}
