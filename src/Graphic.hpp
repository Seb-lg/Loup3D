//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_GRAPHIC_HPP
#define LOUP3D_GRAPHIC_HPP

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include "Player.hpp"

class Graphic {
public:
    static std::shared_ptr<Graphic> get() {static std::shared_ptr<Graphic> graphic = std::make_shared<Graphic>();return graphic;}
    Graphic();


    void InitComputeShader();
    void LoadShader(std::string name);
    void testShader(std::shared_ptr<Player> &player);


    bool update(std::shared_ptr<Player> &player);
    void drawVerticalLine(int pos, float lineHeight, std::shared_ptr<Player> &player, std::vector<float> color) const;
    void drawVerticalLineWithTexture(int pos, int height, std::shared_ptr<Player> &player, unsigned char *img,
                                     int texture_pos, int texture_height);
    static void drawRectangle(std::vector<float> pos, std::vector<float> size,
                       std::vector<float> color);

public:
    int width;
    int height;
    float fov;
    GLFWwindow *window;
    std::map<unsigned char, std::vector<unsigned char>> textures;
    GLuint quad_vao;
    GLuint quad_program;
    GLuint tex_output;

private:
    struct Point {
        float x, y;
        unsigned char r, g, b;
    };
    std::vector<Point> points;
    std::map<std::string, GLint> compute_members;
    std::map<std::string, GLuint> shaders;

private:
    static void print_shader_info_log( GLuint shader ) {
        int max_length    = 4096;
        int actual_length = 0;
        char slog[4096];
        glGetShaderInfoLog( shader, max_length, &actual_length, slog );
        fprintf( stderr, "shader info log for GL index %u\n%s\n", shader, slog );
    }
    static bool check_shader_errors( GLuint shader ) {
        GLint params = -1;
        glGetShaderiv( shader, GL_COMPILE_STATUS, &params );
        if ( GL_TRUE != params ) {
            fprintf( stderr, "ERROR: shader %u did not compile\n", shader );
            print_shader_info_log( shader );
            return false;
        }
        return true;
    }
    static void print_program_info_log( GLuint program ) {
        int max_length    = 4096;
        int actual_length = 0;
        char plog[4096];
        glGetProgramInfoLog( program, max_length, &actual_length, plog );
        fprintf( stderr, "program info log for GL index %u\n%s\n", program, plog );
    }
    static bool check_program_errors( GLuint program ) {
        GLint params = -1;
        glGetProgramiv( program, GL_LINK_STATUS, &params );
        if ( GL_TRUE != params ) {
            fprintf( stderr, "ERROR: program %u did not link\n", program );
            print_program_info_log( program );
            return false;
        }
        return true;
    }
};


#endif //LOUP3D_GRAPHIC_HPP
