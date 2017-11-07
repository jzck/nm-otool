/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:46:23 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 13:24:50 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_OTOOL_H
# define FT_OTOOL_H

/*
** otool flags
**		-t show text section
**		-d show data section
*/
# define OTOOL_TEXT		(1 << 0)
# define OTOOL_DATA		(1 << 1)

void				otool_single_file(void *file, t_fdata *data);

#endif
