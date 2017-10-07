#include "libft.h"

char	*ft_strsepjoin(char **tab, char sep)
{
	char	*join;
	char	**p;
	int		len;

	len = 0;
	if (!(p = tab))
		return (NULL);
	while (*p)
		len += ft_strlen(*p++) + 1;
	if (!(join = ft_strnew(len)))
		return (NULL);
	*join = 0;
	p = tab;
	while (*p)
	{
		ft_strcat(join, *p++);
		ft_strcat(join, &sep);
	}
	join[len - 1] = 0;
	return (join);
}
