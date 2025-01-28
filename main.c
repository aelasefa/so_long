/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/28 17:45:32 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_total_coin(char **map)
{
	int	y;
	int	x;
	int	count;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'C')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
/*void	enmy_place(t_game *game)
{
	int	x;
	int	y;
	int	enemy_count;

	y = 0;
	enemy_count = 0;
	while (y < game->map_height)
	{
		x = 0;
		while (x < game->map_width)
		{
			if (game->map[y][x] == '0')
			{
				game->enemy_x[enemy_count] = x + 10;
				game->enemy_y[enemy_count] = y + 10;
				if (enemy_count == 3)
					return ;
			}
			x++;
		}
		y++;
	}
}*/

void place_enemy_center(t_game *game)
{
    int center_x = game->map_width / 2;
    int center_y = game->map_height / 2;

    // Adjust the center position if the tile isn't valid
    while (game->map[center_y][center_x] != '0' && game->map[center_y][center_x] != 'E')
    {
        if (center_x > 0)
            center_x--;
        else if (center_y > 0)
            center_y--;
        else
            break; // No valid position found
    }

    game->enemy_x = center_x;
    game->enemy_y = center_y;
}

int	key_hook(int key, void *game_ptr, char **map)
{
	char *path_exit_player = "/home/ayelasef/Desktop/so_long/assets/exit_and_player.xpm";
	int	new_x, new_y;
	t_game *game = (t_game *)game_ptr;
	new_x = game->player_x;
	new_y = game->player_y;
	if (key == 97)
		new_x--;			
	if (key == 100)
		new_x++;
	if (key == 119)
		new_y--;
	if (key == 115)
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
		if (new_x == game->enemy_x && new_y == game->enemy_y )
		{
			ft_printf("You lose\n");
			exit(1);
		}
		else if (game->map[new_y][new_x] == 'E')
		{
			if (game->coin_nbr == game->total_coin)
			{
				ft_printf("You Win\n");
				exit(0);
			}
			else
			{
				ft_printf("Collect all coins first!\n");
				int	image_width;
				int	image_height;
				game->image_exit_player = mlx_xpm_file_to_image(game->mlx_connection, path_exit_player,  &image_width,&image_height);
			game->map[game->player_y][game->player_x] = '0';
			mlx_put_image_to_window(game->mlx_connection,game->mlx_window , game->image_exit_player,  new_x * 64, new_y * 64);
				game->map[game->player_y][game->player_x] = 'E';
				game->player_x = new_x;
				game->player_y = new_y;

				return (0);
			}
		}
		game->map[game->player_y][game->player_x] = '0';
		game->player_x = new_x;
		game->player_y = new_y;
	}
	game->moves++;
	render_game(game);
	return (0);
}

void	ft_change_map_to_images(char **map, t_game *game)
{
	int	x = 0;
	int	y = 0;
	int	pixel_x, pixel_y;
	int image_width, image_height;
	char *path_wall = "/home/ayelasef/Desktop/so_long/assets/wall.xpm";
	char *path_player = "/home/ayelasef/Desktop/so_long/assets/player1.xpm";
	char *path_coin = "/home/ayelasef/Desktop/so_long/assets/coin1.xpm";
	char *path_emty_space = "/home/ayelasef/Desktop/so_long/assets/emty_space.xpm";
	char *path_exit = "/home/ayelasef/Desktop/so_long/assets/exit1.xpm";
	char *path_enemy = "/home/ayelasef/Desktop/so_long/assets/enmy.xpm";
	game->image_wall = mlx_xpm_file_to_image(game->mlx_connection, path_wall, &image_width,&image_height);
	game->image_player = mlx_xpm_file_to_image(game->mlx_connection, path_player,  &image_width,&image_height);
	game->image_coin = mlx_xpm_file_to_image(game->mlx_connection, path_coin,  &image_width,&image_height);
	game->image_emty_space = mlx_xpm_file_to_image(game->mlx_connection, path_emty_space,  &image_width,&image_height);
	game->image_exit = mlx_xpm_file_to_image(game->mlx_connection, path_exit,  &image_width,&image_height);
	game->image_enemy = mlx_xpm_file_to_image(game->mlx_connection, path_enemy,  &image_width,&image_height);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			pixel_x = x * 64;
			pixel_y = y * 64;
			mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_emty_space, pixel_x, pixel_y);
			if (map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_wall, pixel_x, pixel_y);
			else if (map[y][x] == 'P')
			{
				game->player_x = x;
				game->player_y = y;
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_player,  pixel_x, pixel_y);
				
			}
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(game->mlx_connection,game->mlx_window, game->image_coin,  pixel_x, pixel_y);
			else if (map[y][x] == 'E')
				mlx_put_image_to_window(game->mlx_connection,game->mlx_window , game->image_exit,  pixel_x, pixel_y);
			x++;
		}
		y++;
	}
        mlx_put_image_to_window(game->mlx_connection, game->mlx_window,game->image_enemy, game->enemy_x * 64, game->enemy_y * 64);
	mlx_put_image_to_window(game->mlx_connection,game->mlx_window, game->image_player, game->player_x * 64 ,game->player_y * 64);
}

void render_game(t_game *game)
{
    // mlx_clear_window(game->mlx_connection, game->mlx_window);
	ft_change_map_to_images(game->map, game);
   mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_player, game->player_x * 64, game->player_y * 64);
	mlx_string_put(game->mlx_connection, game->mlx_window, game->map_height / 2, game->map_width / 2, 0xFFFFFFF, ft_itoa(game->moves));
}

int main() 
{
	int		fd;
	fd = open("map.ber", O_RDONLY);
	char	*line = NULL;
	char	**map = NULL;
	char	*line_tmp = "";
	int		i;
	int		map_width;
	int		map_height;
	i = 0;
	t_game	game;
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
	while (map[0][map_width])
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
	ft_change_map_to_images(map, &game);
	mlx_key_hook(game.mlx_window, key_hook, &game);
	mlx_loop(game.mlx_connection);
}
