#include "test.h"

Test(obj_files, ignoring_unrecognized_lines)
{
	t_obj_loader	loader;
	t_shape			group;

	new_obj_loader(&loader, &group);
	parse_obj_file(&loader, "../obj_files/test/Gibberish.obj");
	cr_assert(eq(int, loader.ignored_lines, 5));
}

// Loader allocations are freed after parsing the file.
/* Test(obj_files, vertex_records)
{
	t_obj_loader	loader;
	t_shape			group;

	new_obj_loader(&loader, &group);
	parse_obj_file(&loader, "../obj_files/test/VertexRecords.obj");
	cr_assert(eq(int, loader.v_count, 4));
	cr_assert(eq(dbl, loader.vertices[0].x, -1));
	cr_assert(eq(dbl, loader.vertices[0].y, 1));
	cr_assert(eq(dbl, loader.vertices[0].z, 0));
	cr_assert(eq(dbl, loader.vertices[1].x, -1));
	cr_assert(eq(dbl, loader.vertices[1].y, 0.5));
	cr_assert(eq(dbl, loader.vertices[1].z, 0));
	cr_assert(eq(dbl, loader.vertices[2].x, 1));
	cr_assert(eq(dbl, loader.vertices[2].y, 0));
	cr_assert(eq(dbl, loader.vertices[2].z, 0));
	cr_assert(eq(dbl, loader.vertices[3].x, 1));
	cr_assert(eq(dbl, loader.vertices[3].y, 1));
  cr_assert(eq(dbl, loader.vertices[3].z, 0));
} */

// Testing: group sort in volumetric order
/* Test(obj_files, parsing_triangle_faces)
{
	t_obj_loader	loader;
	t_shape			group;
	t_shape			*t1;
	t_shape			*t2;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/TriangleFaces.obj");
	group = loader.default_group;
	t1 = group.group.root;
	t2 = group.group.root->next;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t2->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t2->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t2->tri.p2.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t2->tri.p2.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t2->tri.p2.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p3.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t2->tri.p3.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t2->tri.p3.z, loader.vertices[3].z));
} */

// Testing: group sort in volumetric order
/* Test(obj_files, tringulating_polygons)
{
	t_obj_loader	loader;
	t_shape			group;
	t_shape			*t1;
	t_shape			*t2;
	t_shape			*t3;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/TriangulatingPolygons.obj");
	group = loader.default_group;
	t1 = group.group.root;
	t2 = group.group.root->next;
	t3 = group.group.root->next->next;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(ptr, t3, &loader.triangles[2]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t2->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t2->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t2->tri.p2.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t2->tri.p2.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t2->tri.p2.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p3.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t2->tri.p3.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t2->tri.p3.z, loader.vertices[3].z));
	cr_assert(eq(dbl, t3->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t3->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t3->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t3->tri.p2.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t3->tri.p2.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t3->tri.p2.z, loader.vertices[3].z));
	cr_assert(eq(dbl, t3->tri.p3.x, loader.vertices[4].x));
	cr_assert(eq(dbl, t3->tri.p3.y, loader.vertices[4].y));
	cr_assert(eq(dbl, t3->tri.p3.z, loader.vertices[4].z));
} */
/*
* All loader allocations are freed after parsing the file.
Test(obj_files, triangles_in_groups)
{
	t_obj_loader	loader;
	t_shape			g1;
	t_shape			g2;
	t_shape			*t1;
	t_shape			*t2;
	t_shape			group;

	new_obj_loader(&loader, &group);
	parse_obj_file(&loader, "../obj_files/test/TrianglesInGroups.obj");
	g1 = loader.groups[0];
	g2 = loader.groups[1];
	t1 = g1.group.root;
	t2 = g2.group.root;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t2->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t2->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t2->tri.p2.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t2->tri.p2.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t2->tri.p2.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p3.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t2->tri.p3.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t2->tri.p3.z, loader.vertices[3].z));
} */

