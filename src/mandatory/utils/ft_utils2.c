/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 13:50:45 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 13:50:46 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/mandatory/cub3d.h"
#include "../inc/mandatory/err_type.h"

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
