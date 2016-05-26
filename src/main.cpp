#define GLEW_STATIC
#include <GL/glew.h>
#include <GL/glfw3.h>
#include <iostream>
#include <sstream>
#include "Shaders.h"
#include "shaderprog.h"
#include <SOIL/SOIL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Constants //////////////////////////////////////////////////////////////////////////////
bool fullscreen = false;
const int WIDTH = 800;
const int HEIGHT = 600;
const char * TITLE = "Open GL Tutorial";
GLFWwindow * gWindow = NULL;
GLfloat lastX = WIDTH / 2.0;
GLfloat lastY = HEIGHT / 2.0;
GLfloat yaw = -90.0f;
GLfloat pitch = 0.0f;
// Functions //////////////////////////////////////////////////////////////////////////////
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
void mouse_callback(GLFWwindow * window, double xpos, double ypos);
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset);
bool initOpenGL(GLFWwindow ** window, const int width, const int height, const char * title);
void show_fps(GLFWwindow * window, const char * title);
// Camera /////////////////////////////////////////////////////////////////////////////////
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 0.3f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);
GLfloat field_of_view = 45.0f;
double startJump = 0.0;
void jump();
bool jumping = false;
void do_movement();
// Key States ////////////////////////////////////////////////////////////////////////////
bool keys[1024];
// DeltaTime ////////////////////////////////////////////////////////////////////////////
GLfloat deltaTime = 0.0f;
GLfloat lastFrame = 0.0f;
bool firstMouse = true;

// Custom LookAt


int main() {
// Initialize OpenGL
    if(!initOpenGL(&gWindow, WIDTH, HEIGHT, TITLE))
    {
        return -1;
    }
    
// Load shaders into program
// GLuint shaderProgram = LoadShaders("shader.ver", "shader.fra");
    ShaderProg shaderProgram;
    shaderProgram.loadShaders("shader.ver", "shader.fra");
    
// Load Image using SOIL
    int h, w;
    unsigned char * image = SOIL_load_image("container.jpg", &w, &h, 0, SOIL_LOAD_RGB);
    
// Generate and Bind Texture
    GLuint texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// Set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
// Free up memory
    SOIL_free_image_data(image);
    glBindTexture(GL_TEXTURE_2D, 0);
    
    GLfloat vertices[] = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };
    
//    GLuint indices[] = {
//        0, 1, 3,
//        1, 2, 3
//    };
    
// Creation of Buffers and Vertex Arrays
    GLuint vbo, ibo, vao;
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);
// Bind and buffer data from vertices
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    
// Generate, Bind, and set Vertex Attribute Pointers for vao
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    
// Position Attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLvoid*)0);
    glEnableVertexAttribArray(0);
// Color Attribute
    //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 8, (GLvoid*)(sizeof(GLfloat) * 3));
    //glEnableVertexAttribArray(1);
// Texture Attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GLfloat) * 5, (GLvoid*)(sizeof(GLfloat) * 3));
    glEnableVertexAttribArray(2);
    
// Bind and Buffer data from indicies
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 0.0f, 0.0f, 0.0f),
        glm::vec3( 2.0f, 5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f, 3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f, 2.0f, -2.5f),
        glm::vec3( 1.5f, 0.2f, -1.5f),
        glm::vec3(-1.3f, 1.0f, -1.5f)
    };

// Main Loop
    while(!glfwWindowShouldClose(gWindow))
    {
        show_fps(gWindow, TITLE);
// Query window for keyboad and mouse events
        glfwPollEvents();
        GLfloat currentTime = glfwGetTime();
        deltaTime = currentTime - lastFrame;
        lastFrame = currentTime;
        do_movement();
        
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
// Use Shader Program //////////////////////////////////////////////////////////////////////////////
        shaderProgram.use();
// Camera/View Transformations /////////////////////////////////////////////////////////////////////
        //GLfloat radius = 10.0f;
        //GLfloat camX = sin(glfwGetTime()) * radius;
        //GLfloat camZ = cos(glfwGetTime()) * radius;
// Coordinate Matrices /////////////////////////////////////////////////////////////////////////////
        glm::mat4 model, view, proj;
        
        //model = glm::rotate(model, -55.0f, glm::vec3(1, 0, 1));
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        proj = glm::perspective(glm::radians(field_of_view), (GLfloat)WIDTH/(GLfloat)HEIGHT, 0.1f, 100.0f);
// Get handle to shader program ////////////////////////////////////////////////////////////////////
        GLuint ptProg = shaderProgram.reference();
// Get uniform locations //////////////////////////////////////////////////////////////////////////
        GLuint modelLoc = glGetUniformLocation(ptProg, "model");
        GLuint viewLoc = glGetUniformLocation(ptProg, "view");
        GLuint projLoc = glGetUniformLocation(ptProg, "proj");
// Set uniform values /////////////////////////////////////////////////////////////////////////////
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
        //glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));
// Bind and Draw //////////////////////////////////////////////////////////////////////////////////
        for(int i = 0; i < 10; i++)
        {
            model = glm::translate(model, cubePositions[i]);
            GLfloat angle = 20.0f * i;
            model = glm::rotate(model, angle, glm::vec3(1.0f, 0.3f, 0.5f));
            glBindTexture(GL_TEXTURE_2D, texture);
            glBindVertexArray(vao);
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
            //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }
        glBindVertexArray(0);
// Double buffering the window ///////////////////////////////////////////////////////////////////
        glfwSwapBuffers(gWindow);
        //glfwSwapInterval(0);
    }
    
    glDeleteBuffers(1, &vbo);
    glfwTerminate();
    return 0;
}

