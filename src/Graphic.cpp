//
// Created by seub on 3/3/22.
//

#include <fstream>
#include <sstream>
#include "Graphic.hpp"
#include "Helpers/Image.hpp"

GLuint create_quad_vao();
GLuint create_quad_program();


Graphic::Graphic() : width(1920), height(1080), fov(90.) {
    if (!glfwInit()) {
        std::cout << ("Initialisation failed: glfw\n") << std::endl;
        exit(0);
    }

    glfwWindowHint(GLFW_RESIZABLE, GLFW_TRUE);
    glfwWindowHint(GLFW_FLOATING, GLFW_TRUE);
    this->window = glfwCreateWindow(width, height, "Loup3D", NULL, NULL);
    if (!window) {
        std::cout << ("Failed to create window\n") << std::endl;
        exit(0);
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    glewInit();

    glOrtho(0, width, height, 0, 0, 1);

    int a,b;
    textures['W'] = Image::loadBMP("./assets/A.bmp",a,b);

    // OPTI TIME
    this->points.resize(b+1);

    this->InitComputeShader();
    this->LoadShader("compute_shader");

    GLint idData = glGetUniformLocation(this->shaders["compute_shader"], "screenSize");
    glUseProgram(this->shaders["compute_shader"]);
    glUniform2f(idData, (float)width, (float)height);

//        glfwSetErrorCallback(ErrorCallback);
//        glfwSetWindowSizeCallback(window, ResizeCallback);
}

void Graphic::InitComputeShader() {
    const GLubyte* renderer = glGetString( GL_RENDERER );
    const GLubyte* version  = glGetString( GL_VERSION );
    printf( "Renderer: %s\n", renderer );
    printf( "OpenGL version %s\n", version );
    quad_vao     = create_quad_vao();
    quad_program = create_quad_program();

    // texture handle and dimensions
    tex_output = 0;
    { // create the texture
        glGenTextures( 1, &tex_output );
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, tex_output );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );
        // linear allows us to scale the window up retaining reasonable quality
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        // same internal format as compute shader input
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA32F, width, height, 0, GL_RGBA, GL_FLOAT, NULL );
        // bind to image unit so can write to specific pixels from the shader
        glBindImageTexture( 0, tex_output, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F );
    }

    { // query up the workgroups
        int work_grp_size[3], work_grp_inv;
        // maximum global work group (total work in a dispatch)
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_COUNT, 0, &work_grp_size[0] );
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_COUNT, 1, &work_grp_size[1] );
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_COUNT, 2, &work_grp_size[2] );
        printf( "max global (total) work group size x:%i y:%i z:%i\n", work_grp_size[0], work_grp_size[1], work_grp_size[2] );
        // maximum local work group (one shader's slice)
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_SIZE, 0, &work_grp_size[0] );
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_SIZE, 1, &work_grp_size[1] );
        glGetIntegeri_v( GL_MAX_COMPUTE_WORK_GROUP_SIZE, 2, &work_grp_size[2] );
        printf( "max local (in one shader) work group sizes x:%i y:%i z:%i\n", work_grp_size[0], work_grp_size[1], work_grp_size[2] );
        // maximum compute shader invocations (x * y * z)
        glGetIntegerv( GL_MAX_COMPUTE_WORK_GROUP_INVOCATIONS, &work_grp_inv );
        printf( "max computer shader invocations %i\n", work_grp_inv );
    }
}

void Graphic::LoadShader(std::string name) {

    std::ifstream t("./src/shaders/" + name + ".shader");
    std::string str((std::istreambuf_iterator<char>(t)),
                    std::istreambuf_iterator<char>());
    GLuint ray_shader = glCreateShader( GL_COMPUTE_SHADER );
    const char *c_str = str.c_str();
    glShaderSource(ray_shader, 1, &c_str, NULL );
    glCompileShader( ray_shader );
    ( check_shader_errors( ray_shader ) ); // code moved to gl_utils.cpp
    GLuint ray_program = glCreateProgram();
    glAttachShader( ray_program, ray_shader );
    glLinkProgram( ray_program );
    ( check_program_errors( ray_program ) ); // code moved to gl_utils.cpp

    this->shaders[name] = ray_program;
}

