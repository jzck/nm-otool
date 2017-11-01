/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:36:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:20:22 by jhalford         ###   ########.fr       */
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
# include <mach-o/arch.h>

# include "ft_nm.h"
# include "ft_otool.h"

# include "mach_64.h"
# include "mach.h"
# include "ppc.h"

typedef unsigned int	t_u;

# define IS_MACH_64(x)	(*(t_u*)x == MH_MAGIC_64||*(t_u*)x == MH_CIGAM_64)
# define IS_MACH_32(x)	(*(t_u*)x == MH_MAGIC||*(t_u*)x == MH_CIGAM)
# define IS_FAT(x)		(*(t_u*)x == FAT_MAGIC||*(t_u*)x == FAT_CIGAM)
# define IS_REV(x) ({t_u m=*(t_u*)x;m==MH_CIGAM||m==MH_CIGAM_64||m==FAT_CIGAM;})

uint64_t				endian(uint64_t n, uint8_t size);

void					*fat_extract(struct fat_header *fat,
					cpu_type_t cputype,
					cpu_subtype_t cpusubtype);

#endif
