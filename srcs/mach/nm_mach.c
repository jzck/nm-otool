/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_mach.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:04 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 11:31:38 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void		nm_mach(struct mach_header *file, t_nmdata *data)
{
	t_machodata		mach;

	mach.sects = NULL;
	mach.symbols = NULL;
	mach.file = file;
	mach_parse(&mach);
	symbol_sort(&mach.symbols, data->flag);
	symbol_filter(&mach.symbols, data->flag);
	ft_lstiter(mach.symbols, symbol_format, data);
}
