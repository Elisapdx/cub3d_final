/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cleanup_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epraduro <epraduro@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:12:20 by epraduro          #+#    #+#             */
/*   Updated: 2024/01/01 14:12:21 by epraduro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/bonus/cub3d_bonus.h"
#include "../inc/bonus/err_type_bonus.h"

void	free_double_p(char **table)
{
	int	i;

	i = -1;
	while (table[++i])
		free(table[i]);
	free(table);
	table = NULL;
}

int	free_table_err(t_config **conf, char *message, int r_value)
{
	if ((*conf)->map->file)
		free_double_p((*conf)->map->file);
	if ((*conf)->map->sketch)
		free((*conf)->map->sketch);
	if ((*conf)->data)
		free((*conf)->data);
	if (*conf)
		free(*conf);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	return (r_value);
}

void	*free_void_err(t_config **conf, char *message)
{
	if ((*conf)->map->file)
		free_double_p((*conf)->map->file);
	if ((*conf)->map->sketch)
		free((*conf)->map->sketch);
	if ((*conf)->data)
		free((*conf)->data);
	if (*conf)
		free(*conf);
	if (message)
		ft_putendl_fd(message, STDERR_FILENO);
	return (NULL);
}

int	ft_close(t_config **conf)
{
	if ((*conf)->mlx->win)
		mlx_destroy_window((*conf)->mlx->mlx, (*conf)->mlx->win);
	if ((*conf)->mlx->img)
		mlx_destroy_image((*conf)->mlx->mlx, (*conf)->mlx->img);
	if ((*conf)->mlx)
		free((*conf)->mlx);
	if ((*conf)->map->file)
		free_double_p((*conf)->map->file);
	if ((*conf)->map->sketch)
		free((*conf)->map->sketch);
	if ((*conf)->data)
		free((*conf)->data);
	if (*conf)
		free(*conf);
	exit(EXIT_SUCCESS);
	return (SUCCESS);
}
