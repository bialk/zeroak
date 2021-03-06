
ENABLE_LANGUAGE( CXX )

IF(UNIX OR MINGW)
INCLUDE (FindPkgConfig)
ENDIF(UNIX OR MINGW)

##################### general search paths ########################

IF(UNIX OR MINGW)
  set (CMAKE_LIBRARY_PATH $ENV{HOME}/lib )
  set (CMAKE_PROGRAM_PATH $ENV{HOME}/bin )
  set (CMAKE_INCLUDE_PATH $ENV{HOME}/include )
ELSEIF(WIN32)
  set (CMAKE_LIBRARY_PATH  ${PROJECT_SOURCE_DIR}/..)
  set (CMAKE_PROGRAM_PATH ${CMAKE_LIBRARY_PATH} )
  set (CMAKE_INCLUDE_PATH ${CMAKE_LIBRARY_PATH} )
ENDIF(UNIX OR MINGW)

###################### fltk & FLU & etc. ############################

IF(UNIX OR MINGW)

  IF(MINGW)
    set(FLTK_DIR $ENV{HOME} )
    FIND_PROGRAM(FLTK_FLUID_EXECUTABLE NAMES fluid fluid.exe ${FLTK_DIR}/bin )
  ENDIF(MINGW)

  FIND_PACKAGE(FLTK REQUIRED)

  FIND_LIBRARY(FLTK_JPEG_LIB fltk_jpeg)
  FIND_LIBRARY(FLTK_PNG_LIB fltk_png)
  FIND_LIBRARY(FLTK_ZLIB_LIB fltk_zlib)
  FIND_LIBRARY(FLU_LIB flu flu)
  FIND_LIBRARY(FLUGL_LIB flu_gl)

ELSEIF(WIN32)

  if(MSVC10)
    FIND_PATH(FLTK_INCLUDE_DIR_DEBUG FL/Fl.H PATH_SUFFIXES
      fltk-1.1.10-msvc10-debug
    )
    FIND_PATH(FLTK_INCLUDE_DIR_RELEASE FL/Fl.H PATH_SUFFIXES
      fltk-1.1.10-msvc10-release
    )
  elseif(MSVC90)
    FIND_PATH(FLTK_INCLUDE_DIR_DEBUG FL/Fl.H PATH_SUFFIXES
      fltk-1.1.10-msvc9-debug
    )
    FIND_PATH(FLTK_INCLUDE_DIR_RELEASE FL/Fl.H PATH_SUFFIXES
      fltk-1.1.10-msvc9-release
    )
  endif(MSVC10)


  FIND_PROGRAM(FLTK_FLUID_EXECUTABLE fluid.exe
    HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin )

  FIND_LIBRARY(FLTK_LIB_DEBUG fltk HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)
  FIND_LIBRARY(FLTK_IMAGES_LIB_DEBUG fltk_images HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)
  FIND_LIBRARY(FLTK_FORMS_LIB_DEBUG fltk_forms HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)
  FIND_LIBRARY(FLTK_GL_LIB_DEBUG fltk_gl HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)
  FIND_LIBRARY(FLTK_JPEG_LIB_DEBUG fltk_jpeg HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)
  FIND_LIBRARY(FLTK_PNG_LIB_DEBUG fltk_png HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)
  FIND_LIBRARY(FLTK_ZLIB_LIB_DEBUG fltk_zlib HINTS ${FLTK_INCLUDE_DIR_DEBUG}/bin)

  FIND_LIBRARY(FLTK_LIB_RELEASE fltk HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)
  FIND_LIBRARY(FLTK_IMAGES_LIB_RELEASE fltk_images HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)
  FIND_LIBRARY(FLTK_FORMS_LIB_RELEASE fltk_forms HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)
  FIND_LIBRARY(FLTK_GL_LIB_RELEASE fltk_gl HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)
  FIND_LIBRARY(FLTK_JPEG_LIB_RELEASE fltk_jpeg HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)
  FIND_LIBRARY(FLTK_PNG_LIB_RELEASE fltk_png HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)
  FIND_LIBRARY(FLTK_ZLIB_LIB_RELEASE fltk_zlib HINTS ${FLTK_INCLUDE_DIR_RELEASE}/bin)

  set(FLTK_LIBRARIES
    debug "${FLTK_LIB_DEBUG}"
    debug "${FLTK_IMAGES_LIB_DEBUG}"
    debug "${FLTK_FORMS_LIB_DEBUG}"
    debug "${FLTK_GL_LIB_DEBUG}"
    optimized "${FLTK_LIB_RELEASE}"
    optimized "${FLTK_IMAGES_LIB_RELEASE}"
    optimized "${FLTK_FORMS_LIB_RELEASE}"
    optimized "${FLTK_GL_LIB_RELEASE}"
  )

  SET(FLTK_JPEG_LIB
     debug ${FLTK_JPEG_LIB_DEBUG}
     optimized ${FLTK_JPEG_LIB_RELEASE}
  )
  SET(FLTK_PNG_LIB
     debug ${FLTK_PNG_LIB_DEBUG}
     optimized ${FLTK_PNG_LIB_RELEASE}
  )
  SET(FLTK_ZLIB_LIB
     debug ${FLTK_ZLIB_LIB_DEBUG}
     optimized ${FLTK_ZLIB_LIB_RELEASE}
  )
  FIND_LIBRARY(FLTK_ws2_32_LIBS ws2_32)
  FIND_LIBRARY(FLTK_wsock32_LIBS wsock32)
  FIND_LIBRARY(FLTK_comctl32_LIBS comctl32)

  set(FLTK_LIBRARIES
     ${FLTK_ws2_32_LIBS} ${FLTK_wsock32_LIBS} ${FLTK_comctl32_LIBS}
     ${FLTK_LIBRARIES}
  )

  # looking for FLU library
  FIND_PATH(FLU_INCLUDE_DIR FLU/flu_export.h PATH_SUFFIXES FLU_2.14)

  if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(FLTK_INCLUDE_DIR ${FLTK_INCLUDE_DIR_DEBUG})
  ELSE(CMAKE_BUILD_TYPE MATCHES Debug)
    set(FLTK_INCLUDE_DIR ${FLTK_INCLUDE_DIR_RELEASE})
  ENDIF(CMAKE_BUILD_TYPE MATCHES Debug)

  FIND_LIBRARY(FLU_LIBRARY_DEBUG flu
    HINTS ${FLU_INCLUDE_DIR}/visualc/Debug
  )
  FIND_LIBRARY(FLU_LIBRARY_RELEASE flu
    HINTS ${FLU_INCLUDE_DIR}/visualc/Release
  )

  set(FLU_LIB
     debug ${FLU_LIBRARY_DEBUG}
     optimized ${FLU_LIBRARY_RELEASE}
  )

