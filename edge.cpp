#include <iostream>
#include <cmath>
#include <string>
//stb header files to read and write images
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

typedef unsigned char* pixels;
//black border
pixels canny(pixels img, int width, int height){
    pixels output_img = new unsigned char[width*height];
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            output_img[row*width+col]=0;
        }
    }
    return img;
}
pixels deriche(pixels img, int width, int height){
    pixels output_img = new unsigned char[width*height];
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            output_img[row*width+col]=0;
        }
    }
    return img;
}
pixels differential(pixels img, int width, int height){
    pixels output_img = new unsigned char[width*height];
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            output_img[row*width+col]=0;
        }
    }
    return img;
}
pixels sobel(pixels img, int &width, int &height, std::string filter="sobel"){
    int gauss[3]={0,0,0};
    if (filter=="sobel"){
        gauss[0]=1;
        gauss[1]=2;
        gauss[2]=1;
    } else if(filter=="sobel-feldman"){
        gauss[0]=3;
        gauss[1]=10;
        gauss[2]=3;
    } else if(filter=="scharr"){
        gauss[0]=47;
        gauss[1]=162;
        gauss[2]=47;
    }
    pixels output_img = new unsigned char[width*height];
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            output_img[row*width+col]=0;
        }
    }
    int sobel_x;
    int sobel_y;
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            sobel_x =((row>0)&&(col>0)?gauss[0]:0)*(img[(row-1)*width+col-1])+((row>0)&&(col<width-1)?-gauss[0]:0)*(img[(row-1)*width+col+1])+
                    ((col>0)?gauss[1]:0)*(img[row*width+col-1])+((col<width-1)?-gauss[1]:0)*(img[row*width+col+1])+
                    ((row<height-1)&&(col>0)?gauss[2]:0)*(img[(row+1)*width+col-1])+((row<height-1)&&(col<width-1)?-gauss[2]:0)*(img[(row+1)*width+col+1]);
            sobel_y =((row>0)&&(col>0)?gauss[0]:0)*(img[(row-1)*width+col-1])+((row>0)?gauss[1]:0)*(img[(row-1)*width+col])+((row>0)&&(col<width-1)?gauss[2]:0)*(img[(row-1)*width+col+1])+
                    ((row<height-1)&&(col>0)?-gauss[0]:0)*(img[(row+1)*width+col-1])+((row<height-1)?-gauss[1]:0)*(img[(row+1)*width+col])+((row<height-1)&&(col<width-1)?-gauss[2]:0)*(img[(row+1)*width+col+1]);
            output_img[row*width+col]= sqrt(sobel_x*sobel_x+sobel_y*sobel_y);
        }
    }
    return output_img;
}
pixels prewitt(pixels img, int width, int height){
    pixels output_img = new unsigned char[width*height];
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            output_img[row*width+col]=0;
        }
    }
    int prewitt_x;
    int prewitt_y;
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            prewitt_x =((row>0)&&(col>0)?1:0)*(img[(row-1)*width+col-1])+((row>0)&&(col<width-1)?-1:0)*(img[(row-1)*width+col+1])+
                    ((col>0)?1:0)*(img[row*width+col-1])+((col<width-1)?-1:0)*(img[row*width+col+1])+
                    ((row<height-1)&&(col>0)?1:0)*(img[(row+1)*width+col-1])+((row<height-1)&&(col<width-1)?-1:0)*(img[(row+1)*width+col+1]);
            prewitt_y =((row>0)&&(col>0)?1:0)*(img[(row-1)*width+col-1])+((row>0)?1:0)*(img[(row-1)*width+col])+((row>0)&&(col<width-1)?1:0)*(img[(row-1)*width+col+1])+
                    ((row<height-1)&&(col>0)?-1:0)*(img[(row+1)*width+col-1])+((row<height-1)?-1:0)*(img[(row+1)*width+col])+((row<height-1)&&(col<width-1)?-1:0)*(img[(row+1)*width+col+1]);
            output_img[row*width+col]= sqrt(prewitt_x*prewitt_x+prewitt_y*prewitt_y);
        }
    }
    return output_img;
}
pixels roberts_cross(pixels img, int width, int height){
    pixels output_img = new unsigned char[width*height];
    for(int row=0;row<height;row++){
        for(int col=0;col<width;col++){
            output_img[row*width+col]=0;
        }
    }
    int roberts_x;
    int roberts_y;
    for(int row=0;row<height-1;row++){
        for(int col=0;col<width-1;col++){
            roberts_x =img[row*width+col]-img[(row+1)*width+col+1];
            roberts_y =img[row*width+col+1]-img[(row+1)*width+col];
            output_img[row*width+col]= sqrt(roberts_x*roberts_x+roberts_y*roberts_y);
        }
    }
    return output_img;
}


int main(int argc, char* argv[]){
    int width,height,channels;
    int desired_channels=1;
    pixels grey_img=stbi_load("lena.png",&width,&height,&channels,desired_channels);
    // std::cout<<"width:"<<width<<",height:"<<height<<",channels:"<<channels<<std::endl;
    pixels canny_img=canny(grey_img,width,height);
    pixels deriche_img=deriche(grey_img,width,height);
    pixels differential_img=differential(grey_img,width,height);
    pixels sobel_img=sobel(grey_img,width,height);
    pixels prewitt_img=prewitt(grey_img,width,height);
    pixels roberts_cross_img=roberts_cross(grey_img,width,height);
    // stbi_write_png("lena_canny.png",width,height,desired_channels,grey_img,width*desired_channels);
    stbi_write_png("lena_sobel.png",width,height,desired_channels,sobel_img,width*desired_channels);
    stbi_write_png("lena_prewitt.png",width,height,desired_channels,prewitt_img,width*desired_channels);
    stbi_write_png("lena_roberts.png",width,height,desired_channels,roberts_cross_img,width*desired_channels);

}