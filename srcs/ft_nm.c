/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/31 21:50:12 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#define NM_USAGE	"usage: nm [-a]"

t_machodata	*g_data = NULL;

t_cliopts	g_nm_opts[] =
{
	{'n', NULL, NM_NSORT, NM_ASORT, NULL, 0},
	{'p', NULL, NM_NOSORT, 0, NULL, 0},
	{'r', NULL, NM_RSORT, 0, NULL, 0},

	{0xff, "full", NM_FULL, 0, NULL, 0},
	{'a', NULL, NM_ALL, 0, NULL, 0},
	{'g', NULL, NM_NO_LOCAL, 0, NULL, 0},
	{'u', NULL, NM_ONLY_UNDF, 0, NULL, 0},
	{'U', NULL, NM_NO_UNDF, 0, NULL, 0},

	{'o', NULL, NM_OFORMAT, 0, NULL, 0},
	{'A', NULL, 0, 0, NULL, 0},
	{'m', NULL, NM_MFORMAT, 0, NULL, 0},
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
	symbol_sort(&mach.symbols, data->flag);
	symbol_filter(&mach.symbols, data->flag);
	ft_lstiter(mach.symbols, symbol_format, data);
}

int		nm(void *file, t_nmdata *data)
{
	uint32_t	magic = *(int *)file;
	int			is_fat = IS_FAT(magic);
	int			is_64 = IS_MAGIC_64(magic);

	if (is_64)
		mach_64_dump(file, data);
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
	{
		ft_perror("ft_nm");
		ft_dprintf(2, NM_USAGE"\n");
		return (1);
	}
	i = data.av_data - av;
	while (i < ac && av[i])
	{
		if (!(data.flag & NM_OFORMAT) && ac - (data.av_data - av) > 1)
			ft_printf("%c%s:\n", i - (data.av_data - av) ? '\n' : 0, av[i]);
		if ((fd = open((data.filename = av[i]), O_RDONLY)) < 0)
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
