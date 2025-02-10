/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:26:18 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/03 20:52:02 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	*check_image(t_game *game, char *path, int *width, int *height)
{
	void	*img;

	img = mlx_xpm_file_to_image(game->mlx_connection, path, width, height);
	if (!img)
	{
		ft_printf("Error\ncould not load image: %s\n", path);
		free_game_resources(game);
		exit(1);
	}
	return (img);
}

void	file_to_image_for_coins(t_game *game, int image_width, int image_height)
{
	game->coin_frames[0] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin1.xpm", &image_width,
			&image_height);
	game->coin_frames[1] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin2.xpm", &image_width,
			&image_height);
	game->coin_frames[2] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin3.xpm", &image_width,
			&image_height);
	game->coin_frames[3] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin4.xpm", &image_width,
			&image_height);
	game->coin_frames[4] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin5.xpm", &image_width,
			&image_height);
	game->coin_frames[5] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin6.xpm", &image_width,
			&image_height);
	game->coin_frames[6] = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/coin7.xpm", &image_width,
			&image_height);
}

void	file_to_image(t_game *game, int image_width, int image_height)
{
	game->image_wall = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/wall.xpm", &image_width,
			&image_height);
	game->image_player = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/player1.xpm", &image_width,
			&image_height);
	game->image_emty_space = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/emty_space.xpm",
			&image_width, &image_height);
	game->image_exit = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/exit1.xpm", &image_width,
			&image_height);
	game->image_enemy = check_image(game,
			"/home/ayelasef/Desktop/so_long/textures/enmy.xpm", &image_width,
			&image_height);
	file_to_image_for_coins(game, image_width, image_height);
}

void	ft_change_map_to_images(char **map, t_game *game)
{
	int (x), (y);
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
			else if (map[y][x] == 'X')
			{
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
					game->image_enemy, x * 64, y * 64);
			}
			else if (game->coin_nbr == game->total_coin)
			{
				map[game->exit_y][game->exit_x] = 'E';
				if (map[y][x] == 'E')
					draw_exit(game, x, y);
			}
			x++;
		}
		y++;
	}
}
