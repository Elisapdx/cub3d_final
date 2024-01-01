/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:12:31 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 14:12:32 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

double	ft_abs(double num)
{
	if (num < 0)
		return (-num);
	return (num);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	fill_colors(char **color_table, int *to_fill)
{
	int	i;

	i = 0;
	while (color_table[i] && i < 3)
	{
		to_fill[i] = ft_atoi(color_table[i]);
		i++;
	}
}
