#include "../Lib/Libft/inc/libft.h"

/* cub3D custom define */
# define FAILS -1
# define ERROR 2
# define SUCCES 0

/* List of Error messages */
# define ARG_ERR "Error\nPlease provide a valid [.cub] map."
# define OPEN_ERR "Error\nFailed to open the file."
# define CLOSE_ERR "Error\nFailed to close the file."
# define MALLOC_ERR "Error\nFailed to malloc"
# define DIR_ERR "Error\nCan't open a directory"
# define EMPTY_ERR "Error\nNo Map was collected"
# define PLAYER_ERR "Error\nCannot have more than one player"
# define CHAR_ERR "Error\nFound an invalid char in the map"
# define XPM_ERR "Error\nThe file is not a .xpm or there is an invalid char on the line"
# define COLOR_ERR "Error\nPlease give a different color for the sky and the ground"
# define NB_COLOR_ERR "Error\nPlease give a number between 0 and 255"
# define FORMAT_ERR "Error\nPlease follow the RGB format"
# define ELEMENT_ERR "Error\nPlease give 6 elements or be careful to give them the right format"
# define PATH_ERR "Error\nTexture wrong path"
# define MINMAP_ERR "Error\nError with minimap"