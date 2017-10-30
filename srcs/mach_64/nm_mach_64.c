/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_mach_64.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:03:04 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 11:35:53 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void		nm_mach_64(struct mach_header_64 *file, t_nmdata *data)
{
	t_machodata		mach;

	mach.sects = NULL;
	mach.symbols = NULL;
	mach.file = file;
	mach_64_parse(&mach);
	symbol_64_sort(&mach.symbols, data->flag);
	symbol_64_filter(&mach.symbols, data->flag);
	ft_lstiter(mach.symbols, symbol_64_format, data);
}
