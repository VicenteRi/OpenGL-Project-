#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#define WIDTH 1280
#define HEIGHT 720
int main(void)
{
    int width = 1280;
    int height = 720;
    if(!glfwInit())
    {
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    
    GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"El Pepe The Game V1.0",NULL,NULL);
    if (window == NULL)
    {
        std::cout << "el pepe se enojo, CORREEEE" << std::endl;

        glfwTerminate();
        return -1;

    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initalize 'GLAD'" << std::endl;

        glfwTerminate();
        return -1;
    }


    while(!glfwWindowShouldClose)
    {
        glfwSwapBuffers(window);
        glfwPollEvents();
    }



    return 0;


}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
}
