/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 13:20:22 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/01 17:55:11 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	dump_symtab(struct symtab_command *sym, struct dysymtab_command *dysym, void *file)
{
	int						i;
	int						nsyms;
	char					*stringtable;
	char					*string;
	struct nlist_64			*array;
	struct dylib_reference	*ref;

	nsyms = sym->nsyms;
	array = file + sym->symoff;
	stringtable = file + sym->stroff;
	ft_printf("LC_SYMTAB [%d] symbols:\n", sym->nsyms);
	i = 0;
	while (++i < nsyms)
	{
		ft_printf("%s\n", stringtable + array[i].n_un.n_strx);
	}
	ft_putendl("");

	ft_printf("ilocalsym %i\n", dysym->ilocalsym);
	ft_printf("nlocalsym %i\n", dysym->nlocalsym);

	ft_printf("iextdefsym %i\n", dysym->iextdefsym);
	ft_printf("nextdefsym %i\n", dysym->nextdefsym);

	ft_printf("iundefsym %i\n", dysym->iundefsym);
	ft_printf("nundefsym %i\n", dysym->nundefsym);

	i = -1;
	ft_printf("LC_DYSYMTAB ntoc=[%d]\n", dysym->ntoc);
	ft_printf("LC_DYSYMTAB nmodtab=[%d]\n", dysym->nmodtab);
	ft_printf("LC_DYSYMTAB nextrefsyms=[%d]\n", dysym->nextrefsyms);
	ft_printf("LC_DYSYMTAB nmodtab=[%d]\n", dysym->nmodtab);
	ft_printf("LC_DYSYMTAB nindirectsyms=[%d]\n", dysym->nindirectsyms);
	ft_printf("LC_DYSYMTAB nextrel=[%d]\n", dysym->nextrel);
	ft_printf("LC_DYSYMTAB nlocrel=[%d]\n", dysym->nlocrel);
	ft_putendl("");
	ref = file + dysym->indirectsymoff;
	while (++i < (int)dysym->nindirectsyms)
	{
		string = stringtable + array[ref->isym].n_un.n_strx;
		ft_printf("%i: %s,%#x\n", ref->isym, string, ref->flags);
		ref += 1;
	}
	(void)file;
}
