#include <GLFW/glfw3.h>
#include <GL/glu.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>

#define CheckGL do { \
    GLenum e = glGetError(); \
    if (e != GL_NO_ERROR) \
    fprintf ( stderr \
        , "in ['%s', L %d, %s()]: %s\n" \
        , __FILE__, __LINE__, __FUNCTION__ \
        , gluErrorString(e) ); \
} while (false)

const char *src_fs1 = (
    #include "gen/fs1.c"
);

const char *src_vs1 = (
    #include "gen/vs1.c"
);

GLuint createShader(const char *code, GLenum type) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &code, nullptr);
    glCompileShader(shader);

    char *strLog = new char[4096];
    GLsizei length = 0;
    glGetShaderInfoLog(shader, 4096, &length, strLog);
    fprintf(stderr, "%s\n", strLog);
    delete [] strLog;

    return shader;
}

GLint aVertex, aColor;
GLint uRand;
GLuint prog;
GLuint g_buf = 0;

void initPrograms() {
    GLuint shader_v = createShader(src_vs1, GL_VERTEX_SHADER);
    GLuint shader_f = createShader(src_fs1, GL_FRAGMENT_SHADER);

    prog = glCreateProgram();
    CheckGL;

    glAttachShader(prog, shader_v);
    glAttachShader(prog, shader_f);
    glLinkProgram(prog);
    glUseProgram(prog);

    aVertex = 0;
    glEnableVertexAttribArray(aVertex);

    aColor = 1;
    glEnableVertexAttribArray(aColor);

    uRand = glGetUniformLocation(prog, "uRandom");
    
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf ( stderr
                , "Error creating program: %s\n"
                , gluErrorString(error) );
    }
}

static void initBuffers() {
    initPrograms();

    GLfloat pos_color[] = {
    /*    x     y     z      r    g    b    a   */
         0.0,  1.0,  0.0,   1.0, 0.0, 0.0, 1.0,
        -1.0, -1.0,  0.0,   0.0, 1.0, 0.0, 1.0,
         1.0, -1.0,  0.0,   0.0, 0.0, 1.0, 1.0,
         1.0,  1.0, -1.0,   1.0, 1.0, 0.0, 1.0,
        -1.0,  1.0, -1.0,   1.0, 0.0, 1.0, 1.0,
         1.0, -1.0, -1.0,   0.0, 1.0, 1.0, 1.0,
        -1.0, -1.0, -1.0,   0.5, 0.5, 0.5, 1.0,  
    };
 
    glGenBuffers(1, &g_buf);
    glBindBuffer(GL_ARRAY_BUFFER, g_buf);
    
    glBufferData( GL_ARRAY_BUFFER
                , sizeof(pos_color), pos_color
                , GL_STATIC_DRAW );

    glUseProgram(prog);
    glBindBuffer(GL_ARRAY_BUFFER, g_buf);
    glVertexAttribPointer
            ( aVertex, 3, GL_FLOAT, GL_FALSE
            , sizeof(GLfloat)*7
            , (void*)(sizeof(GLfloat)*0) );
    
    glVertexAttribPointer
            ( aColor, 4, GL_FLOAT, GL_FALSE
            , sizeof(GLfloat)*7
            , (void*)(sizeof(GLfloat)*3) );

    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        fprintf ( stderr
                , "Error creating buffer: %s\n"
                , gluErrorString(error) );
    }
}

static void onDraw(GLFWwindow *window) {
    double newTime = glfwGetTime();

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    float ratio = width / (float) height;

    glViewport(0, 0, width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(prog);

    glUniform2f ( uRand
                , (rand()%4096)/4096.0f
                , (rand()%4096)/4096.0f );

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    {
        glScalef(0.5, 0.5, 0.5);
        glTranslatef(-0.8, 0.0, 0.0);
        glDrawArrays(GL_TRIANGLES, 0, 3);
    }
    glPopMatrix();
    glPushMatrix();
    {
        glScalef(0.3, 0.3, 0.3);
        glTranslatef(1.0, 0.0, 0.0);
        glDrawArrays(GL_TRIANGLE_STRIP, 3, 4);
    }
    glPopMatrix();

    glFlush();
    glfwSwapBuffers(window);
}

static void onWindowSize(GLFWwindow *window, int width, int height) {
    //onDraw(window);
}

void reportGl(GLFWwindow* window) {
    int v0 = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MAJOR);
    int v1 = glfwGetWindowAttrib(window, GLFW_CONTEXT_VERSION_MINOR);
    fprintf(stderr, "OpenGL API: %d.%d\n", v0, v1);
}

int main() {

    if (!glfwInit()) { return -1; }

    GLFWwindow* window = 
        glfwCreateWindow( 640, 480
                        , "Hello World"
                        , NULL, NULL );
    
    if (!window) {
        fprintf(stderr, "Failed! Zhazha!\n");
        glfwTerminate();
        return -1;
    }

    reportGl(window);

    glfwSwapInterval(1);
    glfwMakeContextCurrent(window);

    initBuffers();

    glfwSetWindowSizeCallback(window, onWindowSize);
    glfwSetWindowRefreshCallback(window, onDraw);

    while (!glfwWindowShouldClose(window)) {
        onDraw(window);
        glfwPollEvents();
        usleep(1);
    }

    glfwTerminate();
    return 0;

}
