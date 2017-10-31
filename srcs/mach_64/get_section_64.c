/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:00:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/31 19:58:07 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_segment_64(struct mach_header_64 *file, char *lookup)
{
	uint32_t					i;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	uint32_t					ncmds;

	lc = (void*)(file + 1);
	i = -1;
	ncmds = endian(file->ncmds, 32);
	DG("ncmds=%i", ncmds);
	while (++i < ncmds)
	{
		DG("i=%i", i);
		if (endian(lc->cmd, 32) & LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			DG("segment: %s", seg->segname);
			if (ft_strcmp(seg->segname, lookup) == 0)
				return (seg);
		}
		lc = (void*)lc + endian(lc->cmdsize, 32);
	}
	return (NULL);
}

void	*get_section_64(void *file, char *segname, char *sectname)
{
	uint32_t					j;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	if (!(seg = get_segment_64(file, segname)))
		return (NULL);
	sect = (void*)(seg + 1);
	j = -1;
	while (++j < endian(seg->nsects, 32))
	{
		if (ft_strcmp(sect->sectname, sectname) == 0)
			return (sect);
		sect = sect + 1;
	}
	return (NULL);
}
