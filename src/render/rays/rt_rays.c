/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_rays.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:03:08 by rgramati          #+#    #+#             */
/*   Updated: 2024/05/19 17:02:06 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <ft/print.h>
#include <ft/mem.h>
#include <ft/math.h>
#include <ft/math/vector.h>
#include <rt/renderer.h>
#include <rt/object/sphere.h>
#include <rt/object/light.h>
#include <rt/object/camera.h>

void	rt_ray_cast(t_rt_scene *scene, t_rt_ray *ray, t_rt_hit *hit)
{
	size_t		i;
	t_rt_hit	closest;

	i = -1;
	while (++i < scene->objects_size)
	{
		if (scene->objects[i].options \
		&& scene->objects[i].intersect(*ray, &scene->objects[i], &closest))
		{
			hit->hit = true;
			if (closest.dist < hit->dist)
			{
				hit->obj = &scene->objects[i];
				hit->dist = closest.dist;
				hit->pos = ft_vec3d_add(ray->origin, ft_vec3d_mult(ray->dir, closest.dist));
			}
		}
	}
}

void	rt_ray_init(t_rt_scene *scene, t_rt_ray *ray, t_vec2i pixs)
{
	const t_rt_obj_camera	*cam = (t_rt_obj_camera *)scene->camera.options;
	const double			ratio = tan(cam->fov * 0.5 * RT_PI / 180);
	const t_vec3d			uv = ft_vec3d_norm(ft_vec3d( \
	ratio * ((2. * pixs.x - WIDTH) / HEIGHT), \
	ratio * ((2. * pixs.y - HEIGHT) / HEIGHT), 1.));
	const double			trig[4] = {cos(cam->angle.x), cos(cam->angle.y), sin(cam->angle.x), sin(cam->angle.y)};
	const t_vec3d			new = ft_vec3d( \
	uv.x*trig[1] + uv.y*trig[2]*trig[3] - uv.z*trig[0]*trig[3], \
	uv.y*trig[0] + uv.z*trig[2], \
	uv.x*trig[3] - uv.y*trig[2]*trig[1] + uv.z*trig[0]*trig[1]);

	ray->origin = scene->camera.pos;
	ray->dir = new;
}