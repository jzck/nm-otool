/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:08:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/11/07 15:16:18 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#define OTOOL_USAGE	"usage: otool [-dt] filename ..."

t_cliopts	g_otool_opts[] =
{
	{'t', NULL, OTOOL_TEXT, 0, NULL, 0},
	{'d', NULL, OTOOL_DATA, 0, NULL, 0},
};
int			g_rev = 0;

void	otool_fat_file(struct fat_header *fat, t_fdata *data)
{
	uint32_t			narch;
	struct fat_arch		*obj;
	const NXArchInfo	*arch;

	g_rev = IS_REV(fat);
	if ((obj = fat_extract(fat, "x86_64")))
	{
		ft_printf("%s:\n", data->filename);
		otool_single_file(obj, data);
	}
	else
	{
		narch = endian(fat->nfat_arch, 32);
		obj = (struct fat_arch*)(fat + 1);
		while (narch--)
		{
			g_rev = IS_REV(fat);
			arch = NXGetArchInfoFromCpuType(
					endian(obj->cputype, 32),
					endian(obj->cpusubtype, 32));
			ft_printf("%s (architecture %s):\n", data->filename, arch->name);
			otool_single_file((void*)fat + endian(obj->offset, 32), data);
			++obj;
		}
	}
}

void	otool_single_file(void *file, t_fdata *data)
{
	const NXArchInfo *arch;

	data->file = file;
	g_rev = IS_REV(file);
	arch = NXGetArchInfoFromCpuType(
			endian(*((int32_t*)file + 1), 32),
			endian(*((int32_t*)file + 2), 32));
	if (arch)
	{
		if (ft_strcmp(arch->name, "ppc") == 0)
			otool_ppc(data);
		else if (IS_MACH_32(file))
			otool_mach(data);
		else if (IS_MACH_64(file))
			otool_mach_64(data);
		else
			ft_printf("{red}%s unsupported architecture{eoc}\n", arch->name);
	}
	else
		ft_dprintf(2, "unknown architecture, magic=%#x\n", *((int32_t*)file));
}

int		otool(int ac, char **av, t_fdata data)
{
	int				i;
	struct stat		buf;
	int				fd;

	i = data.av_data - av;
	while (i < ac && (data.filename = av[i]))
	{
		if ((fd = open((av[i]), O_RDONLY)) < 0 || fstat(fd, &buf) < 0)
			return (1);
		if ((data.file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (1);
		data.eof = data.file + buf.st_size;
		if (IS_FAT(data.file))
			otool_fat_file(data.file, &data);
		else
		{
			ft_printf("%s:\n", data.filename);
			otool_single_file(data.file, &data);
		}
		if (munmap(data.file, buf.st_size))
			return (1);
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_fdata	data;

	if (cliopts_get(av, g_otool_opts, &data))
	{
		ft_perror("ft_otool");
		ft_dprintf(2, OTOOL_USAGE"\n");
		return (1);
	}
	return (otool(ac, av, data));
}
