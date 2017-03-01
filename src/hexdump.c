/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:14:33 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/01 15:37:46 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static void	print_hex_contents(void *addr, unsigned int size)
{
	void	*a;

	a = addr;
	while (a - addr < 16)
	{
		if ((a - addr) >= size)
			break ;
		else
			ft_printf("%02x", *(unsigned char*)a);
		ft_putchar(' ');
		a++;
	}
}

void	*hexdump(void *addr, unsigned int offset, unsigned int size)
{
	void	*a;

	addr += offset;
	a = addr;
	if (addr == NULL)
		return (addr);
	while ((a - addr) < size)
	{
		ft_printf("%0*llx\t", 16, (a - addr) + (unsigned long)offset);
		print_hex_contents(a, (size - (a - addr)));
		ft_putchar('\n');
		a += 16;
	}
	return (addr);
}
