/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:51:54 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/20 17:36:15 by ayelasef         ###   ########.fr       */
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
	void	*image_player;
	void	*image_coin;
	void	*image_exit;
	void	*image_emty_space;
	void	*image_wall;
	char	**map;
}		t_game;
//creat_2d_array
char **join_arr(char *line);
void	render_game(t_game *game, char **map);

//check_map
int	check_walls(char **map);
int	check_all_components(char **map);
int	check_one_component(char **map, char c);
int	chaeck_rectangular(char **map);
