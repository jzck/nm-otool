/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:56:37 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/26 19:05:53 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static void	symtab_parse(t_machodata *data, struct symtab_command *symtab)
{
	int					i;
	t_symbol			symbol;
	char				*stringtable;
	struct nlist_64		*array;

	data->symtab = symtab;
	stringtable = data->file + symtab->stroff;
	array = (struct nlist_64*)(data->file + symtab->symoff);
	i = -1;
	while (++i < (int)symtab->nsyms)
	{
		symbol_init(&symbol, stringtable, array, i);
		symbol_set(&symbol, data);
		ft_lsteadd(&data->symbols, ft_lstnew(&symbol, sizeof(symbol)));
	}
}

static void	seg_64_parse(t_machodata *data, struct segment_command_64 *seg)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	nsects = seg->nsects;
	sect = (void*)(seg + 1);
	for (i = 0; i < nsects; i++)
	{
		ft_lsteadd(&data->sects, ft_lstnew(&sect, sizeof(sect)));
		sect = sect + 1;
	}
}

void	mach_64_parse(t_machodata *data)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header_64	*header;

	header = data->file;
	ncmds = header->ncmds;
	lc = (void*)(header + 1);
	for (i = 0; i < ncmds; i++)
	{
		if (lc->cmd == LC_SYMTAB)
			symtab_parse(data, (struct symtab_command*)lc);
		else if (lc->cmd == LC_DYSYMTAB)
			data->dysymtab = (struct dysymtab_command*)lc;
		else if (lc->cmd == LC_SEGMENT_64)
			seg_64_parse(data, (struct segment_command_64*)lc);
		lc = (void*)lc + lc->cmdsize;
	}
}

/* static void	fetch_fatheader(t_machodata *data) */
/* { */
/* 	int					i; */
/* 	int					nfat_arch; */
/* 	struct fat_arch		*arch; */
/* 	struct fat_header	*header; */

/* 	header = data->file; */
/* 	nfat_arch = header->nfat_arch; */
/* 	arch = (void*)(header + 1); */
/* 	ft_printf("{yel}{inv}FAT header w/ [%i] architures{eoc}\n", nfat_arch); */
/* 	for (i = 0; i < nfat_arch; i++) */
/* 	{ */
/* 		ft_printf("CPU type=[%i]", arch->cputype); */
/* 		fetch_machheader64(data->file + arch->offset, data); */
/* 		arch += 1; */
/* 	} */
/* } */

