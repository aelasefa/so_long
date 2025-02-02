/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:33:30 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/20 17:36:00 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	chaeck_rectangular(char **map)
{
	size_t	len;
	size_t	len_last;
	size_t	len_y;
	int		y;
	int		i;
	char	*last_line;

	y = 0;
	while (map[y])
		y++;
	y--;
	len = ft_strlen(map[0]);
	len_last = ft_strlen(map[y]);
	if (len != len_last)
		return (0);
	i = 0;
	while (map[i])
	{
		len_y = ft_strlen(map[i]);
		if (ft_strlen(map[0]) != len_y)
			return (0);
		i++;
	}
	return (1);
}

int	check_one_component(char **map, char c)
{
	int	x;
	int	y;
	int	count;

	y = 0;
	count = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x] != '\0')
		{
			if (map[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}

int	check_all_components(char **map)
{
	if (check_one_component(map, 'E') != 1 || check_one_component(map, 'P') != 1
		|| check_one_component(map, 'C') == 0)
		return (0);
	return (1);
}

int	check_walls(char **map)
{
	int x, (y), (last_of_line);
	last_of_line = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		last_of_line = ft_strlen(map[y]) - 2;
		if (map[y][x++] != '1' || map[y][last_of_line] != '1')
			return (0);
		while (map[y][x] != '\n')
		{
			if (map[0][x] != '1')
				return (0);
			x++;
		}
		y++;
	}
	y--;
	x = 0;
	while (map[y][x] != '\n')
	{
		if (map[y][x] != '1')
			return (0);
		x++;
	}
	return (1);
}

int	is_map_valid(char **map, int width, int height)
{
	int		x;
	int		y;
	int		player_x;
	int		player_y;
	int		total_coins;
	int		collected_coins;
	int		exit_found;
	char	**map_copy;

	player_x = -1;
	player_y = -1;
	total_coins = 0;
	collected_coins = 0;
	exit_found = 0;
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			if (map[y][x] == 'P')
			{
				player_x = x;
				player_y = y;
			}
			if (map[y][x] == 'C')
				total_coins++;
			x++;
		}
		y++;
	}
	if (player_x == -1 || player_y == -1)
		return (0);
	map_copy = ft_map_copy(map, height);
	flood_fill(map_copy, player_x, player_y, &exit_found, &collected_coins);
	return (collected_coins == total_coins && exit_found);
}
