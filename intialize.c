/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intialize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:56:58 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 10:56:13 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	position_e_x(t_game *game, char **map)
{
	int (j), y, x;
	j = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == 'X')
			{
				game->enemy_x[j] = x;
				game->enemy_y[j] = y;
				j++;
			}
			if (map[y][x] == 'E')
			{
				game->exit_x = x;
				game->exit_y = y;
			}
			x++;
		}
		y++;
	}
}

void	initialize_values_2(t_game *game, char **map)
{
	game->collected_coins_f = 0;
	game->total_coins_f = 0;
	game->i = 0;
	game->j = 0;
	srand(time(NULL));
	game->enemy_x = 0;
	game->enemy_y = 0;
	game->count_enemy = ft_count_enemy(map);
	game->enemy_x = malloc(sizeof(int) * game->count_enemy);
	if (!game->enemy_x)
		return ;
	game->enemy_y = malloc(sizeof(int) * game->count_enemy);
	if (!game->enemy_y)
		return ;
	while (game->j++ < 7)
		game->coin_frames[game->j] = NULL;
	position_e_x(game, map);
}

void	initialize_values(t_game *game, char **map)
{
	int (map_width), map_height;
	map_width = 0;
	map_height = 0;
	while (map[map_height])
		map_height++;
	map_width = ft_strlen(map[0]) - 1;
	game->map = map;
	game->coin_nbr = 0;
	game->moves = 0;
	game->map_width = 0;
	game->map_height = 0;
	game->map_width = map_width;
	game->map_height = map_height;
	game->total_coin = ft_total_coin(map);
	game->curr_frames = 0;
	game->check_move = 0;
	game->image_exit = NULL;
	game->image_wall = NULL;
	game->image_player = NULL;
	game->image_emty_space = NULL;
	game->image_enemy = NULL;
	initialize_values_2(game, map);
}
