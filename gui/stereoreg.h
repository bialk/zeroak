#ifndef stereoreg_h
#define stereoreg_h

class StereoReg{
public:
  void run(unsigned char* img_reg, 
	   unsigned char* img1, 
	   unsigned char* img2,
	   int w, int h);
};


#endif
