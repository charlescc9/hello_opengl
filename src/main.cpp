#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <shader.h>

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

    // Define triangle vertices
	GLfloat vertices[] =
	{
		-0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
		0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,     // Lower right corner
		0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,  // Upper corner
		-0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
		0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,  // Inner right
		0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f      // Inner down
	};

    // Define vertex indices to define triangles
	GLuint indices[] =
	{
		0, 3, 5, // Lower left triangle
		3, 2, 4, // Upper triangle
		5, 4, 1  // Lower right triangle
	};

	Shader shader_program("../shaders/vertex.glsl", "../shaders/fragment.glsl");
    // glCheckError(); 

    // Create references to vertex array, vertext buffer, and element buffer
    GLuint vertex_array_object, vertex_buffer_object, element_buffer_object;
    glGenVertexArrays(1, &vertex_array_object);
    glGenBuffers(1, &vertex_buffer_object);
    glGenBuffers(1, &element_buffer_object);  
    // glCheckError(); 

    // Bind vertex array
    glBindVertexArray(vertex_array_object);
    // glCheckError(); 

    // Bind vertex buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_object);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    // glCheckError(); 
    
    // Bind element buffer
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_buffer_object);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // glCheckError(); 

    // Configure vertex attriburtes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);
    // glCheckError(); 
    
    // Unbind vertex buffer and element buffer
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    // glCheckError(); 

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

        // Update shader uniform
        // double time = glfwGetTime();
        // float red = static_cast<float>(sin(time) / 2.0 + 0.5);
        // int color_location = glGetUniformLocation(shader_program.ID, "ourColor");
        // glUniform4f(color_location, red, 0.0f, 0.0f, 1.0f);
        // glCheckError(); 

        // Render vertices
        // glBindVertexArray(vertex_array_object);
        // glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        // glCheckError(); 

        glfwSwapBuffers(window);
        glfwPollEvents();    
        // glCheckError(); 
    }

    // Clean up
    glDeleteVertexArrays(1, &vertex_array_object);
    glDeleteBuffers(1, &vertex_buffer_object);
    glDeleteBuffers(1, &element_buffer_object);
    shader_program.Delete();
    glfwDestroyWindow(window);
    glfwTerminate();
    // glCheckError(); 
    return 0;
}
