/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_ppc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 11:32:36 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:58:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

extern int g_rev;

void	otool_ppc(void *file, t_otooldata *data)
{
	struct section	*sect;

	if (data->flag & OTOOL_TEXT)
	{
		if ((sect = get_section(file, SECT_TEXT)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			hexdump_int(file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32), g_rev);
		}
	}
	if (data->flag & OTOOL_DATA)
	{
		if ((sect = get_section(file, SECT_DATA)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_DATA, SECT_DATA);
			hexdump_int(file + endian(sect->offset, 32),
					endian(sect->addr, 32), endian(sect->size, 32), g_rev);
		}
	}
}
