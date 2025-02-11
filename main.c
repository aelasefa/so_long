/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 09:43:26 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	initialize_game(t_game *game, char **map, int map_width, int map_height)
{
	game->mlx_connection = mlx_init();
	game->mlx_window = mlx_new_window(game->mlx_connection, map_width * 64,
			map_height * 64, "SO_LONG");
	int (image_width), (image_height);
	image_width = 0;
	image_height = 0;
	file_to_image(game, image_width, image_height);
	mlx_loop_hook(game->mlx_connection, enemy_loop, game);
	ft_change_map_to_images(map, game);
	mlx_key_hook(game->mlx_window, key_hook, game);
	mlx_hook(game->mlx_window, 17, 0, close_window, game);
	mlx_loop(game->mlx_connection);
}

char	**ft_read_map(int fd)
{
	char	**map;
	char	*line_tmp;
	char	*line;
	char	*tmp;

	line_tmp = strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		{
			tmp = ft_strjoin_get_line(line_tmp, line);
			line_tmp = tmp;
		}
		free(line);
	}
	if (line_tmp[0] == '\0')
	{
		ft_printf("Error\nemty map\n");
		free(line_tmp);
		exit(1);
	}
	map = join_arr(line_tmp);
	return (map);
}

void	check_ac(int ac, char **av)
{
	int	i;

	if (ac != 2)
	{
		ft_printf("Error\nUsage1: %s <map_file.ber>\n", av[0]);
		exit(1);
	}
	i = ft_strlen(av[1]);
	if (i <= 4)
	{
		ft_printf("Error\nUsage: %s <*.ber>\n", av[0]);
		exit(1);
	}
	if (strncmp(".ber", (av[1] + i) - 4, 4) != 0)
	{
		ft_printf("Error\nUsage: %s <*.ber>\n", av[0]);
		exit(1);
	}
}

int	main(int ac, char **av)
{
	char	**map;
	t_game	game;
	char	**map_copy;

	int (fd);
	check_ac(ac, av);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error\n : Cannot open file %s\n", av[1]);
		exit(1);
	}
	map = NULL;
	map = ft_read_map(fd);
	initialize_values(&game, map);
	invalid_map(map, &game);
	initialize_game(&game, map, game.map_width, game.map_height);
	free_game_resources(&game);
}
