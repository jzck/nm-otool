/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_usage.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/02 15:08:56 by jhalford          #+#    #+#             */
/*   Updated: 2017/04/02 20:05:28 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_usage(char *format, ...)
{
	va_list	ap;
	char	*usage;

	va_start(ap, format);
	usage = NULL;
	ft_vasprintf(&usage, format, ap);
	ft_dprintf(2, "usage: %s\n", usage);
	ft_strdel(&usage);
	exit(-1);
}
