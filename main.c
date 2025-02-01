/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/01 19:14:18 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int key, void *game_ptr, char **map)
{
	int	new_x, new_y;
	t_game *game = (t_game *)game_ptr;
	new_x = game->player_x;
	new_y = game->player_y;
	if (key == 97 || key == 65361)
		new_x--;			
	if (key == 100 || key == 65363)
		new_x++;
	if (key == 119 || key == 65362)
		new_y--;
	if (key == 115 || key == 65364)
		new_y++;
	else if (key == 65307)
		exit(0);
	if (game->map[new_y][new_x] != '1')
	{
		if (game->map[new_y][new_x] == 'C')
        {
            game->coin_nbr++;
            game->map[new_y][new_x] = '0';
        }
		if (new_x == game->enemy_x && new_y == game->enemy_y)
		{
			ft_printf("You lose\n");
			exit(1);
		}
		if (game->map[new_y][new_x] == 'E')
		{
			if (game->coin_nbr == game->total_coin)
			{
				ft_printf("You Win\n");
				exit(0);
			}
		}
		if (game->map[game->player_y][game->player_x] != 'E')
			game->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
	}
	game->moves++;
	render_game(game);
	return (0);
}

void render_game(t_game *game)
{
	ft_change_map_to_images(game->map, game);
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_player, game->player_x * 64, game->player_y * 64);
	mlx_string_put(game->mlx_connection, game->mlx_window, game->map_height / 2 * 10, game->map_width / 2 * 10, 0xFFFFFFF, ft_itoa(game->moves));
	ft_printf("%d\n", game->moves);
}



int main(int ac, char **av) 
{
	int		fd;
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
	{
		ft_printf("Error: Cannot open file %s\n", av[1]);
        exit(1);
	}
	char	*line = NULL;
	char	**map = NULL;
	char	*line_tmp = "";
	int		i;
	int		map_width;
	int		map_height;
	i = 0;
	t_game	game;
	if (ac != 2)
	{
		ft_printf("Usage: %s <map_file.ber>\n", av[0]);
		exit(1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		line_tmp = ft_strjoin_get_line(line_tmp, line);
		free(line);
	}
	map = join_arr(line_tmp);
	if (!chaeck_rectangular(map) ||  !check_all_components(map) || !check_walls(map))
	{
		ft_printf("Invalide map");
		exit(1);
	}
	map_width = 0;
	while (map[0][map_width] != '\n')
		map_width++;
	map_height = 0;
	while (map[map_height])
		map_height++;
	game.map_width = map_width;
	game.map_height = map_height;
	game.map = map;
	game.coin_nbr = 0;
	game.moves = 0;
	game.total_coin = ft_total_coin(map);
	game.mlx_connection = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx_connection, map_width * 64, map_height * 64, "SO_LONG");
	place_enemy_center(&game);
	mlx_loop_hook(game.mlx_connection, game_loop, &game);
	ft_change_map_to_images(map, &game);
	mlx_key_hook(game.mlx_window, key_hook, &game);
	mlx_loop(game.mlx_connection);
}
