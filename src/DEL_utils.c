
#include "../include/miniRT.h"

void print_elements_of_rt_file(t_minirt *data)
{
	if (data->ambLight)
	{
		printf("\nAMBIENT LIGHT\n");
		printf("%f\n", data->ambLight->ambientLightRatio);
		printf("%f and %f and %f\n\n\n", data->ambLight->RGB.x, data->ambLight->RGB.y, data->ambLight->RGB.z);
	}
	if (data->camera)
	{
		printf("\nCAMERA\n");
		printf("%f and %f and %f\n", data->camera->coordinatesOfViewpoint.x, data->camera->coordinatesOfViewpoint.y, data->camera->coordinatesOfViewpoint.z);
		printf("%f and %f and %f\n", data->camera->normOrientVec.x, data->camera->normOrientVec.y, data->camera->normOrientVec.z);
		printf("%d\n", data->camera->FOV);
	}
	if (data->light)
	{
		printf("\nLIGHT\n");
		printf("%f and %f and %f\n", data->light->coordinatesOfLightPoint.x, data->light->coordinatesOfLightPoint.y, data->light->coordinatesOfLightPoint.z);
		printf("%f\n", data->light->lightBrightnessRatio);
		printf("%f and %f and %f\n", data->light->RGB.x, data->light->RGB.y, data->light->RGB.z);
	}
	if (data->objects->spheres)
	{
		int i = 0;
		t_sphere *current = data->objects->spheres;
		printf("\nSPHERES\n");
		while (current != NULL)
		{
			printf("\nSphere %d:\n", i++);
			printf("%f and %f and %f\n", current->sphereCenter.x, current->sphereCenter.y, current->sphereCenter.z);
			printf("%f\n", current->diameter);
			printf("%f and %f and %f\n", current->RGB.x, current->RGB.y, current->RGB.z);
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
			printf("%f and %f and %f\n", current->pointInPlane.x, current->pointInPlane.y, current->pointInPlane.z);
			printf("%f and %f and %f\n", current->normNormalVec.x, current->normNormalVec.y, current->normNormalVec.z);
			printf("%f and %f and %f\n", current->RGB.x, current->RGB.y, current->RGB.z);
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
			printf("%f and %f and %f\n", current->cylinderCenter.x, current->cylinderCenter.y, current->cylinderCenter.z);
			printf("%f and %f and %f\n", current->normVecOfAxis.x, current->normVecOfAxis.y, current->normVecOfAxis.z);
			printf("%f\n", current->diameter);
			printf("%f\n", current->height);
			printf("%f and %f and %f\n", current->RGB.x, current->RGB.y, current->RGB.z);
			current = current->next;
		}
	}
}