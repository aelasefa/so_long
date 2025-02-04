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
	char	*last_line;

	int (y), (i);
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
			else if (map[y][x] == '1')
				x++;
			else if (map[y][x] == ' ')
				return (0);
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

void	help_function(int *y, int *x)
{
	*y = *y - 1;
	*x = 0;
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
	help_function(&y, &x);
	while (map[y][x] != '\n')
	{
		if (map[y][x] != '1')
			return (0);
		x++;
	}
	return (1);
}
