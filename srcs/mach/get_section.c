/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:00:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:11:10 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_segment(struct mach_header *file, char *lookup)
{
	uint32_t					i;
	struct load_command			*lc;
	struct segment_command		*seg;
	uint32_t					ncmds;

	lc = (void*)(file + 1);
	i = -1;
	ncmds = endian(file->ncmds, 32);
	DG("ncmds=%i", ncmds);
	while (++i < ncmds)
	{
		DG("i=%i", i);
		if (endian(lc->cmd, 32) & LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			DG("segment: %s", seg->segname);
			if (ft_strcmp(seg->segname, lookup) == 0)
				return (seg);
		}
		lc = (void*)lc + endian(lc->cmdsize, 32);
	}
	return (NULL);
}

void	*get_section(struct mach_header *file, char *lookup)
{
	uint32_t					i;
	uint32_t					j;
	struct load_command			*lc;
	struct segment_command		*seg;
	struct section				*sect;

	lc = (void*)(file + 1);
	i = -1;
	while (++i < endian(file->ncmds, 32))
	{
		if (endian(lc->cmd, 32) & LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			sect = (void*)(seg + 1);
			j = -1;
			while (++j < endian(seg->nsects, 32))
			{
				if (ft_strcmp(sect->sectname, lookup) == 0)
					return (sect);
				sect = sect + 1;
			}
		}
		lc = (void*)lc + endian(lc->cmdsize, 32);
	}
	return (NULL);
}
