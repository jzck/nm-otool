/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/01 12:52:01 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
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
	{0, 0, 0, 0, 0, 0},
};

void	nm_fat_file(struct fat_header *fat, t_nmdata *data)
{
	uint32_t			narch;
	struct fat_arch		*obj;
	const NXArchInfo	*arch;

	g_rev = IS_REV(fat);
	if ((obj = fat_extract(fat, CPU_TYPE_X86_64, CPU_SUBTYPE_X86_64_ALL)))
		nm_single_file(obj, data);
	else
	{
		narch = endian(fat->nfat_arch, 32);
		obj = (struct fat_arch*)(fat + 1);
		while (narch--)
		{
			arch = NXGetArchInfoFromCpuType(
					endian(obj->cputype, 32),
					endian(obj->cpusubtype, 32));
			ft_printf("\n%s (for architecture %s):\n",
					data->filename, arch->name);
			nm_single_file((void*)fat + endian(obj->offset, 32), data);
			g_rev = IS_REV(fat);
			++obj;
		}
	}
}

void	nm_single_file(void *file, t_nmdata *data)
{
	const NXArchInfo *arch;

	g_rev = IS_REV(file);
	if (IS_MACH_32(file))
		nm_mach(file, data);
	else if (IS_MACH_64(file))
		nm_mach_64(file, data);
	else
	{
		arch = NXGetArchInfoFromCpuType(
				endian(*((int32_t*)file + 1), 32),
				endian(*((int32_t*)file + 2), 32));
		if (arch)
			ft_printf("{red}%s unsupported architecture{eoc}\n", arch->name);
		else
			ft_dprintf(2, "unknown arch: magic=%#x\n", *((int32_t*)file));
	}
}

int		nm(int ac, char **av, t_nmdata data)
{
	int				i;
	struct stat		buf;
	int				fd;
	void			*file;

	i = data.av_data - av;
	while (i < ac && (data.filename = av[i]))
	{
		if ((fd = open(data.filename, O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
			return (1);
		if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (1);
		if (!(data.flag & NM_OFORMAT) && ac - (data.av_data - av) > 1)
			ft_printf("\n%s:\n", data.filename);
		if (IS_FAT(file))
			nm_fat_file(file, &data);
		else
			nm_single_file(file, &data);
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
