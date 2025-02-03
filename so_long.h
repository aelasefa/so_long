/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:51:54 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/02 12:33:51 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "get_next_line.h"
#include <mlx.h>
#include <string.h>

typedef struct s_game
{
	void	*mlx_connection;
	void	*mlx_window;
	int		player_x;
	int		player_y;
	int		coin_nbr;
	int		total_coin;
	int		map_width;
	int		map_height;
	int		img_width;
	int		img_height;
	int		count_frames;
	int		moves;
	int		collected_coins;
	int		enemy_x;
	int		enemy_y;
	int		curr_frames;
	int		map_x;
	int		map_y;
	char	*coin_frames[7];
	void	*image_player;
	void	*image_coin;
	void	*image_exit;
	void	*image_emty_space;
	void	*image_wall;
	void	*image_enemy;
	void	*image_exit_player;
	char	**map;
	char	**map_copy;
	int		exit_found;
}			t_game;
// creat_2d_array
char		**join_arr(char *line);
void		render_game(t_game *game);
// map_to_image
void		ft_change_map_to_images(char **map, t_game *game);
// ft_itoa
char		*ft_itoa(int n);
int			animation_coins(t_game *window);

// check_map
int			check_walls(char **map);
int			check_all_components(char **map);
int			check_one_component(char **map, char c);
int			chaeck_rectangular(char **map);

// coin_animation
void		animation_coins_ul(t_game *window);
int			game_loop(t_game *game);
int			ft_total_coin(char **map);

// enemy_place
void		place_enemy_center(t_game *game);
//flood_fill
char	**ft_map_copy(t_game *game, char **map, int y);
int	is_map_valid(t_game *game,char **map, int width, int height);
void	flood_fill(t_game *game, int x, int y);


// move_player
void		ft_move_player(int key, int *new_x, int *new_y);
void		ft_collect_coins(t_game *game, int *new_x, int *new_y);
int			key_hook(int key, void *game_ptr, char **map);
void		render_game(t_game *game);
