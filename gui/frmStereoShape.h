#ifndef frmStereoShape_h
#define frmStereoShape_h
#include "fltk_calllist.h"
#include "frmStereoShapeUI.h"
#include <memory>
#include <sigc++/sigc++.h>

class StereoShape;
class Lights;
class Serializer;
class TSOCntx;
class DispView;
class frmMainDisplay;
class FltkIdleTask;

class frmStereoShape{
 public:  
  int w_x,w_y,w_h,w_w;
  //int do_not_hide;

  std::auto_ptr<frmStereoShapeUI> ui;
  frmMainDisplay *frmmain;
  DispView *dv;  
  StereoShape *stereoshape;

  frmStereoShape(frmMainDisplay *v);
  ~frmStereoShape();

  void Init();
  void SyncUI();

  void TreeScan(TSOCntx* cntx);
  void AskForData(Serializer *s);  

  void select(int v);

  //FltkIdleTask idletask;

  PUBLIC_SLOTS(frmStereoShape):
  void select_image(Fl_Widget* o, void* v);
  void imagefile_dlg(Fl_Widget* o, void* v);
  void pnt_edt(Fl_Widget* o, void* v);
  void reg_go_btn(Fl_Widget* o, void* v);

  void image_off(Fl_Widget* o, void* v);
  void image_albedo(Fl_Widget* o, void* v);
  void image_image(Fl_Widget* o, void* v);

  void shape_off(Fl_Widget* o, void* v);
  void shape_notex(Fl_Widget* o, void* v);
  void shape_albedo(Fl_Widget* o, void* v);
  void shape_image(Fl_Widget* o, void* v);

};

#endif
