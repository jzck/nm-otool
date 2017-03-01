/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/01 17:53:31 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

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

void	print_output(int nsyms, int symoff, int stroff, void *ptr);

void	dump_mach_header_64(void *file)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct symtab_command	*symtab;
	struct dysymtab_command	*dysymtab;
	struct mach_header_64	*header = file;

	ncmds = header->ncmds;
	lc = (void*)(header + 1);
	/* ft_printf("{blu}{inv}mach_header_64 w/ [%d] load_commands{eoc}\n", ncmds); */
	for (i = 0; i < ncmds; i++)
	{
		/* ft_printf("{yel}{inv}load_command #%d: %#x{eoc}\n", i, lc->cmd); */
		if (lc->cmd == LC_SYMTAB)
			symtab = (struct symtab_command*)lc;
			/* dump_symtab((struct symtab_command*)lc, file); */
		else if (lc->cmd == LC_DYSYMTAB)
			dysymtab = (struct dysymtab_command*)lc;
			/* dump_dysymtab((struct dysymtab_command*)lc, file); */
		/* else if (lc->cmd == LC_SEGMENT_64) */
		/* 	dump_segment_64((struct segment_command_64*)lc, file); */
		lc = (void*)lc + lc->cmdsize;
	}
	dump_symtab(symtab, dysymtab, file);
}

void	dump_fat_header(void *file)
{
	struct fat_header	*header = file;
	struct fat_arch		*arch;
	int					i;
	int					nfat_arch;

	nfat_arch = header->nfat_arch;
	arch = (void*)(header + 1);
	ft_printf("{yel}{inv}FAT header w/ [%i] architures{eoc}\n", nfat_arch);
	for (i = 0; i < nfat_arch; i++)
	{
		ft_printf("CPU type=[%i]", arch->cputype);
		dump_mach_header_64(file + arch->offset);
		arch += 1;
	}
}

void	nm(void *file)
{
	uint32_t	magic = *(int *)file;
	int			is_fat = IS_FAT(magic);
	int			is_64 = IS_MAGIC_64(magic);

	if (is_fat)
		dump_fat_header(file);
	else if (is_64)
		dump_mach_header_64(file);
	else
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x\n", magic);
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
