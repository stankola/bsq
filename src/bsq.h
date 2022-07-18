#ifndef BSQ_H
# define BSQ_H

typedef struct bsq
{
	int		height;
	int		width;
	char	empty;
	char	obstacle;
	char	full;
	char	*map;
}			bsq_object;

#endif
