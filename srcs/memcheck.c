/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:24:09 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:19:34 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	memcheck(t_fdata *file, void *ptr, size_t size, const char *function, int line)
{
	if (ptr <= file->file || (ptr + size) >= file->eof)
	{
		ft_dprintf(2, "%s:%i ", function, line);
		ft_dprintf(2, "%s: is corrupted\n", file->filename);
		ft_dprintf(2, "%p - %p (%zu) - %p --> %zu after end\n", file->file, ptr, size, file->eof, ptr - file->eof);
		exit(1);
	}
}
