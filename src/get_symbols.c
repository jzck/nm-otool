/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:20:22 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/23 16:49:03 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

static t_flag	symtype(uint32_t i, struct dysymtab_command *dysym)
{
	if (dysym->ilocalsym <= i && i < dysym->ilocalsym + dysym->nlocalsym)
		return (SYM_DEBUG);
	if (dysym->iextdefsym <= i && i < dysym->iextdefsym + dysym->nextdefsym)
		return (SYM_TEXT);
	if (dysym->iundefsym <= i && i < dysym->iundefsym + dysym->nundefsym)
		return (SYM_UNDEF);
	return (0);
}

t_list			*sym_get(char *file)
{
	int						i;
	char					*stringtable;
	char					*string;
	struct nlist_64			*array;
	struct dylib_reference	*ref;
	t_symbol				sym;
	t_machodata				data;
	t_list					*symbols;

	fetch_header(&data, file);
	stringtable = file + data.symtab->stroff;
	symbols = NULL;

	dump_symtab(data.symtab, file);
	dump_dysymtab(data.dysymtab, file);
	/* return (NULL); */
	i = -1;
	array = (struct nlist_64*)(file + data.symtab->symoff);
	while (++i < (int)data.symtab->nsyms)
	{
		sym.name = stringtable + array[i].n_un.n_strx;
		sym.type = symtype(i, data.dysymtab);
		sym.value = 0;
		ft_lsteadd(&symbols, ft_lstnew(&sym, sizeof(sym)));
	}
	return (symbols);
	i = -1;
	ref = (struct dylib_reference *)(file + data.dysymtab->indirectsymoff);
	while (++i < (int)data.dysymtab->nindirectsyms)
	{
		string = stringtable + array[ref->isym].n_un.n_strx;
		ft_printf("%i: %s,%#x\n", ref->isym, string, ref->flags);
		ref += 1;
	}
	(void)file;
}
