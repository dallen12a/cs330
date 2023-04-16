// Include statements
#include <cstdlib>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <cmath>

#include "ShapeBuilder.h"

using namespace std;

void ShapeBuilder::UBuildPyramid(GLMesh& mesh)
{
	// Pyramid

	float h = mesh.height;

	mesh.v = {
		// Vertex Positions    // color coords					// Texture coords
		 0.0f,	h,		0.0f,	0.0f,	1.0f,	-1.0f,	1.0f,	0.625f, 1.0f,		//back side
		 0.5f, -0.0f, -0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.50f, 0.0f,
		-0.5f, -0.0f, -0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.75f, 0.0f,

		 0.0f,  h,		0.0f,	-1.0f,	1.0f,	0.0f,	1.0f,	0.875f, 1.0f,		//left side
		-0.5f, -0.0f, -0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.75f, 0.0f,
		-0.5f, -0.0f,  0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	1.0f, 0.0f,

		 0.0f,  h,		0.0f,	0.0f,	1.0f,	1.0f,	1.0f,	0.125f, 1.0f,		//front
		-0.5f, -0.0f,  0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f, 0.0f,
		 0.5f, -0.0f,  0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.25f, 0.0f,

		 0.0f,  h,		0.0f,	1.0f,	1.0f,	0.0f,	1.0f,	0.375f, 1.0f,		//right side
		 0.5f, -0.0f,  0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.25f, 0.0f,
		 0.5f, -0.0f, -0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.50f, 0.0f,

		-0.5f, -0.0f, -0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f, 0.0f,		//bottom back
		 0.5f, -0.0f, -0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.25f, 0.0f,
		-0.5f, -0.0f,  0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f, 1.0f,

		 0.5f, -0.0f, -0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.25f, 0.0f,		//bottom front
		-0.5f, -0.0f,  0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f, 1.0f,
		 0.5f, -0.0f,  0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.25f, 1.0f
	};

	UTranslator(mesh);

}
void ShapeBuilder::UBuildCube(GLMesh& mesh)
// Cube
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	mesh.v = {
		0.5f,	0.0f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.25f,	0.5f,	// front left
		-0.5f,	0.0f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	0.5f,
		-0.5f,	1.0f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f,

		0.5f,	0.0f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.25f,	0.5f,	// front right
		0.5f,	1.0f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.25f,	1.0f,
		-0.5f,	1.0f,	0.5f,	0.0f,	0.0f,	1.0f,	1.0f,	0.0f,	1.0f,


		0.5f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.25f,	0.5f,	// right front
		0.5f,	1.0f,	0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.25f,	1.0f,
		0.5f,	1.0f,	-0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.5f,	1.0f,

		0.5f,	0.0f,	0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.25f,	0.5f,	// right back
		0.5f,	0.0f,	-0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.5f,	0.5f,
		0.5f,	1.0f,	-0.5f,	1.0f,	0.0f,	0.0f,	1.0f,	0.5f,	1.0f,


		0.5f,	0.0f,	-0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.5f,	0.5f,	// back left
		-0.5f,	0.0f,	-0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.75f,	0.5f,
		-0.5f,	1.0f,	-0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.75f,	1.0f,

		0.5f,	0.0f,	-0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.5f,	0.5f,	// back right
		0.5f,	1.0f,	-0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.5f,	1.0f,
		-0.5f,	1.0f,	-0.5f,	0.0f,	0.0f,	-1.0f,	1.0f,	0.75f,	1.0f,


		-0.5f,	0.0f,	0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.5f,	// left back
		-0.5f,	1.0f,	0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	1.0f,
		-0.5f,	1.0f,	-0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.75f,	1.0f,

		-0.5f,	0.0f,	0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	1.0f,	0.5f,	// left front
		-0.5f,	0.0f,	-0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.75f,	0.5f,
		-0.5f,	1.0f,	-0.5f,	-1.0f,	0.0f,	0.0f,	1.0f,	0.75f,	1.0f,




		-0.5f,	1.0f,	0.5f,	-0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	// top left
		-0.5f,	1.0f,	-0.5f,	-0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.5f,
		0.5f,	1.0f,	0.5f,	-0.0f,	1.0f,	0.0f,	1.0f,	0.25f,	0.0f,

		-0.5f,	1.0f,	-0.5f,	-0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.5f,	// top right
		0.5f,	1.0f,	0.5f,	-0.0f,	1.0f,	0.0f,	1.0f,	0.25f,	0.0f,
		0.5f,	1.0f,	-0.5f,	-0.0f,	1.0f,	0.0f,	1.0f,	0.25f,	0.5f,

		-0.5f,	0.0f,	0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.0f,	// bottom left
		-0.5f,	0.0f,	-0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.5f,
		0.5f,	0.0f,	0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.25f,	0.0f,

		-0.5f,	0.0f,	-0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	0.5f,	// bottom right
		0.5f,	0.0f,	0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.25f,	0.0f,
		0.5f,	0.0f,	-0.5f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.25f,	0.5f,

	};

	UTranslator(mesh);
}
void ShapeBuilder::UBuildCone(GLMesh& mesh)
// Cone
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float r = mesh.radius;
	float h = mesh.height;
	float s = mesh.number_of_sides;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;
	const float textStep = 1.0f / s;
	float textureXLoc = 0.0f;

	vector<float> v;

	for (auto i = 1; i < s + 1; i++) {

		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;



		v.insert(v.end(), { 0.5f, 0.0f, 0.5f, c[0], -1.0f, c[2], c[3], 0.5f, 0.25f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], -1.0f, c[2], c[3],
										0.5f + (r * cos((i)*sectorStep)) ,
										0.25f + (0.25f * sin((i)*sectorStep))
			});
		v.insert(v.end(), { 0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.0f ,
										0.5f + (r * sin((i + 1) * sectorStep)) ,
										c[0], -1.0f, c[2], c[3],
										0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.25f + (0.25f * sin((i + 1) * sectorStep))
			});


		v.insert(v.end(), { 0.5f + (r * cos(i * sectorStep)) ,
										0.0f ,
										0.5f + (r * sin(i * sectorStep)) ,
										c[0], 1.0f, c[2], c[3],
										textureXLoc ,
										0.5f });
		v.insert(v.end(), { 0.5f + (r * cos((i + 1) * sectorStep)) ,
										0.0f ,
										0.5f + (r * sin((i + 1) * sectorStep)) ,
										c[0], 1.0f, c[2], c[3],
										textureXLoc + textStep,
										0.5f });
		v.insert(v.end(), { 0.5f , h , 0.5f , c[0], 1.0f, c[2], c[3], textureXLoc + (textStep / 2), 1.0f });

		textureXLoc += textStep;

	}

	mesh.v = v;
	v.clear();

	UTranslator(mesh);
}
void ShapeBuilder::UBuildCylinder(GLMesh& mesh)
// Cylinder
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float r = mesh.radius;
	float h = mesh.height;
	float s = mesh.number_of_sides;


	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;


		// triangle fan, bottom
		v.insert(v.end(), { 0.5f, 0.0f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.5f, 0.125f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], -1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										(0.125f + (0.125f * sin((i)*sectorStep))) });


		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], -1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										(0.125f + (0.125f * sin((i + 1) * sectorStep))) });


	}

	for (auto i = 1; i < s + 1; i++)
	{

		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;
		v.insert(v.end(), { 0.5f, h, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.875f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										0.875f + (0.125f * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										0.875f + (0.125f * sin((i + 1) * sectorStep)) });
	}

	constexpr float x = 1.0f;
	float j = 1.0f / (s / x);
	float k = 0.0f;

	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;


		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k ,
										0.25f });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k + j ,
										0.75f });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k + j ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k + j ,
										0.25f });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],					// color data r g b a
										k,
										0.25f });
		k += j;
	}

	mesh.v = v;
	v.clear();
	UTranslator(mesh);

}
void ShapeBuilder::UBuildHollowCylinder(GLMesh& mesh)
// Hollow cylinder
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };

	float ir = mesh.innerRadius;
	float r = mesh.radius;
	float h = mesh.height;
	float s = mesh.number_of_sides;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;

	for (auto i = 0; i < s; i++)
	{

		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;

		v.insert(v.end(), { 0.5f + ir * cos(i * sectorStep) ,
										0.0f ,
										0.5f + ir * sin(i * sectorStep) ,
										-c[0], -1.0f, -c[2], 1.0f,
										0.5f + ((ir / r * 0.5f) * cos((i)*sectorStep)) ,
										(0.125f + ((ir / r * 0.125f) * sin((i)*sectorStep))) });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], -1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										(0.125f + 0.125f * sin((i)*sectorStep)) });

		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], -1.0f, -c[2], 1.0f,
										0.5f + ((ir / r * 0.5f) * cos((i + 1) * sectorStep)) ,
										(0.125f + ((ir / r * 0.125f) * sin((i + 1) * sectorStep))) });
		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], -1.0f, -c[2], 1.0f,
										0.5f + ((ir / r * 0.5f) * cos((i + 1) * sectorStep)) ,
										(0.125f + ((ir / r * 0.125f) * sin((i + 1) * sectorStep))) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], -1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										(0.125f + 0.125f * sin((i + 1) * sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], -1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										(0.125f + (0.125f * sin((i)*sectorStep))) });

	}

	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;

		v.insert(v.end(), { 0.5f + ir * cos(i * sectorStep) ,
										h ,
										0.5f + ir * sin(i * sectorStep) ,
										-c[0], 1.0f, -c[2], 1.0f,
										0.5f + ((ir / r * 0.5f) * cos((i)*sectorStep)) ,
										(0.125f + ((ir / r * 0.125f) * sin((i)*sectorStep))) });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										(0.125f + 0.125f * sin((i)*sectorStep)) });

		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], 1.0f, -c[2], 1.0f,
										0.5f + ((ir / r * 0.5f) * cos((i + 1) * sectorStep)) ,
										(0.125f + ((ir / r * 0.125f) * sin((i + 1) * sectorStep))) });
		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], 1.0f, -c[2], 1.0f,
										0.5f + ((ir / r * 0.5f) * cos((i + 1) * sectorStep)) ,
										(0.125f + ((ir / r * 0.125f) * sin((i + 1) * sectorStep))) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										(0.125f + 0.125f * sin((i + 1) * sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										(0.125f + (0.125f * sin((i)*sectorStep))) });

	}

	constexpr float x = 1.0f;
	float j = 1.0f / (s / x);
	float k = 0.0f;


	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;


		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],
										k ,
										0.25f });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										h ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],
										k ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],
										k + j ,
										0.75f });

		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],
										k + j ,
										0.75f });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 0.0f, c[2], c[3],
										k + j ,
										0.25f });

		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 0.0f, c[2], c[3],
										k,
										0.25f });
		k += j;
	}

	for (auto i = 0; i < s; i++)
	{
		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;


		v.insert(v.end(), { 0.5f + ir * cos(i * sectorStep) ,
										0.0f ,
										0.5f + ir * sin(i * sectorStep) ,
										-c[0], 0.0f, -c[2], c[3],
										k ,
										0.25f });

		v.insert(v.end(), { 0.5f + ir * cos(i * sectorStep) ,
										h ,
										0.5f + ir * sin(i * sectorStep) ,
										-c[0], 0.0f, -c[2], c[3],
										k ,
										0.75f });
		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], 0.0f, -c[2], c[3],
										k + j ,
										0.75f });

		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										h ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], 0.0f, -c[2], c[3],
										k + j ,
										0.75f });
		v.insert(v.end(), { 0.5f + ir * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + ir * sin((i + 1) * sectorStep) ,
										-c[0], 0.0f, -c[2], c[3],
										k + j ,
										0.25f });

		v.insert(v.end(), { 0.5f + ir * cos(i * sectorStep) ,
										0.0f ,
										0.5f + ir * sin(i * sectorStep) ,
										-c[0], 0.0f, -c[2], c[3],
										k,
										0.25f });
		k += j;
	}




	mesh.v = v;

	UTranslator(mesh);

}
void ShapeBuilder::UBuildPlane(GLMesh& mesh)
// Plane
{
	mesh.v = {

		-1.0f,	0.0f,	-1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	1.0f,
		 0.0f,	0.0f,	 1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.5f,	0.0f,
		-1.0f,	0.0f,	 1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	0.0f,

		-1.0f,	0.0f,	-1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	0.0f,	1.0f,
		 0.0f,	0.0f,	 1.0f,	0.0f,	1.0f,	0.0f,	1.0f,	0.5f,	0.0f,
		 0.0f,	0.0f,	-1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	0.5f,	1.0f,

		 0.0f,	0.0f,	-1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	0.5f,	1.0f,
		 0.0f,	0.0f,	 1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	0.5f,	0.0f,
		 1.0f,	0.0f,	 1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	1.0f,	0.0f,

		 0.0f,	0.0f,	-1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	0.5f,	1.0f,
		 1.0f,	0.0f,	 1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	1.0f,	0.0f,
		 1.0f,	0.0f,	-1.0f, 	0.0f,	1.0f,	0.0f,	1.0f,	1.0f,	1.0f,

	};

	UTranslator(mesh);

}
void ShapeBuilder::UBuildCircle(GLMesh& mesh)
// Circle
{
	vector<float> c = { mesh.p[0], mesh.p[1], mesh.p[2], mesh.p[3] };


	float r = mesh.radius;
	float l = mesh.length;
	float s = mesh.number_of_sides;
	float h = mesh.height;

	constexpr float PI = 3.14f;
	const float sectorStep = 2.0f * PI / s;

	vector<float> v;



	for (auto i = 1; i < s + 1; i++)
	{

		float one = 0.5f + r * cos(i * sectorStep);
		float two = 0.5f + r * sin(i * sectorStep);

		one -= 0.5f;
		one *= 2.0f;

		two -= 0.5f;
		two *= 2.0f;

		c[0] = one;
		c[2] = two;
		// triangle fan, top
		v.insert(v.end(), { 0.5f, 0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.5f, 0.5f });
		v.insert(v.end(), { 0.5f + r * cos(i * sectorStep) ,
										0.0f ,
										0.5f + r * sin(i * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i)*sectorStep)) ,
										0.5f + (0.5f * sin((i)*sectorStep)) });
		v.insert(v.end(), { 0.5f + r * cos((i + 1) * sectorStep) ,
										0.0f ,
										0.5f + r * sin((i + 1) * sectorStep) ,
										c[0], 1.0f, c[2], 1.0f,
										0.5f + (0.5f * cos((i + 1) * sectorStep)) ,
										0.5f + (0.5f * sin((i + 1) * sectorStep)) });
	}
	mesh.v = v;
	v.clear();
	UTranslator(mesh);
}

