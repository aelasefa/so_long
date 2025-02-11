/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_map_or_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 20:41:07 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 09:59:33 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	free_map_and_print(t_game *game, char **map, char *str)
{
	free_map(map);
	free(game->enemy_x);
	free(game->enemy_y);
	write(1, str, ft_strlen(str));
	exit(1);
}

void	invalid_map(char **map, t_game *game)
{
	if (!chaeck_rectangular(map, game) || !check_all_components(map, game)
		|| !check_walls(map, game) || !is_map_valid(game, map, game->map_width,
			game->map_height))
	{
		if (game->map_flag == 1)
			free_map_and_print(game, map, "Error\nmap dosen't rectangular\n");
		else if (game->map_flag == 2)
			free_map_and_print(game, map,
				"Error\nmap dosen't have all components\n");
		else if (game->map_flag == 3)
			free_map_and_print(game, map,
				"Error\nmap dosen't closed by walls\n");
		else if (game->map_flag == 4)
			free_map_and_print(game, map, "Error\none components is closed\n");
	}
}

void	ft_lose(t_game *game)
{
	ft_printf("You lose\n");
	free_game_resources(game);
	exit(1);
}

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
	free_enemy(game);
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
	while (game->i < 7)
	{
		if (game->coin_frames[game->i])
			mlx_destroy_image(game->mlx_connection, game->coin_frames[game->i]);
		game->i++;
	}
	if (game->mlx_window)
		mlx_destroy_window(game->mlx_connection, game->mlx_window);
	if (game->mlx_connection)
	{
		mlx_destroy_display(game->mlx_connection);
		free(game->mlx_connection);
	}
}
