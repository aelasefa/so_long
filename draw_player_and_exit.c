/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_player_and_exit.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:49:50 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/03 22:31:10 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	draw_player(t_game *game, int x, int y)
{
	game->player_x = x;
	game->player_y = y;
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->image_player, x * 64, y * 64);
}

void	draw_exit(t_game *game, int x, int y)
{
	game->map_x = x;
	game->map_y = y;
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->image_exit, x * 64, y * 64);
}

int	check_key(int key)
{
	if (key == 97 || key == 65361 || key == 100 || key == 65363 || key == 119
		|| key == 65362 || key == 115 || key == 65364)
	{
		return (1);
	}
	return (0);
}

void	increment_and_print_move(t_game *game)
{
	game->moves++;
	ft_printf("%d\n", game->moves);
}
