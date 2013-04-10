
ENABLE_LANGUAGE( CXX )

INCLUDE (FindPkgConfig)
INCLUDE (FindFLTK)

# searching for fltk_jpeg and FLU
FIND_LIBRARY(FLTKJPEG_LIB fltk_jpeg)
FIND_LIBRARY(FLU_LIB flu flu)
FIND_LIBRARY(FLUGL_LIB flu_gl)

set (CMAKE_LIBRARY_PATH $ENV{HOME}/lib )

FIND_LIBRARY(FREEIMAGE_LIB freeimage)
FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h)

#FIND_LIBRARY(SPOOLES_LIB spooles_I32)
#FIND_PATH(SPOOLES_INCLUDE_DIR spooles/InpMtx.h)

FIND_LIBRARY(LAPACK_LIB lapack)

#FIND_LIBRARY(SIGC_LIB sigc-2.0)
#FIND_PATH(SIGC_INCLUDE_DIR sigc++/sigc++.h)
#FIND_PATH(SIGC_CONFIG_DIR sigc++config.h $ENV{HOME}/lib/sigc++-2.0/include)

PKG_SEARCH_MODULE(sigc sigc++-2.0 REQUIRED)


ADD_LIBRARY( lapackcpp
    ../mathlib/lapackcpp/eigenval.cpp
    ../mathlib/lapackcpp/invert.cpp
    ../mathlib/lapackcpp/leastsquare.cpp
    ../mathlib/lapackcpp/svald.cpp
    ../mathlib/lapackcpp/lapackcpp.h
)

ADD_LIBRARY( apputil
    ../apputil/AppSysSet.cpp ../apputil/AppSysSet.h
    ../apputil/serializer.cpp ../apputil/serializer.h
    ../apputil/eventball.h
    ../apputil/eventballfltk.cpp ../apputil/eventballfltk.h
)

fltk_wrap_ui(
    zeroak
    frmStereoShapeUI.fl  
    frmViewCtrlUI.fl
    frmMainDisplayUI.fl
    frmSurfCtrlUI.fl
    frmPrjTreeUI.fl
)

add_custom_command (
  OUTPUT torch.ico
  DEPENDS torch.ico
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/torch.ico ${CMAKE_CURRENT_BINARY_DIR}/torch.ico
  )

add_custom_command (
  OUTPUT index.html
  DEPENDS index.html
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/index.html ${CMAKE_CURRENT_BINARY_DIR}/index.html
  )

ADD_EXECUTABLE( 
  zeroak
  mainini.cpp
  eventlog.cpp eventlog.h
  toolspanel.cpp
  mathstruct.cpp
  mousectrl.cpp mousectrl.h
  savejpeg.cpp
  glhelper.cpp savejpeg.h
  editviewobj.cpp editviewobj.h
  glhelper.h  mathstruct.h  toolspanel.h
  dispview.cpp dispview.h
  eventhnd.cpp eventhnd.h
  viewctrl.cpp viewctrl.h
  lights.cpp lights.h
  stereoshape.cpp stereoshape.h
  viewsurf.cpp viewsurf.h
  ImageTile.cpp ImageTile.h
  stereoreg.cpp stereoreg.h
  fltk_calllist.cpp fltk_calllist.h fltk_animator.h fltk_defs.h

  frmMainDisplay.cpp frmMainDisplay.h
  frmPrjTree.cpp frmPrjTree.h
  frmSurfCtrl.cpp frmSurfCtrl.h
  frmStereoShape.cpp frmStereoShape.h
  frmViewCtrl.cpp frmViewCtrl.h
  
  ${zeroak_FLTK_UI_SRCS}
  ${CMAKE_CURRENT_BINARY_DIR}/torch.ico
  ${CMAKE_CURRENT_BINARY_DIR}/index.html
)

#MESSAGE("VAR=${FLTK_INCLUDE_DIR}")
#MESSAGE("VAR=${sigc_INCLUDE_DIRS}")

INCLUDE_DIRECTORIES(
                    ${zeroak_SOURCE_DIR}
                    ${sigc_INCLUDE_DIRS}
                    ${FLTK_INCLUDE_DIR}
                    ${FREEIMAGE_INCLUDE_DIR}
#                    ${SPOOLES_INCLUDE_DIR}
)

ADD_DEFINITIONS(
    -DPACKAGE_SHAREDIR="${zeroak_SHAREDIR}"
    -DPACKAGE_NAME="${PROJECT_NAME}"
    -DPACKAGE_VERSION="${CMAKE_VERSION}"
    ${sigc_DEFINITIONS}
)

TARGET_LINK_LIBRARIES(zeroak 
  ${FREEIMAGE_LIB}
#  ${SPOOLES_LIB}
  ${FLU_LIB} 
  ${FLTK_LIBRARIES}
  ${FLTKJPEG_LIB}
  lapackcpp
  ${LAPACK_LIB}
  apputil
  ${sigc_LIBRARIES}
)

ADD_DEPENDENCIES(zeroak apputil)

