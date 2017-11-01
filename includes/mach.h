/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/01 12:03:56 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:08:34 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACH_H
# define MACH_H

typedef struct s_symbol	t_symbol;

struct					s_symbol
{
	int					pos;
	t_symtype			type;
	char				*string;
	struct nlist		nlist;
	struct section		*section;
};

int						symbol_init(t_symbol *symbol,
				char *stringtable, struct nlist *array, int i);
int						symbol_set(t_symbol *symbol, t_machodata *data);
void					symbol_free(void *data, size_t size);
int						symbol_sort(t_list **syms, t_flag flag);
int						symbol_filter(t_list **syms, t_flag flag);
int						is_external(t_symbol *s);
int						is_not_external(t_symbol *s);
int						symbol_format(t_symbol *symbol, t_nmdata *data);
void					*get_section(struct mach_header *file,
		char *lookup);
void					mach_parse(t_machodata *data);

void					nm_mach(struct mach_header *file,
				t_nmdata *data);
void					otool_mach(void *file, t_otooldata *data);

#endif
