#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <math.h>


int main()
{
    // Initialize GLFW
    glfwInit();


    // Tell GLFW to use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Tell GLFW to use OpenGL Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a window
    GLFWwindow* window = glfwCreateWindow(800,800, "LOL", NULL, NULL);

    // Check if window was created
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);
    // Initialize GLAD
    gladLoadGL();
    //set viewport
    glViewport(0,0,800,800);

    // Create and compile our vertex shader
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Create and compile our fragment shader
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Link shaders
    GLuint shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram,vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

     // create the vertices
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
        0, 3, 5,
        3, 2, 4,
        5, 4, 1
    };


    // Set up vertex data (and buffer(s)) and attribute pointers
    GLuint VAO, VBO, EBO;

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER,sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE,3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);


    while(!glfwWindowShouldClose(window))
    {
        
        glClearColor(0.07f,0.13f,0.17f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        //start shader program
        glUseProgram(shaderProgram);
        // bind the vertex array object and draw the triangle
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);
        glfwSwapBuffers(window);

        //check for events
        glfwPollEvents();
    }

    //delete the vertex array object
    glDeleteVertexArrays(1, &VAO);
    //delete the vertex buffer object
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    //delete the shader program
    glDeleteProgram(shaderProgram);
    // Close the window
    glfwDestroyWindow(window);
    // Terminate GLFW
    glfwTerminate();
    return 0;
}