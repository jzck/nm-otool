/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:08:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/30 12:26:10 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"
#define OTOOL_USAGE	"usage: otool [-dt] filename ..."

t_cliopts	g_otool_opts[] =
{
	{'t', NULL, OTOOL_TEXT, 0, NULL, 0},
	{'d', NULL, OTOOL_DATA, 0, NULL, 0},
};

void	otool_file(void *file, t_otooldata *data)
{
	uint32_t			magic;

	magic = *(int *)file;
	if (IS_MACH_32(magic))
		otool_mach(file, data);
	else if (IS_MACH_64(magic))
		otool_mach_64(file, data);
	else if (IS_FAT(magic))
		ft_printf("fat binary not supported yet\n");
	else
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x\n", magic);
}

int		otool(int ac, char **av, t_otooldata data)
{
	int				i;
	struct stat		buf;
	int				fd;
	char			*file;

	i = data.av_data - av;
	while (i < ac && av[i])
	{
		if (!(data.flag & NM_OFORMAT) && ac - (data.av_data - av) > 1)
			ft_printf("%s:\n", av[i]);
		if ((fd = open((av[i]), O_RDONLY)) < 0)
			return (1);
		if ((fstat(fd, &buf)) < 0)
			return (1);
		if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
				== MAP_FAILED)
			return (1);
		otool_file(file, &data);
		if (munmap(file, buf.st_size))
			return (1);
		i++;
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_otooldata	data;

	if (cliopts_get(av, g_otool_opts, &data))
	{
		ft_perror("ft_otool");
		ft_dprintf(2, OTOOL_USAGE"\n");
		return (1);
	}
	return (otool(ac, av, data));
}
