#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <ctime>

using namespace std;

// AoS
struct pixel {
    double r, g, b;
};

// SoA
struct soa {
    double* r;
    double* g;
    double* b;
};

void generate_random_value_AoS(pixel&);
void generate_random_value_SoA(double&);
pixel** set_blur_AoS(pixel** img, int width, int height);
soa set_blur_SoA(soa* img, int width, int height);
void print_image(pixel** img, int width, int height);
void print_image_soa(soa* img, int width, int height);

int main() {

    int width = 4000;
    int height = 3000;

    cout << "generate image AOS" << endl;
    pixel** image = new pixel * [height];
    for (int i = 0; i < height; i++) {
        image[i] = new pixel[width];
    };

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j].r = 0.;
            image[i][j].g = 0.;
            image[i][j].b = 0.;
            generate_random_value_AoS(image[i][j]);
        }
    }

    // print image
    //print_image(image, width, height);

    // AoS 
    clock_t t1 = clock();
    pixel** blur_img = set_blur_AoS(image, width, height);
    clock_t t2 = clock();
    // print blured image
    //cout << "blured image" << endl;
    //print_image(blur_img, width, height);

    double time_AoS = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << endl << "time AoS: " << time_AoS << " sec" << endl;

    cout << "generate image SOA" << endl;
    soa image2;
    image2.r = new double[width * height];
    image2.g = new double[width * height];
    image2.b = new double[width * height];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image2.r[i * width + j] = 0.;
            generate_random_value_SoA(image2.r[i * width + j]);
            image2.g[i * width + j] = 0.;
            generate_random_value_SoA(image2.g[i * width + j]);
            image2.b[i * width + j] = 0.;
            generate_random_value_SoA(image2.b[i * width + j]);
        }
    }

    //print_image_soa(&image2, width, height);
    // SoA 
    t1 = clock();
    soa blur_img2 = set_blur_SoA(&image2, width, height);
    t2 = clock();

    double time_SoA = (double)(t2 - t1) / CLOCKS_PER_SEC;
    cout << endl << "time SoA: " << time_SoA << " sec" << endl;
    system("PAUSE");

    // Освобождение AoS
    for (int i = 0; i < height; i++) {
        delete[] image[i];
        delete[] blur_img[i]; // если blur_img не освобожден
    }
    delete[] image;
    delete[] blur_img;

    // Освобождение SoA
    delete[] image2.r;
    delete[] image2.g;
    delete[] image2.b;
    delete[] blur_img2.r;
    delete[] blur_img2.g;
    delete[] blur_img2.b;

    return 0;
}

void generate_random_value_AoS(pixel& pix) {
    double random_number = ((double)rand() / RAND_MAX * 254 + 1);
    pix.r = round(random_number);

    random_number = ((double)rand() / RAND_MAX * 254 + 1);
    pix.g = round(random_number);

    random_number = ((double)rand() / RAND_MAX * 254 + 1);
    pix.b = round(random_number);
}

pixel** set_blur_AoS(pixel** img, int width, int height) {
    // массив под новое изображение
    pixel** blured_img = new pixel * [height];
    for (int i = 0; i < height; i++) {
        blured_img[i] = new pixel[width];
    };

    // применяем фильтр
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            blured_img[i][j].r = round((img[i - 1][j - 1].r + img[i - 1][j].r + img[i - 1][j + 1].r + img[i][j - 1].r + img[i][j].r + img[i][j + 1].r + img[i + 1][j - 1].r + img[i + 1][j].r + img[i + 1][j + 1].r) / 9);
            blured_img[i][j].g = round((img[i - 1][j - 1].g + img[i - 1][j].g + img[i - 1][j + 1].g + img[i][j - 1].g + img[i][j].g + img[i][j + 1].g + img[i + 1][j - 1].g + img[i + 1][j].g + img[i + 1][j + 1].g) / 9);
            blured_img[i][j].b = round((img[i - 1][j - 1].b + img[i - 1][j].b + img[i - 1][j + 1].b + img[i][j - 1].b + img[i][j].b + img[i][j + 1].b + img[i + 1][j - 1].b + img[i + 1][j].b + img[i + 1][j + 1].b) / 9);
        }
    }
    // границы копируем без изменений
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1)) {
                blured_img[i][j].r = img[i][j].r;
                blured_img[i][j].g = img[i][j].g;
                blured_img[i][j].b = img[i][j].b;
            }
        }
    }
    return blured_img;
}

void generate_random_value_SoA(double &x) {
    double random_number = ((double)rand() / RAND_MAX * 254 + 1);
    x = round(random_number);
}

soa set_blur_SoA(soa* img, int width, int height) {
    // массив под новое изображение
    soa blured_img;
    blured_img.r = new double[width * height];
    blured_img.g = new double[width * height];
    blured_img.b = new double[width * height];
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            blured_img.r[i * width + j] = 0.;
            blured_img.g[i * width + j] = 0.;
            blured_img.b[i * width + j] = 0.;
        }
    }
    // применяем фильтр
    for (int i = 1; i < height - 1; i++) {
        for (int j = 1; j < width - 1; j++) {
            blured_img.r[i * width + j] = round((img->r[(i-1)*height+j] + img->r[i* width + j] + img->r[(i+1)* width + j] + img->r[(i-1)* width + j-1] + img->r[i * width + j-1] + img->r[(i+1)* width + j-1] + img->r[(i-1)* width + j+1] + img->r[i * width + j+1] + img->r[(i+1)* width + j+1]) / 9);
            blured_img.g[i * width + j] = round((img->g[(i - 1)* width + j] + img->g[i * width + j] + img->g[(i + 1)* width + j] + img->g[(i - 1)* width + j - 1] + img->g[i * width + j - 1] + img->g[(i + 1)* width + j - 1] + img->g[(i - 1)* width + j + 1] + img->g[i * width + j + 1] + img->g[(i + 1)* width + j + 1]) / 9);
            blured_img.b[i * width + j] = round((img->b[(i - 1)* width + j] + img->b[i * width + j] + img->b[(i + 1)* width + j] + img->b[(i - 1)* width + j - 1] + img->b[i * width + j - 1] + img->b[(i + 1)* width + j - 1] + img->b[(i - 1)* width + j + 1] + img->b[i * width + j + 1] + img->b[(i + 1)* width + j + 1]) / 9);
        }
    }
    // границы копируем без изменений
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (i == 0 || i == (height - 1) || j == 0 || j == (width - 1)) {
                blured_img.r[i*height+j] = img->r[i*height+j];
                blured_img.g[i*height+j] = img->g[i*height+j];
                blured_img.b[i*height+j] = img->b[i*height+j];
            }
        }
    }
    return blured_img;
}


void print_image(pixel** img, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << "(" << img[i][j].r << "," << img[i][j].g << "," << img[i][j].b << ")" << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void print_image_soa(soa* img, int width, int height) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            cout << "(" << img->r[i*height + j] << "," << img->g[i * width + j] << "," << img->b[i * width + j] << ")" << "\t";
        }
        cout << endl;
    }
    cout << endl;
}