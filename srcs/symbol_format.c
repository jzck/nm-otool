/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 20:34:32 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/31 21:49:55 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_symbolmap	g_symbolmap[] =
{
	{'U', "undefined"},
	{'A', "absolute"},
	{'T', "segname missing"},
	{'D', "segname missing"},
	{'B', "segname missing"},
	{'C', "common"},
	{'-', "?"},
	{'S', "segname missing"},
	{'I', "indirect"},
};

void	symbol_format_desc(t_symbol *symbol)
{
	if (symbol->nlist->n_desc & REFERENCED_DYNAMICALLY)
		ft_printf(" [referenced dynamically]");
	ft_printf(" %sexternal", symbol->nlist->n_type & N_EXT ? "" : "non-");
	ft_printf("%s",
			!(symbol->nlist->n_type & N_EXT)
			&& symbol->nlist->n_type & N_PEXT ? " (was a private externel)" : "");
}

void	symbol_format_m(t_symbol *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap[symbol->type];
	ft_printf(" (%s%c%s)",
			symbol->section ? symbol->section->segname : map.s,
			symbol->section ? ',' : 0,
			symbol->section ? symbol->section->sectname : "");
	symbol_format_desc(symbol);
}

void	symbol_format_full(t_symbol *symbol)
{
	ft_printf("\t%03b|%b|%x|%b \t%i(%s) \t%04x",
			symbol->pos,
			(symbol->nlist->n_type & N_STAB) >> 5,
			(symbol->nlist->n_type & N_PEXT) >> 4,
			symbol->nlist->n_type & N_TYPE,
			symbol->nlist->n_type & N_EXT,
			symbol->nlist->n_sect, symbol->section->sectname,
			symbol->nlist->n_desc);
}

void	symbol_format_dfl(t_symbol *symbol)
{
	t_symbolmap		map;
	char			c;

	map = g_symbolmap[symbol->type];
	c = symbol->nlist->n_type & N_EXT ? map.c : map.c + 32;
	ft_printf(" %c", c);
	if (symbol->type == SYM_STAB)
		ft_printf(" %02x %04b %#x",
				symbol->nlist->n_sect, symbol->nlist->n_desc,
				symbol->nlist->n_type);
}

int		symbol_format(t_symbol *symbol, t_nmdata *data)
{

	if (data->flag & NM_OFORMAT)
		ft_printf("%s: ", data->filename);
	if (!(data->flag & NM_ONLY_UNDF))
	{
		if (symbol->type == SYM_UNDF)
			ft_printf("%16s", " ");
		else
			ft_printf("%016llx", symbol->nlist->n_value);
		if (data->flag & NM_MFORMAT)
			symbol_format_m(symbol);
		else if (data->flag & NM_FULL)
			symbol_format_full(symbol);
		else
			symbol_format_dfl(symbol);
	}
	ft_printf(" %s\n", symbol->string);
	return (0);
}
