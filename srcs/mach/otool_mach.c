/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_mach.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:04:06 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 12:16:36 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	otool_mach(void *file, t_otooldata *data)
{
	struct section	*sect;

	if (data->flag & OTOOL_TEXT)
	{
		if ((sect = get_section(file, SEG_TEXT, SECT_TEXT)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			hexdump(file + sect->offset, sect->addr, sect->size);
		}
	}
	if (data->flag & OTOOL_DATA)
	{
		if ((sect = get_section(file, SEG_DATA, SECT_DATA)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_DATA, SECT_DATA);
			hexdump(file + sect->offset, sect->addr, sect->size);
		}
	}
}
