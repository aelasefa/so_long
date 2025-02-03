/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_or_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:41:07 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/03 20:41:29 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map(char **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_game_resources(t_game *game)
{
	int	i;

	i = 0;
	free_map(game->map);
	if (game->map_copy)
		free_map(game->map_copy);
	if (game->image_wall)
		mlx_destroy_image(game->mlx_connection, game->image_wall);
	if (game->image_exit)
		mlx_destroy_image(game->mlx_connection, game->image_exit);
	if (game->image_emty_space)
		mlx_destroy_image(game->mlx_connection, game->image_emty_space);
	if (game->image_enemy)
		mlx_destroy_image(game->mlx_connection, game->image_enemy);
	if (game->image_player)
		mlx_destroy_image(game->mlx_connection, game->image_player);
	while (i < 7)
	{
		if (game->coin_frames[i][0] != '\0')
			mlx_destroy_image(game->mlx_connection, game->coin_frames[i]);
		i++;
	}
	mlx_destroy_window(game->mlx_connection, game->mlx_window);
	mlx_destroy_display(game->mlx_connection);
	free(game->mlx_connection);
}
