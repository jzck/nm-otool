/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:36:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/26 18:42:47 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>

# include <mach/machine.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>

# define IS_MACH_64(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64)
# define IS_MACH_32(x)	(x == MH_MAGIC || x == MH_CIGAM)
# define IS_FAT(x)		(x == FAT_MAGIC || x == FAT_CIGAM)

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

typedef struct s_nmdata		t_nmdata;
typedef enum e_symtype		t_symtype;
typedef struct s_symbolmap	t_symbolmap;
typedef struct s_machodata	t_machodata;

struct						s_nmdata
{
	t_flag					flag;
	char					**av_data;
	char					*filename;
};

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
	void					*file;
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

# include "mach_64.h"

void						dump_dysymtab(t_machodata *data,
				struct dysymtab_command *dysymtab);

extern t_symbolmap	g_symbolmap[];
extern t_machodata	*g_data;

#endif
