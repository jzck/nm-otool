/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 11:24:09 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:57:51 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	memcheck(t_fdata *file, void *ptr, size_t size)
{
	if (ptr <= file->file || (ptr + size) >= file->eof)
	{
		ft_dprintf(2, "%s: is corrupted\n", file->filename);
		exit(1);
	}
}
