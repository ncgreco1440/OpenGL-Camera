#ifndef Gamesetup_h
#define Gamesetup_h

namespace gconf
{
    //bool gWireframe = false;
    //bool gPoints = false;
    //void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode);
    
//    bool initOpenGL(GLFWwindow ** window, const int width, const int height, const char * title)
//    {
//        if(!glfwInit())
//        {
//            std::cerr << "GLFW Initialization Failed" << std::endl;
//            return false;
//        }
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
//        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
//        
//        *window = glfwCreateWindow(width, height, title, NULL, NULL);
//        
//        if(window == NULL)
//        {
//            std::cerr << "GLFW Window Creation Failed" << std::endl;
//            glfwTerminate();
//            return false;
//        }
//        glfwMakeContextCurrent(*window);
//        glfwSetKeyCallback(*window, key_callback);
//        
//        glewExperimental = GL_TRUE;
//        if(glewInit() != GLEW_OK)
//        {
//            std::cerr << "GLEW Initialization Failed" << std::endl;
//            return false;
//        }
//        
//        glClearColor((GLclampf)0.8, (GLclampf)0.8, (GLclampf)0.8, (GLclampf)1.0);
//        
//        return true;
//    }
    
//    void key_callback(GLFWwindow * window, int key, int scancode, int action, int mode)
//    {
//// Camera Constant ////////////////////////////////////////////////////////////////////
//        GLfloat cameraSpeed = 0.05f;
//        
//        if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) //exit application with 'esc' key
//            glfwSetWindowShouldClose(window, GL_TRUE);
//// Movement Keys //////////////////////////////////////////////////////////////////////
//        if(key == GLFW_KEY_W && action == GLFW_PRESS)
//        {
//            cameraPos += cameraSpeed * cameraFront;
//        }
//        if(key == GLFW_KEY_A && action == GLFW_PRESS)
//        {
//            
//        }
//        if(key == GLFW_KEY_S && action == GLFW_PRESS)
//        {
//            
//        }
//        if(key == GLFW_KEY_D && action == GLFW_PRESS)
//        {
//            
//        }
//    }
    
//    void show_fps(GLFWwindow * window, const char * title)
//    {
//        static double previousSeconds = 0.0;
//        static int framecount = 0;
//        double elapsedSeconds;
//        double currentSeconds = glfwGetTime();
//        
//        elapsedSeconds = currentSeconds - previousSeconds;
//        
//        // limit text 4 times per second
//        if(elapsedSeconds > 0.25)
//        {
//            previousSeconds = currentSeconds;
//            double fps = (double)framecount/elapsedSeconds;
//            double msPerFrame = 1000.0 / fps;
//            
//            std::ostringstream outs;
//            outs.precision(3);
//            outs << std::fixed
//            << title << "\t"
//            << "FPS: " << fps << "\t"
//            << "Frametime: " << msPerFrame << "ms";
//            
//            glfwSetWindowTitle(window, outs.str().c_str());
//            framecount = 0;
//        }
//        framecount++;
//    }
}

#endif