ENDIF(UNIX OR MINGW)
INCLUDE_DIRECTORIES( ${FLU_INCLUDE_DIR} )
INCLUDE_DIRECTORIES( ${FLTK_INCLUDE_DIR} )


#################### opengl ####################

INCLUDE(FindOpenGL)
IF(NOT OPENGL_FOUND)
	MESSAGE(FATAL_ERROR "OpenGL not found!")
ENDIF(NOT OPENGL_FOUND)

################## GL Extentions ################

IF(WIN32)

  FIND_PATH(
    GLEXTS_INCLUDE_DIR GL/glext.h PATH_SUFFIXES glexts 
		DOC "Directory containing GL/glext.h, GL/glxext.h, GL/wglext.h, ..."
  )
  IF(NOT GLEXTS_INCLUDE_DIR)
    MESSAGE(
      FATAL_ERROR "glexts include directory not found. "
      "You can specify it manually in GLEXTS_INCLUDE_DIR."
    )
  ENDIF()
  INCLUDE_DIRECTORIES(BEFORE "${GLEXTS_INCLUDE_DIR}")

ENDIF()


################# FREEIMAGE_LIB #################

IF(UNIX OR MINGW)
  FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h )
  FIND_LIBRARY(FREEIMAGE_LIB NAMES freeimage FreeImage)
ELSEIF(WIN32)
  FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h PATH_SUFFIXES FreeImage/Dist)
  FIND_LIBRARY(FREEIMAGE_LIB FreeImage HINTS ${FREEIMAGE_INCLUDE_DIR} )
  FIND_FILE(FREEIMAGE_DLL FreeImage.dll HINTS ${FREEIMAGE_INCLUDE_DIR} )
  list(APPEND FOR_COPY_TO_BINARY_DIR ${FREEIMAGE_DLL})
ENDIF(UNIX OR MINGW)
INCLUDE_DIRECTORIES(${FREEIMAGE_INCLUDE_DIR})

####################### spooles ##################

#FIND_LIBRARY(SPOOLES_LIB spooles_I32)
#FIND_PATH(SPOOLES_INCLUDE_DIR spooles/InpMtx.h)

################# LAPACK #########################
IF(UNIX OR MINGW)
  FIND_LIBRARY(LAPACK_LIB lapack)
  FIND_LIBRARY(BLAS_LIB blas)
ELSEIF(WIN32)
  FIND_LIBRARY(LAPACK_LIB lapack_win32 PATH_SUFFIXES lapack)
  FIND_LIBRARY(BLAS_LIB blas_win32 PATH_SUFFIXES lapack)
  FIND_FILE(LAPACK_DLL lapack_win32.dll PATH_SUFFIXES lapack)
  FIND_FILE(BLAS_DLL blas_win32.dll PATH_SUFFIXES lapack)
  list(APPEND FOR_COPY_TO_BINARY_DIR ${LAPACK_DLL} ${BLAS_DLL})
