#include "ft_nm_otool.h"

t_symbolmap	g_symbolmap[] =
{
	{'U', sym_format_undf},
	{'A', NULL},
	{'T', sym_format_text},
	{'D', NULL},
	{'B', NULL},
	{'C', NULL},
	{'-', sym_format_stab},
	{'S', NULL},
	{'I', NULL},
};


int		sym_format_undf(t_symbolmap map, t_symbol *symbol)
{
	ft_printf("%16s %c %s\n", " ", map.c, symbol->string);
	return (0);
}

int		sym_format_text(t_symbolmap map, t_symbol *symbol)
{
	char	c;

	c = symbol->nlist->n_type & N_EXT ? 'T' : 't';
	ft_printf("%016llx %c %s\n", symbol->nlist->n_value, map.c, symbol->string);
	return (0);
}

int		sym_format_stab(t_symbolmap map, t_symbol *symbol)
{
	struct nlist_64	*stab;

	stab = symbol->nlist;
	ft_printf("%016llx %c %02x %04b %#x %s\n",
			stab->n_value, map.c,
			stab->n_sect, stab->n_desc, stab->n_type,
			symbol->string);
	return (0);
}

int		symbol_format_full(t_symbol *symbol)
{
	ft_printf("%i:\t%03b|%b|%x|%b \t%i(%s) \t%#06x \t%llx %-20s\n",
			symbol->pos,
			(symbol->nlist->n_type & N_STAB) >> 5,
			(symbol->nlist->n_type & N_PEXT) >> 4,
			symbol->nlist->n_type & N_TYPE, symbol->nlist->n_type & N_EXT,
			symbol->nlist->n_sect, symbol->section->sectname,
			symbol->nlist->n_desc, symbol->nlist->n_value,
			symbol->string);
	return (0);
}

int		symbol_format(t_symbol *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap[symbol->type];

	if (map.format)
		map.format(map, symbol);
	else
	{
		ft_printf("%016llx %c %s\n",
				symbol->nlist->n_value, map.c, symbol->string);
	}
	return (0);
}
