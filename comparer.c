#include <stdio.h>
#include <stdlib.h>
#include "BMP.h"

#define error(...) (fprintf(stderr, __VA_ARGS__))

//#define BYTE unsigned char
//#define WORD unsigned short
//#define DWORD unsigned int
//#define LONG int
//
//#define FILE_TYPE_ERROR 1
//#define RESERVED_NULLS_ERROR 2
//#define VERSION_ERROR 3
//#define WIDTH_ERROR 4
//#define HEIGHT_ERROR 5
//#define PLANES_ERROR 6
//#define BYTES_READING_ERROR 8
//#define MEMORY_ALLOCATION_ERROR 9
//#define FILE_OPEN_ERROR 10
//
//#define error(...) (fprintf(stderr, __VA_ARGS__))
//
//typedef struct {
//    BYTE r;
//    BYTE g;
//    BYTE b;
//} PIXEL;
//
//#pragma pack(push, 1)
//typedef struct {
//    WORD bfType;
//    DWORD bfSize;
//    WORD bfReserved1;
//    WORD bfReserved2;
//    DWORD bfOffBits;
//} BITMAPFILEHEADER;
//#pragma pack(pop)
//
//typedef struct {
//    DWORD biSize;
//    LONG biWidth;
//    LONG biHeight;
//    WORD biPlanes;
//    WORD biBitCount;
//    DWORD biCompression;
//    DWORD biSizeImage;
//    LONG biXPelsPerMeter;
//    LONG biYPelsPerMeter;
//    DWORD biClrUsed;
//    DWORD biClrImportant;
//} BITMAPINFOHEADER;
//
//typedef struct {
//    BITMAPFILEHEADER file_header;
//    BITMAPINFOHEADER info_header;
//    PIXEL **data;
//} BMP_24;
//
//typedef struct {
//    BITMAPFILEHEADER file_header;
//    BITMAPINFOHEADER info_header;
//    PIXEL *palette;
//    BYTE **data;
//} BMP_8;
//
//int read_bitmapfileheader(BITMAPFILEHEADER *bitmapfileheader, FILE *fin) {
//    if (fread(bitmapfileheader, 14, 1, fin) != 1) {
//        error("Some bytes of BITMAPFILEHEADER were not read");
//        return BYTES_READING_ERROR;
//    }
//    if (bitmapfileheader->bfType != 0x4d42) {
//        error("Error in type of bmp file");
//        return FILE_TYPE_ERROR;
//    }
//    if (bitmapfileheader->bfReserved1 != 0x00 || bitmapfileheader->bfReserved2 != 0x00) {
//        error("Something was written to reserved nulls at 06-0A");
//        return RESERVED_NULLS_ERROR;
//    }
//    return 0;
//}
//
//int read_bitmapinfoheader(BITMAPINFOHEADER *bitmapinfoheader, FILE *fin) {
//    if (fread(bitmapinfoheader, 40, 1, fin) != 1) {
//        error("Some bytes of BITMAPINFOHEADER were not read");
//        return BYTES_READING_ERROR;
//    }
//    if (bitmapinfoheader->biSize != 0x28) {
//        error("Wrong version of file (must be 3)");
//        return VERSION_ERROR;
//    }
//    if (bitmapinfoheader->biWidth <= 0) {
//        error("Error in width (position 12, must be greater 0)");
//        return WIDTH_ERROR;
//    }
//    if (bitmapinfoheader->biHeight == 0) {
//        error("Error in height (position 16, must not be 0)");
//        return HEIGHT_ERROR;
//    }
//    if (bitmapinfoheader->biPlanes != 0x01) {
//        error("Field biPlane is not equal 1");
//        return PLANES_ERROR;
//    }
//    return 0;
//}
//
//int count_padding(LONG width) {
//    width *= 3;
//    if (width % 4 == 0) {
//        return 0;
//    } else if (width % 4 == 1) {
//        return 3;
//    } else if (width % 4 == 2) {
//        return 2;
//    } else {
//        return 1;
//    }
//}
//
//int load_bmp_24(BMP_24 *image, char const *filename) {
//    FILE *input = fopen(filename, "rb");
//    if (input == NULL) {
//        error("Cannot open file %s\n", filename);
//        return FILE_OPEN_ERROR;
//    }
//    BITMAPFILEHEADER file_header;
//    BITMAPINFOHEADER info_header;
//    int correctness_file_header = read_bitmapfileheader(&file_header, input);
//    if (correctness_file_header != 0) {
//        return correctness_file_header;
//    }
//    int correctness_info_header = read_bitmapinfoheader(&info_header, input);
//    if (correctness_info_header != 0) {
//        return correctness_info_header;
//    }
//    PIXEL **data = (PIXEL **)malloc(sizeof(PIXEL *) * info_header.biHeight);
//    if (data == NULL) {
//        error("Cannot allocate memory for pixels data");
//        return MEMORY_ALLOCATION_ERROR;
//    }
//    for (int i = 0; i < info_header.biHeight; ++i) {
//        data[i] = (PIXEL *)malloc(sizeof(PIXEL) * info_header.biWidth);
//        if (data[i] == NULL) {
//            error("Cannot allocate memory for %d-th pixel row", i);
//            return MEMORY_ALLOCATION_ERROR;
//        }
//    }
//    int padding = count_padding(info_header.biWidth);
//    BYTE padding_zero;
//    for (int i = 0; i < info_header.biHeight; ++i) {
//        for (int j = 0; j < info_header.biWidth; ++j) {
//            if (fread(&data[i][j], sizeof(PIXEL), 1, input) != 1) {
//                error("Cannot read pixel");
//                return BYTES_READING_ERROR;
//            }
//        }
//        if (fread(&padding_zero, 1, padding, input) != padding) {
//            error("Cannot read pixel");
//            return BYTES_READING_ERROR;
//        }
//    }
//    image->file_header = file_header;
//    image->info_header = info_header;
//    image->data = data;
//    fclose(input);
//    return 0;
//}
//
//int load_bmp_8(BMP_8 *image, char const *filename) {
//    FILE *input = fopen(filename, "rb");
//    if (input == NULL) {
//        error("Cannot open file %s", filename);
//        return FILE_OPEN_ERROR;
//    }
//    if (image == NULL) {
//        error("Cannot allocate memory for loading image");
//        return MEMORY_ALLOCATION_ERROR;
//    }
//    int correctness_file_header = read_bitmapfileheader(&image->file_header, input);
//    if (correctness_file_header != 0) {
//        return correctness_file_header;
//    }
//    int correctness_info_header = read_bitmapinfoheader(&image->info_header, input);
//    if (correctness_info_header != 0) {
//        return correctness_info_header;
//    }
//    image->palette = malloc(sizeof(PIXEL) * image->info_header.biClrUsed);
//    if (image->palette == NULL) {
//        error("Cannot allocate memory for palette");
//        return MEMORY_ALLOCATION_ERROR;
//    }
//    image->data = malloc(sizeof(PIXEL *) * image->info_header.biHeight);
//    if (image->data == NULL) {
//        error("Cannot allocate memory for pixels data");
//        return MEMORY_ALLOCATION_ERROR;
//    }
//    for (int i = 0; i < image->info_header.biHeight; ++i) {
//        image->data[i] = malloc(sizeof(PIXEL) * image->info_header.biWidth);
//        if (image->data[i] == NULL) {
//            error("Cannon allocate memory for %d-th pixel row", i);
//            return MEMORY_ALLOCATION_ERROR;
//        }
//    }
//    BYTE zero_byte;
//    for (int i = 0; i < image->info_header.biClrUsed; ++i) {
//        if (fread(&image->palette[i], sizeof(BYTE), 3, input) != 3) {
//            error("Some bytes of palette were not read");
//            return BYTES_READING_ERROR;
//        }
//        if (fread(&zero_byte, sizeof(BYTE), 1, input) != 1) {
//            error("0x00 byte after %d-th node in palette was nor read", i);
//            return BYTES_READING_ERROR;
//        }
//    }
//    for (int i = 0; i < image->info_header.biHeight; ++i) {
//        for  (int j = 0; j < image->info_header.biWidth; ++j) {
//            if (fread(&image->data[i][j], sizeof(BYTE), 1, input) != 1) {
//                error("Some bytes of pixels data were not read");
//                return BYTES_READING_ERROR;
//            }
//        }
//    }
//    fclose(input);
//    return 0;
//}
//
//int return_bits_per_pixel(char const *filename) {
//    FILE *input = fopen(filename, "rb");
//    fseek(input, 28, SEEK_SET);
//    int bits;
//    fread(&bits, 1, 2, input);
//    fseek(input, 0, SEEK_SET);
//    return bits;
//}
//
//int compare_pixels(PIXEL a, PIXEL b) {
//    return (a.r - b.r || a.b - b.b || a.g - b.g);
//}
//
//int compare_bmp8(BMP_8 *image1, BMP_8 *image2) {
//    LONG width1 = image1->info_header.biWidth;
//    LONG height1 = image1->info_header.biHeight;
//    LONG width2 = image2->info_header.biWidth;
//    LONG height2 = image2->info_header.biHeight;
//    if (width1 != width2) {
//        error("Images have different width");
//        return -1;
//    }
//    if (height1 != height2) {
//        error("Images have different height");
//        return -1;
//    }
//    BYTE **data1 = image1->data;
//    BYTE **data2 = image2->data;
//    int deviation_counter = 0;
//    for (int i = 0; i < height1; ++i) {
//        for (int j = 0; j < width1; ++j) {
//            if (deviation_counter < 100) {
//                if (data1[i][j] != data2[i][j]) {
//                    deviation_counter ++;
//                    printf("%d %d", data1[i][j], data2[i][j]);
//                }
//            }
//        }
//    }
//    return 0;
//}
//
//int compare_bmp24(BMP_24 *image1, BMP_24 *image2) {
//    LONG width1 = image1->info_header.biWidth;
//    LONG height1 = image1->info_header.biHeight;
//    LONG width2 = image2->info_header.biWidth;
//    LONG height2 = image2->info_header.biHeight;
//    if (width1 != width2) {
//        error("Images have different width");
//        return -1;
//    }
//    if (height1 != height2) {
//        error("Images have different height");
//        return -1;
//    }
//    PIXEL **data1 = image1->data;
//    PIXEL **data2 = image2->data;
//    int deviation_counter = 0;
//    for (int i = 0; i < height1; ++i) {
//        for (int j = 0; j < width1; ++j) {
//            if (deviation_counter < 100) {
//                if (compare_pixels(data1[i][j], data2[i][j])) {
//                    deviation_counter++;
//                    printf("%d %d\n", i, j);
//                }
//            }
//        }
//    }
//    return 0;
//}

