#ifndef LIBFT_RS_H
# define LIBFT_RS_H

#include <float.h>
#include <dlfcn.h>

extern struct s_stats {
	int		count;
	double	min;
	double	max;
	double	avg;
	double	m;
	double	stdev;
	double	var;
} g_rs;

void	rs_clear();
void	rs_push(double n);
void	rs_calcmore();

#endif