bool Graphic::update(std::shared_ptr<Player> &player) {
    glfwSwapBuffers(this->window);
    glfwPollEvents();

    {                                          // launch compute shaders!
        glUseProgram( this->shaders["compute_shader"] );

        glDispatchCompute( (GLuint)width, (GLuint)height, 1 );
    }

    // prevent sampling befor all writes to image are done
    glMemoryBarrier( GL_SHADER_IMAGE_ACCESS_BARRIER_BIT );

    glClearColor((float) 135 / 255., (float) 206 / 255., (float) 235 / 255., 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    this->drawRectangle({0, (float)((this->height / 2) - (int)player->sightHeight)},
                        {(float)this->width, (float)(this->height * 2)},
                        {(float)249 / 255., (float)97 / 255., (float)97 / 255.});
    glUseProgram( quad_program );
    glBindVertexArray( quad_vao );
    glActiveTexture( GL_TEXTURE0 );
    glBindTexture( GL_TEXTURE_2D, tex_output );
    glDrawArrays( GL_TRIANGLE_STRIP, 0, 4 );
    return glfwWindowShouldClose(this->window);
}


[[maybe_unused]]
void Graphic::drawVerticalLine(int pos, float lineHeight, std::shared_ptr<Player> &player, std::vector<float> color) const {
//    std::cout << pos << " " << lineHeight << " " << this->height / 2 - lineHeight / 2 << " " << this->height / 2 + lineHeight / 2 << std::endl;
    glBegin(GL_LINES);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(pos, this->height / 2 - lineHeight / 2 - player->sightHeight, 0.0);
    // glVertex3f(00, 200,0.0);
    glColor3f(color[0], color[1], color[2]);
    glVertex3f(pos, this->height / 2 + lineHeight / 2 - player->sightHeight, 0.0);
    // glVertex3f(400, 100,0.0);
    glEnd();
}

void Graphic::drawVerticalLineWithTexture(int pos, int height, std::shared_ptr<Player> &player, unsigned char *img,
                                 int texture_pos, int texture_height) {

    float yPos = (float)this->height / 2 - (float)height / 2 - player->sightHeight;
    float yDelta = (float)height / (float)texture_height;
    img += texture_pos * 3;
    auto elem = points.data();
    for (int i = 0; i < texture_height; i++) {
        elem->x = pos;
        elem->y = yPos;
        yPos += yDelta;
        elem->r = img[0];
        elem->g = img[1];
        elem->b = img[2];
        elem += 1;
        img += texture_height * 3;
    }

    glColor3ub(255, 255, 255);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glVertexPointer(2, GL_FLOAT, sizeof(struct Point), &points[0].x);
    glColorPointer(3, GL_UNSIGNED_BYTE, sizeof(struct Point), &points[0].r);
    // glLineWidth( 3.0 );
    // glPointSize(3.0);
    glDrawArrays(GL_LINE_STRIP, 0, texture_height);
//    free(points);
}

void Graphic::drawRectangle(std::vector<float> pos, std::vector<float> size,
                   std::vector<float> color) {
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3f(pos[0], pos[1], 0);
    glVertex3f(pos[0] + size[0], pos[1], 0);
    glVertex3f(pos[0] + size[0], pos[1] + size[1], 0);
    glVertex3f(pos[0], pos[1] + size[1], 0);
    glEnd();
}


GLuint create_quad_vao() {
    GLuint vao = 0, vbo = 0;
    float verts[] = { -1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, -1.0f, 1.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f };
    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, 16 * sizeof( float ), verts, GL_STATIC_DRAW );
    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );
    glEnableVertexAttribArray( 0 );
    GLintptr stride = 4 * sizeof( float );
    glVertexAttribPointer( 0, 2, GL_FLOAT, GL_FALSE, stride, NULL );
    glEnableVertexAttribArray( 1 );
    GLintptr offset = 2 * sizeof( float );
    glVertexAttribPointer( 1, 2, GL_FLOAT, GL_FALSE, stride, (GLvoid*)offset );
    return vao;
}

// this is the quad's vertex shader in an ugly C string
const char* vert_shader_str =
        "#version 430\n                                                             \
layout (location = 0) in vec2 vp;\n                                           \
layout (location = 1) in vec2 vt;\n                                           \
out vec2 st;\n                                                                \
\n                                                                            \
void main () {\n                                                              \
  st = vt;\n                                                                  \
  gl_Position = vec4 (vp, 0.0, 1.0);\n                                        \
}\n";

// this is the quad's fragment shader in an ugly C string
const char* frag_shader_str =
        "#version 430\n                                                             \
in vec2 st;\n                                                                 \
uniform sampler2D img;\n                                                      \
out vec4 fc;\n                                                                \
\n                                                                            \
void main () {\n                                                              \
  fc = texture (img, st);\n                                                 \
}\n";

GLuint create_quad_program() {
    GLuint program     = glCreateProgram();
    GLuint vert_shader = glCreateShader( GL_VERTEX_SHADER );
    glShaderSource( vert_shader, 1, &vert_shader_str, NULL );
    glCompileShader( vert_shader );
//    check_shader_errors( vert_shader ); // code moved to gl_utils.cpp
    glAttachShader( program, vert_shader );
    GLuint frag_shader = glCreateShader( GL_FRAGMENT_SHADER );
    glShaderSource( frag_shader, 1, &frag_shader_str, NULL );
    glCompileShader( frag_shader );
//    check_shader_errors( frag_shader ); // code moved to gl_utils.cpp
    glAttachShader( program, frag_shader );
    glLinkProgram( program );
//    check_program_errors( program ); // code moved to gl_utils.cpp
    return program;
}
