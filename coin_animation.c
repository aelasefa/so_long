/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coin_animation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:23:45 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/01 18:28:32 by ayelasef         ###   ########.fr       */
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

void	animation_coins_ul(t_game *window)
{
	static int	count = 0;

	int (i), (j);
	if (count % 3000 == 0)
	{
		window->curr_frames = (window->curr_frames + 1) % 7;
		i = 0;
		while (window->map[i])
		{
			j = 0;
			while (window->map[i][j])
			{
				if (window->map[i][j] == 'C')
				{
					mlx_put_image_to_window(window->mlx_connection,
						window->mlx_window,
						window->coin_frames[window->curr_frames], j * 64 + 12, i
						* 64 + 12);
				}
				j++;
			}
			i++;
		}
	}
	count++;
}

int	game_loop(t_game *game)
{
	animation_coins_ul(game);
	return (0);
}
