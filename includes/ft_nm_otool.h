/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:36:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/31 21:01:14 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_OTOOL_H
# define FT_NM_OTOOL_H

# include "libft.h"
# include <stdio.h>
# include <sys/mman.h>

# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach/machine.h>

# include <fcntl.h>
# include <sys/stat.h>
# include <stdlib.h>

# define IS_MAGIC_64(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64)
# define IS_FAT(x)		(x == FAT_MAGIC || x == FAT_CIGAM)

/*
** sorting flags
*/
# define NM_NOSORT		(1 << 0)
# define NM_NSORT		(1 << 1)
# define NM_ASORT		(1 << 2)
# define NM_RSORT		(1 << 3)

/*
** filtering flags
*/
# define NM_ALL			(1 << 4)
# define NM_NO_LOCAL	(1 << 5)
# define NM_NO_UNDF		(1 << 6)
# define NM_ONLY_UNDF	(1 << 7)

/*
** formating flags
*/
# define NM_FULL		(1 << 8)
# define NM_OFORMAT		(1 << 9)
# define NM_MFORMAT		(1 << 10)

typedef struct s_nmdata		t_nmdata;
typedef enum e_symtype		t_symtype;
typedef struct s_symbol		t_symbol;
typedef struct s_symbolmap	t_symbolmap;
typedef struct s_machodata	t_machodata;
typedef struct s_symbol		t_symbol;

struct s_nmdata
{
	t_flag	flag;
	char	**av_data;
	char	*filename;
};

enum e_symtype
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

struct s_machodata
{
	void					*file;
	t_list					*sects;
	t_list					*symbols;
	struct symtab_command	*symtab;
	struct dysymtab_command	*dysymtab;
};

struct s_symbol
{
	int					pos;
	t_symtype			type;
	char				*string;
	struct nlist_64		*nlist;
	struct section_64	*section;
};

struct s_symbolmap
{
	char	c;
	char	*s;
};

extern t_symbolmap	g_symbolmap[];
extern t_machodata	*g_data;

int		mach_o_parse(t_machodata *data);
int		fetch_header(t_machodata *data);

int		symbol_init(t_symbol *symbol,
				char *stringtable, struct nlist_64 *array, int i);
int		symbol_set(t_symbol *symbol, t_machodata *data);
int		symbol_sort(t_list **syms, t_flag flag);
int		symbol_filter(t_list **syms, t_flag flag);
void	symbol_free(void *data, size_t size);

int		symbol_format(t_symbol *symbol, t_nmdata *data);
void	symbol_format_dfl(t_symbol *symbol);
void	symbol_format_m(t_symbol *symbol);
void	symbol_format_full(t_symbol *symbol);

void	mach_64_parse(t_machodata *data);
void	dump_dysymtab(t_machodata *data, struct dysymtab_command *dysymtab);

void	*hexdump(void *addr, unsigned int offset, unsigned int size);

#endif