// Testing: group sort in volumetric order
/* Test(obj_files, converting_OBJ_file_to_a_group)
{
	t_obj_loader	loader;
	t_shape			g0;
	t_shape			g1;
	t_shape			g2;
	t_shape			*t1;
	t_shape			*t2;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/TrianglesInGroups.obj");
	g0 = loader.default_group;
	g1 = *g0.group.root;
	g2 = *g0.group.root->next;
	t1 = g1.group.root;
	t2 = g2.group.root;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t2->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t2->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t2->tri.p2.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t2->tri.p2.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t2->tri.p2.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t2->tri.p3.x, loader.vertices[3].x));
	cr_assert(eq(dbl, t2->tri.p3.y, loader.vertices[3].y));
	cr_assert(eq(dbl, t2->tri.p3.z, loader.vertices[3].z));
} */
/*
* Loader allocations are freed after parsing the file.
Test(obj_files, vertex_normal_records)
{
	t_obj_loader	loader;
	t_shape			group;

	new_obj_loader(&loader, &group);
	parse_obj_file(&loader, "../obj_files/test/VertexNormalRecords.obj");
	cr_assert(eq(int, loader.n_count, 3));
	cr_assert(eq(dbl, loader.normals[0].x, 0));
	cr_assert(eq(dbl, loader.normals[0].y, 0));
	cr_assert(eq(dbl, loader.normals[0].z, 1));
	cr_assert(epsilon_eq(dbl, loader.normals[1].x, 0.707, EPSILON));
	cr_assert(eq(dbl, loader.normals[1].y, 0));
	cr_assert(epsilon_eq(dbl, loader.normals[1].z, -0.707, EPSILON));
	cr_assert(eq(dbl, loader.normals[2].x, 1));
	cr_assert(eq(dbl, loader.normals[2].y, 2));
	cr_assert(eq(dbl, loader.normals[2].z, 3));
} */

// Testing: group sort in volumetric order
/* Test(obj_files, faces_with_normals)
{
	t_obj_loader	loader;
	t_shape			group;
	t_shape			*t1;
	t_shape			*t2;

	loader = new_obj_loader();
	parse_obj_file(&loader, "../obj_files/test/FacesWithNormals.obj");
	group = loader.default_group;
	t1 = group.group.root;
	t2 = group.group.root->next;
	cr_assert(eq(ptr, t1, &loader.triangles[0]));
	cr_assert(eq(ptr, t2, &loader.triangles[1]));
	cr_assert(eq(dbl, t1->tri.p1.x, loader.vertices[0].x));
	cr_assert(eq(dbl, t1->tri.p1.y, loader.vertices[0].y));
	cr_assert(eq(dbl, t1->tri.p1.z, loader.vertices[0].z));
	cr_assert(eq(dbl, t1->tri.p2.x, loader.vertices[1].x));
	cr_assert(eq(dbl, t1->tri.p2.y, loader.vertices[1].y));
	cr_assert(eq(dbl, t1->tri.p2.z, loader.vertices[1].z));
	cr_assert(eq(dbl, t1->tri.p3.x, loader.vertices[2].x));
	cr_assert(eq(dbl, t1->tri.p3.y, loader.vertices[2].y));
	cr_assert(eq(dbl, t1->tri.p3.z, loader.vertices[2].z));
	cr_assert(eq(dbl, t1->tri.n1.x, loader.normals[2].x));
	cr_assert(eq(dbl, t1->tri.n1.y, loader.normals[2].y));
	cr_assert(eq(dbl, t1->tri.n1.z, loader.normals[2].z));
	cr_assert(eq(dbl, t1->tri.n2.x, loader.normals[0].x));
	cr_assert(eq(dbl, t1->tri.n2.y, loader.normals[0].y));
	cr_assert(eq(dbl, t1->tri.n2.z, loader.normals[0].z));
	cr_assert(eq(dbl, t1->tri.n3.x, loader.normals[1].x));
	cr_assert(eq(dbl, t1->tri.n3.y, loader.normals[1].y));
	cr_assert(eq(dbl, t1->tri.n3.z, loader.normals[1].z));
	cr_assert(eq(dbl, t2->tri.p1.x, t1->tri.p1.x));
	cr_assert(eq(dbl, t2->tri.p1.y, t1->tri.p1.y));
	cr_assert(eq(dbl, t2->tri.p1.z, t1->tri.p1.z));
	cr_assert(eq(dbl, t2->tri.p2.x, t1->tri.p2.x));
	cr_assert(eq(dbl, t2->tri.p2.y, t1->tri.p2.y));
	cr_assert(eq(dbl, t2->tri.p2.z, t1->tri.p2.z));
	cr_assert(eq(dbl, t2->tri.p3.x, t1->tri.p3.x));
	cr_assert(eq(dbl, t2->tri.p3.y, t1->tri.p3.y));
	cr_assert(eq(dbl, t2->tri.p3.z, t1->tri.p3.z));
	cr_assert(eq(dbl, t2->tri.n1.x, t1->tri.n1.x));
	cr_assert(eq(dbl, t2->tri.n1.y, t1->tri.n1.y));
	cr_assert(eq(dbl, t2->tri.n1.z, t1->tri.n1.z));
	cr_assert(eq(dbl, t2->tri.n2.x, t1->tri.n2.x));
	cr_assert(eq(dbl, t2->tri.n2.y, t1->tri.n2.y));
	cr_assert(eq(dbl, t2->tri.n2.z, t1->tri.n2.z));
	cr_assert(eq(dbl, t2->tri.n3.x, t1->tri.n3.x));
	cr_assert(eq(dbl, t2->tri.n3.y, t1->tri.n3.y));
	cr_assert(eq(dbl, t2->tri.n3.z, t1->tri.n3.z));
} */
