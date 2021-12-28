/*
  Demo program from The Cherno  OpenGL series....
  This is the first shader example
  All this code was derived from his excellent tutorial
*/

//#define GLFW_DLL 
//#define GLFW_INCLUDE_NONE
#define GLEW_STATIC
#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>
#include <vector>
#include <string>

using namespace std;

static unsigned int CompileShader(unsigned int type, const std::string& source)
{
  unsigned int id = glCreateShader(type);
  const char* src = source.c_str();
  glShaderSource(id, 1, &src, nullptr);
  glCompileShader(id);

  int result;
  glGetShaderiv(id, GL_COMPILE_STATUS, &result);
  if(result == GL_FALSE){
    int length;
    glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
    char* message = (char*)alloca(length * sizeof(char));
    glGetShaderInfoLog(id, length, &length, message);
    std::cout << "Failed to compile shader! " << (type == GL_VERTEX_SHADER ? "vertex" : "Fragment") << std::endl;
    std:cout << message << std::endl;
    
  }
  return id;
}

static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
  unsigned int program = glCreateProgram();
  unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
  unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glValidateProgram(program);

  glDeleteShader(vs);
  glDeleteShader(fs);

  return program;
}

int main()
{
/*
  int a;
  vector<string> msg {"Hello", "C++", "World", "from", "VS Code", "and the C++ extension!"};

  for (const string& word : msg)
  {
      cout << word << " ";
  }
  cout << endl;
*/

  GLFWwindow* window;

  /* Initialize the library */
  if (!glfwInit())
      return -1;

  /* Create a windowed mode window and its OpenGL context */
  //window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
  window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
  if (!window)
  {
      glfwTerminate();
      return -1;
  }


  /* Make the window's context current */
  glfwMakeContextCurrent(window);

  if (glewInit() != GLEW_OK)
    std::cout << "Error!" << std::endl;

  std::cout << glGetString(GL_VERSION) << std::endl;

  float postions[6] = {
    -0.5f, -0.5f,
     0.0f,  0.5f,
     0.5f, -0.5f
  };

  // set up the OpenGL to draw something
  unsigned int buffer;
  glGenBuffers(1, &buffer);
  glBindBuffer(GL_ARRAY_BUFFER, buffer);
  glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), postions, GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float)*2, 0);


  std::string vertexSharder = 
    "#version 410 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   gl_Position = position;\n"
    "}\n";

  std::string fragmentSharder = 
    "#version 410\n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "\n"
    "void main()\n"
    "{\n"
    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";


  unsigned int shader = CreateShader(vertexSharder, fragmentSharder);
  glUseProgram(shader);

  /* Loop until the user closes the window */
  while (!glfwWindowShouldClose(window)){
      /* Render here */
      glClear(GL_COLOR_BUFFER_BIT);

      glDrawArrays(GL_TRIANGLES, 0, 3);

      /* Swap front and back buffers */
      glfwSwapBuffers(window);

      /* Poll for and process events */
      glfwPollEvents();
  }

  glDeleteProgram(shader);
  glfwTerminate();
  return 0;

}
