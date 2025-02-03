/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_place.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:38:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/01 18:39:15 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	place_enemy_center(t_game *game)
{
	int	center_x;
	int	center_y;

	center_x = game->map_width / 2;
	center_y = game->map_height / 2;
	while (game->map[center_y][center_x] != '0'
		&& game->map[center_y][center_x] != 'E')
	{
		if (center_x > 0)
			center_x--;
		else if (center_y > 0)
			center_y--;
		else
			break ;
	}
	game->enemy_x = center_x;
	game->enemy_y = center_y;
}
