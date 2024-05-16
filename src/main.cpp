#include "glad/gl.h"
#include "GLFW/glfw3.h"

#include <cstdint>
#include <random>

//#define FULLSCREEN

const uint32_t SIZEX = 1024;
const uint32_t SIZEY = 1024;

const float FPS = 30;

const char* vertex_frame = 
"#version 420 core \n"

"layout (location = 0) in vec2 a_Position; \n"

"void main() { \n"
"   gl_Position = vec4(a_Position.xy, 0, 1); \n"
"};";

const char* fragment_frame = 
"#version 420 core \n"

"layout (location = 0) out vec4 o_Color; \n"

"layout (binding = 0) uniform sampler2D screenTexture; \n"
"layout (binding = 1) uniform sampler2D screenTexture1; \n"

"uniform vec2 size; "

"void main() { \n"
"   float lookup[9*2] = float[]( "
"       0, 0, 0, 1, 0, 0, 0, 0, 0,"
"       0, 0, 1, 1, 0, 0, 0, 0, 0 "
"   ); \n"

"   vec2 offset[8] = vec2[]( \n"
"       vec2(-1, -1), \n"
"       vec2( 0, -1), \n"
"       vec2( 1, -1), \n"
"       vec2(-1,  0), \n"
"       vec2( 1,  0), \n"
"       vec2(-1,  1), \n"
"       vec2( 0,  1), \n"
"       vec2( 1,  1) \n"
"   ); \n"

"   vec3 sampleTex[8]; \n"

"   for (int i = 0; i < 8; i++) { \n"
"       sampleTex[i] = vec3(texture(screenTexture, (gl_FragCoord.xy + offset[i]) / size)); \n"
"   } \n"

"   int n = 0; \n"
"   for (int i = 0; i < 8; i++) { \n"
"       n += int(sampleTex[i].r); \n"
"   } \n"

"   float c = texture(screenTexture, gl_FragCoord.xy / size).r; \n"
"   float color = lookup[int(c)*9 + n]; \n"

"   o_Color = vec4(color, color, color, 1); \n"
"};";

const char* vertex_quad = 
"#version 420 core \n"

"layout (location = 0) in vec2 a_Position; \n"

"out vec2 TexCoords; \n"

"void main() { \n"
"   TexCoords = 0.5*(a_Position + vec2(1)); \n"

"   gl_Position = vec4(a_Position.xy, 0, 1); \n"
"};";

const char* fragment_quad = 
"#version 420 core \n"

"layout (location = 0) out vec4 o_Color; \n"

"in vec2 TexCoords; \n"

"layout (binding = 0) uniform sampler2D screenTexture; \n"
"layout (binding = 1) uniform sampler2D screenTexture1; \n"

"void main() { \n"
"   o_Color = texture(screenTexture1, TexCoords); \n"
"};";

