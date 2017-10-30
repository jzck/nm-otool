/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:00:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 12:18:02 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_segment(void *file, char *lookup)
{
	uint32_t					i;
	struct load_command			*lc;
	struct segment_command	*seg;

	lc = (void*)((struct mach_header*)file + 1);
	i = -1;
	while (++i < ((struct mach_header*)file)->ncmds)
	{
		if (lc->cmd & LC_SEGMENT)
		{
			seg = (struct segment_command*)lc;
			if (ft_strcmp(seg->segname, lookup) == 0)
				return (seg);
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (NULL);
}

void	*get_section(void *file, char *segname, char *sectname)
{
	uint32_t					j;
	struct segment_command	*seg;
	struct section			*sect;

	seg = get_segment(file, segname);
	sect = (void*)(seg + 1);
	j = -1;
	while (++j < seg->nsects)
	{
		if (ft_strcmp(sect->sectname, sectname) == 0)
			return (sect);
		sect = sect + 1;
	}
	return (NULL);
}
