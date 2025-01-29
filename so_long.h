/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:51:54 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/28 16:45:48 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "get_next_line.h"
#include <mlx.h>

typedef struct s_game
{
	void *mlx_connection;
	void *mlx_window;
	int	player_x;
	int	player_y;
	int	coin_nbr;
	int	total_coin;
	int	map_width;
	int	map_height;
	int	moves;
	int	enemy_x;
	int	enemy_y;
	int	frame_count;
	void	*image_player;
	void	*image_coin;
	void	*image_exit;
	void	*image_emty_space;
	void	*image_wall;
	void	*image_enemy;
	void	*image_exit_player;
	char	**map;
}		t_game;
//creat_2d_array
char **join_arr(char *line);
void	render_game(t_game *game);
void	ft_change_map_to_images(char **map, t_game *game);
//ft_itoa
char	*ft_itoa(int n);

//check_map
int	check_walls(char **map);
int	check_all_components(char **map);
int	check_one_component(char **map, char c);
int	chaeck_rectangular(char **map);
