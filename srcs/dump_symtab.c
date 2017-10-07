/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dump_symtab.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/25 19:39:15 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/07 18:26:32 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	dump_dysymtab(t_machodata *data, struct dysymtab_command *dysymtab)
{
	(void)data;
	ft_printf("{blu}{inv}struct dysymtab_command{eoc}\n");
	ft_printf("ilocalsym     %i\n", dysymtab->ilocalsym);
	ft_printf("nlocalsym     %i\n", dysymtab->nlocalsym);
	ft_printf("iextdefsym    %i\n", dysymtab->iextdefsym);
	ft_printf("nextdefsym    %i\n", dysymtab->nextdefsym);
	ft_printf("iundefsym     %i\n", dysymtab->iundefsym);
	ft_printf("nundefsym     %i\n", dysymtab->nundefsym);
	ft_printf("---------------\n");
	ft_printf("ntoc          %i\n", dysymtab->ntoc);
	ft_printf("nmodtab       %i\n", dysymtab->nmodtab);
	ft_printf("nextrefsyms   %i\n", dysymtab->nextrefsyms);
	ft_printf("nmodtab       %i\n", dysymtab->nmodtab);
	ft_printf("nindirectsims %i\n", dysymtab->nindirectsyms);
	ft_printf("nextrel       %i\n", dysymtab->nextrel);
	ft_printf("nlocrel       %i\n", dysymtab->nlocrel);
	ft_putendl("");
}
