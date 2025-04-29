
#include "../include/miniRT.h"

void print_elements_of_rt_file(t_minirt *data)
{
	if (data->amb_light)
	{
		printf("\nAMBIENT LIGHT\n");
		printf("%f\n", data->amb_light->ratio);
		printf("%f and %f and %f\n\n\n", data->amb_light->rgb.x, data->amb_light->rgb.y, data->amb_light->rgb.z);
	}
	if (data->camera)
	{
		printf("\nCAMERA\n");
		printf("%f and %f and %f\n", data->camera->coordinates.x, data->camera->coordinates.y, data->camera->coordinates.z);
		printf("%f and %f and %f\n", data->camera->orientation.x, data->camera->orientation.y, data->camera->orientation.z);
		printf("%d\n", data->camera->fov);
	}
	if (data->light)
	{
		printf("\nLIGHT\n");
		printf("%f and %f and %f\n", data->light->coordinates.x, data->light->coordinates.y, data->light->coordinates.z);
		printf("%f\n", data->light->ratio);
		printf("%f and %f and %f\n", data->light->rgb.x, data->light->rgb.y, data->light->rgb.z);
	}
	if (data->objects->spheres)
	{
		int i = 0;
		t_sphere *current = data->objects->spheres;
		printf("\nSPHERES\n");
		while (current != NULL)
		{
			printf("\nSphere %d:\n", i++);
			printf("%f and %f and %f\n", current->center.x, current->center.y, current->center.z);
			printf("%f\n", current->diameter);
			printf("%f and %f and %f\n", current->rgb.x, current->rgb.y, current->rgb.z);
			current = current->next;
		}
	}
	if (data->objects->planes)
	{
		int i = 0;
		t_plane *current = data->objects->planes;
		printf("\nPLANES\n");
		while (current != NULL)
		{
			printf("\nPlane %d:\n", i++);
			printf("%f and %f and %f\n", current->point_in_plane.x, current->point_in_plane.y, current->point_in_plane.z);
			printf("%f and %f and %f\n", current->orientation.x, current->orientation.y, current->orientation.z);
			printf("%f and %f and %f\n", current->rgb.x, current->rgb.y, current->rgb.z);
			current = current->next;
		}
	}
	if (data->objects->cylinders)
	{
		int i = 0;
		t_cylinder *current = data->objects->cylinders;
		printf("\nCYLINDERS\n");
		while (current != NULL)
		{
			printf("\nCylinder %d:\n", i++);
			printf("%f and %f and %f\n", current->center.x, current->center.y, current->center.z);
			printf("%f and %f and %f\n", current->orientation.x, current->orientation.y, current->orientation.z);
			printf("%f\n", current->diameter);
			printf("%f\n", current->height);
			printf("%f and %f and %f\n", current->rgb.x, current->rgb.y, current->rgb.z);
			current = current->next;
		}
	}
}