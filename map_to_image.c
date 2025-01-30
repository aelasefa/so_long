/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_to_image.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:26:18 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/30 10:27:19 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "so_long.h"

void	ft_change_map_to_images(char **map, t_game *game)
{
	int	x = 0;
	int	y = 0;
	int	pixel_x, pixel_y;
	int image_width, image_height;
	char *path_wall = "/home/ayelasef/Desktop/so_long/assets/wall.xpm";
	char *path_player = "/home/ayelasef/Desktop/so_long/assets/player1.xpm";
	char *path_coin1 = "/home/ayelasef/Desktop/so_long/assets/coin5.xpm";
	char *path_emty_space = "/home/ayelasef/Desktop/so_long/assets/emty_space.xpm";
	char *path_exit = "/home/ayelasef/Desktop/so_long/assets/exit1.xpm";
	char *path_enemy = "/home/ayelasef/Desktop/so_long/assets/enmy.xpm";
	game->image_wall = mlx_xpm_file_to_image(game->mlx_connection, path_wall, &image_width,&image_height);
	game->image_player = mlx_xpm_file_to_image(game->mlx_connection, path_player,  &image_width,&image_height);
	game->image_coin = mlx_xpm_file_to_image(game->mlx_connection, path_coin1,  &image_width,&image_height);
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
			{
				animation_coins(game);
				//mlx_put_image_to_window(game->mlx_connection,game->mlx_window, game->image_coin,  pixel_x, pixel_y);
			}
			else if (map[y][x] == 'E' && game->coin_nbr == game->total_coin)
			{
				mlx_put_image_to_window(game->mlx_connection,game->mlx_window , game->image_exit,  pixel_x, pixel_y);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,game->image_enemy, game->enemy_x * 64, game->enemy_y * 64);
}
