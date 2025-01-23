/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/20 17:56:32 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	key_hook(int key, void *game_ptr)
{
	t_game *game = (t_game *)game_ptr;
	if (key == 97)
		game->player_x--;			
	if (key == 100)
		game->player_x++;
	if (key == 119)
		game->player_y--;
	if (key == 115)
		game->player_y++;
	render_game(game);
return (0);
}
void	ft_change_map_to_images(char **map, t_game game)
{
	int	x = 0;
	int	y = 0;
	int image_width, image_height;
	int	pixel_x, pixel_y;
	char *path_wall = "/home/ayelasef/Desktop/so_long/assets/wall.xpm";
	char *path_player = "/home/ayelasef/Desktop/so_long/assets/player.xpm";
	char *path_coin = "/home/ayelasef/Desktop/so_long/assets/coin.xpm";
	char *path_emty_space = "/home/ayelasef/Desktop/so_long/assets/emty_space.xpm";
	char *path_exit = "/home/ayelasef/Desktop/so_long/assets/exit.xpm";
	game.image_wall = mlx_xpm_file_to_image(game.mlx_connection, path_wall, &image_width,&image_height);
	game.image_player = mlx_xpm_file_to_image(game.mlx_connection, path_player,  &image_width,&image_height);
	game.image_coin = mlx_xpm_file_to_image(game.mlx_connection, path_coin,  &image_width,&image_height);
	game.image_emty_space = mlx_xpm_file_to_image(game.mlx_connection, path_emty_space,  &image_width,&image_height);
	game.image_exit = mlx_xpm_file_to_image(game.mlx_connection, path_exit,  &image_width,&image_height);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			pixel_x = x * 64;
			pixel_y = y * 64;
			if (map[y][x] == '1')
				mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.image_wall, pixel_x, pixel_y);
			else if (map[y][x] == 'P')
				mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.image_player,  pixel_x, pixel_y);
			else if (map[y][x] == 'C')
				mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.image_coin,  pixel_x, pixel_y);
			else if (map[y][x] == '0')
				mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.image_emty_space,  pixel_x, pixel_y);
			else if (map[y][x] == 'E')
				mlx_put_image_to_window(game.mlx_connection, game.mlx_window, game.image_exit,  pixel_x, pixel_y);

			x++;
		}
		y++;
	}
}

void render_game(t_game *game)
{
    mlx_clear_window(game->mlx_connection, game->mlx_window);

    mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_player, game->player_x * 64, game->player_y * 64);
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
	//game.player_x = 1;
	//game.player_y = 1;
	game.mlx_connection = mlx_init();
	game.mlx_window = mlx_new_window(game.mlx_connection, 3000, 3000, "SO_LONG");
	//mlx_key_hook(game.mlx_window, key_hook, &game);
	ft_change_map_to_images(map, game);
	mlx_loop(game.mlx_connection);
}
