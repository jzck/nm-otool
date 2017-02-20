/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:20:22 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/20 15:03:38 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	dump_symtab(struct symtab_command *sym, void *file)
{
	int					i;
	int					nsyms;
	char				*stringtable;
	struct nlist_64		*array;

	nsyms = sym->nsyms;
	array = file + sym->symoff;
	stringtable = (void*)file + sym->stroff;
	ft_printf("{und}LC_SYMTAB w/ [%d] symbols:{eoc}\n", sym->nsyms);
	for (i = 0; i < nsyms; ++i)
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
}
