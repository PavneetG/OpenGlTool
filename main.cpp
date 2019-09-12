#include <iostream>
#include <fstream>
#include <stdlib.h>

//Name: Pavneet Gill
//Date: 2019-08-18
//Description: Sketch App using GL_LINE_STRIP To draw
//Instruction: To draw use left mouse key and draw along surface to draw
//to erase use spacebar

// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glut.h>
#include <vector>
#include <array>

// GLFW
#include <GLFW/glfw3.h>

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

GLuint texture_id, program_id;
GLint uniform_mytexture;

double xpos, ypos;
bool lbutton_down;
std::vector<std::array<int, 2>> points;

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
void cursorEnterCallback(GLFWwindow* window, int entered);
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main(void)
{
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit())
    {
        return -1;
    }

    // Create a windowed mode window and its OpenGL context
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Hello World", NULL, NULL);

    glfwSetCursorPosCallback(window, cursorPositionCallback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    glfwSetKeyCallback(window, keyCallback);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

    glfwSetCursorEnterCallback(window, cursorEnterCallback);

    glfwSetMouseButtonCallback(window, mouseButtonCallback);

    glfwSetInputMode(window, GLFW_STICKY_MOUSE_BUTTONS, 1);

    glfwSetScrollCallback(window, scrollCallback);

    unsigned char pixels[16 * 16 * 4];
    memset(pixels, 0xff, sizeof(pixels));
    GLFWimage image;
    image.width = 16;
    image.height = 16;
    image.pixels = pixels;
    GLFWcursor* cursor = glfwCreateCursor(&image, 0, 0);
    glfwSetCursor(window, cursor); // set to null to reset cursor

    int screenWidth, screenHeight;
    glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, screenWidth, screenHeight); // specifies the part of the window to which OpenGL will draw (in pixels), convert from normalised to pixels
    glMatrixMode(GL_PROJECTION); // projection matrix defines the properties of the camera that views the objects in the world coordinate frame. Here you typically set the zoom factor, aspect ratio and the near and far clipping planes
    glLoadIdentity(); // replace the current matrix with the identity matrix and starts us a fresh because matrix transforms such as glOrpho and glRotate cumulate, basically puts us at (0, 0, 0)
    glOrtho(0, SCREEN_WIDTH, SCREEN_HEIGHT, 0, 0, 1); // essentially set coordinate system
    glMatrixMode(GL_MODELVIEW); // (default matrix mode) modelview matrix defines how your objects are transformed (meaning translation, rotation and scaling) in your world

    glLoadIdentity(); // same as above comment

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window))
    {
        // // Swap front and back buffers
        glfwSwapBuffers(window);

        // // Poll for and process events
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

static void cursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
    std::cout << xpos << " : " << ypos << std::endl;

}

void cursorEnterCallback(GLFWwindow* window, int entered)
{
    if (entered)
    {
        std::cout << "Entered Window" << std::endl;
    }
    else
    {
        std::cout << "Left window" << std::endl;
    }
}

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
    glfwMakeContextCurrent(window);
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
    {
        std::cout << "Right button pressed" << std::endl;
    }
    else if (button == GLFW_MOUSE_BUTTON_LEFT)
    {
        std::cout << "Left button pressed" << std::endl;

       while (!glfwWindowShouldClose(window))
        {
            //glClear(GL_COLOR_BUFFER_BIT);
            if (GLFW_PRESS == action)
                lbutton_down = true;
            else if (GLFW_RELEASE == action) {
                lbutton_down = false;
                points.clear();
            }

            if (lbutton_down) {
                glfwGetCursorPos(window, &xpos, &ypos);

                 std::array<int, 2> point = { xpos ,ypos };
                 points.push_back(point);

 
                glLineWidth(5);
                glBegin(GL_LINE_STRIP);
                

                for (int i = 0; i < points.size(); i++)
                {
                    glVertex2d(points[i][0], points[i][1]);
                }
                glEnd();


            }
            glfwSwapBuffers(window);
            // Poll for and process events
            glfwPollEvents();
        }
        glfwTerminate();

    }
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
    std::cout << xoffset << " : " << yoffset << std::endl;
}


void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << key << std::endl;

    // actions are GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT
    if (key == GLFW_KEY_SPACE )
    {
        glClear(GL_COLOR_BUFFER_BIT);//clears window
    }
}
