/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 09:53:46 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 09:42:51 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

char	**ft_map_copy(t_game *game, int y)
{
	int	i;

	game->map_copy = malloc(sizeof(char *) * (y + 1));
	if (!game->map_copy)
		return (NULL);
	i = 0;
	while (game->map[i])
	{
		game->map_copy[i] = strdup(game->map[i]);
		i++;
	}
	game->map_copy[i] = NULL;
	return (game->map_copy);
}

void	flood_fill(t_game *game, int x, int y)
{
	if (x < 0 || y < 0 || !game->map_copy || !game->map_copy[y]
		|| !game->map_copy[y][x] || game->map_copy[y][x] == '1'
		|| game->map_copy[y][x] == 'V')
	{
		game->map_flag = 4;
		return ;
	}
	if (game->map_copy[y][x] == 'E')
		game->exit_found = 1;
	if (game->map_copy[y][x] == 'C')
		game->collected_coins_f++;
	game->map_copy[y][x] = 'V';
	flood_fill(game, x - 1, y);
	flood_fill(game, x + 1, y);
	flood_fill(game, x, y - 1);
	flood_fill(game, x, y + 1);
}

void	check_player_and_coin(t_game *game, int width, int height)
{
	int (x), (y);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (game->map[y][x] == 'P')
			{
				game->player_x_f = x;
				game->player_y_f = y;
			}
			if (game->map[y][x] == 'C')
				game->total_coins_f++;
			x++;
		}
		y++;
	}
}

int	is_map_valid(t_game *game, int width, int height)
{
	game->player_x_f = -1;
	game->player_y_f = -1;
	game->total_coins_f = 0;
	check_player_and_coin(game, width, height);
	if (game->player_x_f == -1 || game->player_y_f == -1)
	{
		game->map_flag = 4;
		return (0);
	}
	game->collected_coins = 0;
	game->exit_found = 0;
	game->enemy_found = 0;
	game->map_copy = ft_map_copy(game, height);
	flood_fill(game, game->player_x_f, game->player_y_f);
	free_map(game->map_copy);
	game->map_copy = NULL;
	return (game->collected_coins_f == game->total_coins_f && game->exit_found);
}
