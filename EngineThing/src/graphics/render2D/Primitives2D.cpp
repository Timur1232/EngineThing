#include "Primitives2D.h"

#include <iostream>
#include <GL/glew.h>
#include <glm/glm.hpp>

#include "../shader/Shader.h"
#include "../../window/Window.h"

namespace Render2D
{

static uint s_VAO;
static uint s_VBO;
static uint s_EBO;

static Shader s_CircleShader;

const float SCREEN_SPACE_QUAD[8] = {
	//   x	   y
	   -1.0f,-1.0f,
		1.0f,-1.0f,
	   -1.0f, 1.0f,
		1.0f, 1.0f
};

const uint_32 SCREEN_SPACE_INDECIES[6] = {
		0, 1, 2,
		1, 2, 3
};

static int load_circle_shader();
static void bind_all();
static void unbind_all();

int initialize()
{
	if (load_circle_shader())
		return -1;

	glGenVertexArrays(1, &s_VAO);
	glGenBuffers(1, &s_VBO);
	glGenBuffers(1, &s_EBO);

	bind_all();
	
	glBufferData(GL_ARRAY_BUFFER, sizeof(SCREEN_SPACE_QUAD), SCREEN_SPACE_QUAD, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SCREEN_SPACE_INDECIES), SCREEN_SPACE_INDECIES, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
	glEnableVertexAttribArray(0);
	
	unbind_all();

	return 0;
}

void draw_circle(const glm::vec2& pos, float radius, float thickness, glm::vec3& color, const Window& window)
{
	s_CircleShader.use();
	s_CircleShader.setUniform("iPosition", pos);
	s_CircleShader.setUniform("iRadius", radius);
	s_CircleShader.setUniform("iThickness", thickness);
	s_CircleShader.setUniform("iResolution", glm::vec2(window.getWidth(), window.getHeight()));
	s_CircleShader.setUniform("iColor", color);
	s_CircleShader.setUniform("iFade", 0.005f);

	bind_all();
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	unbind_all();
}

void draw_box(const glm::vec2& pos, float width, float height, float thickness, glm::vec3& color)
{
}

int load_circle_shader()
{
	try
	{
		s_CircleShader.loadShader("res/shaders/vertex/v_shader.glsl", "res/shaders/fragment/f_circle.glsl");
	}
	catch (std::runtime_error& err)
	{
		std::cerr << err.what() << std::endl;
		return -1;
	}
	return 0;
}

void bind_all()
{
	glBindVertexArray(s_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, s_VBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, s_EBO);
}

void unbind_all()
{
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}
