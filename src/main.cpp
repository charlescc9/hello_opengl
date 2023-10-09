#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>
#include <vertex_array.h>
#include <vertex_buffer.h>
#include <element_buffer.h>

// Vertices coordinates
GLfloat vertices[] =
{
	-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
	0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
	0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
	-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
	0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
	0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
};

// Indices for vertices order
GLuint indices[] =
{
	0, 3, 5, // Lower left triangle
	3, 2, 4, // Lower right triangle
	5, 4, 1  // Upper triangle
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
    GLFWwindow* window = glfwCreateWindow(800, 600, "Hello OpenGL", NULL, NULL);
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
    vertex_array.LinkVertextBuffer(vertex_buffer, 0);

    // Unbind to prevent accidental modification
    vertex_array.Unbind();
    vertex_buffer.Unbind();
    element_buffer.Unbind();

    // Main loop
    while(!glfwWindowShouldClose(window))
    {
        processInput(window);

        // Clear frame
        glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        // glCheckError(); 
        
        // Activate shader
        shader_program.Activate();
        // glCheckError(); 

        // Bind vertex array
        vertex_array.Bind();

        // Draw vertices
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swap buffer
        glfwSwapBuffers(window);
        // glCheckError(); 

        // Poll for events
        glfwPollEvents();    
        // glCheckError(); 
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
