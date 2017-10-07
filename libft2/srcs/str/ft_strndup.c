
#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	char	*dup;

	if (!(dup = ft_memalloc(n)))
		return (NULL);
	ft_strncpy(dup, s1, n);
	return (dup);
}
