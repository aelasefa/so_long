/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_2d_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 17:31:24 by ayelasef          #+#    #+#             */
/*   Updated: 2025/02/11 09:28:13 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	count_line(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\n' || line[i + 1] == '\0')
			count++;
		i++;
	}
	return (count);
}

char	**join_arr(char *line)
{
	char	(**arr);

	int (i), (j), (index), count;
	count = count_line(line);
	arr = NULL;
	arr = malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	index = 0;
	while (line[i] != '\0')
	{
		j = i;
		while (line[i] != '\n' && line[i])
			i++;
		if (line[i] == '\n')
			i++;
		arr[index] = malloc(i - j + 1);
		if (!arr[index])
			return (NULL);
		ft_strlcpy(arr[index], line + j, i - j + 1);
		index++;
	}
	return (arr[index] = NULL, free(line), arr);
}

int	check_map_2(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (game->map[y])
	{
		x = 0;
		while (game->map[y][x])
		{
			if (game->map[y][x] != '0' && game->map[y][x] != 'P'
				&& game->map[y][x] != '1' && game->map[y][x] != 'E'
				&& game->map[y][x] != 'C' && game->map[y][x] != '\n'
				&& game->map[y][x] != 'X')
				return (game->map_flag = 5, 0);
			x++;
		}
		y++;
	}
	return (1);
}
