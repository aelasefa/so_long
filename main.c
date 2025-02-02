/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/02 12:47:00 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_game(t_game *game, char **map, int map_width, int map_height)
{
	game->map = map;
	game->coin_nbr = 0;
	game->moves = 0;
	game->map_width = map_width;
	game->map_height = map_height;
	game->total_coin = ft_total_coin(map);
	game->mlx_connection = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx_connection, map_width * 64,
			map_height * 64, "SO_LONG");
	place_enemy_center(game);
	mlx_loop_hook(game->mlx_connection, game_loop, game);
	ft_change_map_to_images(map, game);
	mlx_key_hook(game->mlx_window, key_hook, game);
	mlx_loop(game->mlx_connection);
}

char	**ft_read_map(int fd)
{
	char	**map;
	char	*line_tmp;
	char	*line;

	line_tmp = "";
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		line_tmp = ft_strjoin_get_line(line_tmp, line);
		free(line);
	}
	map = join_arr(line_tmp);
	return (map);
}

int	main(int ac, char **av)
{
	char	**map;
	t_game	game;
	char	**map_copy;

	int(map_width), (map_height), (fd);
	if (ac != 2)
	{
		ft_printf("Usage: %s <map_file.ber>\n", av[0]);
		exit(1);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Cannot open file %s\n", av[1]);
		exit(1);
	}
	map = ft_read_map(fd);
	map_width = 0;
	map_height = 0;
	while (map[map_height])
		map_height++;
	while (map[0][map_width] != '\n')
		map_width++;
	if (!chaeck_rectangular(map) || !check_all_components(map)
		|| !check_walls(map) || !is_map_valid(map, map_width, map_height))
	{
		ft_printf("Invalid map\n");
		exit(1);
	}
	initialize_game(&game, map, map_width, map_height);
}