bool initOpenGL(GLFWwindow ** window, const int width, const int height, const char * title)
{
    if(!glfwInit())
    {
        std::cerr << "GLFW Initialization Failed" << std::endl;
        return false;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
    
    *window = glfwCreateWindow(width, height, title, NULL, NULL);
    
    if(window == NULL)
    {
        std::cerr << "GLFW Window Creation Failed" << std::endl;
        glfwTerminate();
        return false;
    }
    glfwMakeContextCurrent(*window);
    glfwSetKeyCallback(*window, key_callback);
    glfwSetCursorPosCallback(*window, mouse_callback);
    glfwSetScrollCallback(*window, scroll_callback);
    
    glewExperimental = GL_TRUE;
    if(glewInit() != GLEW_OK)
    {
        std::cerr << "GLEW Initialization Failed" << std::endl;
        return false;
    }
    
    glViewport(0, 0, WIDTH, HEIGHT);
    glEnable(GL_DEPTH_TEST);
    
    glfwSetInputMode(*window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
    
    return true;
}

// KEY CALLBACK
void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
{
    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) //exit application with 'esc' key
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
    if(action == GLFW_PRESS)
        keys[key] = true;
    else if(action == GLFW_RELEASE)
        keys[key] = false;
}

// MOUSE CURSOR CALLBACK
void mouse_callback(GLFWwindow * window, double xpos, double ypos)
{
    GLfloat sensitivity = 0.15f;
    
    if(firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }
    
    GLfloat xOffset = (xpos - lastX);
    GLfloat yOffset = (lastY - ypos);
    
    lastX = xpos;
    lastY = ypos;
    
    xOffset *= sensitivity;
    yOffset *= sensitivity;
    
    yaw += xOffset;
    pitch += yOffset;
    
// Constraints for pitch angle
    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;
    
// Camera Variables ///////////////////////////////////////////////////////////////////
    glm::vec3 front;
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(front);
    
    std::cout << "Mouse Cursor at (" << xpos << ", " << ypos << ")" << std::endl;
}

// MOUSE SCROLL CALLBACK
void scroll_callback(GLFWwindow * window, double xoffset, double yoffset)
{
    if(field_of_view >= 1.0f && field_of_view <= 45.0f)
        field_of_view += yoffset;
    if(field_of_view <= 1.0f)
        field_of_view = 1.0f;
    if(field_of_view >= 45.0f)
        field_of_view = 45.0f;
}

void show_fps(GLFWwindow * window, const char * title)
{
    static double previousSeconds = 0.0;
    static int framecount = 0;
    double elapsedSeconds;
    double currentSeconds = glfwGetTime();
    
    elapsedSeconds = currentSeconds - previousSeconds;
    
    // limit text 4 times per second
    if(elapsedSeconds > 0.25)
    {
        previousSeconds = currentSeconds;
        double fps = (double)framecount/elapsedSeconds;
        double msPerFrame = 1000.0 / fps;
        
        std::ostringstream outs;
        outs.precision(3);
        outs << std::fixed
        << title << "\t"
        << "FPS: " << fps << "\t"
        << "Frametime: " << msPerFrame << "ms";
        
        glfwSetWindowTitle(window, outs.str().c_str());
        framecount = 0;
    }
    framecount++;
}

void do_movement()
{
// Camera Constant ////////////////////////////////////////////////////////////////////
    GLfloat cameraSpeed = 5.0f * deltaTime;
// Movement Keys //////////////////////////////////////////////////////////////////////
    if(keys[GLFW_KEY_W])
    {
        cameraPos += cameraSpeed * cameraFront;
    }
    if(keys[GLFW_KEY_A])
    {
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(keys[GLFW_KEY_S])
    {
        cameraPos -= cameraSpeed * cameraFront;
    }
    if(keys[GLFW_KEY_D])
    {
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    }
    if(keys[GLFW_KEY_SPACE])
    {
        if(!jumping)
        {
            startJump = glfwGetTime();
            jumping = true;
        }
    }
    
    if(jumping)
        jump();
    else
        cameraPos.y = 0.0f;
}
// For FPS style camera (no flying) cameraPos.y should always be 0.0f


void jump()
{
//Are we done jumping? For 1 second space bar becomes inactive
    if(glfwGetTime() - startJump >= 1.0)
    {
        jumping = false;
        return;
    }
    else if(glfwGetTime() - startJump <= 0.5)
    {
//Incrementing height
        cameraPos.y += 0.01 * 1.5;
    }
    else
    {
//Decrementing height
        if(cameraPos.y - (0.01 * 1.98) >= 0.0f)
            cameraPos.y -= (0.01 * 1.98);
        else
            cameraPos.y = 0.0f;
    }
}
