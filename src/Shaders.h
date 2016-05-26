#ifndef Shaders_h
#define Shaders_h

#include <iostream>
#include <fstream>
#include <string>

using std::string;

string readShader(const char * filePath)
{
    string programTxt = "";
    std::ifstream inFile(filePath);
    
    if(!inFile.is_open())
    {
        std::cerr << "Error: \"" << filePath << "\" could not be opened.";
        return programTxt.c_str();
    }
    
    string line = "";
    while(!inFile.eof())
    {
        std::getline(inFile, line);
        programTxt.append(line + '\n');
    }
    
    inFile.close();
    return programTxt;
}

GLuint LoadShaders(const char * vertexShaderFile, const char * fragementShaderFile)
{
    // Create and read shader files
    GLuint vertexShader, fragmentShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    string vertexShaderStr = readShader(vertexShaderFile);
    string fragmentShaderStr = readShader(fragementShaderFile);
    const char * vertexShaderSrc = vertexShaderStr.c_str();
    const char * fragmentShaderSrc = fragmentShaderStr.c_str();
    
    // Compile Shaders
    glShaderSource(vertexShader, 1, &vertexShaderSrc, nullptr);
    glCompileShader(vertexShader);
    glShaderSource(fragmentShader, 1, &fragmentShaderSrc, nullptr);
    glCompileShader(fragmentShader);
    
    // Check for successful compilation
    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertexShader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Error! Vertex Shader Failed to compile! " << infoLog << std::endl;
    }
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(fragmentShader, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Error! Fragment Shader Failed to compile! " << infoLog << std::endl;
    }
    
    // Create Shader Program
    GLuint shaderProgram = glCreateProgram();
    
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    
    // Check for successful link
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetProgramInfoLog(shaderProgram, sizeof(infoLog), NULL, infoLog);
        std::cerr << "Shader program linking failed! " << infoLog << std::endl;
    }
    
    // After shaders are linked, delete them to free up the memory
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    // Return program reference
    return shaderProgram;
}

#endif
