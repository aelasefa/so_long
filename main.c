/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:30:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/30 12:05:55 by ayelasef         ###   ########.fr       */
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

void place_enemy_center(t_game *game)
{
    int center_x = game->map_width / 2;
    int center_y = game->map_height / 2;

    while (game->map[center_y][center_x] != '0' && game->map[center_y][center_x] != 'E')
    {
        if (center_x > 0)
            center_x--;
        else if (center_y > 0)
            center_y--;
        else
            break;
    }
    game->enemy_x = center_x;
    game->enemy_y = center_y;
}

int	key_hook(int key, void *game_ptr, char **map)
{
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
	mlx_string_put(game->mlx_connection, game->mlx_window, game->map_height / 2, game->map_width / 2, 0xFFFFFFF, ft_itoa(game->moves));
	ft_printf("%d\n", game->moves);
}

void	image_coin(t_game *window)
{
	window->coin_frames[0] = mlx_xpm_file_to_image(window->mlx_connection,
		 "/home/ayelasef/Desktop/so_long/assets/coin1.xpm",&window->img_width,
				&window->img_height);

window->coin_frames[1] = mlx_xpm_file_to_image(window->mlx_connection,
		 "/home/ayelasef/Desktop/so_long/assets/coin2.xpm",&window->img_width,
			&window->img_height);
window->coin_frames[2] = mlx_xpm_file_to_image(window->mlx_connection,
		 "/home/ayelasef/Desktop/so_long/assets/coin3.xpm",&window->img_width,
			&window->img_height);
window->coin_frames[3] = mlx_xpm_file_to_image(window->mlx_connection,
		 "/home/ayelasef/Desktop/so_long/assets/coin4.xpm",&window->img_width,
			&window->img_height);
window->coin_frames[4] = mlx_xpm_file_to_image(window->mlx_connection,
		 "/home/ayelasef/Desktop/so_long/assets/coin5.xpm",&window->img_width,
			&window->img_height);


}
void	animation_coins_ul(t_game *window)
{
	int	i;
	int	j;

	if(window->count_frames % 100 == 0)
	{
		window->curr_frames = (window->curr_frames + 1) % 5;
	}
	i = 0;
	while (window->map[i])
	{

		j = 0;
		while (window->map[i][j])
		{
			if (window->map[i][j] == 'C')
			{
				mlx_put_image_to_window(window->mlx_connection, window->mlx_window,window->coin_frames[window->curr_frames],
					j * 64 + 12, i * 64 + 12);
				usleep(10000);

			}
			j++;
		}
		i++;
	}
}


int game_loop(t_game *game)
{
	animation_coins_ul(game);
	game->curr_frames++;
	return (0);
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
	mlx_loop_hook(game.mlx_connection, game_loop, &game);
	ft_change_map_to_images(map, &game);
	mlx_key_hook(game.mlx_window, key_hook, &game);
	mlx_loop(game.mlx_connection);
}
