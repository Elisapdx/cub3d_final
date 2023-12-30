#include "cub3d.h"
#include "parse_err.h"

int	inspect_map_bonus(t_config **conf)
{
	int		i;
	char	**tmp;

	i = -1;
	(*conf)->player = 0;
	while ((*conf)->map[++i])
	{
		if (inspect_line(conf, (*conf)->map[i], "102 NWES") == false)
			return (ft_putendl_fd(CHAR_ERR, STDERR_FILENO));
		else if ((*conf)->player > 1)
			return (ft_putendl_fd(PLAYER_ERR, STDERR_FILENO));
	}
	printf("numb of player: %d\n", (*conf)->player);
	tmp = map_dup(conf, (*conf)->map);
	if (!tmp)
		return (ft_putendl_fd(MALLOC_ERR, STDERR_FILENO));
	//here
	if (flood_fill(conf, tmp) == false)
		return (FAILS);
	return (0);
}