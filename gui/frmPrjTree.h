#ifndef frmPrjTree_h
#define frmPrjTree_h
#include "frmPrjTreeUI.h"
#include "fltk_calllist.h"
#include <memory>

class DispView;
class frmMainDisplay;
class frmViewCtrl;
class frmSurfCtrl;
class TSOCntx;
class Serializer;
class frmStereoShape;

class frmPrjTree{
 public:
  int wx,wy,ww,wh,sliderh;
  frmPrjTreeUI ui;
  frmMainDisplay               *frmmain;
  std::auto_ptr<frmViewCtrl>    frmviewctrl;
  std::auto_ptr<frmSurfCtrl>    frmsurfctrl;
  std::auto_ptr<frmStereoShape> frmstereoshape;

  frmPrjTree(frmMainDisplay *f);
  ~frmPrjTree();

  void Init();
  void SyncUI();

  void TreeScan(TSOCntx* cntx);
  void AskForData(Serializer *s);  

  PUBLIC_SLOTS(frmPrjTree):
  void tree_event(Fl_Widget* o, void* v);
};

#endif
