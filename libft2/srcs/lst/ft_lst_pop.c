#include "libft.h"

t_list		*ft_lst_pop(t_list **lst)
{
	t_list	*top;

	top = *lst;
	if (lst && *lst)
		*lst = (*lst)->next;
	return (top);
}
