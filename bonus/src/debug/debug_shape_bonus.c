

#include "miniRT_bonus.h"

static void	print_sphere(t_sphere sphere)
{
	printf("Sphere:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		sphere.center.x, sphere.center.y, sphere.center.z);
	printf("  Radius: %.2lf\n", sphere.radius);
	printf("  Color:  %d, %d, %d\n", sphere.color.red,
		sphere.color.green, sphere.color.blue);
}

static void	print_plane(t_plane plane)
{
	printf("plane:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		plane.center.x, plane.center.y, plane.center.z);
	printf("  Normal: %.2lf, %.2lf, %.2lf\n", \
		plane.normal.x, plane.normal.y, plane.normal.z);
	printf("  Color:  %d, %d, %d\n", plane.color.red,
		plane.color.green, plane.color.blue);
}

static void	print_cylinder(t_cylinder cylinder)
{
	printf("cylinder:\n");
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		cylinder.center.x, cylinder.center.y, cylinder.center.z);
	printf("  Normal: %.2lf, %.2lf, %.2lf\n", \
		cylinder.normal.x, cylinder.normal.y, cylinder.normal.z);
	printf("  Color:  %d, %d, %d\n", cylinder.color.red,
		cylinder.color.green, cylinder.color.blue);
}



static void	print_cone(t_cone cone)
{
	printf("cone:\n");
	printf("  tip: %.2lf, %.2lf, %.2lf\n", \
		cone.tip.x, cone.tip.y, cone.tip.z);
	printf("  Base: %.2lf, %.2lf, %.2lf\n", \
		cone.base.x, cone.base.y, cone.base.z);
	printf("  Center: %.2lf, %.2lf, %.2lf\n", \
		cone.center.x, cone.center.y, cone.center.z);
	printf("  Normal: %.2lf, %.2lf, %.2lf\n", \
		cone.normal.x, cone.normal.y, cone.normal.z);
	printf("  Color:  %d, %d, %d\n", cone.color.red,
		cone.color.green, cone.color.blue);
	printf("  radius:  %f, height %f, angle %f\n", cone.radius,
		cone.height, cone.angle);
}

void	print_shape(t_shape *shape)
{
	printf("ID: %d\n", shape->id);
	if (shape->type == SPHERE)
		print_sphere(shape->data.sphere);
	if (shape->type == PLANE)
		print_plane(shape->data.plane);
	if (shape->type == CYLINDER)
		print_cylinder(shape->data.cylinder);
	if (shape->type == CONE)
		print_cone(shape->data.cone);
}

void	print_light(t_light *light)
{
	printf("Light coordinate: %1lf,%1lf,%1lf\n",
		light->point.x, light->point.y, light->point.z);
	printf("Light brightness level: %1lf\n", light->brightness);
	printf("Light color: %d,%d,%d\n",
		light->color.red, light->color.green, light->color.blue);
}

void	print_camera(t_camera *camera)
{
	printf("camera coordinate: %f,%f,%f\n",
		camera->coordinate.x, camera->coordinate.y, camera->coordinate.z);
	//printf("camera normal: %.2lf,%.2lf,%.2lf\n",
	//	camera->normal.x, camera->normal.y, camera->normal.z);
	//printf("camera fov: %d\n", camera->fov);
}

void	print_box(t_aabb box)
{
	printf("AABB min: (%f, %f, %f), max: (%f, %f, %f)\n",
		box.min.x, box.min.y, box.min.z,
		box.max.x, box.max.y, box.max.z);
}
