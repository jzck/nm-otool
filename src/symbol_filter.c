/*
 ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 03:23:32 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/27 03:23:32 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		cmp_symtype(t_symbol *sym, void *type)
{
	return (sym->type - *(t_type*)type);
}

int		symbol_filter(t_list **symbols, t_flag flag)
{
	t_type	symtype;

	if (!(flag & NM_ALL) && (symtype = SYM_STAB))
		ft_lst_filterout(symbols, &symtype, cmp_symtype, symbol_free);
	return (0);
}
