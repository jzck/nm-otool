/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 21:22:06 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/25 22:53:07 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_machodata	*g_data;

int	symbol_init(t_symbol *symbol, char *stringtable, struct nlist_64 *array, int i)
{
	symbol->type = 0;
	symbol->pos = i;
	symbol->nlist = array[i];
	symbol->string = stringtable + array[i].n_un.n_strx;
	return (0);
}

int		symbol_set(t_symbol *symbol)
{
	struct nlist_64	nlist;
	uint8_t			n_type;
	uint8_t			type_mask;
	char			*sect_name;

	nlist = symbol->nlist;
	n_type = symbol->nlist.n_type;
	type_mask = n_type & N_TYPE;
	sect_name = symbol->nlist.n_sect ?
		(*(struct section_64**)ft_lst_at(g_data->sects,
		symbol->nlist.n_sect - 1)->content)->sectname : NULL;
	if (n_type & N_STAB)
		symbol->type = SYM_STAB;
	else if (type_mask == N_UNDF && n_type & N_EXT && nlist.n_value != 0)
		symbol->type = SYM_COMMON;
	else if (type_mask == N_UNDF)
		symbol->type = SYM_UNDF;
	else if (type_mask == N_SECT && ft_strcmp("__text", sect_name) == 0)
		symbol->type = SYM_TEXT;
	else if (type_mask == N_SECT && ft_strcmp("__data", sect_name) == 0)
		symbol->type = SYM_DATA;
	else if (type_mask == N_ABS)
		symbol->type = SYM_ABS;
	else if (type_mask == N_INDR)
		symbol->type = SYM_INDR;
	else
		symbol->type = SYM_UNDF;
	return (0);
}