#include "so_long.h"
#include <stdio.h>
#include <stdlib.h>

// Function to render the game map
void ft_change_map_to_images(char **map, t_game *game)
{
    int x, y, pixel_x, pixel_y;
    int image_width, image_height;

    // Load images
    game->image_wall = mlx_xpm_file_to_image(game->mlx_connection, "/home/ayelasef/Desktop/so_long/assets/wall.xpm", &image_width, &image_height);
    game->image_player = mlx_xpm_file_to_image(game->mlx_connection, "/home/ayelasef/Desktop/so_long/assets/player.xpm", &image_width, &image_height);
    game->image_coin = mlx_xpm_file_to_image(game->mlx_connection, "/home/ayelasef/Desktop/so_long/assets/coin.xpm", &image_width, &image_height);
    game->image_emty_space = mlx_xpm_file_to_image(game->mlx_connection, "/home/ayelasef/Desktop/so_long/assets/emty_space.xpm", &image_width, &image_height);
    game->image_exit = mlx_xpm_file_to_image(game->mlx_connection, "/home/ayelasef/Desktop/so_long/assets/exit.xpm", &image_width, &image_height);

    if (!game->image_wall || !game->image_player || !game->image_coin || !game->image_emty_space || !game->image_exit)
    {
        fprintf(stderr, "Failed to load images.\n");
        exit(1);
    }

    // Render the map
    y = 0;
    while (map[y])
    {
        x = 0;
        while (map[y][x])
        {
            pixel_x = x * 64;
            pixel_y = y * 64;
            if (map[y][x] == '1')
                mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_wall, pixel_x, pixel_y);
            else if (map[y][x] == 'P')
            {
                game->player_x = x;
                game->player_y = y;
                mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_player, pixel_x, pixel_y);
            }
            else if (map[y][x] == 'C')
                mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_coin, pixel_x, pixel_y);
            else if (map[y][x] == '0')
                mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_emty_space, pixel_x, pixel_y);
            else if (map[y][x] == 'E')
                mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_exit, pixel_x, pixel_y);

            x++;
        }
        y++;
    }
}

// Function to render the entire game (including player)
void render_game(t_game *game, char **map)
{
    mlx_clear_window(game->mlx_connection, game->mlx_window);
    ft_change_map_to_images(map, game);
    mlx_put_image_to_window(game->mlx_connection, game->mlx_window, game->image_player, game->player_x * 64, game->player_y * 64);
}

// Key hook function to handle player movement
int key_hook(int key, void *param)
{
    t_game *game = (t_game *)param;

    if (key == 97) // 'A'
        game->player_x--;
    else if (key == 100) // 'D'
        game->player_x++;
    else if (key == 119) // 'W'
        game->player_y--;
    else if (key == 115) // 'S'
        game->player_y++;
    else if (key == 65307) // Escape key
        exit(0);

    render_game(game, game->map);
    return (0);
}

int main()
{
    int fd;
    char *line = NULL;
    char **map = NULL;
    char *line_tmp = "";
    t_game game;

    // Open and read the map file
    fd = open("map.ber", O_RDONLY);
    if (fd < 0)
    {
        fprintf(stderr, "Error: Could not open map file.\n");
        return (1);
    }

    while ((line = get_next_line(fd)))
    {
        line_tmp = ft_strjoin_get_line(line_tmp, line);
        free(line);
    }
    close(fd);

    map = join_arr(line_tmp);
    free(line_tmp);

    if (!chaeck_rectangular(map) || !check_all_components(map) || !check_walls(map))
    {
        fprintf(stderr, "Error: Invalid map.\n");
        return (1);
    }

    // Initialize game variables
    game.map = map;
    game.mlx_connection = mlx_init();
    int map_width = 0;
    while (map[0][map_width])
        map_width++;
    int map_height = 0;
    while (map[map_height])
        map_height++;

    game.mlx_window = mlx_new_window(game.mlx_connection, map_width * 64, map_height * 64, "SO_LONG");

    // Render the initial map
    ft_change_map_to_images(map, &game);

    // Set up key hook
    mlx_key_hook(game.mlx_window, key_hook, &game);

    // Start the event loop
    mlx_loop(game.mlx_connection);

    return 0;
}

