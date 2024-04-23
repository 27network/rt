/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_obj_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgramati <rgramati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 13:39:30 by rgramati          #+#    #+#             */
/*   Updated: 2024/04/23 22:31:50 by rgramati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <ft/math.h>
#include <ft/print.h>
#include <rt/object/cylinder.h>

void	rt_swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

bool	rt_obj_cylinder_delta(
	t_rt_ray ray,
	t_rt_object *obj,	
	t_rt_hit *hit,
	double *t_s)
{
	if (t_s[2] > t_s[1] || t_s[3] < t_s[0])
		return (false);
	t_s[4] = ft_fmax(t_s[0], t_s[2]);
	if (t_s[4] < 0)
		t_s[4] = ft_fmin(t_s[1], t_s[3]);
	if (t_s[4] <= 0)
		return (false);
	return (rt_hit_update(t_s[4], ray, obj, hit));
}

void	rt_obj_cylinder_cut(
	t_rt_ray ray,
	t_rt_object *obj,
	double *t_s)
{
	t_rt_obj_cylinder	*cyl;
	t_vec3d				tmp_vects[3];
	double				eq_params[4];
	double				delta_root;

	cyl = (t_rt_obj_cylinder *)obj->options;
	tmp_vects[0] = ft_vec3d_cross(ray.direction, cyl->norm);
	eq_params[0] = ft_vec3d_dot(tmp_vects[0], tmp_vects[0]);
	tmp_vects[1] = ft_vec3d_sub(ray.origin, obj->position);
	tmp_vects[2] = ft_vec3d_cross(tmp_vects[1], cyl->norm);
	eq_params[1] = 2 * ft_vec3d_dot(tmp_vects[0], tmp_vects[2]);
	eq_params[2] = ft_vec3d_dot(tmp_vects[2], tmp_vects[2])
		 - ft_fpow(cyl->diameter / 2.0f, 2);
	eq_params[3] = ft_fpow(eq_params[1], 2) - (4 * eq_params[0] * eq_params[2]);
	delta_root = sqrt(eq_params[3]);
	t_s[0] = ((-eq_params[1] - delta_root) / (2 * eq_params[0]));
	t_s[1] = ((-eq_params[1] + delta_root) / (2 * eq_params[0]));
	if (t_s[0] > t_s[1])
	{
		double tmp;
		tmp = t_s[0];
		t_s[0] = t_s[1];
		t_s[1] = tmp;
	}
}

bool	rt_obj_cylinder_intersect(
	t_rt_ray ray,
	t_rt_object *obj,
	t_rt_hit *hit)
{
	t_rt_obj_cylinder	*cyl;
	double	t_s[5];
	double	tmps[2];
	t_vec3d	tmp_vects[2];

	cyl = (t_rt_obj_cylinder *)obj->options;
	rt_obj_cylinder_cut(ray, obj, t_s);
	tmp_vects[0] = ft_vec3d_mult(cyl->norm, cyl->height / 2.0f);
	tmp_vects[1] = ft_vec3d_add(obj->position, tmp_vects[0]);
	tmps[0] = ft_vec3d_dot(ft_vec3d_sub(tmp_vects[1], ray.origin), cyl->norm);
	tmps[1] = ft_vec3d_dot(ray.direction, cyl->norm);
	t_s[2] = (tmps[0] + cyl->height / 2.0f) / tmps[1];
	t_s[3] = (tmps[0] - cyl->height / 2.0f) / tmps[1];
	if (t_s[2] > t_s[3])
	{
		double tmp;
		tmp = t_s[2];
		t_s[2] = t_s[3];
		t_s[3] = tmp;
	}
	return (rt_obj_cylinder_delta(ray, obj, hit, t_s));
}

t_vec3d	rt_obj_cylinder_norm(
	t_rt_ray ray,
	t_rt_hit hit)
{
	t_rt_obj_cylinder	*cyl;

	cyl = (t_rt_obj_cylinder *)hit.hit_object->options;
	if (ft_vec3d_dot(ray.direction, cyl->norm) > 0.0)
  		return (ft_vec3d_mult(cyl->norm, -1.0f));
	else
  		return (cyl->norm);
}