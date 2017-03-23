/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:56:37 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/23 16:25:49 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static void	fetch_machheader64(t_machodata *data, void *file)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header_64	*header = file;

	ncmds = header->ncmds;
	lc = (void*)(header + 1);
	/* ft_printf("{blu}{inv}mach_header_64 w/ [%d] load_commands{eoc}\n", ncmds); */
	for (i = 0; i < ncmds; i++)
	{
		/* ft_printf("{yel}{inv}load_command #%d: %#x{eoc}\n", i, lc->cmd); */
		if (lc->cmd == LC_SYMTAB)
			data->symtab = (struct symtab_command*)lc;
		else if (lc->cmd == LC_DYSYMTAB)
			data->dysymtab = (struct dysymtab_command*)lc;
		lc = (void*)lc + lc->cmdsize;
	}
}

static void	fetch_fatheader(t_machodata *data, void *file)
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
		fetch_machheader64(data, file + arch->offset);
		arch += 1;
	}
}

int		fetch_header(t_machodata *data, void *file)
{
	uint32_t	magic = *(int *)file;
	int			is_fat = IS_FAT(magic);
	int			is_64 = IS_MAGIC_64(magic);

	if (is_64)
		fetch_machheader64(data, file);
	if (is_fat)
		fetch_fatheader(data, file);
	else
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x\n", magic);
	return (0);
}

