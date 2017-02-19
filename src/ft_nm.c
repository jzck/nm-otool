/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/19 05:32:56 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

void	print_output(int nsyms, int symoff, int stroff, void *ptr)
{
	int					i;
	char				*stringtable;
	struct nlist_64		*array;

	array = ptr + symoff;
	stringtable = (void*)ptr + stroff;
	for (i = 0; i < nsyms; ++i)
	{
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
}

void	handle_64(void *ptr)
{
	int						ncmds;
	int						i;
	struct mach_header_64	*header;
	struct load_command		*lc;
	struct symtab_command	*sym;

	header = (struct mach_header_64*)ptr;
	ncmds = header->ncmds;
	lc = ptr + sizeof(*header);
	for (i = 0; i < ncmds; i++)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			sym = (struct symtab_command*)lc;
			/* ft_printf("nb symbols: %d\n", sym->nsyms); */
			print_output(sym->nsyms, sym->symoff, sym->stroff, ptr);
			break ;
		}
		lc = (void*)lc + lc->cmdsize;
	}
}

void	nm(char *ptr)
{
	unsigned int	magic_number;

	magic_number = *(int *)ptr;
	if (magic_number == MH_MAGIC_64 || magic_number == MH_CIGAM_64)
	{
		ft_printf("I'm a 64 it binary\n");
		handle_64(ptr);
	}
	else if (magic_number == MH_MAGIC)
	{
		ft_printf("I'm a 32 it binary\n");
		/* handle_32(ptr); */
	}
	else
	{
		ft_printf("unknown architecure\n");
	}
}

int		main(int ac, char **av)
{
	int			fd;
	char		*ptr;
	struct stat	buf;

	if (ac != 2)
	{
		ft_dprintf(2, "Please give me an arg\n");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (1);
	if ((fstat(fd, &buf)) < 0)
		return (1);
	if ((ptr = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (1);
	nm(ptr);
	if (munmap(ptr, buf.st_size))
		return (1);
	return (0);
}
