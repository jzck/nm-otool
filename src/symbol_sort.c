#include "ft_nm_otool.h"

static int		sym_asort(t_symbol *sym1, t_symbol *sym2)
{
	return (ft_strcmp(sym1->string, sym2->string));
}

static int		sym_nsort(t_symbol *sym1, t_symbol *sym2)
{
	if (sym1->nlist.n_value == sym2->nlist.n_value)
		return (ft_strcmp(sym1->string, sym2->string));
	return (sym1->nlist.n_value - sym2->nlist.n_value);
}

int		symbol_sort(t_list **syms, t_flag flag)
{
	if (flag & NM_ASORT)
		ft_lstsort(syms, sym_asort);
	else if (flag & NM_NSORT)
		ft_lstsort(syms, sym_nsort);
	if (flag & NM_RSORT)
		ft_lst_reverse(syms);
	return (0);
}