// Standard translate method to move, rotate, and resize the shape
void ShapeBuilder::UTranslator(GLMesh& mesh)
{
	// Mesh

	constexpr GLuint floatsPerVertex = 3;
	constexpr GLuint floatsPerColor = 4;
	constexpr GLuint floatsPerUV = 2;

	mesh.nIndices = mesh.v.size() / (floatsPerVertex + floatsPerUV + floatsPerColor);

	glGenVertexArrays(1, &mesh.vao);
	glBindVertexArray(mesh.vao);

	// Creates VBO
	glGenBuffers(1, &mesh.vbo);
	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);

	glBufferData(
		GL_ARRAY_BUFFER,
		mesh.v.size() * sizeof(float),
		&mesh.v.front(),
		GL_STATIC_DRAW
	);

	// Stride
	constexpr GLint stride = sizeof(float) * (floatsPerVertex + floatsPerUV + floatsPerColor);

	// Create vertex pointers

	glVertexAttribPointer(0, floatsPerVertex, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, floatsPerUV, GL_FLOAT, GL_FALSE, stride, (void*)(7 * sizeof(float)));
	glEnableVertexAttribArray(2);


	// Sets scale
	mesh.scale = glm::scale(glm::vec3(mesh.p[4], mesh.p[5], mesh.p[6]));

	const glm::mat4 rot = glm::mat4(1.0f);

	// Sets rotation
	mesh.xrotation = glm::rotate(rot, glm::radians(mesh.p[7]), glm::vec3(mesh.p[8], mesh.p[9], mesh.p[10]));
	mesh.yrotation = glm::rotate(rot, glm::radians(mesh.p[11]), glm::vec3(mesh.p[12], mesh.p[13], mesh.p[14]));
	mesh.zrotation = glm::rotate(rot, glm::radians(mesh.p[15]), glm::vec3(mesh.p[16], mesh.p[17], mesh.p[18]));


	// Sets movement
	mesh.translation = glm::translate(glm::vec3(mesh.p[19], mesh.p[20], mesh.p[21]));

	mesh.model = mesh.translation * mesh.xrotation * mesh.zrotation * mesh.yrotation * mesh.scale;

	mesh.gUVScale = glm::vec2(mesh.p[22], mesh.p[23]);
}

