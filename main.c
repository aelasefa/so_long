#include "so_long.h"

int	count_line(char *line)
{
	int	count;
	int	i;
	
	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			count++;
		i++;
	}
	return (count);
}

char **join_arr(char *line)
{
	char	**arr;
	int		count;
	int		i;
	int		j;
	int		index;

	count = count_line(line);
	arr = NULL;
	arr = malloc(sizeof(char *) * count + 1);
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	index = 0;
	while (line[i])
	{
		j = i;
		while (line[i] != '\n' && line[i])
			i++;
		i++;
		arr[index] = malloc(i - j + 1);
		if (!arr[index])
			return (NULL);
		ft_strlcpy(arr[index++], line + j, i - j + 1);
	}
	arr[index] = NULL;
	return (arr);
}

int	chaeck_rectangular(char **map)
{
	size_t	len;
	size_t	len_last;
	size_t len_y;
	int		y;
	int		i;
	char	*last_line;

	y = 0;
	while (map[y])
		y++;
	y--;
	len = ft_strlen(map[0]);
	len_last = ft_strlen(map[y]);
	if (len != len_last)
		return (0);
	i = 0;
	while (map[i])
	{
		len_y = ft_strlen(map[i]);
		if (ft_strlen(map[0]) != len_y)
			return (0);
		i++;
	}
	return(1);
}

int	check_one_component(char **map, char c)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	check_all_components(char **map)
{
	if (check_one_component(map, 'E') != 1 || check_one_component(map, 'P') != 1 || check_one_component(map, 'C') == 0)
		return (0);
	return (1);
}

int	check_walls(char **map)
{
	int	x;
	int	y;
	int	last_of_line;

	last_of_line = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		last_of_line = ft_strlen(map[y]) - 2;
		if (map[y][x++] != '1' || map[y][last_of_line] != '1')
			return (0);
		while (map[y][x] != '\n')
		{
			if (map[0][x] != '1' )
				return (0);
			x++;
		}
		y++;
	}
	y--;
	x = 0;
	while(map[y][x] != '\n')
	{
		if (map[y][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int main() 
{
	int		fd;
	fd = open("map.ber", O_RDONLY);
	char	*line = NULL;
	char	**map = NULL;
	char	*line_tmp = "";
	int		i;
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line_tmp = ft_strjoin_get_line(line_tmp, line);
		free(line);
	}
	map = join_arr(line_tmp);
	for(int i = 0; i < 6; i++) printf("%s", map[i]);
	if (!chaeck_rectangular(map) ||  !check_all_components(map) || !check_walls(map))
		ft_printf("Invalide map");

	/*void	*mlx_connection = mlx_init();
	void *mlx_window = mlx_new_window(mlx_connection, 500, 500, "SO_LONG");
	for (int i = 50; i < 500 - 50; i++)
	{
		for (int y = 0; y < 500 - 50; y++)
		{
			mlx_pixel_put(mlx_connection, mlx_window, i, y, 0xff0000);
		}
	}
	mlx_loop(mlx_connection);*/
}
