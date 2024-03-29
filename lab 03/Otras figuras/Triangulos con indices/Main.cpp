#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Vertex Shader
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

//Fragment Shader 
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

void processInput(GLFWwindow* window);
int main() {
	// Inicializa GLFW
	glfwInit();


	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow* window = glfwCreateWindow(800, 800, "Intro OpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) 
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glViewport(0, 0, 800, 800);

	//objeto Vertex Shader y obtener su referencia
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// combinar el objetto vertexShader con ShaderSource
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compilacion
	glCompileShader(vertexShader);

	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Creacion de fragmentShader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	// combinar el objetto fragmentShader con ShaderSource
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compilacion en leguaje maquina
	glCompileShader(fragmentShader);

	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Creacion del objeto shaderProgram
	GLuint shaderProgram = glCreateProgram();
	// concectar el shaderpragram con vertexShader y fragmenteShader
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	// enlazar todos los sombreados al programa
	glLinkProgram(shaderProgram);
	//verifica si hubo algun error al enlazar
	/*glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}*/

	// elimninar los objetos vertexShader y fragmentShader
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	// Vertices coordenadas
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f, // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f, // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f // Inner down
	};

	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Lower right triangle
		5, 4, 1 // Upper triangle
	};
	

	//Creacion de contenedores para el Vertex Array, VertexBuffer y ElementBuffer
	GLuint VBO, VAO, EBO;

	//Generar el VAO, el VBO y el EBO con s�lo 1 objeto cada uno
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Hacer que VAO sea el objeto de matriz de v�rtices actual vincul�ndolo
	glBindVertexArray(VAO);

	
	//Vincular el VBO especificando que es un GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// Introducir los v�rtices en el VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	// Configurar el atributo de v�rtices para que OpenGL sepa c�mo leer el VBO
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//// Habilitar el atributo de v�rtices para que OpenGL sepa usarlo
	glEnableVertexAttribArray(0);

	// Vincula tanto el VBO como el VAO a 0 para que no modifiquemos accidentalmente el VAO y el VBO que hemos creado
	glBindBuffer(GL_ARRAY_BUFFER, 0);	
	glBindVertexArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	while (!glfwWindowShouldClose(window))
	{
		//processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);;
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUseProgram(shaderProgram);

		glBindVertexArray(VAO);

		glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;	
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}
