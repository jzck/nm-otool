/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mach_64.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/26 18:39:31 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 16:01:54 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MACH_64_H
# define MACH_64_H

typedef struct s_fdata	t_fdata;
typedef struct s_symbol_64	t_symbol_64;

struct					s_symbol_64
{
	int					pos;
	t_symtype			type;
	char				*string;
	struct nlist_64		nlist;
	struct section_64	*section;
};

int						symbol_64_init(t_symbol_64 *symbol,
				char *stringtable, struct nlist_64 *array, int i);
int						symbol_64_set(t_symbol_64 *symbol, t_machodata *data);
void					symbol_64_free(void *data, size_t size);
int						symbol_64_sort(t_list **syms, t_flag flag);
int						symbol_64_filter(t_list **syms, t_flag flag);
int						is_external_64(t_symbol_64 *s);
int						is_not_external_64(t_symbol_64 *s);
int						symbol_64_format(t_symbol_64 *symbol, t_fdata *data);
void					*get_section_64(t_machodata *data, char *lookup);
void					mach_64_parse(t_machodata *data);

void					nm_mach_64(t_fdata *data);
void					otool_mach_64(t_fdata *data);

#endif
