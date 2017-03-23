/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:36:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/23 17:04:06 by jhalford         ###   ########.fr       */
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

enum e_symtype
{
	SYM_UNDEF,
	SYM_ABS,
	SYM_TEXT,
	SYM_DATA,
	SYM_BSS,
	SYM_COMMON,
	SYM_DEBUG,
	SYM_OTHER,
	SYM_INDIRECT,
};


struct s_machodata
{
	struct symtab_command	*symtab;
	struct dysymtab_command	*dysymtab;
};

struct s_symbol
{
	t_symtype	type;
	long		value;
	char		*name;
};

struct s_symbolmap
{
	char	c;
	int		(*format)();
};

extern t_symbolmap	g_symbolmap[];

t_list	*get_symbols(char *file);
int		fetch_header(t_machodata *data, void *file);

int		symprint(t_symbol *symbol);
int		symprint_text(t_symbol *symbol);

void	*hexdump(void *addr, unsigned int offset, unsigned int size);

#endif
