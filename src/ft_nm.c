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

void	nm(void *file)
{
	t_list		*symbols;

	symbols = sym_get(file);
	ft_lstiter(symbols, sym_format);
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
