/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fat.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 16:31:48 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:23:08 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*fat_extract(struct fat_header *fat,
		cpu_type_t cputype,
		cpu_subtype_t cpusubtype)
{
	uint32_t		narch;
	struct fat_arch	*arch;

	narch = endian(fat->nfat_arch, 32);
	arch = (struct fat_arch*)(fat + 1);
	while (narch--)
	{
		if ((int32_t)endian(arch->cputype, 32) == cputype
				&& (int32_t)endian(arch->cpusubtype, 32) & cpusubtype)
			return ((void *)fat + endian(arch->offset, 32));
		++arch;
	}
	return (NULL);
}