int main() {
    if (!glfwInit()) return -1;

    uint32_t sizex = SIZEX;
    uint32_t sizey = SIZEY;
    
    uint32_t width = sizex;
    uint32_t height = sizey;

    GLFWmonitor* monitor = nullptr;

#ifdef FULLSCREEN
    monitor = glfwGetPrimaryMonitor();

    const GLFWvidmode * mode = glfwGetVideoMode(monitor);

    width = mode->width;
    height = mode->height;

    sizex = width;
    sizey = height;
#endif

    GLFWwindow* window(glfwCreateWindow(width, height, "oie", monitor, nullptr));

    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    int version = gladLoadGL(glfwGetProcAddress);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    glFrontFace(GL_CCW);

    glClearColor(0, 0, 0, 1);
    
    uint32_t vao,
             vbo,
             ibo;

    glCreateVertexArrays(1, &vao);
    glCreateBuffers(1, &vbo);
    glCreateBuffers(1, &ibo);

    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);


    float vertices[4 * 2] = {
        -1, -1,
         1, -1,
        -1,  1,
         1,  1,
    };

    uint32_t indices[2 * 3] = {
        0, 1, 2,
        1, 3, 2
    };

    glNamedBufferData(vbo, 8 * sizeof(float), &vertices[0], GL_STATIC_DRAW);
    glNamedBufferData(ibo, 6 * sizeof(uint32_t), &indices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    uint32_t program = glCreateProgram();
    uint32_t vert = glCreateShader(GL_VERTEX_SHADER);
    uint32_t frag = glCreateShader(GL_FRAGMENT_SHADER);


    glAttachShader(program, vert);
    glAttachShader(program, frag);

    glShaderSource(vert, 1, &vertex_quad, nullptr);
    glCompileShader(vert);

    glShaderSource(frag, 1, &fragment_quad, nullptr);
    glCompileShader(frag);

    glLinkProgram(program);


    GLint is_compiled;
    
    glGetShaderiv(vert, GL_COMPILE_STATUS, &is_compiled);
    /*
    if (is_compiled != GL_TRUE)
        std::cout << "vert fuck" << std::endl;
    
    glGetShaderiv(frag, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
        std::cout << "frag fuck" << std::endl;

    glGetProgramiv(program, GL_LINK_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
        std::cout << "link fuck" << std::endl;
    */

    glDeleteShader(vert);
    glDeleteShader(frag);

    uint32_t program_frame = glCreateProgram();
    vert = glCreateShader(GL_VERTEX_SHADER);
    frag = glCreateShader(GL_FRAGMENT_SHADER);

    glAttachShader(program_frame, vert);
    glAttachShader(program_frame, frag);

    glShaderSource(vert, 1, &vertex_frame, nullptr);
    glCompileShader(vert);

    glShaderSource(frag, 1, &fragment_frame, nullptr);
    glCompileShader(frag);

    glLinkProgram(program_frame);
    
    /*
    glGetShaderiv(vert, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
        std::cout << "vert f fuck" << std::endl;
    
    glGetShaderiv(frag, GL_COMPILE_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
        std::cout << "frag f fuck" << std::endl;

    glGetProgramiv(program, GL_LINK_STATUS, &is_compiled);
    if (is_compiled != GL_TRUE)
        std::cout << "link f fuck" << std::endl;
    */

    
    glDeleteShader(vert);
    glDeleteShader(frag);

    // framebuffer
    uint32_t fbo;
    unsigned int tex;

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    struct rgb {
        uint8_t r, g, b;
    };

    rgb* startingImage = new rgb[sizex * sizey];

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist2(0,1); // distribution in range [1, 6]

    for(int y = 0; y < sizey; y++) {
        for(int x = 0; x < sizex; x++) {
            if (dist2(rng))
                startingImage[y*sizex + x] = {255, 255, 255};
            else
                startingImage[y*sizex + x] = {0, 0, 0};
        }
    }

    startingImage[30*sizex + 30] = {255, 255, 255};
    startingImage[30*sizex + 31] = {255, 255, 255};
    startingImage[30*sizex + 32] = {255, 255, 255};

    startingImage[31*sizex + 32] = {255, 255, 255};
    startingImage[32*sizex + 31] = {255, 255, 255};

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, GL_UNSIGNED_BYTE, &startingImage[0]);

    delete[] startingImage;

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    uint32_t tex1;
    glGenTextures(1, &tex1);
    glActiveTexture(GL_TEXTURE0 + 1);
    glBindTexture(GL_TEXTURE_2D, tex1);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, sizex, sizey, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex1, 0);

    /*
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    */

    float step = FPS == 0 ? 0 : 1.0/FPS;

    double last = glfwGetTime();

    int size_location = glGetUniformLocation(program_frame, "size");
    
    while (!glfwWindowShouldClose(window)) {
        double current = glfwGetTime();
        /*
        */
        if (current - last > step) {
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glUseProgram(program_frame);
        glUniform2f(size_location, sizex, sizey);

        glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_INT, nullptr);

        glCopyImageSubData(
                tex1, GL_TEXTURE_2D, 0, 0, 0, 0,
                tex, GL_TEXTURE_2D, 0, 0, 0, 0,
                sizex, sizey, 1);

        last = current;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program);
        glDrawElements(GL_TRIANGLES, 2*3, GL_UNSIGNED_INT, nullptr);


        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ibo);
    glDeleteVertexArrays(1, &vao);

    glDetachShader(program, vert);
    glDetachShader(program, frag);
    glDeleteProgram(program);

    glDeleteFramebuffers(1, &fbo);

    glDeleteTextures(1, &tex);
    glDeleteTextures(1, &tex1);

    glfwTerminate();

    return 0;
}
