// Include statements
#include "SceneBuilder.h"
#include "ShapeBuilder.h"
#include "Mesh.h"

using namespace std;


void SceneBuilder::UBuildScene(vector<GLMesh>& scene)
{
	// Seeds the rand() function once
	srand(time(nullptr));

	// Pen creation
	GLMesh cyl_gMesh01;
	cyl_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 1.0f, 0.25f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.10f, 3.0f,
		1.0f, 1.0f
	};
	cyl_gMesh01.height = 4.0f;
	cyl_gMesh01.radius = 0.5f;
	cyl_gMesh01.number_of_sides = 128.0f;
	cyl_gMesh01.texFilename = "textures\\pen_body2.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh01);
	scene.push_back(cyl_gMesh01);
	GLMesh cyl_gMesh02;
	cyl_gMesh02.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 1.0f, 0.02f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		-45.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		-0.063f, 0.22f, 2.5f,
		1.0f, 1.0f
	};
	cyl_gMesh02.height = 1.5f;	cyl_gMesh02.radius = 0.4f;	cyl_gMesh02.number_of_sides = 16.0f;
	cyl_gMesh02.texFilename = "textures\\clip.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh02);
	scene.push_back(cyl_gMesh02);
	GLMesh cyl_gMesh03;
	cyl_gMesh03.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 1.0f, 0.25f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.10f, 3.05f,
		1.0f, 1.0f
	};
	cyl_gMesh03.height = 3.0f;	cyl_gMesh03.radius = 0.45f;	cyl_gMesh03.number_of_sides = 128.0f;
	cyl_gMesh03.texFilename = "textures\\grey.png";
	ShapeBuilder::UBuildCylinder(cyl_gMesh03);
	scene.push_back(cyl_gMesh03);
	GLMesh con_gMesh01;
	con_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		0.25f, 0.5f, 0.25f,
		-90.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		0.0f, 0.10f, -1.0f,
		1.0f, 1.0f
	};
	con_gMesh01.height = 1.0f;	con_gMesh01.radius = 0.5f;	con_gMesh01.number_of_sides = 128.0f;
	con_gMesh01.texFilename = "textures\\pen_tip.png";
	ShapeBuilder::UBuildCone(con_gMesh01);
	scene.push_back(con_gMesh01);

	// Plane setup
	GLMesh plan_gMesh01;
	plan_gMesh01.p = {
		1.0f, 1.0f, 1.0f, 1.0f,
		16.0f, 2.0f, 16.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		45.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		2.0f, 2.0f
	};
	plan_gMesh01.texFilename = "textures\\desk.png";
	ShapeBuilder::UBuildPlane(plan_gMesh01);
	scene.push_back(plan_gMesh01);


	// Paper setup
	GLMesh paper_gMesh01;
	paper_gMesh01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		8.0f,	0.1f,	6.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		55.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		0.0f,	0.0f,	0.0f,
		1.0f,	1.0f
	};
	paper_gMesh01.texFilename = "textures\\paper.png";
	ShapeBuilder::UBuildCube(paper_gMesh01);
	scene.push_back(paper_gMesh01);


	// Cup setup
	GLMesh hollow_cyl;
	hollow_cyl.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		2.0f,	2.0f,	2.0f,
		0.0f,	1.0f,	0.0f,	0.0f,
		-90.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		-4.0f,	0.0f,	3.0f,
		1.0f,	1.0f
	};
	hollow_cyl.texFilename = "textures\\cup.png";
	hollow_cyl.innerRadius = 0.45f;
	hollow_cyl.radius = 0.5f;
	hollow_cyl.height = 2.0f;
	hollow_cyl.number_of_sides = 144.0f;
	ShapeBuilder::UBuildHollowCylinder(hollow_cyl);
	scene.push_back(hollow_cyl);

	// Small pc setup
	GLMesh pc_gMesh01;
	pc_gMesh01.p = {
		1.0f,	1.0f,	1.0f,	1.0f,
		1.4f,	1.4f,	1.4f,
		0.0f,	1.0f,	0.0f,	0.0f,
		-110.0f,	0.0f,	1.0f,	0.0f,
		0.0f,	0.0f,	0.0f,	1.0f,
		2.0f,	0.1f,	-2.0f,
		1.0f,	1.0f
	};
	pc_gMesh01.texFilename = "textures\\pc.png";
	ShapeBuilder::UBuildCube(pc_gMesh01);
	scene.push_back(pc_gMesh01);
}