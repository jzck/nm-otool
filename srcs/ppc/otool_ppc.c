/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_ppc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:32:36 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:28:34 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

extern int g_rev;

void	otool_ppc(t_fdata *data)
{
	struct section	*sect;
	t_machodata		mach;

	mach.file = data;
	if (data->flag & OTOOL_TEXT)
	{
		if ((sect = get_section(&mach, SECT_TEXT)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			hexdump_int(data->file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32), g_rev);
		}
	}
	if (data->flag & OTOOL_DATA)
	{
		if ((sect = get_section(&mach, SECT_DATA)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_DATA, SECT_DATA);
			hexdump_int(data->file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32), g_rev);
		}
	}
}
