#version <version_number> //At a minimun this will be 330 for GLSL version 3.3

in <type> <in variable name>        // input from the previous stage or CPU
in <type> <in variable name>        // input from the previous stage or CPU

out <type> <out variable name>      // output for the next stage

uniform <type> <uniform name>       // variables

// other misc functions...

int main()                          // main function
{
    /* Process input[s] and do some graphics stuff
     ...
     Output processed stuff to output variable */
    <out variable name> = stuff here;
}
/**
 
Data types for Shaders
 
 Built-in: 
    float
    double 
    bool
    int
    uint
 
 Vectors:
    vec2, vec3, vec4        floats
    dvec2, dvec3, dvec4     double
    bvec2, bvec3, bvec4     bool
    ivec2, ivec3, ivec4     int
    uvec2, uvec3, uvec4     uint
    
 Square Matrices:
    mat2, mat3, mat4        floats
    dmat2, dmat3, dmat4     double
 
 Non-Square Matrices:
    mat{2x3,4}x{2,3,4}      floats
    dmat{2x3,4}x{2,3,4}     double
 
 
 in <type> <in variable name>:
    layout(location = 0) in vec3 pos; 
    
    The first location in the Vertex Array Object will be a position attribute of vec3 
    this particular vec3 variable named "pos" will be passed into the shader.
 
 out <type> <out variable name>:
    Whatever variable that needs to be passed into the next stage of the render pipeline. 
 
    out vec3 vertColor;
 
    A variable name "vertColor" which pertains to a color attribute of the Vertex Array Object 
    will be passed into the next stage, in this case the fragment shader. The fragment shader
    must be ready to accept this variable with an "in" statement 
 
    in vec3 vertColor;
 
 uniform <type> <uniform name> 
    global variable that is seen by all shaders 
*/

