/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 14:49:44 by rgramati          #+#    #+#             */
/*   Updated: 2024/04/20 23:26:09 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <ft/print.h>
#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/renderer.h>
#include <rt/object/sphere.h>

bool	rt_obj_sphere_intersect(t_rt_ray ray, t_rt_object *obj, t_rt_hit *hit)
{
	t_vec3d			c_to_r;
	double			params[3];
	double			delta;
	double			t;

	params[0] = ft_vec3d_dot(ray.direction, ray.direction);
	c_to_r = ft_vec3d_sub(ray.origin, obj->position);
	params[1] = 2 * ft_vec3d_dot(c_to_r, ray.direction);
	params[2] = ft_vec3d_dot(c_to_r, c_to_r)
		- ft_fpow(((t_rt_obj_sphere *)obj->options)->diameter / 2, 2);
	delta = ft_fpow(params[1], 2) - (4 * params[0] * params[2]);
	if (delta < 0 || fabs(params[0]) < PRECISION)
		return (false);
	if (fabs(delta) < PRECISION)
	{
		hit->position = ft_vec3d_add(ray.origin,
				ft_vec3d_mult(ray.direction, -params[2] / (2 * params[0])));
		hit->hit_object = obj;
		return (true);
	}
	t = ((-params[1] + (sqrt(delta))) / (2 * params[0]));
	if (t > ((-params[1] - (sqrt(delta))) / (2 * params[0])))
		t = ((-params[1] - (sqrt(delta))) / (2 * params[0]));
	hit->position = ft_vec3d_add(ray.origin, ft_vec3d_mult(ray.direction, t));
	return (true);
}