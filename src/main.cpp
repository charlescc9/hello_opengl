#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <shader.h>
#include <vertex_array.h>
#include <vertex_buffer.h>
#include <element_buffer.h>

const unsigned int width = 800;
const unsigned int height = 800;

// Vertices coordinates
GLfloat vertices[] =
{ 
	-0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
	-0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
	 0.5f, 0.0f, -0.5f,     0.83f, 0.70f, 0.44f,
	 0.5f, 0.0f,  0.5f,     0.83f, 0.70f, 0.44f,
	 0.0f, 0.8f,  0.0f,     0.92f, 0.86f, 0.76f,
};

// Indices for vertices order
GLuint indices[] =
{
	0, 1, 2,
	0, 2, 3,
	0, 1, 4,
	1, 2, 4,
	2, 3, 4,
	3, 0, 4
};

void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

int main()
{
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window and context
    GLFWwindow* window = glfwCreateWindow(width, height, "Hello OpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);  
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }  

	Shader shader_program("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    glCheckError(); 

    // Create and bind vertex array
    VertexArrayObject vertex_array;
    vertex_array.Bind();

    // Create vertex buffer from vertices
    VertexBufferObject vertex_buffer(vertices, sizeof(vertices));

    // Create element buffer from indices
    ElementBufferObject element_buffer(indices, sizeof(indices));

    // Link vertex array with vertex buffer
    vertex_array.LinkVertextBuffer(vertex_buffer, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*) 0);
    vertex_array.LinkVertextBuffer(vertex_buffer, 1, 3, GL_FLOAT, 6 * sizeof(float), 
                                   (void*) (3 * sizeof(float)));

    // Unbind to prevent accidental modification
    vertex_array.Unbind();
    vertex_buffer.Unbind();
    element_buffer.Unbind();

    // Set up rotation
    float rotation = 0.0f;
	double prev_time = glfwGetTime();

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

    // Main loop
    while(!glfwWindowShouldClose(window))
    { 
        processInput(window);

        // Clear frame
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glCheckError(); 
        
        // Activate shader
        shader_program.Activate();
        glCheckError(); 

        // Change rotation based on timer
		double curr_time = glfwGetTime();
		if (curr_time - prev_time >= 1 / 60)
		{
			rotation += 0.1f;
			prev_time = curr_time;
		}

        // Initialize MVP matrices
        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = glm::mat4(1.0f);
        glm::mat4 projection = glm::mat4(1.0f);

        model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 1.0f, 0.0f));
        view = glm::translate(view, glm::vec3(0.0f, -0.5f, -2.0f));
        projection = glm::perspective(glm::radians(45.0f), (float) (width / height), 0.1f, 100.0f);

        int model_id = glGetUniformLocation(shader_program.id, "model");
        glUniformMatrix4fv(model_id, 1, GL_FALSE, glm::value_ptr(model));
        int view_id = glGetUniformLocation(shader_program.id, "view");
        glUniformMatrix4fv(view_id, 1, GL_FALSE, glm::value_ptr(view));
        int projection_id = glGetUniformLocation(shader_program.id, "projection");
        glUniformMatrix4fv(projection_id, 1, GL_FALSE, glm::value_ptr(projection));

        // Bind vertex array
        vertex_array.Bind();

        // Draw vertices
        glDrawElements(GL_TRIANGLES, sizeof(indices) / sizeof(int), GL_UNSIGNED_INT, 0);

        // Swap buffer
        glfwSwapBuffers(window);
        glCheckError(); 

        // Poll for events
        glfwPollEvents();    
        glCheckError(); 
    }

    // Clean up
    vertex_array.Delete();
    vertex_buffer.Delete();
    element_buffer.Delete();
    shader_program.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    glCheckError();
    return 0;
}
