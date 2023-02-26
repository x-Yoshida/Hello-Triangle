#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <math.h>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

enum ShaderNames
{
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
};

struct Vector2
{
    float x;
    float y;
    Vector2(float posX=0,float posY=0)
    {
        x=posX;
        y=posY;
    }
};

struct Color
{
    float r,g,b,a;
    Color(float red=0,float green=0,float blue=0,float alpha=255.0f)
    {
        if(red>255)
        {
            red=255;
        }
        if(green>255)
        {
            green=255;
        }
        if(blue>255)
        {
            blue=255;
        }
        if(alpha>255)
        {
            alpha=255;
        }
        r=red/255;
        g=green/255;
        b=blue/255;
        a=alpha/255;
    }
    void changeUsingRgb(float red=0,float green=0,float blue=0,float alpha=255.0f)
    {
        if(red>255)
        {
            red=255;
        }
        if(green>255)
        {
            green=255;
        }
        if(blue>255)
        {
            blue=255;
        }
        if(alpha>255)
        {
            alpha=255;
        }
        r=red/255;
        g=green/255;
        b=blue/255;
        a=alpha/255;
    }
};

//struct Vertex
//{
//    float x;
//    float y;
//};

struct Vertex
{
    Vector2 pos;
    Color color;
};


struct ShaderSources
{
    std::string vertexShader;
    std::string fragmentShader;
};

void loadShader(std::string path,std::string& shader)
{
    std::ifstream shaderSrc;
    std::string line;
    std::stringstream ss;
    shaderSrc.open(path);
    while(std::getline(shaderSrc,line))
    {
        ss << line << std::endl;
    }

    shader = ss.str();

    shaderSrc.close();
}

ShaderSources loadShaders(std::string path)
{
    ShaderSources result;
    loadShader(path+"/vertexShader.glsl",result.vertexShader);
    loadShader(path+"/fragmentShader.glsl",result.fragmentShader);
    return result;
}

static int compileShader(unsigned int type,const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);
    
    //No errors ez
    int res;
    glGetShaderiv(id,GL_COMPILE_STATUS,&res);
    if(res == GL_FALSE)
    {
        int length;
        glGetShaderiv(id,GL_INFO_LOG_LENGTH,&length);
        char* mess = (char*)alloca(length*sizeof(char));
        glGetShaderInfoLog(id,length,&length,mess);
        std::cout << mess <<std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}

static unsigned int createShader(const std::string& vertexShader,const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = compileShader(GL_VERTEX_SHADER,vertexShader);
    unsigned int fs = compileShader(GL_FRAGMENT_SHADER,fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}

int main(int argc, char** argv)
{
    Color backgroundColor={0,0,0};
    Color triangleColor={128,255,255};
    if(!glfwInit())
    {
        return 1;
    }
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
    
    GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL", nullptr, nullptr); // Windowed
    
    glfwMakeContextCurrent(window);
    glewInit();

    Vertex vertices[] = {{{-0.5f,-0.5f},{255}},{{0.0f, 0.5f},{0,255}},{{0.5f,-0.5f},{0,0,255}}};
    Vertex testVertices[] = {{{-0.5f,-0.5f},{255}},{{0.0f, 0.5f},{0,255}},{{0.5f,-0.5f},{0,0,255}}};
    std::cout << "Adres: " << &(testVertices[0].pos.x) <<" Wartosc: " << testVertices[0].pos.x << " " <<"Adres: " << ((float*)testVertices)<<" Wartosc: "<< *((float*)testVertices)<<std::endl;
    std::cout << "Adres: " << &(testVertices[0].pos.y) <<" Wartosc: " << testVertices[0].pos.y << " " <<"Adres: " << ((float*)testVertices+1)<<" Wartosc: "<< *((float*)testVertices+1)<<std::endl;
    std::cout << "Adres: " << &(testVertices[0].color.r) <<" Wartosc: " << testVertices[0].color.r << " " <<"Adres: " << ((float*)testVertices+2)<<" Wartosc: "<< *((float*)testVertices+2)<<std::endl;
    std::cout << "Adres: " << &(testVertices[1].pos.x) <<" Wartosc: " << testVertices[1].pos.x << " " <<"Adres: " << ((float*)testVertices+6)<<" Wartosc: "<< *((float*)testVertices+6)<<std::endl;
    std::cout << "Adres: " << &(testVertices[1].pos.y) <<" Wartosc: " << testVertices[1].pos.y << " " <<"Adres: " << ((float*)testVertices+7)<<" Wartosc: "<< *((float*)testVertices+7)<<std::endl;
    std::cout << "Adres: " << &(testVertices[1].color.r) <<" Wartosc: " << testVertices[1].color.r << " " <<"Adres: " << ((float*)testVertices+8)<<" Wartosc: "<< *((float*)testVertices+8)<<std::endl;
    float verticesPositions[6] = {
        -0.5f,-0.5f,
         0.0f, 0.5f,
         0.5f,-0.5f
    };
    
    unsigned int buffer;
    glGenBuffers(1,&buffer);
    glBindBuffer(GL_ARRAY_BUFFER,buffer);
    glBufferData(GL_ARRAY_BUFFER,6*3*sizeof(float),vertices,GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,6*sizeof(float),(const void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,4,GL_FLOAT,GL_FALSE,6*sizeof(float),(const void*)(2*sizeof(float)));
    
    ShaderSources shadersources = loadShaders("./res/shaders");
    
    unsigned int shader = createShader(shadersources.vertexShader,shadersources.fragmentShader);
    glUseProgram(shader);
    //int uniColor = glGetUniformLocation(shader,"triangleColor");
    //glUniform4f(uniColor,triangleColor.r,triangleColor.g,triangleColor.b,triangleColor.a);
    //std::cout << triangleColor.a << std::endl;
    
    while(!glfwWindowShouldClose(window))
    {
        glClearColor(backgroundColor.r,backgroundColor.g,backgroundColor.b,backgroundColor.a);
        glClear(GL_COLOR_BUFFER_BIT);

        glDrawArrays(GL_TRIANGLES,0,3);

        glfwPollEvents();
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, GL_TRUE);
        }
        glfwSwapBuffers(window);
    }

    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}
