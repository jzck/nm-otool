/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/30 11:44:40 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 16:02:11 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_H
# define FT_NM_H

/*
** sorting flags
** 		-r reverse sort
** 		-n numerical sort (as opposed to alphabetical)
**		-p don't sort
*/

# define NM_NOSORT		(1 << 0)
# define NM_NSORT		(1 << 1)
# define NM_ASORT		(1 << 2)
# define NM_RSORT		(1 << 3)

/*
** filtering flags
** 		-a show all symbols
** 		-g filter-out local symbols
** 		-U filter-out undefined symbols
** 		-u show only undefined symbols
*/

# define NM_ALL			(1 << 4)
# define NM_NO_LOCAL	(1 << 5)
# define NM_NO_UNDF		(1 << 6)
# define NM_ONLY_UNDF	(1 << 7)

/*
** formating flags
** 		-o prepend file name on each line
** 		-m Display  the  N_SECT  type symbols (Mach-O symbols) as (segment_name,
** 		   section_name) followed by either external or  non-external  and  then
** 		   the  symbol  name.   Undefined, common, absolute and indirect symbols
** 		   get displayed as (undefined), (common), (absolute),  and  (indirect),
** 		   respectively.
*/

# define NM_FULL		(1 << 8)
# define NM_OFORMAT		(1 << 9)
# define NM_MFORMAT		(1 << 10)

typedef struct s_fdata		t_fdata;
typedef enum e_symtype		t_symtype;
typedef struct s_symbolmap	t_symbolmap;
typedef struct s_machodata	t_machodata;

enum						e_symtype
{
	SYM_UNDF,
	SYM_ABS,
	SYM_TEXT,
	SYM_DATA,
	SYM_BSS,
	SYM_COMMON,
	SYM_STAB,
	SYM_OTHER,
	SYM_INDR,
};

struct						s_machodata
{
	t_fdata					*file;
	t_list					*sects;
	t_list					*symbols;
	struct symtab_command	*symtab;
	struct dysymtab_command	*dysymtab;
};

struct						s_symbolmap
{
	char					c;
	char					*s;
};

void						nm_single_file(void *file, t_fdata *data);

#endif
