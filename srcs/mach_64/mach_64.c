/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:06:44 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:57:12 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static void	symtab_64_parse(t_machodata *data, struct symtab_command *symtab)
{
	int					i;
	t_symbol_64			symbol;
	char				*stringtable;
	struct nlist_64		*array;
	int					nsyms;

	data->symtab = symtab;
	MC(stringtable = data->file->file + endian(symtab->stroff, 32));
	MC(array = (struct nlist_64*)(data->file->file
				+ endian(symtab->symoff, 32)));
	nsyms = endian(symtab->nsyms, 32);
	i = -1;
	while (++i < nsyms)
	{
		symbol_64_init(&symbol, stringtable, array, i);
		symbol_64_set(&symbol, data);
		ft_lsteadd(&data->symbols, ft_lstnew(&symbol, sizeof(symbol)));
	}
}

static void	seg_64_parse(t_machodata *data, struct segment_command_64 *seg)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	nsects = endian(seg->nsects, 32);
	MC(sect = (void*)(seg + 1));
	i = -1;
	while (++i < nsects)
	{
		ft_lsteadd(&data->sects, ft_lstnew(&sect, sizeof(sect)));
		MC(sect = sect + 1);
	}
}

void		mach_64_parse(t_machodata *data)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header_64	*header;

	header = data->file->file;
	ncmds = endian(header->ncmds, 32);
	MC(lc = (void*)(header + 1));
	i = -1;
	while (++i < ncmds)
	{
		if (endian(lc->cmd, 32) == LC_SYMTAB)
			symtab_64_parse(data, (struct symtab_command*)lc);
		else if (endian(lc->cmd, 32) == LC_SEGMENT_64)
			seg_64_parse(data, (struct segment_command_64*)lc);
		MC(lc = (void*)lc + endian(lc->cmdsize, 32));
	}
}

void		nm_mach_64(t_fdata *data)
{
	t_machodata		mach;

	mach.sects = NULL;
	mach.symbols = NULL;
	mach.file = data;
	mach_64_parse(&mach);
	symbol_64_sort(&mach.symbols, data->flag);
	symbol_64_filter(&mach.symbols, data->flag);
	ft_lstiter(mach.symbols, symbol_64_format, data);
}
