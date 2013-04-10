#include "frmPrjTree.h"
#include "../apputil/serializer.h"
#include "dispview.h"
#include "viewctrl.h"
#include "lights.h"
//#include "imageplane.h"
//#include "matting.h"
#include "frmMainDisplay.h"
#include "frmMainDisplayUI.h"
#include "frmViewCtrl.h"
#include "frmSurfCtrl.h"
#include "frmStereoShape.h"

frmPrjTree::frmPrjTree(frmMainDisplay *f):
  frmmain(f),
  frmviewctrl(new frmViewCtrl(f)),
  frmstereoshape(new frmStereoShape(f)),
  frmsurfctrl(new frmSurfCtrl(f)),
  //insert here for new panel
  ww(0){}

frmPrjTree::~frmPrjTree(){}

void frmPrjTree::Init(){
  ui.Init();
  frmviewctrl->Init();
  frmstereoshape->Init();
  frmsurfctrl->Init();
  //insert here for new panel

  CONNECT(ui.tree,frmPrjTree::tree_event);

  // construct tree  
  ui.tree->selection_mode(FLU_SINGLE_SELECT);
  ui.tree->box( FL_DOWN_BOX );
  ui.tree->auto_branches( true );
  ui.tree->insertion_mode(FLU_INSERT_BACK);
  //ui.tree->label( "Control Tree" );  
  ui.tree->always_open( true );
  ui.tree->show_root(false);
  

  Flu_Tree_Browser::Node *n;

  n = ui.tree->add("Scene");
  n->add("View");
  n->add("3D Stereo");
  //n->add("Surface");
  {
    // this is an example to add new item with subitems
    // Flu_Tree_Browser::Node *n1 = n->add("Jaw");
    // n1->add("Model");
    // n1->open(true);
  }
  n->open(true);
  
  ui.main->show();

  //syncronize data
  SyncUI();

  // event handlers initialisation
  frmmain->ehq_view.push();
  frmmain->ehq_view.top().ins_top(&frmmain->dv->viewctrl->viewctrleh);
  frmmain->ehq_view.top().ins_top(&frmmain->dv->lights->lighteh);
  frmmain->ehq_view.top().ins_top(&frmmain->dv->dispvieweh);
  frmmain->ehq_view.top().ins_top(&frmmain->ehq_scene);
  frmmain->ehq_scene.push();

  // event handler for scene object should be added dynamicaly
  // in the frmPrjTree when tree item is selected.
  // Example:
  // ehq_scene.top().ins_top(&dv->imageplane->eh);
}


void frmPrjTree::TreeScan(TSOCntx* cntx){

  if(cntx == &TSOCntx::TSO_LayoutLoad) {
    // window positioning
    if(ww && wh){
      ui.main->resize(wx,wy,ww,wh);
      //ui.tree->resize(0,0,ww,sliderh);
      //ui.panel->resize(0,wh,ww,wh-sliderh);
    }
  }
  else if(cntx == &TSOCntx::TSO_LayoutStore) {
    wx=ui.main->x();
    wy=ui.main->y();
    ww=ui.main->w();
    wh=ui.main->h();
    //sliderh = ui.tree->h();
  }
  frmviewctrl->TreeScan(cntx);
  frmstereoshape->TreeScan(cntx);
  frmsurfctrl->TreeScan(cntx);
  //insert here for new panel

}
void frmPrjTree::AskForData(Serializer *s){
  s->Item("wx", Sync(&wx));
  s->Item("wy", Sync(&wy));
  s->Item("ww", Sync(&ww));
  s->Item("wh", Sync(&wh));
  s->Item("sliderh", Sync(&sliderh));
  s->Item("frmviewctrl", Sync(&*frmviewctrl));
  s->Item("frmstereoshape", Sync(&*frmstereoshape));
  s->Item("frmsurfctrl", Sync(&*frmsurfctrl));
  //insert here for new panel
}

void frmPrjTree::SyncUI(){
  frmviewctrl->SyncUI();
  frmstereoshape->SyncUI();
  frmsurfctrl->SyncUI();
  //insert here for new panel
}

void frmPrjTree::tree_event(Fl_Widget* w, void* v){
  Flu_Tree_Browser* t=(Flu_Tree_Browser*) w;
  int reason = t->callback_reason();
  Flu_Tree_Browser::Node *n = t->callback_node();

  //if( tree->num_selected() )
  //  deleteNode->activate();
  //else
  //  deleteNode->deactivate();

  switch( reason )
    {
    case FLU_HILIGHTED:
      printf( "%s hilighted\n", n->label() );
      break;

    case FLU_UNHILIGHTED:
      printf( "%s unhilighted\n", n->label() );
      break;

    case FLU_SELECTED:      
      printf( "%s selected\n", n->label() );
      if(!strcmp(n->label(),"View")){
	frmviewctrl->select(true);
      }
      else if(!strcmp(n->label(),"3D Stereo")){
	frmstereoshape->select(true);
      }
      else if(!strcmp(n->label(),"Surface")){
	frmsurfctrl->select(true);
      }
      //insert here for new panel
      break;

    case FLU_UNSELECTED:
      printf( "%s unselected\n", n->label() );
      if(!strcmp(n->label(),"View")){
	frmviewctrl->select(false);
      }
      if(!strcmp(n->label(),"3D Stereo")){
	frmstereoshape->select(false);
      }
      else if(!strcmp(n->label(),"Surface")){
	frmsurfctrl->select(false);
      }
      //insert here for new panel
      break;

    case FLU_OPENED:
      printf( "%s opened\n", n->label() );
      break;

    case FLU_CLOSED:
      printf( "%s closed\n", n->label() );
      break;

    case FLU_DOUBLE_CLICK:
      printf( "%s double-clicked\n", n->label() );
      break;

    case FLU_WIDGET_CALLBACK:
      printf( "%s widget callback\n", n->label() );
      break;

    case FLU_MOVED_NODE:
      printf( "%s moved\n", n->label() );
      break;

    case FLU_NEW_NODE:
      printf( "node '%s' added to the tree\n", n->label() );
      break;
    }  
}





