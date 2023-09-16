#include "Images.h"

#define IMAGE_RLE_BWR(name) \
    extern const unsigned int name##_rle_width, name##_rle_height; \
    extern const unsigned char name##_rle_black[], name##_rle_red[]; \
    const GfxImageBWR name(GfxImageBWR::Content( \
        name##_rle_width, name##_rle_height, \
        name##_rle_black, name##_rle_red));

#define IMAGE_RLE(name, color) \
    extern const unsigned int name##_rle_width, name##_rle_height; \
    extern const unsigned char name##_rle[]; \
    const GfxImage name(GfxImage::Content( \
        name##_rle_width, name##_rle_height, name##_rle), \
        GfxImage::Color(color, TRANSPARENT));
    
IMAGE_RLE_BWR(img_background)
IMAGE_RLE_BWR(img_battery)
IMAGE_RLE_BWR(img_weather_0)
IMAGE_RLE_BWR(img_weather_1)
IMAGE_RLE_BWR(img_weather_2)
IMAGE_RLE_BWR(img_weather_3)
IMAGE_RLE_BWR(img_weather_4)
IMAGE_RLE_BWR(img_weather_5)
IMAGE_RLE_BWR(img_flow_horiz)
IMAGE_RLE_BWR(img_flow_vert)
IMAGE_RLE_BWR(img_flow_diag)
