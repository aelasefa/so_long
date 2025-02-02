/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:26:18 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/01 19:04:54 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	file_to_image_for_coins(t_game *game, int image_width, int image_height)
{
	game->coin_frames[0] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin1.xpm", &image_width,
			&image_height);
	game->coin_frames[1] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin2.xpm", &image_width,
			&image_height);
	game->coin_frames[2] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin3.xpm", &image_width,
			&image_height);
	game->coin_frames[3] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin4.xpm", &image_width,
			&image_height);
	game->coin_frames[4] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin5.xpm", &image_width,
			&image_height);
	game->coin_frames[5] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin6.xpm", &image_width,
			&image_height);
	game->coin_frames[6] = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/coin7.xpm", &image_width,
			&image_height);
}

void	file_to_image(t_game *game, int image_width, int image_height)
{
	game->image_wall = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/wall.xpm", &image_width,
			&image_height);
	game->image_player = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/player1.xpm", &image_width,
			&image_height);
	game->image_emty_space = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/emty_space.xpm",
			&image_width, &image_height);
	game->image_exit = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/exit1.xpm", &image_width,
			&image_height);
	game->image_enemy = mlx_xpm_file_to_image(game->mlx_connection,
			"/home/ayelasef/Desktop/so_long/assets/enmy.xpm", &image_width,
			&image_height);
	file_to_image_for_coins(game, image_width, image_height);
}

void	draw_player(t_game *game, int x, int y)
{
	game->player_x = x;
	game->player_y = y;
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->image_player, x * 64, y * 64);
}

void	draw_exit(t_game *game, int x, int y)
{
	game->map_x = x;
	game->map_y = y;
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->image_exit, x * 64, y * 64);
}

void	ft_change_map_to_images(char **map, t_game *game)
{
	int (x), (y), (image_width), (image_height);
	image_width = 0;
	image_height = 0;
	file_to_image(game, image_width, image_height);
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
				game->image_emty_space, x * 64, y * 64);
			if (map[y][x] == '1')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
					game->image_wall, x * 64, y * 64);
			else if (map[y][x] == 'P')
				draw_player(game, x, y);
			else if (map[y][x] == 'E' && game->coin_nbr == game->total_coin)
				draw_exit(game, x, y);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->image_enemy, game->enemy_x * 64, game->enemy_y * 64);
}
