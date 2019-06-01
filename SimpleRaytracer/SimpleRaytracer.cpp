// SimpleRaytracer.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#define MAXFLOAT 3.40E38
using namespace std;
ofstream fout("test.ppm");

float hit_sphere(const vec3& center, float radius, const ray& r)
{
	vec3 oc = r.origin() - center;
	float a = vec3::dot(r.direction(), r.direction());
	float b = 2.0*vec3::dot(oc, r.direction());
	float c = vec3::dot(oc, oc) - radius * radius;
	float discriminant = b * b - 4 * a*c;
	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		return (-b - sqrt(discriminant)) / (2.0*a);
	}
}
vec3 color(const ray& r)
{
	float t = hit_sphere(vec3(0, 0, -1), 0.5, r);
	if (t > 0.0)
	{
		vec3 N = vec3::unit_vector(r.point_at_parameter(t) - vec3(0, 0, -1));
		return 0.5*vec3(N.x() + 1, N.y() + 1, N.z() + 1);
	}
	vec3 unit_direction = vec3::unit_vector(r.direction());
	t = 0.5*(unit_direction.y() + 1.0);
	return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}
vec3 random_in_unit_sphere()
{
	vec3 p;
	do
	{
		p = 2.0*vec3(rand()%10000/10000.0, rand() % 10000 / 10000.0, rand() % 10000 / 10000.0) - vec3(1, 1, 1);
	} while (p.squared_length() >= 1.0);
	return p;
}
vec3 color(const ray& r, hitable *world)
{
	hit_record rec;
	if (world->hit(r, 0.001, MAXFLOAT, rec))
	{
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5*color(ray(rec.p,target-rec.p),world);
	}
	else {
		vec3 unit_direction = vec3::unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}
int main()
{
	srand(time(NULL));
	int nx = 1920;
	int ny = 1080;
	fout << "P3\n" << nx << " " << ny << "\n255\n";
	
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++)
		{
			float u = float(i) / float(nx);
			float v = float(j) / float(ny);
			ray r=cam.get_ray(u,v);
			vec3 p = r.point_at_parameter(2.0);
			vec3 col = color(r,world);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99*col[0]);
			int ig = int(255.99*col[1]);
			int ib = int(255.99*col[2]);
			fout << ir << ' ' << ig << ' ' << ib << "\n";
		}
	}
	return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
