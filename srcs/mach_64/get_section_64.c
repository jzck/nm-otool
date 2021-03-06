/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_section_64.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:00:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:26:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_segment_64(t_machodata *data, char *lookup)
{
	uint32_t					i;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	uint32_t					ncmds;

	MC(lc = (void*)((struct mach_header_64*)data->file->file + 1));
	i = -1;
	ncmds = endian(((struct mach_header_64*)data->file->file)->ncmds, 32);
	while (++i < ncmds)
	{
		if (endian(lc->cmd, 32) & LC_SEGMENT_64)
		{
			MC(seg = (struct segment_command_64*)lc);
			if (ft_strcmp(seg->segname, lookup) == 0)
				return (seg);
		}
		MC(lc = (void*)lc + endian(lc->cmdsize, 32));
	}
	return (NULL);
}

void	*get_section_64(t_machodata *data, char *lookup)
{
	uint32_t					i;
	uint32_t					j;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	MC(lc = (void*)((struct mach_header_64*)data->file->file + 1));
	i = -1;
	while (++i < endian(((struct mach_header_64*)data->file->file)->ncmds, 32))
	{
		if (endian(lc->cmd, 32) & LC_SEGMENT_64)
		{
			MC(seg = (struct segment_command_64*)lc);
			MC(sect = (void*)(seg + 1));
			j = -1;
			while (++j < endian(seg->nsects, 32))
			{
				if (ft_strcmp(sect->sectname, lookup) == 0)
					return (sect);
				MC(sect = sect + 1);
			}
		}
		MC(lc = (void*)lc + endian(lc->cmdsize, 32));
	}
	return (NULL);
}
