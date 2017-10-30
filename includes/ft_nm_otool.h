/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_otool.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:36:10 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 16:37:24 by jhalford         ###   ########.fr       */
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

# include "ft_nm.h"
# include "ft_otool.h"

# include "mach_64.h"
# include "mach.h"

# define IS_MACH_64(x)	(x == MH_MAGIC_64 || x == MH_CIGAM_64)
# define IS_MACH_32(x)	(x == MH_MAGIC || x == MH_CIGAM)
# define IS_FAT(x)		(x == FAT_MAGIC || x == FAT_CIGAM)
# define IS_REV(x)		(x == MH_CIGAM  || x == MH_CIGAM_64 || x == FAT_CIGAM)

uint64_t		endian(uint64_t n, uint8_t size);
uint8_t			bswap_8(uint8_t x);
uint16_t		bswap_16(uint16_t x);
uint32_t		bswap_32(uint32_t x);
uint64_t		bswap_64(uint64_t x);

void			*fat_extract(struct fat_header *fat,
					cpu_type_t cputype,
					cpu_subtype_t cpusubtype);

#endif
