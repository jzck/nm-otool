/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump_int.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:57:21 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:59:57 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static void	print_hex_contents(void *addr, uint64_t size, int swap)
{
	void	*a;

	a = addr;
	while (a - addr < 16)
	{
		if ((uint64_t)(a - addr) >= size)
			break ;
		else if (swap)
			ft_printf("%08x", bswap_32(*(uint64_t*)a));
		else
			ft_printf("%08x", *(uint64_t*)a);
		ft_putchar(' ');
		a += 4;
	}
}

void		*hexdump_int(void *addr, uint32_t offset, uint32_t size, int swap)
{
	void	*a;

	a = addr;
	if (addr == NULL)
		return (addr);
	while ((uint32_t)(a - addr) < size)
	{
		ft_printf("%08llx\t", (a - addr) + offset);
		print_hex_contents(a, (size - (a - addr)), swap);
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}

void		*hexdump_64_int(void *addr, uint64_t offset, uint64_t size,
		int swap)
{
	void	*a;

	a = addr;
	if (addr == NULL)
		return (addr);
	while ((uint64_t)(a - addr) < size)
	{
		ft_printf("%016llx\t", (a - addr) + offset);
		print_hex_contents(a, (size - (a - addr)), swap);
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}
