/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:36:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/25 22:50:17 by jhalford         ###   ########.fr       */
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

typedef enum e_symtype		t_symtype;
typedef struct s_symbol		t_symbol;
typedef struct s_symbolmap	t_symbolmap;
typedef struct s_machodata	t_machodata;
typedef struct s_symbol		t_symbol;

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
	void		*file;
	t_list		*sects;
	t_list		*symbols;
	struct symtab_command *symtab;
};

struct s_symbol
{
	t_symtype		type;
	int				pos;
	struct nlist_64	nlist;
	char			*string;
};

struct s_symbolmap
{
	char	c;
	int		(*format)();
};

extern t_symbolmap	g_symbolmap[];
extern t_machodata	*g_data;

int			mach_o_parse(t_machodata *data);
int			fetch_header(t_machodata *data);

int			symbol_init(t_symbol *symbol,
				char *stringtable, struct nlist_64 *array, int i);
int			symbol_set(t_symbol *symbol);

int			sym_format(t_symbol *symbol);
int			sym_format_undf(t_symbolmap map, t_symbol *symbol);
int			sym_format_text(t_symbolmap map, t_symbol *symbol);
int			sym_format_stab(t_symbolmap map, t_symbol *symbol);

void		dump_symbol(t_machodata *data, t_symbol *symbol);
void		dump_machheader_64(t_machodata *data);
void		dump_segment_64(t_machodata *data, struct segment_command_64 *seg);
void		dump_symtab(t_machodata *data, struct symtab_command *symtab);
void		dump_dysymtab(t_machodata *data, struct dysymtab_command *dysymtab);

void		*hexdump(void *addr, unsigned int offset, unsigned int size);

#endif
