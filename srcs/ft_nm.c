/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 18:36:32 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#include <sys/utsname.h>
#define NM_USAGE	"usage: nm [-agmnpruU] filename ..."

t_machodata	*g_data = NULL;
int			g_rev = 0;

t_cliopts	g_nm_opts[] =
{
	{'n', NULL, NM_NSORT, NM_ASORT, NULL, 0},
	{'p', NULL, NM_NOSORT, 0, NULL, 0},
	{'r', NULL, NM_RSORT, 0, NULL, 0},

	{'a', NULL, NM_ALL, 0, NULL, 0},
	{'g', NULL, NM_NO_LOCAL, 0, NULL, 0},
	{'u', NULL, NM_ONLY_UNDF, 0, NULL, 0},
	{'U', NULL, NM_NO_UNDF, 0, NULL, 0},

	{0xff, "full", NM_FULL, 0, NULL, 0},
	{'o', NULL, NM_OFORMAT, 0, NULL, 0},
	{'m', NULL, NM_MFORMAT, 0, NULL, 0},
};

int		nm_file(void *file, t_nmdata *data);

int		nm_fat(struct fat_header *fat, t_nmdata *data)
{
	void *arch;
	struct utsname	host;

	uname(&host);
	NXGetLocalArchInfo();

	arch = fat_extract(fat, CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL);
	if (!arch)
		ft_printf("{red}fat doesn't have x86_64 !{eoc}");
	else
	{
		uint32_t	magic;
		magic = *(int*)arch;
		nm_file(arch, data);
	}
	return (0);
}

int		nm_file(void *file, t_nmdata *data)
{
	uint32_t	magic;

	magic = *(int*)file;
	g_rev = IS_REV(magic);
	if (IS_MACH_32(magic))
		nm_mach(file, data);
	else if (IS_MACH_64(magic))
		nm_mach_64(file, data);
	else if (IS_FAT(magic))
		nm_fat(file, data);
	else
		ft_printf("{red}unsupported arch:{eoc} magic=%#x\n", magic);
	return (0);
}

int		nm(int ac, char **av, t_nmdata data)
{
	int				i;
	struct stat		buf;
	int				fd;
	char			*file;

	i = data.av_data - av;
	while (i < ac && av[i])
	{
		data.filename = av[i];
		if (!(data.flag & NM_OFORMAT) && ac - (data.av_data - av) > 1)
			ft_printf("%c%s:\n", i - (data.av_data - av) ? '\n' : 0, av[i]);
		if ((fd = open((data.filename), O_RDONLY)) < 0)
			return (1);
		if ((fstat(fd, &buf)) < 0)
			return (1);
		if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (1);
		nm_file(file, &data);
		if (munmap(file, buf.st_size))
			return (1);
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_nmdata		data;

	data.flag = NM_ASORT;
	if (cliopts_get(av, g_nm_opts, &data))
	{
		ft_perror("ft_nm");
		ft_dprintf(2, NM_USAGE"\n");
		return (1);
	}
	return (nm(ac, av, data));
}
