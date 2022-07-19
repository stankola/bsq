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

bsq_object	*construct_bsq_object();

void	destruct_bsq_object(bsq_object *bsq_obj);

char	get_char_at(bsq_object *bsq_obj, int x, int y);

int	get_size_of_square_drawn_at(bsq_object *bsq_obj, int x, int y);

int	get_biggest_square_brute_force(bsq_object *bsq_obj);

#endif
