/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:59 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/15 12:37:10 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

void raytracer(t_minirt *data)
{
	int x;
	int y;
	t_ray ray;
	t_xyz camera_forward; //set in camera struct instead?, but still here
	t_xyz world_up;
	t_xyz camera_right_view;
	float aspect_ratio;
	float FOV_scale;

	camera_forward = data->camera->normOrientVec; //already normalized?? fix in parsing check that is. The direction of the camera
	world_up = (t_xyz){0, 1, 0}; // can have problems?? The direction of up
	camera_right_view = vec_normalize(vec_cross(world_up, camera_forward)); //Direction to the right of the camera
	aspect_ratio = (float)IMG_WIDTH/IMG_HEIGHT;

	//FOV is the total angle a camera can see
	//tan input needs to be a radian, which is calculated as degrees * PI / 180.
	//We divide by two to get the angle from the center of the view, to the edge.
	//Tells how wide the camera view is at a certain distance.
	//Object near the camera = camera sees a wide area of the object. Object is "big".
	//Object further from the camera = camera sees a smaller area of the object. Object is "small".
	FOV_scale = tanf((data->camera->FOV * M_PI / 180) / 2);


	x = 0;
	y = 0;

	ray.origin = data->camera->coordinatesOfViewpoint; //can i even do this?
	//loop through all pixels of screen
	while (y < IMG_HEIGHT)
	{
		while (x < IMG_WIDTH)
		{
			//How far the ray is pointing left or right
			//
			float ray_direction_x = (2 * ((x + 0.5f) / IMG_WIDTH) - 1) * aspect_ratio * FOV_scale;
			//How far the ray is pointing up or down
			float ray_direction_y = (1 - 2 * ((y + 0.5f) / IMG_HEIGHT)) * FOV_scale; //no aspect ratio?

			// Create the ray direction

			//We scale cam_right_view according to ray_dir_x. same for world_up and ray_dir_y. 
			ray.direction = vec_add(vec_scale(camera_right_view, ray_direction_x), vec_scale(world_up, ray_direction_y));
			ray.direction = vec_add(ray.direction, camera_forward);
			ray.direction = vec_normalize(ray.direction);
			//printf("\n\n\nray direction: %f and %f and %f\n", ray.direction.x, ray.direction.y, ray.direction.z);
			//printf("ray origin (coord of viewpoint): %f and %f and %f\n", ray.origin.x, ray.origin.y, ray.origin.z);
			float intersection = intersect(data, ray);
			if (intersection > -1.0)
			{
				printf("HIT FOR SPHERE, intersect is %f\n", intersection);
				return ;
			}
			//object and coordinate to leo
			x++;
		}
		y++;
	}
}
