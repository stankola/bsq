#include "bsq.h"
#include <stdlib.h>

bsq_object	*construct_bsq_object()
{
	bsq_object	*bsq_obj;

	if (!(bsq_obj = malloc(sizeof(bsq_object))))
		return (0);
	bsq_obj->height = 0;
	bsq_obj->width = 0;
	bsq_obj->empty = '\0';
	bsq_obj->obstacle = '\0';
	bsq_obj->full = '\0';
	bsq_obj->map = NULL;
	return (bsq_obj);
}

void	destruct_bsq_object(bsq_object *bsq_obj)
{
	bsq_obj->height = 0;
	bsq_obj->width = 0;
	bsq_obj->empty = '\0';
	bsq_obj->obstacle = '\0';
	bsq_obj->full = '\0';
	if (bsq_obj->map != NULL)
	{
		free(bsq_obj->map);
		bsq_obj->map = NULL;
	}
	free(bsq_obj);
	bsq_obj = NULL;
}

