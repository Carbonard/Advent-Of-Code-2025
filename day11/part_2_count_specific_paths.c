#include "../libft/libft.h"
#include "../dynamic_arrays/src/ft_dynarray.h"
#include <fcntl.h>
#include <stdio.h>

#define DEBUG 0
#define DAC 0b01
#define FFT 0b10

typedef struct s_device
{
	char			*name;
	int				n_outputs;
	struct s_device	**outputs;
	size_t			paths_to_out_none;
	size_t			paths_to_out_dac;
	size_t			paths_to_out_fft;
	size_t			paths_to_out_both;
	unsigned char	checked;
	// unsigned char	findable_devs;
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
		devices[i].paths_to_out_none = 0;
		devices[i].paths_to_out_dac = 0;
		devices[i].paths_to_out_fft = 0;
		devices[i].paths_to_out_both = 0;
		devices[i].checked = 0;
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

t_device	*find_svr(t_device *device, size_t n_dev)
{
	for(size_t i = 0; i < n_dev; i++)
	{
		if (!ft_strncmp(device[i].name, "svr", 3))
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

size_t	count_paths(t_device *device, size_t *p_dac, size_t *p_fft, size_t *p_none)
{
	size_t 			paths_only_dac = 0, paths_only_fft = 0, paths_only_none = 0;
	unsigned char	found_dev = 0;

	if (device->checked)
	{
		*p_dac = device->paths_to_out_dac;
		*p_fft = device->paths_to_out_fft;
		*p_none = device->paths_to_out_none;
		return (device->paths_to_out_both);
	}
	if (!ft_strncmp(device->name, "dac", 3))
	{
		found_dev = DAC;
	}
	if (!ft_strncmp(device->name, "fft", 3))
	{
		found_dev = FFT;
	}
	if (out_in_outputs(device))
	{
		if (found_dev == DAC)
		{
			*p_dac = 1;
			device->paths_to_out_dac = 1;
			device->paths_to_out_fft = 0;
			device->paths_to_out_none = 0;
		}
		else if (found_dev == FFT)
		{
			*p_fft = 1;
			device->paths_to_out_dac = 0;
			device->paths_to_out_fft = 1;
			device->paths_to_out_none = 0;
		}
		else
		{
			*p_none = 1;
			device->paths_to_out_dac = 0;
			device->paths_to_out_fft = 0;
			device->paths_to_out_none = 1;
		}
		device->paths_to_out_both = 0;
		device->checked = 1;
		return (0);
	}
	for (int i = 0; i < device->n_outputs; i++)
	{
		paths_only_fft = 0;
		paths_only_dac = 0;
		paths_only_none = 0;
		device->paths_to_out_both += count_paths(device->outputs[i], &paths_only_dac, &paths_only_fft, &paths_only_none);
		if (found_dev == DAC)
		{
			device->paths_to_out_both += paths_only_fft;
			device->paths_to_out_dac += paths_only_none;
			device->paths_to_out_dac += paths_only_dac;
			device->paths_to_out_fft = 0;
			device->paths_to_out_none = 0;
		}
		else if (found_dev == FFT)
		{
			device->paths_to_out_both += paths_only_dac;
			device->paths_to_out_fft += paths_only_none;
			device->paths_to_out_fft += paths_only_fft;
			device->paths_to_out_dac = 0;
			device->paths_to_out_none = 0;
		}
		else
		{
			device->paths_to_out_dac += paths_only_dac;
			device->paths_to_out_fft += paths_only_fft;
			device->paths_to_out_none += paths_only_none;
		}
	}
	device->checked = 1;
	*p_dac = device->paths_to_out_dac;
	*p_fft = device->paths_to_out_fft;
	*p_none = device->paths_to_out_none;
	return (device->paths_to_out_both);
}

int main()
{
	t_device	*devices;
	t_device	*svr;
	size_t		n_dev = 0;
	size_t		paths;

	devices = read_input(&n_dev);

	if (DEBUG)
		print_devices(devices, n_dev);

	svr = find_svr(devices, n_dev);
	if (!svr)
	{
		free_devices(devices, n_dev);
		ft_putendl_fd("Device 'svr' not found", 2);
		return (1);
	}
	size_t _ = 0;
	paths = count_paths(svr, &_, &_, &_);
	printf("The total paths from 'svr' to 'out', visiting 'dac' and 'fft', is %lu.\n", paths);
	free_devices(devices, n_dev);

	return (0);
}
