#include "stereoreg.h"


void StereoReg::run(unsigned char* img_reg, 
		    unsigned char* img1, 
		    unsigned char* img2,
		    int w, int h)
{
  //this is place for registration algorithm
  
  //img1 - pointer to the source image one  in BGRA format with size of w*h*4 bytes
  //img2 - pointer to the source image two
  //img_reg - pointer to the output image

  // an example where img_reg=(img1+img2)*0.5 ( is average of two images)
  
  int x,y;
  for(x=0;x<w;x++){
    for(y=0;y<h;y++){
      int idx = (y*w+x)*4;
      img_reg[idx+0]=(img1[idx+0]+img2[idx+0])*0.5;
      img_reg[idx+1]=(img1[idx+1]+img2[idx+1])*0.5;
      img_reg[idx+2]=(img1[idx+2]+img2[idx+2])*0.5;
      img_reg[idx+3]=(img1[idx+3]+img2[idx+3])*0.5;
    }
  }    
}

