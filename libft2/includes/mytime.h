/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mytime.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhalford <jack@crans.org>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 11:43:12 by jhalford          #+#    #+#             */
/*   Updated: 2017/02/18 13:11:26 by jhalford         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MYTIME_H
# define MYTIME_H

# include <sys/time.h>

# include "libft.h"

struct		s_mytime
{
	char	*year;
	char	*month;
	char	*day;
	char	*hour;
	char	*min;
	char	*sec;
};

typedef struct s_mytime		t_mytime;

int			ft_time_isrecent(time_t event);
t_mytime	*ft_mytime_get(time_t epoch);
void		ft_mytime_free(t_mytime **time);
size_t		epoch_micro(void);

#endif
