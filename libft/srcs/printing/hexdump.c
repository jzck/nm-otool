/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/07 17:56:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 11:25:51 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static void	print_hex_contents(void *addr, uint64_t size)
{
	void	*a;

	a = addr;
	while (a - addr < 16)
	{
		if ((uint64_t)(a - addr) >= size)
			break ;
		else
			ft_printf("%02x", *(unsigned char*)a);
		ft_putchar(' ');
		a++;
	}
}

void		*hexdump(void *addr, uint32_t offset, uint32_t size)
{
	void	*a;

	/* addr += offset; */
	a = addr;
	if (addr == NULL)
		return (addr);
	while ((uint32_t)(a - addr) < size)
	{
		ft_printf("%08llx\t", (a - addr) + offset);
		print_hex_contents(a, (uint64_t)(size - (a - addr)));
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}

void		*hexdump_64(void *addr, uint64_t offset, uint64_t size)
{
	void	*a;

	/* addr += offset; */
	a = addr;
	if (addr == NULL)
		return (addr);
	while ((uint64_t)(a - addr) < size)
	{
		ft_printf("%016llx\t", (a - addr) + offset);
		print_hex_contents(a, (size - (a - addr)));
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}
