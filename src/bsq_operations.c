#include "bsq.h"
#include <stdlib.h>
#include <stdio.h>

void	set_width(bsq_object *bsq_obj)
{
	int	i;

	i = 0;
	while (bsq_obj->map[i] != '\n')
		i++;
	bsq_obj->width = i;
}

char	get_char_at(bsq_object *bsq_obj, int x, int y)
{
	// Width check?
	if (bsq_obj->width == 0 && bsq_obj->map != NULL)
		set_width(bsq_obj);
	if (y <= bsq_obj->height && x <= bsq_obj->width && y >= 0 && x >= 0)
		return *(bsq_obj->map + y * (bsq_obj->width + 1) + x);
	else
		return '\0';
}

int	draw_square(bsq_object *bsq_obj, int x, int y, int side)
{
	int	x1;
	int	y1;

	side--;
	x1 = x + side;
	y1 = y + side;
	while (x <= x1)
	{
		if (x > bsq_obj->width || get_char_at(bsq_obj, x, y1) == bsq_obj->obstacle)
			return (0);
		x++;
	}
	while (y <= y1)
	{
		if (y > bsq_obj->height || get_char_at(bsq_obj, x1, y) == bsq_obj->obstacle)
			return (0);
		y++;
	}
	return (side + 1);
}

int	get_size_of_square_drawn_at(bsq_object *bsq_obj, int x, int y)
{
	int	size;

	size = 1;
	if (!(get_char_at(bsq_obj, x, y) == bsq_obj->obstacle || x < 0 || y < 0
		|| x > bsq_obj->width || y > bsq_obj->height))
	{
		while (draw_square(bsq_obj, x, y, size))
			size++;
	}
	return (size - 1);
}

int	get_biggest_square_brute_force(bsq_object *bsq_obj)
{
	int	x;
	int	y;
	int	largest_size;
	int	largest_x;
	int	largest_y;

	set_width(bsq_obj);
	y = 0;
	largest_size = -1;
	while (y < bsq_obj->height)
	{
		x = 0;
		while (x < bsq_obj->width)
		{
			if (get_size_of_square_drawn_at(bsq_obj, x, y) > largest_size)
			{
				largest_size = get_size_of_square_drawn_at(bsq_obj, x, y);
				largest_x = x; largest_y = y;
			}
			x++;
		}
		y++;
	}
	largest_x +=0; largest_y +=0;
	return (largest_size);
}
