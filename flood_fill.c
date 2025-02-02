/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 09:53:46 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/02 10:09:30 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_map_copy(t_game *game,char **map, int y)
{
	int		i;

	game->map_copy = NULL;
	game->map_copy = malloc(sizeof(char *) * y + 1);
	i = 0;
	while (map[i])
	{
		game->map_copy[i] = strdup(map[i]);
		i++;
	}
	game->map_copy[i] = NULL;
	return (game->map_copy);
}

void	flood_fill(t_game *game, char **map, int x, int y)
{
	game->exit_found = 0;
	if (map || map[y] || map[y][x] 
		|| map[y][x] == '1' || map[y][x] == 'V')
		return ;
	if (map[y][x] == 'E')
		game->exit_found = 1;
	if (map[y][x] == 'C')
		game->collected_coins++;
	game->map[y][x] = 'V';
	flood_fill(game,map, x - 1, y);
	flood_fill(game,map, x + 1, y);
	flood_fill(game, map, x, y - 1);
	flood_fill(game,map, x, y + 1);
}

int	is_map_valid(t_game *game,char **map, int width, int height)
{
	int		exit_found;

	int (x), (y), (player_x), (player_y), (total_coins);
	player_x = -1;
	player_y = -1;
	total_coins = 0;
	game->collected_coins = 0;
	game->exit_found = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'P')
			{
				player_x = x;
				player_y = y;
			}
			if (map[y][x] == 'C')
				total_coins++;
			x++;
		}
		y++;
	}
	if (player_x == -1 || player_y == -1)
		return (0);
	
	game->map_copy = ft_map_copy(game, map, height);
	flood_fill(game,game->map_copy,  player_x, player_y);
	return (game->collected_coins == total_coins && game->exit_found);
}
