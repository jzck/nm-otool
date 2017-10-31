#include "ft_nm_otool.h"

t_symbolmap	g_symbolmap_64[] =
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

void	symbol_64_format_desc(t_symbol_64 *symbol)
{
	if (symbol->nlist.n_desc & REFERENCED_DYNAMICALLY)
		ft_printf(" [referenced dynamically]");
	if (is_external_64(symbol))
		ft_printf(" external");
	else
	{
		ft_printf(" non-external");
		if (symbol->nlist.n_type & N_PEXT)
			ft_printf(" (was a private external)");
	}
}

void	symbol_64_format_m(t_symbol_64 *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap_64[symbol->type];
	ft_printf(" (%s%c%s)",
			symbol->section ? symbol->section->segname : map.s,
			symbol->section ? ',' : 0,
			symbol->section ? symbol->section->sectname : "");
	symbol_64_format_desc(symbol);
}

void	symbol_64_format_full(t_symbol_64 *symbol)
{
	ft_printf("\t%i %03b|%b|%x|%b \t%i(%s) \t%04x",
			symbol->pos,
			(symbol->nlist.n_type & N_STAB) >> 5,
			(symbol->nlist.n_type & N_PEXT) >> 4,
			symbol->nlist.n_type & N_TYPE,
			symbol->nlist.n_type & N_EXT,
			symbol->nlist.n_sect, symbol->section->sectname,
			symbol->nlist.n_desc);
}

void	symbol_64_format_dfl(t_symbol_64 *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap_64[symbol->type];
	if (is_external_64(symbol))
		ft_printf(" %c", map.c);
	else
		ft_printf(" %c", map.c + 'a' - 'A');
	if (symbol->type == SYM_STAB)
		ft_printf(" %02x %04b %#x",
				symbol->nlist.n_sect, symbol->nlist.n_desc,
				symbol->nlist.n_type);
}

int		symbol_64_format(t_symbol_64 *symbol, t_nmdata *data)
{
	if (data->flag & NM_OFORMAT)
		ft_printf("%s: ", data->filename);
	if (!(data->flag & NM_ONLY_UNDF))
	{
		if (symbol->type == SYM_UNDF)
			ft_printf("%16s", " ");
		else
			ft_printf("%016llx", symbol->nlist.n_value);
		if (data->flag & NM_MFORMAT)
			symbol_64_format_m(symbol);
		else if (data->flag & NM_FULL)
			symbol_64_format_full(symbol);
		else
			symbol_64_format_dfl(symbol);
	}
	ft_putchar(' ');
	ft_putstr(symbol->string);
	ft_putchar('\n');
	return (0);
}
