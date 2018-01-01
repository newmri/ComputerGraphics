#include "sb6.h"
#include <math.h>

class my_application : public sb6::application
{
public:
	GLuint compile_shaders(void)
	{
		GLuint vertex_shader;
		GLuint fragment_shader;
		GLuint program;

		// Vertex Shader Code
		static const GLchar* vertex_shader_source[] =
		{
			"#version 430 core			\n"
			"							\n"
			"void main(void)			\n"
			"{							\n"
			"	gl_Position = vec4(0.0, 0.0, 0.5, 1.0); \n"
			"}							\n"
		};

		// Fragment Shader Code
		static const GLchar* fragment_shader_source[] = 
		{
			"#version 430 core			\n"
			"							\n"
			"out vec4 color;			\n"
			"							\n"
			"void main(void)			\n"
			"{							\n"
			"	color = vec4(1.0, 1.0, 1.0, 1.0); \n"
			"}							\n"
		};

		// Create Vertex Shader and Compile
		vertex_shader = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
		glCompileShader(vertex_shader);

		// Create Fragment Shader and Comppile
		fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
		glCompileShader(fragment_shader);

		// Create Program and Attach shader
		program = glCreateProgram();
		glAttachShader(program, vertex_shader);
		glAttachShader(program, fragment_shader);
		glLinkProgram(program);

		// Delete Shader
		glDeleteShader(vertex_shader);
		glDeleteShader(fragment_shader);

		return program;

	}

	void startup()
	{
		rendering_program = compile_shaders();
		glGenVertexArrays(1, &vertex_array_object);
		glBindVertexArray(vertex_array_object);

	}

	void shutdown()
	{
		glDeleteVertexArrays(1, &vertex_array_object);
		glDeleteProgram(rendering_program);
		glDeleteVertexArrays(1, &vertex_array_object);
	}

	void render(double currentTime)
	{
		const GLfloat color[] = { (float)sin(currentTime) * 0.5f + 0.5f, (float)cos(currentTime) * 0.5f + 0.5f, 0.0f,1.0f };
		glClearBufferfv(GL_COLOR, 0, color);

		glUseProgram(rendering_program);
		glPointSize(40.0f);
		glDrawArrays(GL_POINTS, 0, 1);
	}

private:
	GLuint rendering_program;
	GLuint vertex_array_object;
};

DECLARE_MAIN(my_application);