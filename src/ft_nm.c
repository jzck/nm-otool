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

void	dump_section_64(struct section_64 *sect)
{
	ft_printf("section64: segname=[%s], sectname=[%s]\n", sect->segname, sect->sectname);
}

void	dump_segment_64(struct segment_command_64 *seg, void *file)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	(void)file;
	nsects = seg->nsects;
	ft_printf("LC_SEGMENT_64: segname=[%s], nsects=[%i]\n", seg->segname, nsects);
	sect = (void*)(seg + 1);
	for (i = 0; i < nsects; i++)
	{
		dump_section_64(sect);
		sect = sect + 1;
	}
}

void	dump_symtab(struct symtab_command *sym, void *file)
{
	int					i;
	int					nsyms;
	char				*stringtable;
	struct nlist_64		*array;

	nsyms = sym->nsyms;
	array = file + sym->symoff;
	stringtable = (void*)file + sym->stroff;
	ft_printf("{und}LC_SYMTAB with %d symbols:{eoc}\n", sym->nsyms);
	for (i = 0; i < nsyms; ++i)
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
}

void	dump_load_commands(void *file)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header_64	*header = file;

	ncmds = header->ncmds;
	lc = (void*)(header + 1);
	for (i = 0; i < ncmds; i++)
	{
		ft_printf("{yel}load_command #%d: %i{eoc}\n", i, lc->cmd);
		if (lc->cmd == LC_SYMTAB)
			dump_symtab((struct symtab_command*)lc, file);
		else if (lc->cmd == LC_SEGMENT_64)
			dump_segment_64((struct segment_command_64*)lc, file);
		lc = (void*)lc + lc->cmdsize;
	}
}

void	nm(char *file)
{
	uint32_t	magic = *(int *)file;
	int			is_64 = IS_MAGIC_64(magic);

	ft_printf("{gre}I'm %s a 64 bit binary{eoc}\n", is_64 ? "" : "not");
	dump_load_commands(file);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*file;
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
	if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (1);
	nm(file);
	if (munmap(file, buf.st_size))
		return (1);
	return (0);
}
