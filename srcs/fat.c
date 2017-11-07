/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:31:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 14:29:26 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*fat_extract(struct fat_header *fat, char *aname)
{
	uint32_t		narch;
	struct fat_arch	*obj;
	const NXArchInfo	*arch;

	narch = endian(fat->nfat_arch, 32);
	obj = (struct fat_arch*)(fat + 1);
	while (narch--)
	{
		arch = NXGetArchInfoFromCpuType(
				endian(obj->cputype, 32),
				endian(obj->cpusubtype, 32));
		if (ft_strequ(aname, arch->name))
			return ((void *)fat + endian(obj->offset, 32));
		++obj;
	}
	return (NULL);
}
