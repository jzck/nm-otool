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

void	nm(void *file)
{
	t_machodata	data;

	data.sects = NULL;
	data.symbols = NULL;
	data.file = file;
	fetch_header(&data);
	dump_symtab(&data, data.symtab);
	g_data = &data;
	ft_lstiter(data.symbols, symbol_set);
	ft_lstiter(data.symbols, sym_format);
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
	nm(file);
	if (munmap(file, buf.st_size))
		return (1);
	return (0);
}
