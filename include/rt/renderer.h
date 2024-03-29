/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiroussa <oss@xtrm.me>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 07:50:09 by kiroussa          #+#    #+#             */
/*   Updated: 2024/02/23 04:13:14 by kiroussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include <rt/error.h>
# include <rt/scene.h>

t_rt_error	rt_render(t_rt_scene *scene);

#endif // RENDERER_H
