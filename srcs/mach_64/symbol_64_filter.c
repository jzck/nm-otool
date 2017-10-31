/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_64_filter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:31:27 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/31 16:36:55 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int			cmp_symtype_64(t_symbol_64 *sym, void *type)
{
	return ((1 << sym->type) & *(uint64_t*)type);
}

inline int	is_not_external_64(t_symbol_64 *s)
{
	return (!(s->nlist.n_type & N_EXT));
}

inline int	is_external_64(t_symbol_64 *s)
{
	return (s->nlist.n_type & N_EXT);
}

int			symbol_64_filter(t_list **symbols, t_flag flag)
{
	uint64_t	allowed_syms;

	allowed_syms = ~(1 << SYM_STAB);
	if (flag & NM_ALL)
		allowed_syms |= (1 << SYM_STAB);
	if (flag & NM_NO_UNDF)
		allowed_syms &= ~(1 << SYM_UNDF);
	if (flag & NM_ONLY_UNDF)
		allowed_syms &= (1 << SYM_UNDF);
	ft_lst_filterout(symbols, &allowed_syms, cmp_symtype_64, symbol_64_free);
	if (flag & NM_NO_LOCAL)
		ft_lst_filterout(symbols, NULL, is_external_64, symbol_64_free);
	return (0);
}
