/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_filter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/28 20:34:36 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/28 20:35:11 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		cmp_symtype(t_symbol *sym, void *type)
{
	return (sym->type - *(t_type*)type);
}

int		cmp_no_symtype(t_symbol *sym, void *type)
{
	return (!(sym->type - *(t_type*)type));
}

int		mask_nlisttype(t_symbol *sym, void *type)
{
	return (sym->nlist->n_type & *(t_type*)type);
}

int		symbol_filter(t_list **symbols, t_flag flag)
{
	t_type	symtype;

	if (!(flag & NM_ALL) && (symtype = SYM_STAB))
		ft_lst_filterout(symbols, &symtype, cmp_symtype, symbol_free);
	if ((flag & NM_NO_UNDF) && !(symtype = SYM_UNDF))
		ft_lst_filterout(symbols, &symtype, cmp_symtype, symbol_free);
	if ((flag & NM_ONLY_UNDF) && !(symtype = SYM_UNDF))
		ft_lst_filterout(symbols, &symtype, cmp_no_symtype, symbol_free);
	if ((flag & NM_NO_LOCAL) && (symtype = N_EXT))
		ft_lst_filterout(symbols, &symtype, mask_nlisttype, symbol_free);
	return (0);
}
