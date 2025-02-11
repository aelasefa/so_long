/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_enemy_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 08:24:51 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 09:59:00 by ayelasef         ###   ########.fr       */
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

void	free_enemy(t_game *game)
{
	if (game->enemy_x)
		free(game->enemy_x);
	if (game->enemy_y)
		free(game->enemy_y);
	free_map(game->map);
	free_map(game->map_copy);
}

char	get_random_move(void)
{
	static char	moves[] = {'U', 'D', 'L', 'R'};

	return (moves[rand() % 4]);
}
