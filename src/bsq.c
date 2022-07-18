#include "bsq.h"
#include <stdlib.h> // malloc, free, exit
#include <unistd.h> // read, write
#include <fcntl.h> // open, close 
#include <stdio.h>
#define READBUFFERSIZE 80
#define WRITEBUFFERSIZE 80

// • You may only use the following functions : exit, open, close,
// write, read, malloc and free

int	read_initial_values_from_buffer_to_target(char *buffer, bsq_object *bsq_obj)
{
	int	order_of_magnitude;
	int	i;

	order_of_magnitude = 1;
	i = 0;
	bsq_obj->height = 0;
	while ('0' <= buffer[i] && buffer[i] <= '9')
	{
		bsq_obj->height *= order_of_magnitude;	
		bsq_obj->height += buffer[i] - '0';
		order_of_magnitude *= 10;
		i++;
	}
	//TODO: Handle overflows
	bsq_obj->empty = buffer[i++]; // what if null?
	bsq_obj->obstacle = buffer[i++];
	bsq_obj->full = buffer[i++];
	if (buffer[i] == '\n')
		i++;
	return (i);
}

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

int	moar_space(char **buffer, int totalsize)
{
	char	*newbuffer;
	int	i;

	newbuffer = malloc(sizeof(char) * (totalsize + WRITEBUFFERSIZE));
	if (newbuffer == NULL)
		exit(124);
	i = 0;
	while (i < totalsize)
	{
		newbuffer[i] = (*buffer)[i];
		i++;
	}
	free(*buffer);
	*buffer = newbuffer;
	return (totalsize + WRITEBUFFERSIZE);
}

//char_counter[0] = chars read from file, char_counter[1] = chars parsed
void	read_map_from_file(int file_descriptor, bsq_object *bsq_obj)
{
	int char_counter[2];
	int write_buffer_size;
	int write_buffer_counter;
	char *read_buffer;
	char *write_buffer;
	
	read_buffer = malloc(sizeof(char) * READBUFFERSIZE);
	write_buffer = malloc(sizeof(char) * (WRITEBUFFERSIZE + 1));
	write_buffer_size = WRITEBUFFERSIZE + 1;
	if ((char_counter[0] = read(file_descriptor, read_buffer, READBUFFERSIZE)))
		char_counter[1] = read_initial_values_from_buffer_to_target(read_buffer, bsq_obj);
	write_buffer_counter = 0;
	while (char_counter[0] > 0)
		{
			while (char_counter[1] < char_counter[0])
				{
					if (write_buffer_counter + 1 >= write_buffer_size - 1)
						write_buffer_size = moar_space(&write_buffer, write_buffer_size);
					write_buffer[write_buffer_counter++] = read_buffer[char_counter[1]++];
				}
			char_counter[0] = read(file_descriptor, read_buffer, READBUFFERSIZE);
			char_counter[1] = 0;
		}
	write_buffer[write_buffer_counter] = '\0';
	free(read_buffer);
	bsq_obj->map = write_buffer;
}

bsq_object	*initialize_bsq_object_and_read_data(char *filename)
{
	int file_descriptor;
	bsq_object	*bsq_obj;

	bsq_obj = construct_bsq_object();
	
	if (filename != NULL)
	{
		file_descriptor = open(filename, O_RDONLY);
		read_map_from_file(file_descriptor, bsq_obj);
		close(file_descriptor);
	}
	else
	{
		file_descriptor = STDIN_FILENO;
		read_map_from_file(file_descriptor, bsq_obj);
	}
	return(bsq_obj);
}

int	main(int argc, char *argv[])
{
	bsq_object	*bsq_obj;
	int			i;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{
			bsq_obj = initialize_bsq_object_and_read_data(argv[i++]);
			printf("%i\n", bsq_obj->height);
			printf("%c\n", bsq_obj->empty);
			printf("%c\n", bsq_obj->obstacle);
			printf("%c\n", bsq_obj->full);
			printf("%s\n", bsq_obj->map);
		}
	}
	else
	{
		bsq_obj = initialize_bsq_object_and_read_data(NULL);
		printf("%i\n", bsq_obj->height);
		printf("%c\n", bsq_obj->empty);
		printf("%c\n", bsq_obj->obstacle);
		printf("%c\n", bsq_obj->full);
		printf("%s\n", bsq_obj->map);
	}
	return (0);
}
