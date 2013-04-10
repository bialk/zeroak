#ifndef stereoshape_h
#define stereoshape_h

#include "editviewobj.h"
//#include "mathlib/mathutl/mymath.h"
//#include "mathlib/mathutl/meshandalg.h"
//#include "glhelper.h"
#include "eventhnd.h"
#include <GL/gl.h>
#include <vector>
#include <sigc++/sigc++.h>
#include "ImageTile.h"

class StereoShape;
class StereoShapeEH: public EvtHandle{
 public:
  StereoShape *ev;
  int state_drag;
  sigc::signal<void> SyncUI;

  StereoShapeEH(StereoShape *v);
  virtual void Handle(EventBall *eventball);
};

class GLTexHandle{
 public:
  GLuint txtid;

  GLTexHandle():txtid(0){}
  ~GLTexHandle(){ clear(); }

  void clear(){
    if(txtid){ 
      glDeleteTextures(1,&txtid);
      txtid=0;
    }
  }

  GLuint operator()(){
    if(!txtid){
      glGenTextures(1,&txtid);
    }
    return txtid;  
  }
};



class GLTex2D: public GLTexHandle{
 public:
  GLTex2D(){}
};


class GLListHandle{
 public:
  GLuint id;

  GLListHandle():id(0){}
  ~GLListHandle(){ clear(); }

  void clear(){
    if(id){ 
      glDeleteLists(id,1);
      id=0;
    }
  }

  GLuint operator()(){
    if(!id) id = glGenLists(1);
    return id;  
  }
};

class StereoShape: public EditViewObj{
 public:

  // input data 
  int w,h;
  int curslot;
  std::string imagefname[5];
  std::vector<unsigned char> img[5];
  std::vector<float> data_attd;
  //float lights[4][3];

  ImageTile image_tile;

  GLTex2D albedo_tex;

  GLListHandle circle;

  StereoShape();
  ~StereoShape();

  virtual void AskForData(Serializer *s);
  virtual void TreeScan(TSOCntx *cntx);
  virtual void Draw(DrawCntx *cntx);

  enum {
    /*
    image_mode_off,
    image_mode_image,
    image_mode_albedo,

    shape_mode_off,
    shape_mode_notex,
    shape_mode_albedo,
    shape_mode_image
    */

    image_sel_s1 = 0,
    image_sel_s2,
    image_sel_s3,
    image_sel_s4,
    image_sel_reg,
    image_sel_off
  };

  int image_mode;
  int shape_mode;

  GLListHandle shape;
  void reg_go();

  StereoShapeEH  eh;

  int  cache_slot;
  void Open(int slot);
  void LoadTxt(int slot);

  GLuint glsel_lightcur;
  GLuint glsel_light[4];
  void DrawLightPoints();

  void Build();
};

#endif
