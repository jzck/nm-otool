#include "ft_nm_otool.h"

t_symbolmap	g_symbolmap[] =
{
	{'U', NULL},
	{'A', NULL},
	{'T', sym_format_text},
	{'D', NULL},
	{'B', NULL},
	{'C', NULL},
	{'-', NULL},
	{'S', NULL},
	{'I', NULL},
};

int		sym_format_text(t_symbolmap map, t_symbol *symbol)
{
	ft_printf("%016x %c %s\n", symbol->value, map.c, symbol->name);
	return (0);
}

int		sym_format(t_symbol *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap[symbol->type];
	if (map.format)
		map.format(map, symbol);
	else
		ft_printf("%16s %c %s\n", " ", map.c, symbol->name);
	return (0);
}
