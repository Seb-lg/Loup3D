//
// Created by seub on 3/3/22.
//

#ifndef LOUP3D_IMAGE_HPP
#define LOUP3D_IMAGE_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstring>

namespace Image {
    std::vector<unsigned char> loadBMP(std::string path, int &width, int &height) {
        std::cout << "Reading image " << path << std::endl;
        width = -1;
        height = -1;
        // Data read from the header of the BMP file
        unsigned char header[54];
        unsigned int dataPos;
        unsigned int imageSize;
        // Actual RGB data
        std::vector<unsigned char> data;

        // Open the file
        FILE *file = fopen(path.c_str(), "rb");
        if (!file) {
            printf("Image could not be opened\n");
            return {};
        }

        // Read the header, i.e. the 54 first bytes

        // If less than 54 byes are read, problem
        if (fread(header, 1, 54, file) != 54) {
            printf("Not a correct BMP file\n");
            return {};
        }
        // A BMP files always begins with "BM"
        if (header[0] != 'B' || header[1] != 'M') {
            printf("Not a correct BMP file\n");
            return {};
        }
        // Make sure this is a 24bpp file
        if (*(int *)&(header[0x1E]) != 0) {
            printf("Not a correct BMP file\n");
            return {};
        }
        if (*(int *)&(header[0x1C]) != 24) {
            printf("Not a correct BMP file\n");
            return {};
        }

        // Read the information about the image
        dataPos = *(int *)&(header[0x0A]);
        imageSize = *(int *)&(header[0x22]);
        width = *(int *)&(header[0x12]);
        height = *(int *)&(header[0x16]);

        // Some BMP files are misformatted, guess missing information
        if (imageSize == 0)
            imageSize = width * height *
                        3; // 3 : one byte for each Red, Green and Blue component
        if (dataPos == 0)
            dataPos = 54; // The BMP header is done that way

        // Create a buffer
        data.resize(imageSize);

        // Read the actual data from the file into the buffer
        fread(data.data(), 1, imageSize, file);

        // Everything is in memory now, the file wan be closed
        fclose(file);

        // swap y-axis
        unsigned char *tmpBuffer = (unsigned char *)malloc(width * 3);
        int size = width * 3;
        for (int i = 0; i < height / 2; i++) {
            // copy row i to tmp
            memcpy(tmpBuffer, data.data() + width * 3 * i, size);
            // copy row h-i-1 to i
            memcpy(data.data() + width * 3 * i, data.data() + width * 3 * (height - i - 1),
                   size);
            // copy tmp to row h-i-1
            memcpy(data.data() + width * 3 * (height - i - 1), tmpBuffer, size);
        }
        free(tmpBuffer);

        unsigned char tmp;
        for (int y = 0; y < height; y++)
            for (int x = 0; x < height; x++) {
                tmp = data[y * width * 3 + (x * 3)];
                data[y * width * 3 + (x * 3)] = data[y * width * 3 + (x * 3) + 2];
                data[y * width * 3 + (x * 3) + 2] = tmp;
            }

        return {data};
    }
}

#endif //LOUP3D_IMAGE_HPP
