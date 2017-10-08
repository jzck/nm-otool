/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:22:06 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/08 11:02:50 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_machodata	*g_data;

int				symbol_init(t_symbol *symbol,
		char *stringtable, struct nlist_64 *array, int i)
{
	symbol->type = 0;
	symbol->pos = i;
	symbol->nlist = array + i;
	symbol->string = stringtable + array[i].n_un.n_strx;
	return (0);
}

static int		symbol_gettype(int type_mask,
		struct nlist_64 *nlist, struct section_64 *section)
{
	if (nlist->n_type & N_STAB)
		return (SYM_STAB);
	else if (type_mask == N_UNDF && nlist->n_type & N_EXT && nlist->n_value)
		return (SYM_COMMON);
	else if (type_mask == N_UNDF)
		return (SYM_UNDF);
	else if (type_mask == N_ABS)
		return (SYM_ABS);
	else if (type_mask == N_SECT && ft_strequ("__text", section->sectname))
		return (SYM_TEXT);
	else if (type_mask == N_SECT && ft_strequ("__data", section->sectname))
		return (SYM_DATA);
	else if (type_mask == N_SECT && ft_strequ("__bss", section->sectname))
		return (SYM_BSS);
	else if (type_mask == N_INDR)
		return (SYM_INDR);
	else
		return (SYM_OTHER);
}

int				symbol_set(t_symbol *sym, t_machodata *data)
{
	t_list	*lst;

	if (sym->nlist->n_sect)
	{
		lst = ft_lst_at(data->sects, sym->nlist->n_sect - 1);
		sym->section = *(struct section_64**)(lst->content);
	}
	else
		sym->section = NULL;
	sym->type = symbol_gettype(
			sym->nlist->n_type & N_TYPE,
			sym->nlist,
			sym->section);
	return (0);
}
