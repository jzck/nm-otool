/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_mach_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:04:06 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/31 19:31:45 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	otool_mach_64(void *file, t_otooldata *data)
{
	struct section_64	*sect;

	DG("check");
	if (data->flag & OTOOL_TEXT)
	{
		DG("check");
		if ((sect = get_section_64(file, SEG_TEXT, SECT_TEXT)))
		{
			DG("check");
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			DG("check");
			DG("hexdump: %i %i %i", sect->offset, sect->addr, sect->size);
			hexdump_64(file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32));
		}
		DG("check");
	}
	if (data->flag & OTOOL_DATA)
	{
		if ((sect = get_section_64(file, SEG_DATA, SECT_DATA)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_DATA, SECT_DATA);
			hexdump_64(file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32));
		}
	}
}
