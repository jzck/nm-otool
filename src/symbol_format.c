/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_format.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 20:34:32 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/28 20:50:00 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_symbolmap	g_symbolmap[] =
{
	{'U', "undefined", sym_format_undf},
	{'A', "absolute", NULL},
	{'T', NULL, NULL},
	{'D', NULL, NULL},
	{'B', NULL, NULL},
	{'C', "common", NULL},
	{'-', NULL, sym_format_stab},
	{'S', NULL, NULL},
	{'I', "indirect", NULL},
};


int		sym_format_undf(t_symbol *symbol, t_nmdata *data)
{
	if (data->flag & NM_ONLY_UNDF)
		ft_printf("%s\n", symbol->string);
	else
		ft_printf("%16s %c %s\n", " ", 'U', symbol->string);
	return (0);
}

int		sym_format_stab(t_symbol *symbol, t_nmdata *data)
{
	struct nlist_64	*stab;

	(void)data;
	stab = symbol->nlist;
	ft_printf("%016llx %c %02x %04b %#x %s\n",
			stab->n_value, '-',
			stab->n_sect, stab->n_desc, stab->n_type,
			symbol->string);
	return (0);
}

int		symbol_format_m(t_symbol *symbol)
{
	if (symbol->sect)

	ft_printf("%016llx (%s%c%s) %sexternal %s\n",
			symbol->nlist->n_value,
			symbol->sect ? symbol->sect->segname : "undefined",
			symbol->sect ? ',' : 0,
			symbol->sect ? symbol->sect->sectname : "",
			symbol->nlist->n_type & N_EXT ? "" : "non-",
			!(symbol->nlist->n_type & N_EXT)
			&& symbol->nlist->n_type & P_EXT ? "(was a private externel)" : "",
			(symbol->nlist->n_type & N_STAB) >> 5,
			(symbol->nlist->n_type & N_PEXT) >> 4,
			symbol->nlist->n_type & N_TYPE,
			symbol->nlist->n_sect, symbol->section->sectname,
			symbol->nlist->n_desc, symbol->nlist->n_value,
			symbol->string);
}

int		symbol_format_full(t_symbol *symbol)
{
	ft_printf("%i:\t%03b|%b|%x|%b \t%i(%s) \t%08llx \t%llx %-20s\n",
			symbol->pos,
			(symbol->nlist->n_type & N_STAB) >> 5,
			(symbol->nlist->n_type & N_PEXT) >> 4,
			symbol->nlist->n_type & N_TYPE,
			symbol->nlist->n_type & N_EXT,
			symbol->nlist->n_sect, symbol->section->sectname,
			symbol->nlist->n_desc, symbol->nlist->n_value,
			symbol->string);
	return (0);
}

int		symbol_format(t_symbol *symbol, t_nmdata *data)
{
	t_symbolmap		map;
	char			c;

	map = g_symbolmap[symbol->type];

	if (data->flag & NM_OFORMAT)
		ft_printf("file: ");
	if (map.format)
		map.format(symbol, data);
	else
	{
		c = symbol->nlist->n_type &  N_EXT ? map.c : map.c + 32;
		ft_printf("%016llx %c %s\n",
				symbol->nlist->n_value, c, symbol->string);
	}
	return (0);
}
