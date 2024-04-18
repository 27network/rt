/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/23 03:19:27 by kiroussa          #+#    #+#             */
/*   Updated: 2024/04/18 19:49:31 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLANE_H
# define PLANE_H

# include <ft/math/vector.h>

typedef struct s_rt_obj_plane
{
	t_vec3d	size;
}	t_rt_obj_plane;

t_rt_obj_plane	*rt_obj_plane_init(double sx, double sy);

#endif // PLANE_H