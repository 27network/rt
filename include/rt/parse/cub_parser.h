/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parser.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/26 20:26:57 by rgramati          #+#    #+#             */
/*   Updated: 2024/06/01 16:15:38 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_PARSER_H
# define CUB_PARSER_H
#include "rt/scene.h"
# undef CUB_PARSER_H
# ifndef __CUB_PARSER_H__
#  define __CUB_PARSER_H__

#  include <ft/io.h>

#  define NOATTR "Excepted one of {\"NO\",\"SO\",\"EA\",\"WE\",\"F\",\"C\"}"
#  define NOCHAR "Unexcepted character"

#  include <rt/renderer.h>

typedef enum e_cub_wall_mask
{
	CUB_ZERO = 0,
	CUB_NOR = 1 << 0,
	CUB_EAS = 1 << 1,
	CUB_SOU = 1 << 2,
	CUB_WES = 1 << 3,
	CUB_HOR = 1 << 4,
	CUB_NEG = 1 << 5,
}	t_wall_mask;

typedef struct s_char_list
{
	char				*line;
	struct s_char_list	*next;
}	t_clist;

typedef struct s_cub_map
{
	t_clist		*map_list;
	char		**map;
	int			wall_count;
	int			width;
	int			height;
	char		*textures[4];
	t_toc_color	colors[2];
	int			fd;
}	t_cub_map;

typedef struct s_cub_parser
{
	t_wall_mask	mask;
	t_rt_object	*walls;
	t_toc_vec2i	pos;
}	t_cub_parser;

t_clist		*rt_clist_new(
				char *line
				);

void		rt_clist_add_back(
				t_clist **list,
				t_clist *new
				);

void		rt_clist_del(
				t_clist *list
				);

t_rt_error	rt_cub_parse_file(
				t_cub_map *map,
				const char *file
				);

t_rt_error	rt_cub_parse_map_line(
				t_cub_map *map,
				char **line,
				const char *file,
				int *lc
				);

t_rt_error	rt_cub_parse_attribute(
				t_cub_map *map,
				char **line,
				const char *filename,
				int *lc
				);

t_rt_error	rt_cub_check_map(
				t_cub_map *map
				);

t_rt_error	rt_cub_convert_map(
				t_cub_map *map,
				t_rt_object **objects
				);

t_rt_error	rt_cub_map_error(
				t_cub_map *map,
				const char *msg,
				t_rt_error err
				);

# endif // __CUB_PARSER_H__
#endif // CUB_PARSER_H