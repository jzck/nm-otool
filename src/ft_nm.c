/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/25 22:49:54 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_machodata	*g_data = NULL;

t_cliopts	g_nm_opts[] =
{
	{'n', NULL, NM_NSORT, NM_ASORT, NULL, 0},
	{'p', NULL, 0, NM_NSORT | NM_ASORT, NULL, 0},
	{'r', NULL, NM_RSORT, 0, NULL, 0},

	{'g', NULL, 0, 0, NULL, 0},
	{'u', NULL, 0, 0, NULL, 0},
	{'a', NULL, 0, 0, NULL, 0},
	{'U', NULL, 0, 0, NULL, 0},
	{'o', NULL, 0, 0, NULL, 0},
	{'A', NULL, 0, 0, NULL, 0},
	{'m', NULL, 0, 0, NULL, 0},
	{'x', NULL, 0, 0, NULL, 0},
	{'j', NULL, 0, 0, NULL, 0},
};

void	mach_64_dump(struct mach_header_64 *file, t_nmdata *data)
{
	t_machodata		mach;

	mach.sects = NULL;
	mach.symbols = NULL;
	mach.file = file;
	mach_64_parse(&mach);
	dump_symtab(&mach, mach.symtab);
	symbol_sort(&mach.symbols, data->flag);
	ft_lstiter(mach.symbols, sym_format);
}

int		nm(void *file, t_nmdata *data)
{
	uint32_t	magic = *(int *)file;
	int			is_fat = IS_FAT(magic);
	int			is_64 = IS_MAGIC_64(magic);

	if (is_64)
	{
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x (FAT)\n", magic);
		mach_64_dump(file, data);
	}
	else if (is_fat)
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x (FAT)\n", magic);
	else
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x\n", magic);
	return (0);
}

int		main(int ac, char **av)
{
	char			*file;
	t_nmdata		data;
	int				fd;
	int				i;
	struct stat		buf;

	data.flag = NM_ASORT;
	if (cliopts_get(av, g_nm_opts, &data))
		return (ft_dprintf(2, "USAGE PLACEHOLDER\n") * 0 + 1);
	i = 1;
	while (i < ac && av[i])
	{
		if ((fd = open(av[i], O_RDONLY)) < 0)
			return (1);
		if ((fstat(fd, &buf)) < 0)
			return (1);
		if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (1);
		nm(file, &data);
		if (munmap(file, buf.st_size))
			return (1);
		i++;
	}
	return (0);
}
