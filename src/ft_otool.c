/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_otool.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/20 14:08:14 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/26 19:10:48 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

void	*get_text_section(void *file)
{
	uint32_t					i;
	struct load_command			*lc;
	struct mach_header_64		*header = file;
	struct segment_command_64	*seg;
	struct section_64			*sect;

	lc = (void*)(header + 1);
	for (i = 0; i < header->ncmds; i++)
	{
		if (lc->cmd & LC_SEGMENT_64)
		{
			seg = (struct segment_command_64*)lc;
			sect = (void*)(seg + 1);
			for (i = 0; i < seg->nsects; i++)
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
	uint32_t	magic = *(int *)file;
	int			is_fat = IS_FAT(magic);
	int			is_64 = IS_MAGIC_64(magic);
	struct section_64			*sect;

	if (is_fat)
		ft_printf("fat binary: not supported yet.\n");
	else if (is_64)
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