ENDIF(UNIX OR MINGW)

################# SIGC++ #########################
IF(MINGW)
  FIND_LIBRARY(SIGC_LIB sigc-2.0)
  set( sigc_LIBRARIES ${SIGC_LIB} )
  FIND_PATH(sigc_INCLUDE_DIR sigc++/sigc++.h PATH_SUFFIXES sigc++-2.0)
  FIND_PATH(sigc_CONFIG_DIR sigc++config.h $ENV{HOME}/lib/sigc++-2.0/include /usr/lib/x86_64_linux-gnu/sigc++-2.0/include)
  set( sigc_INCLUDE_DIRS ${sigc_INCLUDE_DIR} ${sigc_CONFIG_DIR} )
ELSEIF(UNIX)
  PKG_SEARCH_MODULE(sigc sigc++-2.0 REQUIRED)
  FIND_PATH(sigc_INCLUDE_DIR sigc++/sigc++.h PATH_SUFFIXES sigc++-2.0)
  FIND_PATH(sigc_CONFIG_DIR sigc++config.h $ENV{HOME}/lib/sigc++-2.0/include /usr/lib/x86_64-linux-gnu/sigc++-2.0/include)
  set( sigc_INCLUDE_DIRS ${sigc_INCLUDE_DIR} ${sigc_CONFIG_DIR} )
ELSEIF(WIN32)
  FILE(GLOB sigc_DIR "${CMAKE_LIBRARY_PATH}/libsigc++-2.*[0-9].*[0-9]")
  FIND_PATH(sigc_INCLUDE_DIR sigc++/sigc++.h HINTS ${sigc_DIR})

  IF(MSVC10)
    FIND_PATH(sigc_CONFIG_DIR  sigc++config.h HINTS ${sigc_DIR}/MSVC_Net2010)
    FIND_LIBRARY(sigc_LIBRARIES_DEBUG
	sigc-vc100-d-2_0 
        HINTS ${sigc_DIR}
        PATH_SUFFIXES MSVC_Net2010/Win32/Debug 
    )
    FIND_FILE(sigc_DLL_DEBUG
        sigc-vc100-d-2_0.dll
        HINTS ${sigc_DIR}
        PATH_SUFFIXES MSVC_Net2010/Win32/Debug
    )
    FIND_LIBRARY(sigc_LIBRARIES_RELEASE
	sigc-vc100-2_0 
        HINTS ${sigc_DIR}
        PATH_SUFFIXES MSVC_Net2010/Win32/Release
    )
    FIND_FILE(sigc_DLL_RELEASE
        sigc-vc100-2_0.dll
        HINTS ${sigc_DIR}
        PATH_SUFFIXES MSVC_Net2010/Win32/Release
    )
  ENDIF(MSVC10)
  set(sigc_LIBRARIES
    debug "${sigc_LIBRARIES_DEBUG}"
    optimized "${sigc_LIBRARIES_RELEASE}"
  )
  if(CMAKE_BUILD_TYPE MATCHES Debug)
    set(sigc_DLL ${sigc_DLL_DEBUG})
  else(CMAKE_BUILD_TYPE MATCHES Debug)
    set(sigc_DLL ${sigc_DLL_RELEASE})
  endif(CMAKE_BUILD_TYPE MATCHES Debug)
  list(APPEND FOR_COPY_TO_BINARY_DIR ${sigc_DLL})

  set( sigc_INCLUDE_DIRS ${sigc_INCLUDE_DIR};${sigc_CONFIG_DIR})
ENDIF(MINGW)
INCLUDE_DIRECTORIES( ${sigc_INCLUDE_DIRS} )


################# pthread #########################

IF(MINGW)
ELSEIF(WIN32)
  FILE(GLOB pthread_DIR "${CMAKE_LIBRARY_PATH}/pthreads-w32-*[0-9]-*[0-9]-*[0-9]")

  FIND_PATH(pthread_INCLUDE_DIR pthread.h 
    HINTS ${pthread_DIR}/Pre-built.2/include  
  )
  FIND_LIBRARY(pthread_LIB pthreadVSE2
    HINTS ${pthread_DIR}/Pre-built.2/lib/x86
  )
  FIND_FILE(pthread_DLL pthreadVSE2.dll
    HINTS ${pthread_DIR}/Pre-built.2/dll/x86
  )
  list(APPEND FOR_COPY_TO_BINARY_DIR ${pthread_DLL})

  INCLUDE_DIRECTORIES( ${pthread_INCLUDE_DIR} )  
ENDIF(MINGW)


################## source include dir ################
INCLUDE_DIRECTORIES( ${zeroak_SOURCE_DIR} )

