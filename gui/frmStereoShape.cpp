#include "frmStereoShape.h"
#include "stereoshape.h"
#include "frmMainDisplay.h"
#include "frmMainDisplayUI.h"
#include "../apputil/serializer.h"
#include <Fl/Fl_File_Chooser.h>


void frmStereoShape::TreeScan(TSOCntx* cntx){
  if(cntx == &TSOCntx::TSO_LayoutLoad) {
    if(w_w){
      ui->pnl->position(w_x,w_y);
      ui->pnl->size(w_w,w_h);
    }
  }
  else if(cntx == &TSOCntx::TSO_LayoutStore) {
    w_x = ui->pnl->x();    
    w_y = ui->pnl->y();    
    w_w = ui->pnl->w();    
    w_h = ui->pnl->h();
  }
}

void frmStereoShape::AskForData(Serializer *s){
  if(s->ss->storageid==SRLZ_LAYOUT){
    s->Item("w_x",Sync(&w_x));
    s->Item("w_y",Sync(&w_y));
    s->Item("w_w",Sync(&w_w));
    s->Item("w_h",Sync(&w_h));
  }
}

frmStereoShape::frmStereoShape(frmMainDisplay *f):
  frmmain(f),
  dv(f->dv),
  stereoshape(dv->stereoshape.get()),
  w_w(0),
  ui(new frmStereoShapeUI){
  //ui->pnl->label("View");
  ui->pnl->position(20,20);
  //ui->pnt_x->type(FL_FLOAT_INPUT);
  //ui->pnt_y->type(FL_FLOAT_INPUT);
  //ui->pnt_z->type(FL_FLOAT_INPUT);
  //ui->image_off->type(FL_RADIO_BUTTON);
  //ui->image_albedo->type(FL_RADIO_BUTTON);
  //ui->image_image->type(FL_RADIO_BUTTON);

  //ui->shape_off->type(FL_RADIO_BUTTON);
  //ui->shape_notex->type(FL_RADIO_BUTTON);
  //ui->shape_albedo->type(FL_RADIO_BUTTON);
  //ui->shape_image->type(FL_RADIO_BUTTON);

  ui->img_off->type(FL_RADIO_BUTTON);
  ui->img1->type(FL_RADIO_BUTTON);
  ui->img2->type(FL_RADIO_BUTTON);
  ui->img3->type(FL_RADIO_BUTTON);
  ui->img4->type(FL_RADIO_BUTTON);
  ui->img_reg->type(FL_RADIO_BUTTON);
}

frmStereoShape::~frmStereoShape(){}

void frmStereoShape::Init(){

  CONNECT(ui->img_off,frmStereoShape::select_image);
  CONNECT(ui->img1,frmStereoShape::select_image);
  CONNECT(ui->img2,frmStereoShape::select_image);
  CONNECT(ui->img3,frmStereoShape::select_image);
  CONNECT(ui->img4,frmStereoShape::select_image);
  CONNECT(ui->img_reg,frmStereoShape::select_image);
  //CONNECT(ui->pnt_x,frmStereoShape::pnt_edt);
  //CONNECT(ui->pnt_y,frmStereoShape::pnt_edt);
  //CONNECT(ui->pnt_z,frmStereoShape::pnt_edt);
  CONNECT(ui->imagefile_dlg,frmStereoShape::imagefile_dlg);
  CONNECT(ui->reg_go_btn,frmStereoShape::reg_go_btn);

  //CONNECT(ui->image_off,frmStereoShape::image_off);
  //CONNECT(ui->image_albedo,frmStereoShape::image_albedo);
  //CONNECT(ui->image_image,frmStereoShape::image_image);

  //CONNECT(ui->shape_off,frmStereoShape::shape_off);
  //CONNECT(ui->shape_notex,frmStereoShape::shape_notex);
  //CONNECT(ui->shape_image,frmStereoShape::shape_image);
  //CONNECT(ui->shape_albedo,frmStereoShape::shape_albedo);

  stereoshape->eh.SyncUI.connect(sigc::mem_fun(this,&frmStereoShape::SyncUI));
}

