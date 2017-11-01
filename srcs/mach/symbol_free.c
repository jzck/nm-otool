/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   symbol_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 17:06:23 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:11:42 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	symbol_free(void *data, size_t size)
{
	t_symbol	*symbol;

	symbol = data;
	(void)size;
	if (symbol)
		free(symbol);
}
