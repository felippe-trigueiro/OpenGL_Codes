#include <GL/glew.h>
#include <iostream>
#include <GLFW/glfw3.h>

GLuint compile_shader();

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

	//THE CODE SHOULD START HERE!!!
	if (glewInit() != GLEW_OK)
		std::cout << "That's an ERROR" << std::endl;

	GLuint vertex_array_object, rendering_program;
	GLfloat color[] = { 0.0f, 0.0f, 1.0f, 1.0f };
	rendering_program = compile_shader();
	glCreateVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */		
		glClearBufferfv(GL_COLOR, 0, color);
		glUseProgram(rendering_program);
		glDrawArrays(GL_LINES, 0, 2);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

GLuint compile_shader() {
	GLuint program, vertex_shader, fragment_shader;

	const GLchar* vertex_shader_source[] = {
		"#version 450 core                                                         \n"
		"                                                                          \n"
		"void main(void) {                                                         \n"
		"   const vec4 vertices[2] = vec4[2](vec4(0.25, -0.25, 0.5, 1.0),          \n" 
		"                                    vec4(-0.25, 0.25, 0.5, 1.0));        \n"
		"   gl_Position = vertices[gl_VertexID];                                   \n"
		"}                                                                         \n"
	};

	const GLchar* fragment_shader_source[] = {
		"#version 450 core                                                         \n"
		"                                                                          \n"
		"out vec4 color;                                                           \n"
		"                                                                          \n"
		"void main(void) {                                                         \n"
		"   color = vec4(0.0, 0.8, 1.0, 1.0);                                      \n"
		"}                                                                         \n"
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
