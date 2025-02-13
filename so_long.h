/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 14:51:54 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 09:58:01 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf/ft_printf.h"
#include "get_next_line.h"
#include <mlx.h>
#include <string.h>
#include <time.h>

typedef struct s_game
{
	int		*enemy_x;
	int		*enemy_y;
	char	move_enemy;
	int		count_enemy;
	int		exit_x;
	int		exit_y;
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
	int		collected_coins_f;
	int		curr_frames;
	int		map_x;
	int		map_y;
	int		i;
	int		j;
	int		map_flag;
	char	*coin_frames[7];
	void	*image_player;
	void	*image_coin;
	void	*image_exit;
	void	*image_emty_space;
	void	*image_wall;
	void	*image_enemy;
	char	**map;
	char	**map_copy;
	int		exit_found;
	int		enemy_found;
	int		player_x_f;
	int		player_y_f;
	int		total_coins_f;
	int		check_move;
	// void	*img;
}			t_game;
// creat_2d_array
char		**join_arr(char *line);
void		render_game(t_game *game);
int			check_map_2(t_game *game);
// map_to_image
void		ft_change_map_to_images(char **map, t_game *game);
// ft_itoa
char		*ft_itoa(int n);
int			animation_coins(t_game *window);

// check_map
int			check_walls(char **map, t_game *game);
int			check_all_components(char **map, t_game *game);
int			check_one_component(char **map, char c);
int			check_rectangular(char **map, t_game *game);

// coin_animation
void		animation_coins_ul(t_game *window);
int			game_loop(t_game *game);
int			ft_total_coin(char **map);

// enemy_place
void		place_enemy_center(t_game *game);
// flood_fill
char		**ft_map_copy(t_game *game, char **map, int y);
int			is_map_valid(t_game *game, char **map, int width, int height);
void		flood_fill(t_game *game, int x, int y);
void		check_player_and_coin(t_game *game, int width, int height);

// move_player
void		ft_move_player(t_game *game, int key, int *new_x, int *new_y);
void		ft_collect_coins(t_game *game, int *new_x, int *new_y);
int			key_hook(int key, void *game_ptr, char **map);
void		render_game(t_game *game);
int			close_window(t_game *game);

// free_map_or_game
void		free_game_resources(t_game *game);
void		free_map(char **map);
void		ft_lose(t_game *game);
void		free_map_and_print(t_game *game, char **map, char *str);
void		invalid_map(char **map, t_game *game);
void		file_to_image(t_game *game, int image_width, int image_height);
// draw_player_and_exit
void		draw_player(t_game *game, int x, int y);
void		draw_exit(t_game *game, int x, int y);
void		draw_enemy(t_game *game, int x, int y);
int			check_key(int key);
void		increment_and_print_move(t_game *game);

// mouve_enemy
void		render_enemies(t_game *game);
int			enemy_loop(t_game *game);

// move_enmey_2
int			ft_count_enemy(char **map);
char		get_random_move(void);
void		free_enemy(t_game *game);
// intialize

void		initialize_values_2(t_game *game, char **map);
void		initialize_values(t_game *game, char **map);