void frmStereoShape::SyncUI(){


  /*
  switch(stereoshape->image_mode){
  case StereoShape::image_mode_off: ui->image_off->setonly();break;
  case StereoShape::image_mode_image: ui->image_image->setonly();break;
  case StereoShape::image_mode_albedo: ui->image_albedo->setonly();break;
  }

  switch(stereoshape->shape_mode){
  case StereoShape::shape_mode_off: ui->shape_off->setonly();break;
  case StereoShape::shape_mode_notex: ui->shape_notex->setonly();break;
  case StereoShape::shape_mode_image: ui->shape_image->setonly();break;
  case StereoShape::shape_mode_albedo: ui->shape_albedo->setonly();break;
  }
  */

  int slot = stereoshape->curslot;
  switch(slot){
  case StereoShape::image_sel_off: 
    ui->img_off->setonly(); break;
  case StereoShape::image_sel_s1: 
    ui->img1->setonly(); break;
  case StereoShape::image_sel_s2: 
    ui->img2->setonly(); break;
  case StereoShape::image_sel_s3: 
    ui->img3->setonly(); break;
  case StereoShape::image_sel_s4: 
    ui->img4->setonly(); break;
  case StereoShape::image_sel_reg: 
    ui->img_reg->setonly(); break;
  }

  if(slot==StereoShape::image_sel_off ||
     slot==StereoShape::image_sel_reg ){
    ui->imagefile_dlg->hide();
    ui->imagefile->hide();
  }
  else {
    ui->imagefile_dlg->show();
    ui->imagefile->show();    
    ui->imagefile->value(stereoshape->imagefname[slot].c_str());    
    ui->imagefile->position(1000);
  }
  //ui->norm_x->value(SPrintF()("%f",stereoshape->lights[slot][0]));
  //ui->norm_y->value(SPrintF()("%f",stereoshape->lights[slot][1]));
  //ui->norm_z->value(SPrintF()("%f",stereoshape->lights[slot][2]));
}


void frmStereoShape::select(int v){
  if(v){
    ui->pnl->hide();
    ui->pnl->show();
  }
  else{
    ui->pnl->hide();
  }
}

void frmStereoShape::select_image(Fl_Widget* o, void* v){
  Fl_Button *btn = (Fl_Button*)o;

  if(btn==ui->img_off){
    stereoshape->curslot=StereoShape::image_sel_off;
  }
  else if(btn==ui->img1){
    stereoshape->curslot=StereoShape::image_sel_s1;
  }
  else if(btn==ui->img2){
    stereoshape->curslot=StereoShape::image_sel_s2;
  }
  else if(btn==ui->img3){
    stereoshape->curslot=StereoShape::image_sel_s3;
  }
  else if(btn==ui->img4){
    stereoshape->curslot=StereoShape::image_sel_s4;
  }
  else if(btn==ui->img_reg){
    stereoshape->curslot=StereoShape::image_sel_reg;
  }
  
  SyncUI();
  frmmain->ui->output->redraw();
}

void frmStereoShape::imagefile_dlg(Fl_Widget* o, void* v){
  int slot = stereoshape->curslot;

  const char * s = ".";
  if(!stereoshape->imagefname[slot].empty())
   s = stereoshape->imagefname[slot].c_str();
  

  Fl_File_Chooser f(s,"Image Files (*.{tiff,tif,ppm,bmp,gif,jpg,jpeg,png})",FL_SINGLE,"Open Image");
  f.show();  
  while(f.shown()) { Fl::wait(); }  
  if ( f.value() != NULL ){
    stereoshape->imagefname[slot]=f.value();
    stereoshape->Open(slot);
    SyncUI();
    frmmain->ui->output->redraw();
  }
};


void frmStereoShape::pnt_edt(Fl_Widget* o, void* v){

  int slot= stereoshape->curslot;
  /*
  if(o==ui->pnt_x){
    //stereoshape->lights[slot][0]=strtod(ui->norm_x->value(),0);
  }
  else if(o==ui->pnt_y){
    //stereoshape->lights[slot][1]=strtod(ui->norm_y->value(),0);
  }
  else if(o==ui->pnt_z){
    //stereoshape->lights[slot][2]=strtod(ui->norm_z->value(),0);
  }
  */

}

void frmStereoShape::reg_go_btn(Fl_Widget* o, void* v){
  //err_printf((" build_shape_bnt is not implemented yet!"));
  stereoshape->reg_go();
  frmmain->ui->output->redraw();
}



void frmStereoShape::image_off(Fl_Widget* o, void* v){
  //stereoshape->image_mode = StereoShape::image_mode_off;
  //frmmain->ui->output->redraw();
}
void frmStereoShape::image_albedo(Fl_Widget* o, void* v){
  //stereoshape->image_mode = StereoShape::image_mode_albedo;
  //frmmain->ui->output->redraw();
}
void frmStereoShape::image_image(Fl_Widget* o, void* v){
  //stereoshape->image_mode = StereoShape::image_mode_image;
  //frmmain->ui->output->redraw();
}


void frmStereoShape::shape_off(Fl_Widget* o, void* v){
  //stereoshape->shape_mode = StereoShape::shape_mode_off;
  //frmmain->ui->output->redraw();
}
void frmStereoShape::shape_notex(Fl_Widget* o, void* v){
  //stereoshape->shape_mode = StereoShape::shape_mode_notex;
  //frmmain->ui->output->redraw();
}
void frmStereoShape::shape_albedo(Fl_Widget* o, void* v){
  //stereoshape->shape_mode = StereoShape::shape_mode_albedo;
  //frmmain->ui->output->redraw();
}
void frmStereoShape::shape_image(Fl_Widget* o, void* v){
  //stereoshape->shape_mode = StereoShape::shape_mode_image;
  //frmmain->ui->output->redraw();
}
