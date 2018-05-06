#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

GLuint compile_shaders();

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
		std::cout << "That's an ERROR!" << std::endl;

	GLfloat color[] = { 1.0f, 0.0f, 0.0f, 1.0f };
	float angle = 0.0;

	GLuint VAO;

	GLuint program = compile_shaders();
	std::cout << program << std::endl;
	glCreateVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		//glClear(GL_COLOR_BUFFER_BIT);
		color[0] = (float)sin(angle)*0.5f + 0.5f;
		color[1] = (float)cos(angle)*0.5f + 0.5f;
		
		glClearBufferfv(GL_COLOR, 0, color);
		glUseProgram(program);
		glPointSize(40.0f);
		glDrawArrays(GL_POINTS, 0, 1);

		angle += 0.001f;
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

GLuint compile_shaders() {
	GLuint vertex_shader, fragment_shader, program;

	const GLchar* vertex_shader_source[] = {

		"#version 450 core                                \n"
		"                                                 \n"
		"void main (void) {                               \n"
		"	gl_Position = vec4(0.0, 0.0, 1.0, 1.0);   \n"
		"}                                                \n"
	};

	const GLchar* fragment_shader_source[] = {
		"#version 450 core                            \n"
		"out vec4 color;                              \n"
		"                                             \n"
		"void main() {                                \n"
		"	color = vec4(0.0, 0.0, 1.0, 1.0);         \n"
		"}                                            \n"
	};

	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, NULL);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, NULL);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}
