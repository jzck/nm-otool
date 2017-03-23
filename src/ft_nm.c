/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 03:09:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/03/23 17:04:13 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm_otool.h"

t_symbolmap	g_symbolmap[] =
{
	{'U', NULL},
	{'A', NULL},
	{'T', symprint_text},
	{'D', NULL},
	{'B', NULL},
	{'C', NULL},
	{'-', NULL},
	{'S', NULL},
	{'I', NULL},
};

void	dump_section_64(struct section_64 *sect)
{
	ft_printf("section64: segname=[%s], sectname=[%s]\n",
			sect->segname, sect->sectname);
}

void	dump_segment_64(struct segment_command_64 *seg, void *file)
{
	uint32_t			nsects;
	uint32_t			i;
	struct section_64	*sect;

	(void)file;
	nsects = seg->nsects;
	ft_printf("LC_SEGMENT_64: segname=[%s], nsects=[%i]\n", seg->segname, nsects);
	sect = (void*)(seg + 1);
	for (i = 0; i < nsects; i++)
	{
		dump_section_64(sect);
		sect = sect + 1;
	}
}

void	nm(void *file)
{
	t_list		*symbols;

	symbols = get_symbols(file);
	ft_lstiter(symbols, symprint);
}

int		main(int ac, char **av)
{
	int			fd;
	char		*file;
	struct stat	buf;
	if (ac != 2)
	{
		ft_dprintf(2, "Please give me an arg\n");
		return (1);
	}
	if ((fd = open(av[1], O_RDONLY)) < 0)
		return (1);
	if ((fstat(fd, &buf)) < 0)
		return (1);
	if ((file = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0))
			== MAP_FAILED)
		return (1);
	nm(file);
	if (munmap(file, buf.st_size))
		return (1);
	return (0);
}
