/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aalbrech <aalbrech@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:41:59 by aalbrech          #+#    #+#             */
/*   Updated: 2025/04/24 16:25:28 by aalbrech         ###   ########.fr       */
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

4. It can happen that the screen isn't fully square. In that case every pixel isn't representing a square area of the scene anymore.
The pixel is representing a rectangular area. Since the ray then would sample a rectangular area, the rendered image result of the scene would look
distorted. To make the a pixel represent a square area again, we scale scalar_x with the aspect ratio (multiplication).
(2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1) * camera->aspect_ratio

5. The same goes for the camera field of view (FOV) and the scene we are making.
We need to scale the pixel grid to correctly represent what the camera sees. We scale scalar_x with the FOV_scale.
Camera zoomed out (wide FOV) = camera sees more of the scene.
Camera zoomed in (narrow FOV) = camera sees less of the scene.
(2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1) * camera->aspect_ratio * camera->FOV_scale

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

4. For scalar_y we don't need to take into account the aspect ratio.
Aspect ratio is calculated in relation to the screen_height, so scalar_y and aspect_ratio are already in sync.
We however take into account the FOV_scale, just like with scalar_x.
scalar_y = (-2 * ((pixel_y + 0.5f) / IMG_HEIGHT) + 1) * camera->FOV_scale;

Return:
The calculated ray direction as a unit vector.

--------Getting a ray direction from the information we now have--------

1. We begin by scaling our two unit vectors (right_view and world_up), with the scalars scalar_x and scalar_y we just made.
This means that right_view now knows how far to the right/left to point in order to reach the pixel at [pixel_x, pixel_y],
and world_up now knows how far up/down to point in order to reach the pixel at [pixel_x, pixel_y].
vec_scale(camera->right_view, scalar_x), vec_scale(camera->world_up, scalar_y)

2. We add this together, to get a vector that knows both how far right/left and up/down to reach the pixel at [pixel_x, pixel_y].
direction = vec_add(vec_scale(camera->right_view, scalar_x), vec_scale(camera->world_up, scalar_y));

3. We also add the camera's normalized orientation vector (which way the camera is looking in the scene, it's forward direction). We add it because we're
working in 3d. Move up and down, move sideways, and move forward and backwards.

4. We normalize the vector to get a pure unit vector, only giving us a direction and no length.

Return:
A unit vector pointing in the direction of the pixel at coordinate [pixel_x, pixel_y], in 3d space.

*/
static t_xyz get_ray_direction(int pixel_x, int pixel_y, t_camera *camera)
{
	float scalar_x;
	float scalar_y;
	t_xyz direction;

	scalar_x = (2 * ((pixel_x + 0.5f) / IMG_WIDTH) - 1) * camera->aspect_ratio * camera->FOV_scale;
	scalar_y = (-2 * ((pixel_y + 0.5f) / IMG_HEIGHT) + 1) * camera->FOV_scale;

	direction = vec_add(vec_scale(camera->right_view, scalar_x), vec_scale(camera->world_up, scalar_y));
	direction = vec_add(direction, camera->normOrientVec);
	direction = vec_normalize(direction);
	return (direction);
}

/*
Arguments:
The camera struct.

Description:
We already have some basic information about the camera's orientation and so on, gotten from the file.rt.
Here we add more esential information to the camera struct, needed to make rays correctly point from the camera out into the scene.

world_up: We need some base for the program to know what "up" means in a scene, what verticality means. Up means that the y-coordinate is bigger than 0.

right_view: To the right of the camera. The program needs some sort of idea of what it would mean to move horizontally in a space.
We get that by doing cross_product(), which returns a vector at a 90° angle from the two input vectors.
World_up points upwards, normOrientVec points forwards. What is at at 90° to both up and forward? It's left or right.

The reason why we don't need a world_down and left_view, is that world_up and right_view can be used for that aswell. A positive value
would mean more up/more to the right, and a negative value would mean less up(meaning: down), and less to the right (meaning: to the left).

aspect_ratio: The proportial relationship between the screen width and screen height.
Essential for some calculations to not make the rendered scene-image look distorted.

FOV_scale: FOV is the total angle a camera can see. It tells us how much the camera is zoomed in/out when looking out into the 3d world.
Tan input needs to be a radian, which is calculated as degrees * PI / 180. We already have a FOV in degrees, but now we are making a scalar.
Tan also need a right-angled triangle to work. We divide by two to get that. An angle = a triangle, half of an angle = a right-angled triangle.
FOV_scale is essential for some calculations, to correctly depict the cameras zooming and how it affects what it sees in the scene.
Tan gives us a ratio between the height and the depth of the scene.
The FOV_scale can tell us how far up/down in the scene the camera can capture, when you stand at a certain distance from the camera.

Return:
Nothing. Only sets values in the camera struct.
*/
static void set_detailed_camera(t_camera *camera)
{
	camera->world_up = (t_xyz){0, 1, 0}; // can have problems?? The direction of up
	if (camera->normOrientVec.x == 0 && fabs(camera->normOrientVec.y) == 1 && camera->normOrientVec.z == 0)
		camera->right_view = (t_xyz){1, 0, 0};
	else 
		camera->right_view = vec_normalize(vec_cross(camera->world_up, camera->normOrientVec));
	camera->aspect_ratio = (float)IMG_WIDTH/IMG_HEIGHT;
	camera->FOV_scale = tanf((camera->FOV * M_PI / 180) / 2);
}

/*
Arguments:
The t_minirt struct.

Description:
We go through every pixel of the screen, from the upper left corner, to the bottom right corner.
The screen is defined with the macros? IMG_HEIGHT and IMG_WIDTH.
For every pixel we make a ray from the camera (coordinatesOfViewPoint), in the direction of the current pixel.
We then see if the ray happens to intersect with an object (defined in the file.rt).

Return:
Nothing.
*/
void raytracer(t_minirt *data)
{
	int x;
	int y;
	t_ray ray;
	t_intersection intersection;
	//uint32_t color;

	set_detailed_camera(data->camera);
	x = 0;
	y = 0;
	ray.origin = data->camera->coordinatesOfViewpoint;
	data->ambLight->RGB = divide_color(data->ambLight->RGB);
	while (y < IMG_HEIGHT)
	{
		while (x < IMG_WIDTH)
		{
			ray.direction = get_ray_direction(x, y, data->camera);
			intersection = intersect(data, ray);
			if (intersection.object.spheres || intersection.object.planes || intersection.object.cylinders)
			{
				/*intersection.RGB = divide_color(intersection.RGB); // probably better way and place to do this.
				color = calculate_light(data, intersection);
				mlx_put_pixel(data->image_ptr, x, y, color);*/
				mlx_put_pixel(data->image_ptr, x, y, 0xFF000000); //test
			}
			else
				mlx_put_pixel(data->image_ptr, x, y, 0xFFFFFFFF); //test
			x++;
		}
		x = 0;
		y++;
	}
}
