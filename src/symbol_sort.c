/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_sort.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 15:03:55 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/26 19:20:49 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static int		sym_asort(t_symbol *sym1, t_symbol *sym2)
{
	return (ft_strcmp(sym1->string, sym2->string));
}

static int		sym_nsort(t_symbol *sym1, t_symbol *sym2)
{
	if (sym1->nlist->n_value == sym2->nlist->n_value)
		return (sym_asort(sym1, sym2));
	return (sym1->nlist->n_value > sym2->nlist->n_value ? 1 : -1);
}

int		symbol_sort(t_list **syms, t_flag flag)
{
	if (!(flag & NM_NOSORT))
	{
		if (flag & NM_ASORT)
			ft_lstsort(syms, sym_asort);
		else if (flag & NM_NSORT)
			ft_lstsort(syms, sym_nsort);
		if (flag & NM_RSORT)
			ft_lst_reverse(syms);
	}
	return (0);
}
