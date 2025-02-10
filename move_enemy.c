/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 20:24:05 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/06 20:31:43 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	ft_count_enemy(char **map)
{
	int	count;
	int	x;
	int	y;

	count = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'X')
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

char	get_random_move(void)
{
	static char moves[] = {'U', 'D', 'L', 'R'};
	return (moves[rand() % 4]);
}

void valide_move(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->count_enemy)
	{
		if (game->move_enemy == 'L' && game->map[game->enemy_y[i]][game->enemy_x[i] - 1] != '1' 
			&& game->map[game->enemy_y[i]][game->enemy_x[i] - 1] != 'C' && game->map[game->enemy_y[i]][game->enemy_x[i] - 1] != 'X' 
			&& game->map[game->enemy_y[i]][game->enemy_x[i] - 1] != 'E')
		{

			if (game->map[game->enemy_y[i]][game->enemy_x[i] - 1] == 'P')
			{
				ft_printf("You lose\n");
				free_game_resources(game);
				exit(1);
			}
			game->map[game->enemy_y[i]][game->enemy_x[i]] = '0';
			game->enemy_x[i] -= 1;
			game->map[game->enemy_y[i]][game->enemy_x[i]] = 'X';
		}
		else if  (game->move_enemy == 'D' && game->map[game->enemy_y[i] + 1][game->enemy_x[i]] != '1' 
			&& game->map[game->enemy_y[i] + 1][game->enemy_x[i]] != 'C' && game->map[game->enemy_y[i] + 1][game->enemy_x[i]] != 'X' && game->map[game->enemy_y[i] + 1][game->enemy_x[i]] != 'E' )
		{
			if (game->map[game->enemy_y[i] + 1][game->enemy_x[i]] == 'P')
			{
				ft_printf("You lose\n");
				free_game_resources(game);
				exit(1);
			}

			game->map[game->enemy_y[i]][game->enemy_x[i]] = '0';
			game->enemy_y[i] += 1;
			game->map[game->enemy_y[i]][game->enemy_x[i]] = 'X';
		}
		else if  (game->move_enemy == 'R' && game->map[game->enemy_y[i]][game->enemy_x[i] + 1] != '1' 
			&& game->map[game->enemy_y[i]][game->enemy_x[i] + 1] != 'C' && game->map[game->enemy_y[i]][game->enemy_x[i] + 1] != 'X' 
			&& game->map[game->enemy_y[i]][game->enemy_x[i] + 1] != 'E')
		{

			if (game->map[game->enemy_y[i]][game->enemy_x[i] + 1] == 'P')
			{
				ft_printf("You lose\n");
				free_game_resources(game);
				exit(1);
			}

			game->map[game->enemy_y[i]][game->enemy_x[i]] = '0';
			game->enemy_x[i] += 1;
			game->map[game->enemy_y[i]][game->enemy_x[i]] = 'X';
		}
		else if  (game->move_enemy == 'U' && game->map[game->enemy_y[i] - 1][game->enemy_x[i]] != '1' 
			&& game->map[game->enemy_y[i] - 1][game->enemy_x[i]] != 'C' && game->map[game->enemy_y[i] - 1][game->enemy_x[i]] != 'X' 
			&& game->map[game->enemy_y[i] - 1][game->enemy_x[i]] != 'E')
		{
			if (game->map[game->enemy_y[i] - 1][game->enemy_x[i]] == 'P')
			{
				ft_printf("You lose\n");
				free_game_resources(game);
				exit(1);
			}

			game->map[game->enemy_y[i]][game->enemy_x[i]] = '0';
			game->enemy_y[i] -= 1;
			game->map[game->enemy_y[i]][game->enemy_x[i]] = 'X';
		}
		i++;
	}
}

int	enemy_loop(t_game *game)
{
	static int count = 0;
	if (count % 300 == 0)
	{
		count = 0;
		game->move_enemy = get_random_move();
		valide_move(game);
	}
	animation_coins_ul(game);
	render_enemies(game);
	count++;
	return (0);
}

void render_enemies(t_game *game)
{
    int x, y;

    y = 0;
    while (game->map[y])
    {
        x = 0;
        while (game->map[y][x])
        {
			if (game->map[y][x] == '1')
			{
			             mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
			                 game->image_wall, x * 64, y * 64);
			}
			if (game->map[y][x] == '0')
			{
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
			                 game->image_emty_space, x * 64, y * 64);
			}
			else if (game->map[y][x] == 'P')
				mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
			                 game->image_player, x * 64, y * 64);
			else if (game->map[y][x] == 'E' && game->coin_nbr == game->total_coin)
			             draw_exit(game, x, y);
			else if (game->map[y][x] == 'X')
                mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
                    game->image_enemy, x * 64, y * 64);
			x++;
        }
        y++;
    }

	char	*tmp = ft_itoa(game->moves);
	mlx_string_put(game->mlx_connection, game->mlx_window, 1 * 64, 1 * 64, 0xFFFFFFF, tmp);
	free(tmp);
}

