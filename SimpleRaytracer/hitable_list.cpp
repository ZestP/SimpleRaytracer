#include "pch.h"
#include "hitable_list.h"


hitable_list::hitable_list()
{
}

bool hitable_list::hit(const ray & r, float t_min, float t_max, hit_record & rec) const
{
	hit_record temp_rec;
	bool hit_anything = false;
	double closeset_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closeset_so_far, temp_rec))
		{
			hit_anything = true;
			closeset_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return hit_anything;
}


hitable_list::~hitable_list()
{
}
