/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ayelasef <ayelasef@1337.ma>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 16:06:30 by ayelasef          #+#    #+#             */
/*   Updated: 2025/01/28 16:07:11 by ayelasef         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

static int	ft_count_nb(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	else if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n > 0)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static char	*ft_rev(char *str)
{
	int		i;
	int		j;
	char	tmp;

	i = 0;
	j = ft_strlen(str) - 1;
	if (str[0] == '-')
		i = 1;
	while (i < j)
	{
		tmp = str[i];
		str[i] = str[j];
		str[j] = tmp;
		i++;
		j--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	char	*arr;
	int		i;
	long	nn;

	nn = n;
	i = 0;
	arr = malloc(sizeof(char) * ft_count_nb(nn) + 1);
	if (!arr)
		return (NULL);
	if (nn == 0)
		arr[i++] = '0';
	if (n < 0)
	{
		arr[i++] = '-';
		nn *= -1;
	}
	while (nn > 0)
	{
		arr[i] = (nn % 10) + '0';
		nn /= 10;
		i++;
	}
	arr[i] = '\0';
	return (ft_rev(arr));
}


