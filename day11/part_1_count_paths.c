#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>

#define DEBUG 0

typedef struct s_device
{
	char			*name;
	int				n_outputs;
	struct s_device	**outputs;
	unsigned int	paths_to_out;
}	t_device;

void free_devices(t_device *devices, size_t n_dev)
{
	for (size_t i = 0; i < n_dev; i++)
	{
		free(devices[i].name);
		free(devices[i].outputs);
	}
	free(devices);
}

t_device *find_device(char *dev, t_device *devices, size_t size)
{
	if (!ft_strncmp("out", dev, 3))
		return (NULL);
	for (size_t i = 0; i < size; i++)
	{
		if (!ft_strncmp(devices[i].name, dev, 3))
			return (devices + i);
	}
	ft_putendl_fd("\nDevice not found", 2);
	free_devices(devices, size);
	free(dev);
	exit(1);
}

t_device *read_input(size_t *n_devices)
{
	int			fd = open("input.txt", O_RDONLY);
	t_dyn_ptr	input;
	t_device	*devices;
	size_t		n_dev = 0;

	init_dyn_ptr(&input, 16);
	while (add_ptr(&input, get_next_line(fd)));
	n_dev = input.index;
	devices = malloc (n_dev * sizeof(t_device));
	for (size_t i = 0; i < n_dev; i++)
	{
		devices[i].name = ft_substr(input.arr[i], 0, 3);
		devices[i].paths_to_out = 0;
		devices[i].n_outputs = 0;
		int j = 4;
		while (input.arr[i][j])
		{
			if (input.arr[i][j] == ' ')
				devices[i].n_outputs++;
			j++;
		}
		devices[i].outputs = malloc(devices[i].n_outputs * sizeof(t_device *));
	}
	for (size_t i = 0; i < n_dev; i++)
	{
		char	*dev;
		int		j = 0;
		while (j < devices[i].n_outputs)
		{
			dev = ft_substr(input.arr[i], 5+4*j, 3);
			devices[i].outputs[j] = find_device(dev, devices, n_dev);
			free(dev);
			j++;
		}
	}
	free_dyn_ptr(&input);
	*n_devices = n_dev;
	return (devices);	
}

void print_devices(t_device *devices, size_t n_dev)
{
	for (size_t i = 0; i < n_dev; i++)
	{
		printf("Device %lu:\n", i);
		printf("\tName: %s\n", devices[i].name);
		printf("\tNumber of outputs: %d\n", devices[i].n_outputs);
		printf("\tOutputs:");
		for (int j = 0; j < devices[i].n_outputs; j++)
		{
			if (devices[i].outputs[j])
				printf(" %s", devices[i].outputs[j]->name);
			else
				printf(" out");
		}
		printf("\n");
	}
	putchar('\n');
}

t_device	*find_you(t_device *device, size_t n_dev)
{
	for(size_t i = 0; i < n_dev; i++)
	{
		if (!ft_strncmp(device[i].name, "you", 3))
			return (device + i);
	}
	return (NULL);
}

int	out_in_outputs(t_device *device)
{
	for (int i = 0; i < device->n_outputs; i++)
	{
		if (device->outputs[i] == NULL)
			return (1);
	}
	return (0);
}

unsigned int	count_paths(t_device *device)
{
	unsigned int	cnt = 0;
	if (device->paths_to_out)
		return (device->paths_to_out);
	if (out_in_outputs(device))
	{
		device->paths_to_out = 1;
		return (1);	
	}
	for (int i = 0; i < device->n_outputs; i++)
	{
		cnt += count_paths(device->outputs[i]);
	}
	device->paths_to_out = cnt;
	return (cnt);
}

int main()
{
	t_device		*devices;
	t_device		*you;
	size_t			n_dev = 0;
	unsigned int	paths;

	devices = read_input(&n_dev);

	if (DEBUG)
		print_devices(devices, n_dev);

	you = find_you(devices, n_dev);
	if (!you)
	{
		free_devices(devices, n_dev);
		ft_putendl_fd("Device 'you' not found", 2);
		return (1);
	}
	paths = count_paths(you);
	printf("The total paths from 'you' to 'out' is %u.\n", paths);
	free_devices(devices, n_dev);

	return (0);
}