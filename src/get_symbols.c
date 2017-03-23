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

static t_flag	get_symtype(uint32_t i, struct dysymtab_command *dysym)
{
	if (dysym->ilocalsym <= i && i <= dysym->ilocalsym + dysym->nlocalsym)
		return (SYM_DEBUG);
	if (dysym->iextdefsym <= i && i <= dysym->iextdefsym + dysym->nextdefsym)
		return (SYM_TEXT);
	if (dysym->iundefsym <= i && i <= dysym->iundefsym + dysym->nundefsym)
		return (SYM_UNDEF);
	return (0);
}

t_list			*get_symbols(char *file)
{
	int						i;
	int						nsyms;
	char					*stringtable;
	char					*string;
	struct nlist_64			*array;
	struct dylib_reference	*ref;
	t_symbol				sym;
	t_machodata				data;
	t_list					*symbols;

	fetch_header(&data, file);
	nsyms = data.symtab->nsyms;
	array = (struct nlist_64*)(file + data.symtab->symoff);
	stringtable = file + data.symtab->stroff;
	ft_printf("LC_SYMTAB [%d] symbols:\n", data.symtab->nsyms);
	i = -1;
	symbols = NULL;
	while (++i < nsyms)
	{
		sym.name = stringtable + array[i].n_un.n_strx;
		sym.type = get_symtype(i, data.dysymtab);
		sym.value = 0;
		ft_lstadd(&symbols, ft_lstnew(&sym, sizeof(sym)));
	}
	return (symbols);
	ft_putendl("");

	ft_printf("ilocalsym %i\n", data.dysymtab->ilocalsym);
	ft_printf("nlocalsym %i\n", data.dysymtab->nlocalsym);

	ft_printf("iextdefsym %i\n", data.dysymtab->iextdefsym);
	ft_printf("nextdefsym %i\n", data.dysymtab->nextdefsym);

	ft_printf("iundefsym %i\n", data.dysymtab->iundefsym);
	ft_printf("nundefsym %i\n", data.dysymtab->nundefsym);

	ft_printf("LC_DYSYMTAB ntoc=[%d]\n", data.dysymtab->ntoc);
	ft_printf("LC_DYSYMTAB nmodtab=[%d]\n", data.dysymtab->nmodtab);
	ft_printf("LC_DYSYMTAB nextrefsyms=[%d]\n", data.dysymtab->nextrefsyms);
	ft_printf("LC_DYSYMTAB nmodtab=[%d]\n", data.dysymtab->nmodtab);
	ft_printf("LC_DYSYMTAB nindirectsyms=[%d]\n", data.dysymtab->nindirectsyms);
	ft_printf("LC_DYSYMTAB nextrel=[%d]\n", data.dysymtab->nextrel);
	ft_printf("LC_DYSYMTAB nlocrel=[%d]\n", data.dysymtab->nlocrel);
	ft_putendl("");
	ref = (struct dylib_reference *)(file + data.dysymtab->indirectsymoff);
	i = -1;
	while (++i < (int)data.dysymtab->nindirectsyms)
	{
		string = stringtable + array[ref->isym].n_un.n_strx;
		ft_printf("%i: %s,%#x\n", ref->isym, string, ref->flags);
		ref += 1;
	}
	(void)file;
}
