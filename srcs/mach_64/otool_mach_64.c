/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool_mach_64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:04:06 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 12:16:36 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	otool_mach_64(void *file, t_otooldata *data)
{
	struct section_64	*sect;

	if (data->flag & OTOOL_TEXT)
	{
		if ((sect = get_section_64(file, SEG_TEXT, SECT_TEXT)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_TEXT, SECT_TEXT);
			hexdump_64(file + sect->offset, sect->addr, sect->size);
		}
	}
	if (data->flag & OTOOL_DATA)
	{
		if ((sect = get_section_64(file, SEG_DATA, SECT_DATA)))
		{
			ft_printf("Contents of (%s,%s) section\n", SEG_DATA, SECT_DATA);
			hexdump_64(file + sect->offset, sect->addr, sect->size);
		}
	}
}
