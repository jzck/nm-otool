/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 15:56:37 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/25 22:51:09 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static void	fetch_symtab(t_machodata *data, struct symtab_command *symtab)
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
		ft_lsteadd(&data->symbols, ft_lstnew(&symbol, sizeof(symbol)));
	}
}

static void	fetch_sects(t_machodata *data, struct segment_command_64 *seg)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	nsects = seg->nsects;
	sect = (void*)(seg + 1);
	for (i = 0; i < nsects; i++)
	{
		/* DG("sect at %p (%s)", sect, sect->sectname); */
		/* DG("data->sects at %p", ft_lstlast(data->sects)); */
		ft_lsteadd(&data->sects, ft_lstnew(&sect, sizeof(sect)));
		/* DG("data->sects at %p -> %p", ft_lstlast(data->sects), *(struct section_64*)ft_lstlast(data->sects)->content); */
		/* DG("------------------"); */
		sect = sect + 1;
	}
}

static void	fetch_machheader64(t_machodata *data)
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
			fetch_symtab(data, (struct symtab_command*)lc);
		/* else if (lc->cmd == LC_DYSYMTAB) */
		/* 	data->dysymtab = (struct dysymtab_command*)lc; */
		else if (lc->cmd == LC_SEGMENT_64)
			fetch_sects(data, (struct segment_command_64*)lc);
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

int		fetch_header(t_machodata *data)
{
	uint32_t	magic = *(int *)data->file;
	/* int			is_fat = IS_FAT(magic); */
	int			is_64 = IS_MAGIC_64(magic);

	if (is_64)
		fetch_machheader64(data);
	/* else if (is_fat) */
	/* 	fetch_fatheader(data); */
	else
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x\n", magic);
	return (0);
}

