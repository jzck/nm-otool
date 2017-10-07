/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hashtab.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ariard <ariard@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 19:16:49 by ariard            #+#    #+#             */
/*   Updated: 2017/06/22 20:25:20 by ariard           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HASHTAB_H
# define HASHTAB_H

# include "libft.h"

struct s_hashtab
{	
	int					capacity;
	int					size;
	int					(*hashfunc)(const void *key, int capacity);
	struct s_list		**head;
};

typedef struct s_hashtab		t_hashtab;

void			hashtab_init(t_hashtab *htb, int capacity,
				int (*hashfunc)(const void *key, int size));	

int				hashtab_insert(t_hashtab *htb, struct s_list  *new, void *key,
				int (*match)(const void *data_ref, const void *key));

struct s_list	*hashtab_lookup(t_hashtab *htb, void *key,
				int (*match)(const void *data_ref, const void *key));

struct s_list	*hashtab_remove(t_hashtab *htb, void *key,
				int (*match)(const void *data_ref, const void *key));

void			hashtab_destroy(t_hashtab *htb, void (*destroy)());

void			hashtab_print(t_hashtab *htb, int (*printer)());

int				ft_hash_string(const void *key, int size);

struct s_list	*hashtab_iterator(t_hashtab *htb, char init);

void			hashtab_del(t_hashtab *htb, void *key,
				int (*match)(const void *, const void *),
				void (*del)(void *, size_t));

#endif 
