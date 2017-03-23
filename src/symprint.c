/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symprint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 16:05:55 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/23 16:59:36 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

int		symprint_text(t_symbol *symbol)
{
	ft_printf("%16x %c %s\n", " ", symbol->value, symbol->name);
	return (0);
}

int		symprint(t_symbol *symbol)
{
	t_symbolmap		map;

	map = g_symbolmap[symbol->type];
	if (map.format)
		map.format(symbol);
	else
		ft_printf("%16s %c %s\n", " ", map.c, symbol->name);
	return (0);
}
