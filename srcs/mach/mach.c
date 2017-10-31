/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:06:44 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/31 17:46:14 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static void	symtab_parse(t_machodata *data, struct symtab_command *symtab)
{
	int					i;
	t_symbol			symbol;
	char				*stringtable;
	struct nlist		*array;

	data->symtab = symtab;
	stringtable = data->file + endian(symtab->stroff, 32);
	array = (struct nlist*)(data->file + endian(symtab->symoff, 32));
	i = -1;
	while (++i < (int)endian(symtab->nsyms, 32))
	{
		symbol_init(&symbol, stringtable, array, i);
		symbol_set(&symbol, data);
		ft_lsteadd(&data->symbols, ft_lstnew(&symbol, sizeof(symbol)));
	}
}

static void	seg_parse(t_machodata *data, struct segment_command *seg)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section		*sect;

	nsects = endian(seg->nsects, 32);
	sect = (void*)(seg + 1);
	i = -1;
	while (++i < nsects)
	{
		ft_lsteadd(&data->sects, ft_lstnew(&sect, sizeof(sect)));
		sect = sect + 1;
	}
}

void		mach_parse(t_machodata *data)
{
	uint32_t				ncmds;
	uint32_t				i;
	struct load_command		*lc;
	struct mach_header	*header;

	header = data->file;
	ncmds = endian(header->ncmds, 32);
	lc = (void*)(header + 1);
	i = -1;
	while (++i < ncmds)
	{
		if (endian(lc->cmd, 32) == LC_SYMTAB)
			symtab_parse(data, (struct symtab_command*)lc);
		else if (endian(lc->cmd, 32) == LC_SEGMENT)
			seg_parse(data, (struct segment_command*)lc);
		lc = (void*)lc + endian(lc->cmdsize, 32);
	}
}
