/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:46:23 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/31 19:15:26 by jhalford         ###   ########.fr       */
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

typedef struct s_otooldata		t_otooldata;

struct				s_otooldata
{
	t_flag			flag;
	char			**av_data;
	char			*filename;
};

#endif
