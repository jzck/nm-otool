/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:06:44 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/23 16:42:06 by jhalford         ###   ########.fr       */
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
	i = -1;
	while (++i < nsects)
	{
		ft_lsteadd(&data->sects, ft_lstnew(&sect, sizeof(sect)));
		sect = sect + 1;
	}
}

void		mach_64_parse(t_machodata *data)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header_64	*header;

	header = data->file;
	ncmds = header->ncmds;
	lc = (void*)(header + 1);
	i = -1;
	while (++i < ncmds)
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

void		mach_64_dump(struct mach_header_64 *file, t_nmdata *data)
{
	t_machodata		mach;

	mach.sects = NULL;
	mach.symbols = NULL;
	mach.file = file;
	mach_64_parse(&mach);
	symbol_sort(&mach.symbols, data->flag);
	symbol_filter(&mach.symbols, data->flag);
	ft_lstiter(mach.symbols, symbol_format, data);
}
