/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:07:28 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/31 16:42:20 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_machodata	*g_data;

int				symbol_init(t_symbol *symbol,
		char *stringtable, struct nlist *array, int i)
{
	symbol->type = 0;
	symbol->pos = i;
	symbol->nlist.n_type = endian(array[i].n_type, 8);
	symbol->nlist.n_sect = endian(array[i].n_sect, 8);
	symbol->nlist.n_desc = endian(array[i].n_desc, 16);
	symbol->nlist.n_value = endian(array[i].n_value, 32);
	symbol->string = stringtable + endian(array[i].n_un.n_strx, 32);
	return (0);
}

static int		symbol_gettype(int type_mask,
		struct nlist nlist, struct section *section)
{
	if (nlist.n_type & N_STAB)
		return (SYM_STAB);
	else if (type_mask == N_UNDF && nlist.n_type & N_EXT && nlist.n_value)
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

	if (sym->nlist.n_sect &&
			(lst = ft_lst_at(data->sects, sym->nlist.n_sect - 1)))
		sym->section = *(struct section**)(lst->content);
	else
		sym->section = NULL;
	sym->type = symbol_gettype(
			sym->nlist.n_type & N_TYPE,
			sym->nlist,
			sym->section);
	return (0);
}