#ADD_LIBRARY( flu
#  ../../FLU_2.14/src/FluSimpleString.cpp
#  ../../FLU_2.14/src/Flu_Button.cpp
#  ../../FLU_2.14/src/Flu_Chat_Buffer.cpp
#  ../../FLU_2.14/src/Flu_Choice_Group.cpp
#  ../../FLU_2.14/src/Flu_Collapsable_Group.cpp
#  ../../FLU_2.14/src/Flu_Combo_Box.cpp
#  ../../FLU_2.14/src/Flu_Combo_List.cpp
#  ../../FLU_2.14/src/Flu_Combo_Tree.cpp
#  ../../FLU_2.14/src/Flu_DND.cpp
#  ../../FLU_2.14/src/Flu_Dual_Progress_Meter.cpp
#  ../../FLU_2.14/src/Flu_Dual_Slider.cpp
#  ../../FLU_2.14/src/Flu_File_Chooser.cpp
#  ../../FLU_2.14/src/flu_file_chooser_pixmaps.cpp
#  ../../FLU_2.14/src/Flu_Float_Input.cpp
#  ../../FLU_2.14/src/Flu_GL_Canvas.cpp
#  ../../FLU_2.14/src/Flu_GL_Window.cpp
#  ../../FLU_2.14/src/Flu_Helpers.cpp
#  ../../FLU_2.14/src/Flu_Int_Input.cpp
#  ../../FLU_2.14/src/Flu_Label.cpp
#  ../../FLU_2.14/src/Flu_Link_Button.cpp
#  ../../FLU_2.14/src/Flu_Output.cpp
#  ../../FLU_2.14/src/flu_pixmaps.cpp
#  ../../FLU_2.14/src/Flu_Progress.cpp
#  ../../FLU_2.14/src/Flu_Progress_Meter.cpp
#  ../../FLU_2.14/src/Flu_Return_Button.cpp
#  ../../FLU_2.14/src/Flu_Separator.cpp
#  ../../FLU_2.14/src/Flu_Simple_Group.cpp
#  ../../FLU_2.14/src/Flu_Spinner.cpp
#  ../../FLU_2.14/src/Flu_Toggle_Group.cpp
#  ../../FLU_2.14/src/Flu_Tree_Browser.cpp
#  ../../FLU_2.14/src/Flu_Wrap_Group.cpp
#)



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
)
list(APPEND FOR_COPY_TO_BINARY_DIR
  ${CMAKE_CURRENT_SOURCE_DIR}/index.html
  ${CMAKE_CURRENT_SOURCE_DIR}/torch.ico
)

######################### copy additional resources ######################

IF(MSVC_IDE)
  set( COPY_PATH_TO_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE} )
else(MSVC_IDE)
  set( COPY_PATH_TO_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR} )
ENDIF(MSVC_IDE)

foreach(loop_dll_path ${FOR_COPY_TO_BINARY_DIR})
  get_filename_component(loop_dll_name ${loop_dll_path} NAME)
  # message("${loop_dll_name}")
  add_custom_command (
    OUTPUT ${COPY_PATH_TO_BINARY_DIR}/${loop_dll_name}
    DEPENDS ${loop_dll_path}
    COMMAND ${CMAKE_COMMAND} -E copy ${loop_dll_path} ${COPY_PATH_TO_BINARY_DIR}/${loop_dll_name}
  )
  list(APPEND zeroak_RESOURCES ${COPY_PATH_TO_BINARY_DIR}/${loop_dll_name})
endforeach(loop_dll_path)

add_custom_target( zeroak_RESOURCES DEPENDS ${zeroak_RESOURCES})
add_dependencies( zeroak zeroak_RESOURCES )

########################## compilator settings ############################

IF(WIN32)
  set(zeroak_WIN32_OPTIONS "-DNOMINMAX -D_USE_MATH_DEFINES")
ENDIF(WIN32)

ADD_DEFINITIONS(
    -DPACKAGE_SHAREDIR="${zeroak_SHAREDIR}"
    -DPACKAGE_NAME="${PROJECT_NAME}"
    -DPACKAGE_VERSION="${CMAKE_VERSION}"
    ${zeroak_WIN32_OPTIONS}
    ${sigc_DEFINITIONS}
)

TARGET_LINK_LIBRARIES(zeroak 
#  ${SPOOLES_LIB}
  ${FLU_LIB}
  ${FLTK_LIBRARIES}
  ${FLTK_ZLIB_LIB}
  ${FLTK_JPEG_LIB}
  ${FLTK_PNG_LIB}
  lapackcpp
  ${LAPACK_LIB}
  ${BLAS_LIB}
  apputil
  ${sigc_LIBRARIES}
  ${FREEIMAGE_LIB}
  ${pthread_LIB}
  ${OPENGL_LIBRARIES}
)