int main(int argc, char *argv[]) {
    int bit_count1 = return_bits_per_pixel(argv[1]);
    int bit_count2 = return_bits_per_pixel(argv[2]);
    if (bit_count1 != bit_count2) {
        error("In file %s %d bits per pixel but in file %s %d", argv[1], bit_count1, argv[2], bit_count2);
        return -1;
    } else {
        if (bit_count1 == 8) {
            BMP_8 *image1 = malloc(sizeof(*image1));
            BMP_8 *image2 = malloc(sizeof(*image2));
            int loading_result1 = load_bmp_8(image1, argv[1]);
            int loading_result2 = load_bmp_8(image2, argv[2]);
            if (loading_result1 != 0) {
                return loading_result1;
            }
            if (loading_result2 != 0) {
                return loading_result2;
            }
            int compare_result = compare_bmp8(image1, image2);
            if (compare_result != 0) {
                return compare_result;
            }
        } else if (bit_count1 == 24) {
            BMP_24 *image1 = malloc(sizeof(*image1));
            BMP_24 *image2 = malloc(sizeof(*image2));
            int loading_result1 = load_bmp_24(image1, argv[1]);
            int loading_result2 = load_bmp_24(image2, argv[2]);
            if (loading_result1 != 0) {
                return loading_result1;
            }
            if (loading_result2 != 0) {
                return loading_result2;
            }
            int compare_result = compare_bmp24(image1, image2);
            if (compare_result != 0) {
                return compare_result;
            }
        }
    }
    return 0;
}
