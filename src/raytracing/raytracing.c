/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:59 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/16 12:34:53 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

static t_xyz get_ray_direction(int pixel_x, int pixel_y, t_camera *camera)
{
	float direction_x;
	float direction_y;
	t_xyz direction;

	//memset direction?

	//How far the ray is pointing left or right
	//
	direction_x = (2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1) * camera->aspect_ratio * camera->FOV_scale;
	//How far the ray is pointing up or down
	direction_y = (1 - 2 * ((pixel_y + 0.5f) / IMG_HEIGHT)) * camera->FOV_scale; //no aspect ratio?

	// Create the ray direction

	//We scale cam_right_view according to ray_dir_x. same for world_up and ray_dir_y.
	direction = vec_add(vec_scale(camera->right_view, direction_x), vec_scale(camera->world_up, direction_y));
	direction = vec_add(direction, camera->normOrientVec);
	direction = vec_normalize(direction);
	return (direction);
}

static void set_detailed_camera(t_camera *camera)
{
	camera->world_up = (t_xyz){0, 1, 0}; // can have problems?? The direction of up
	camera->right_view = vec_normalize(vec_cross(camera->world_up, camera->normOrientVec)); //Direction to the right of the camera
	camera->aspect_ratio = (float)IMG_WIDTH/IMG_HEIGHT;

	//FOV is the total angle a camera can see
	//tan input needs to be a radian, which is calculated as degrees * PI / 180.
	//We divide by two to get the angle from the center of the view, to the edge.
	//Tells how wide the camera view is at a certain distance.
	//Object near the camera = camera sees a wide area of the object. Object is "big".
	//Object further from the camera = camera sees a smaller area of the object. Object is "small".
	camera->FOV_scale = tanf((camera->FOV * M_PI / 180) / 2);
}

void raytracer(t_minirt *data)
{
	int x;
	int y;
	t_ray ray;
	t_intersection intersection;

	set_detailed_camera(data->camera);
	x = 0;
	y = 0;

	ray.origin = data->camera->coordinatesOfViewpoint; //test transfer x,y,z

	//loop through all pixels of screen
	while (y < IMG_HEIGHT)
	{
		while (x < IMG_WIDTH)
		{
			ray.direction = get_ray_direction(x, y, data->camera);
			intersection = intersect(data, ray);
			if (intersection.object.spheres)
			{
				printf("HIT FOR SPHERE, intersect coordinate is (%f, %f, %f)\n", intersection.coorinates.x, intersection.coorinates.y, intersection.coorinates.z);
				return ;
			}
			//object and coordinate to leo
			x++;
		}
		y++;
	}
}
