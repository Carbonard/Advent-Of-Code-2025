
#include "../libft/libft.h"
#include <fcntl.h>

int main()
{
	int		dial = 50;
	int		pass = 0;
	int		fd = open("input.txt", O_RDONLY);
	char	*line;
	int		d;
	int		m;

	if (fd < 0)
	{
		ft_putendl_fd("File not found", 2);
		return (1);
	}

	line = get_next_line(fd);
	ft_printf("The dial starts by pointing at %d.\n", dial);
	while (line)
	{
		if (line[0]=='L')
			d = -1;
		else if(line[0]=='R')
			d = 1;
		else
		{
			ft_putendl_fd("direction error", 2);
			return (1);
		}
		m = ft_atoi(line + 1);
		if (m == 0)
		{
			ft_putendl_fd("number error", 2);
			return (1);
		}
		dial = (dial + d * m + 100) % 100;
		ft_printf("The dial is rotated %s to point at %d.\n", line, dial);
		if (dial == 0)
			pass++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	ft_printf("Pass: %d\n", pass);
	return (0);
}
