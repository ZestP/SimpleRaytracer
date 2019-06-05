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
#include "lambertian.h"
#include "metal.h"
#include "dielectric.h"
#include <thread>
#define MAXFLOAT 3.40E38
using namespace std;
ofstream fout("test.ppm");

hitable *random_scene()
{
	int n = 500;
	hitable **list = new hitable*[n + 1];
	list[0] = new sphere(vec3(0, -1000, 0), 1000, new lambertian(vec3(0.5, 0.5, 0.5)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = rand() % 10000 / 10000.0;
			vec3 center(a + 0.9*(rand() % 10000 / 10000.0),0.2, b + 0.9*(rand() % 10000 / 10000.0));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					list[i++] = new sphere(center, 0.2, new lambertian(vec3((rand() % 10000 / 10000.0)*
						(rand() % 10000 / 10000.0), (rand() % 10000 / 10000.0)*
						(rand() % 10000 / 10000.0), (rand() % 10000 / 10000.0)*
						(rand() % 10000 / 10000.0))));
				}
				else if (choose_mat < 0.95)
				{
					list[i++] = new sphere(center, 0.2, new metal(vec3(0.5*(1+ (rand() % 10000 / 10000.0)),
						0.5*(1 + (rand() % 10000 / 10000.0)),
						0.5*(1 + (rand() % 10000 / 10000.0))), 0.5*((rand() % 10000 / 10000.0))));
				}
				else
				{
					list[i++] = new sphere(center, 0.2, new dielectric(1.5));
				}
			}
		}
	}
	list[i++] = new sphere(vec3(0, 1, 0), 1, new dielectric(1.5));
	list[i++] = new sphere(vec3(-4, 1, 0), 1, new lambertian(vec3(0.4, 0.2, 0.1)));
	list[i++] = new sphere(vec3(4, 1, 0), 1, new metal(vec3(0.7, 0.6, 0.5), 0));
	return new hitable_list(list, i);
}


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

vec3 color(const ray& r, hitable *world,int depth)
{
	hit_record rec;
	if (world->hit(r, 0.001, MAXFLOAT, rec))
	{
		ray scattered;
		vec3 attenuation;
		if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return vec3(0, 0, 0);
		}
		
	}
	else {
		vec3 unit_direction = vec3::unit_vector(r.direction());
		float t = 0.5*(unit_direction.y() + 1.0);
		return (1.0 - t)*vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}
int i, j, nx, ny, cnt;
camera cam;
hitable* world;
vec3 col;
void gather()
{
	//cout << "gathering" << cnt<<endl;
	float u = float(i + rand() % 10000 / 10000.0) / float(nx);
	float v = float(j + rand() % 10000 / 10000.0) / float(ny);
	ray r = cam.get_ray(u, v);
	vec3 p = r.point_at_parameter(2.0);
	col += color(r, world, 0);
	//cout << "gathering complete" << cnt<<endl;
	cnt++;
}

int main()
{
	srand(time(NULL));
	nx = 200;
	ny = 100;
	int ns = 10;
	fout << "P3\n" << nx << " " << ny << "\n255\n";
	float R = cos(M_PI / 4);
	hitable *list[5];
	list[0] = new sphere(vec3(0, 0, -1), 0.5,new lambertian(vec3(0.1,0.2,0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 1));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	world = new hitable_list(list, 5);
	/*hitable *list[2];
	list[0] = new sphere(vec3(-R, 0, -1), R, new lambertian(vec3(0, 0, 1)));
	list[1] = new sphere(vec3(R, 0, -1), R, new lambertian(vec3(1, 0, 0.0)));
	
	hitable *world = new hitable_list(list, 2);*/
	//world=random_scene();
	vec3 lookfrom(3, 3, 2);
	vec3 lookat(0, 0, -1);
	float dist_to_focus = (lookfrom - lookat).length();
	float aperture = 2.0;
	cam=camera(lookfrom,lookat,vec3(0,1,0),20,float(nx)/float(ny),aperture,dist_to_focus);
	for (j = ny - 1; j >= 0; j--) {
		for (i = 0; i < nx; i++)
		{
			col=vec3(0, 0, 0);
			cnt = 0;
			thread* ths[100];
			/*for (int s = 0; s < ns; s++)
			{
				
				ths[s]=new thread(gather);
			}
			for (int s = 0; s < ns; s++)
				ths[s]->join();*/
			for (int s = 0; s < ns; s++)
				gather();
			cnt = 0;
			col /= float(ns);
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
