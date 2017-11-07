/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_mach_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:04:06 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:27:26 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

extern int g_rev;

void	otool_mach_64(t_fdata *data)
{
	struct section_64	*sect;
	t_machodata			mach;

	mach.file = data;
	if (data->flag & OTOOL_TEXT)
	{
		if ((sect = get_section_64(&mach, SECT_TEXT)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			hexdump_64(data->file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32), g_rev);
		}
	}
	if (data->flag & OTOOL_DATA)
	{
		if ((sect = get_section_64(&mach, SECT_DATA)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_DATA, SECT_DATA);
			hexdump_64(data->file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32), g_rev);
		}
	}
}
