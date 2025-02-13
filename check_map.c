/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:33:30 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 08:43:55 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int	check_rectangular(char **map, t_game *game)
{
	size_t (len);
	size_t (len_last);
	size_t (len_y);
	int (y), (i);
	y = 0;
	while (map[y])
		y++;
	y--;
	len = ft_strlen(map[0]);
	len_last = ft_strlen(map[y]);
	if (map[y][len_last - 1] != '\n')
		len_last += 1;
	if (len != len_last)
		return (game->map_flag = 1, 0);
	i = 0;
	while (map[i + 1] != NULL)
	{
		len_y = ft_strlen(map[i]);
		if (len != len_y)
			return (game->map_flag = 1, 0);
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
			else if (map[y][x] == ' ')
				return (0);
			x++;
		}
		y++;
	}
	return (count);
}

int	check_all_components(char **map, t_game *game)
{
	if (check_one_component(map, 'E') != 1 || check_one_component(map, 'P') != 1
		|| check_one_component(map, 'C') == 0)
	{
		game->map_flag = 2;
		return (0);
	}
	return (1);
}

int	help_function(int *y, int *x, char **map, t_game *game)
{
	*y = *y - 1;
	*x = 0;
	while (map[*y][*x] != '\0')
	{
		if (map[*y][*x] != '1')
			return (game->map_flag = 3, 0);
		(*x)++;
	}
	return (1);
}

int	check_walls(char **map, t_game *game)
{
	int x, (y), (last_of_line);
	last_of_line = 0;
	y = 0;
	while (map[y])
	{
		x = 0;
		last_of_line = ft_strlen(map[y]) - 2;
		if (map[y + 1] == NULL && map[y][last_of_line] != '\n')
			last_of_line = ft_strlen(map[y]) - 1;
		if (map[y][0] != '1' || map[y][last_of_line] != '1')
			return (game->map_flag = 3, 0);
		if (y == 0)
		{
			while (map[y][x] != '\0')
			{
				if (map[y][x] != '1' && map[y][x] != '\n')
					return (game->map_flag = 3, 0);
				x++;
			}
		}
		y++;
	}
	if (!help_function(&y, &x, map, game))
		return (0);
	return (1);
}
