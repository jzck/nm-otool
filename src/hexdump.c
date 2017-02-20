/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hexdump.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 15:14:33 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/20 15:47:08 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	ft_putnbr_base16(int nbr, int format)
{
	int		base_size;
	int		i;
	int		result[100];

	base_size = 16;
	i = 0;
	if (base_size > 1)
	{
		if (nbr < 0)
		{
			ft_putchar('-');
			nbr = -nbr;
		}
		while (nbr)
		{
			result[i] = nbr % base_size;
			nbr = nbr / base_size;
			i++;
		}
		while (format-- > i)
			ft_putchar('0');
		while (--i >= 0)
			ft_putchar("0123456789abcdef"[result[i]]);
	}
}

static void	print_contents(void *addr, unsigned int size)
{
	void	*a;

	a = addr;
	ft_putstr("  |");
	while (a - addr < 16)
	{
		if ((a - addr) >= size)
			break ;
		else if (*(char *)a < 32 || *(char *)a > 126)
			ft_putchar('.');
		else
			ft_putchar(*(char *)a);
		a++;
	}
	ft_putchar('|');
}

static void	print_hex_contents(void *addr, unsigned int size, int option)
{
	void	*a;

	a = addr;
	(void)option;
	while (a - addr < 16)
	{
		if ((a - addr) >= size)
			break ;
		if (option && FT_IS_DIV((a - addr), 8))
			ft_putchar(' ');
		else
			/* ft_putnbr_base16(*(unsigned char *)a, 2); */
			ft_printf("%02x", *(unsigned char*)a);
		ft_putchar(' ');
		a++;
	}
}

void	*hexdump(void *addr, unsigned int size, int option)
{
	void	*a;

	a = addr;
	if (addr == NULL)
		return (addr);
	while ((a - addr) < size)
	{
		/* ft_putnbr_base16((int)(a - addr), 7 + option); */
		ft_printf("%0*x\t", 16, (a - addr));
		print_hex_contents(a, (size - (a - addr)), option);
		if (option)
			print_contents(a, (size - (a - addr)));
		ft_putchar('\n');
		a += 16;
		/* if (!ft_strncmp((char *)a, (char *)(a - 16), 16)) */
		/* { */
		/* 	ft_putstr("*\n"); */
		/* 	while (!ft_strncmp((char *)a, (char *)(a - 16), 16)) */
		/* 		a += 16; */
		/* } */
	}
	return (addr);
}
