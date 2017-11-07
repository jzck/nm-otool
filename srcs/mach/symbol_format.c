/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_format.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:37:07 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 13:57:06 by jhalford         ###   ########.fr       */
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
	if (symbol->nlist.n_desc & REFERENCED_DYNAMICALLY)
		ft_printf(" [referenced dynamically]");
	if (is_external(symbol))
		ft_printf(" external");
	else
	{
		ft_printf(" non-external");
		if (symbol->nlist.n_type & N_PEXT)
			ft_printf(" (was a private external)");
	}
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
	ft_printf(" %02i(%s)\t %04x %03b|%b|%x|%b \t",
			symbol->nlist.n_sect, symbol->section->sectname,
			symbol->nlist.n_desc,
			(symbol->nlist.n_type & N_STAB) >> 5,
			(symbol->nlist.n_type & N_PEXT) >> 4,
			symbol->nlist.n_type & N_TYPE,
			symbol->nlist.n_type & N_EXT);
}

void	symbol_format_dfl(t_symbol *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap[symbol->type];
	if (is_external(symbol))
		ft_printf(" %c", map.c);
	else
		ft_printf(" %c", map.c + 'a' - 'A');
	if (symbol->type == SYM_STAB)
		ft_printf(" %02x %04b %#x",
				symbol->nlist.n_sect, symbol->nlist.n_desc,
				symbol->nlist.n_type);
}

int		symbol_format(t_symbol *symbol, t_fdata *data)
{
	int		nbyte;

	nbyte = ft_strstr(__FUNCTION__, "64") ? 16 : 8;
	if (data->flag & NM_OFORMAT)
		ft_printf("%s: ", data->filename);
	if (!(data->flag & NM_ONLY_UNDF))
	{
		if (symbol->type == SYM_UNDF)
			ft_printf("%*s", nbyte, " ");
		else
			ft_printf("%0*llx", nbyte, symbol->nlist.n_value);
		if (data->flag & NM_MFORMAT)
			symbol_format_m(symbol);
		else if (data->flag & NM_FULL)
			symbol_format_full(symbol);
		else
			symbol_format_dfl(symbol);
	}
	ft_putchar(' ');
	ft_putstr(symbol->string);
	ft_putchar('\n');
	return (0);
}
