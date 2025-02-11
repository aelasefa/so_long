/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 12:31:23 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 08:34:52 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	ft_move_player(t_game *game, int key, int *new_x, int *new_y)
{
	if (key == 97 || key == 65361)
		(*new_x)--;
	if (key == 100 || key == 65363)
		(*new_x)++;
	if (key == 119 || key == 65362)
		(*new_y)--;
	if (key == 115 || key == 65364)
		(*new_y)++;
	else if (key == 65307)
	{
		free_game_resources(game);
		exit(0);
	}
}

void	ft_collect_coins(t_game *game, int *new_x, int *new_y)
{
	if (game->map[*new_y][*new_x] == 'C')
	{
		game->coin_nbr++;
		game->map[*new_y][*new_x] = '0';
	}
	if (game->map[*new_y][*new_x] == 'E')
	{
		if (game->coin_nbr == game->total_coin)
		{
			ft_printf("You Win\n");
			free_game_resources(game);
			exit(0);
		}
	}
}

int	close_window(t_game *game)
{
	free_game_resources(game);
	exit(0);
	return (0);
}

int	key_hook(int key, void *game_ptr, char **map)
{
	t_game	*game;

	game = (t_game *)game_ptr;
	int (new_x), new_y;
	new_x = game->player_x;
	new_y = game->player_y;
	ft_move_player(game, key, &new_x, &new_y);
	if (game->map[new_y][new_x] != '1')
	{
		ft_collect_coins(game, &new_x, &new_y);
		if (game->map[new_y][new_x] == 'X')
			ft_lose(game);
		if (game->map[game->player_y][game->player_x] != 'E')
		{
			game->map[game->player_y][game->player_x] = '0';
			game->map[new_y][new_x] = 'P';
		}
		game->player_x = new_x;
		game->player_y = new_y;
		if (check_key(key))
			increment_and_print_move(game);
	}
	render_game(game);
	return (0);
}

void	render_game(t_game *game)
{
	char	*tmp;

	ft_change_map_to_images(game->map, game);
	mlx_put_image_to_window(game->mlx_connection, game->mlx_window,
		game->image_player, game->player_x * 64, game->player_y * 64);
	tmp = ft_itoa(game->moves);
	mlx_string_put(game->mlx_connection, game->mlx_window, 1 * 64, 1 * 64,
		0xFFFFFFF, tmp);
	free(tmp);
}
