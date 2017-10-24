/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:08:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/10/23 16:37:45 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_text_section(void *file)
{
	uint32_t					i;
	uint32_t					j;
	struct load_command			*lc;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	lc = (void*)((struct mach_header_64*)file + 1);
	i = -1;
	while (++i < ((struct mach_header_64*)file)->ncmds)
	{
		if (lc->cmd & LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sect = (void*)(seg + 1);
			j = -1;
			while (++j < seg->nsects)
			{
				if (ft_strcmp(sect->sectname, "__text") == 0)
					return (sect);
				sect = sect + 1;
			}
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (NULL);
}

void	otool(void *file)
{
	uint32_t			magic;
	struct section_64	*sect;

	magic = *(int *)file;
	if (IS_FAT(magic))
		ft_printf("fat binary not supported yet\n");
	else if (IS_MACH_64(magic))
	{
		sect = get_text_section(file);
		ft_printf("Contents of (__TEXT,__text) section\n");
		hexdump(file, sect->offset, sect->size);
	}
	else
		ft_printf("{red}unsupported architecture:{eoc} magic = %#x\n", magic);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*file;
	struct stat	buf;

	if (ac != 2)
	{
		ft_dprintf(2, "USAGE PLACEHOLDER\n");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (1);
	if ((fstat(fd, &buf)) < 0)
		return (1);
	if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (1);
	otool(file);
	if (munmap(file, buf.st_size))
		return (1);
	return (0);
}
