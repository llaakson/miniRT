/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:59 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/16 18:32:01 by aalbrech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/miniRT.h"

/*
Arguments:
x- and y-coordinate of where on the screen we are (which pixel).
The camera struct.

Description:
Create a direction for a ray coming from the camera. The direction points to a certain pixel on the screen.

----Calculate scalar_x (how far the ray is pointing to the left or right)------------------------

1. We center the calculation to go right through the pixel, not on some edge of it.
pixel_x + 0.5f

2. Divide that by the IMG_WIDTH, to get a value between 0-1. That is a scalar of where on the screen we
are horizontally. 0 meaning left edge, 1 meaning right edge, and 0.5 meaning in the middle of the screen.
(pixel_x + 0.5f) / IMG_WIDTH

3. Multiply that by 2 and subract by 1. Since we want the space/screen to be x=0 at the center, and not x=0.5 to be the centre, we make a new scalar
going from -1 to 1. Vector scaling would work wrong if we don't fix this. -1 = left edge, 0 middle of screen, 1 right edge
2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1

4. For the width of the screen we only have a certain amount of rays to use. There's one ray for every pixel_y, but not a ray for every pixel_x
(if the screen doesn't happen to be square). To cover the whole screen, we need to distribute the rays evenly. We do that by scaling scalar_x
with the aspect ratio.
(2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1) * camera->aspect_ratio

5. The same goes for the camera field of view (FOV) and the scene we are making. We need to distribute the rays to correctly interpret the FOV.
Camera zoomed out (wide FOV) = camera sees more of the scene = rays need to cover a larger area = rays are furher apart from each other.
Camera zoomed in (narrow FOV) = camera sees less of the scene  = rays need to cover a smaller area = rays are closer to each other.

----Calculate scalar_y (how far the ray is pointing up or down)----------------------------------

This scalar instead shows where on the screen we are vertically.
-1 meaning the bottom of the screen, 0 middle of screen, 1 the top of the screen.

1. pixel_y + 0.5f

2. (pixel_y + 0.5f) / IMG_HEIGHT

3. The screen pixel coordinates go from smallest at upper left corner to biggest at bottom right corner,
which would mean that the smaller y is, the more "up" we are.
We want the y-coordinates to work a bit more "stereotypically" according to space.
(Ex. world up in unit vector is 0,1,0 and not 0,-1,0), so we use this formula to get -1 is down, 1 is up.
-2 * ((pixel_y + 0.5f) / IMG_HEIGHT) + 1

4. In the scalar_x calculation we scale it according to the screen aspect ratio.
We don't have to do that for scalar_y, since there is a ray for every pixel_y.
(-2 * ((pixel_y + 0.5f) / IMG_HEIGHT) + 1) * camera->FOV_scale;

Return:
The calculated ray direction as a unit vector.

--------Getting a ray direction from the information we now have--------

1. We begin by scaling our two unit vectors (right_view and world_up), with the scalars scalar_x and scalar_y we just made.
This means that right_view now knows how far to the right/left to point in order to reach the pixel at [pixel_x, pixel_y],
and world_up now knows how far up/down to point in order to reach the pixel at [pixel_x, pixel_y].
vec_scale(camera->right_view, scalar_x), vec_scale(camera->world_up, scalar_y)

2. We add this together, to get a vector who knows both how far right/left and up/down to reach the pixel at [pixel_x, pixel_y].
direction = vec_add(vec_scale(camera->right_view, scalar_x), vec_scale(camera->world_up, scalar_y));

3. We also add the camera's normalized orientation vector (which way the camera is looking in the scene)

*/
static t_xyz get_ray_direction(int pixel_x, int pixel_y, t_camera *camera)
{
	float scalar_x;
	float scalar_y;
	t_xyz direction;

	scalar_x = (2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1) * camera->aspect_ratio * camera->FOV_scale;
	scalar_y = (-2 * ((pixel_y + 0.5f) / IMG_HEIGHT) + 1) * camera->FOV_scale;

	// Create the ray direction

	//We scale cam_right_view according to ray_dir_x. same for world_up and ray_dir_y.
	direction = vec_add(vec_scale(camera->right_view, scalar_x), vec_scale(camera->world_up, scalar_y));
	direction = vec_add(direction, camera->normOrientVec);
	direction = vec_normalize(direction);
	return (direction);
}

/*
Arguments:


Description:


Return:

*/
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

/*
Arguments:


Description:


Return:

*/
void raytracer(t_minirt *data)
{
	int x;
	int y;
	t_ray ray;
	t_intersection intersection;

	set_detailed_camera(data->camera);
	x = 0;
	y = 0;

	ray.origin = data->camera->coordinatesOfViewpoint; //test

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

			x++;
		}
		y++;
	}
}
