
ENABLE_LANGUAGE( CXX )

IF(UNIX)
INCLUDE (FindPkgConfig)
ENDIF(UNIX)

IF(UNIX OR MINGW)
  set (CMAKE_LIBRARY_PATH $ENV{HOME}/lib )
  set (CMAKE_PROGRAM_PATH $ENV{HOME}/bin )
  set (CMAKE_INCLUDE_PATH $ENV{HOME}/include )
ELSEIF(WIN32)
  set (CMAKE_LIBRARY_PATH ${PROJECT_SOURCE_DIR}/..)
  set ( CMAKE_PROGRAM_PATH ${CMAKE_LIBRARY_PATH} )
  set ( CMAKE_INCLUDE_PATH ${CMAKE_LIBRARY_PATH} )
ENDIF(UNIX OR MINGW)

# searching for fltk_jpeg and FLU
IF(MINGW)
  set(FLTK_DIR $ENV{HOME})
  FIND_PROGRAM(FLTK_FLUID_EXECUTABLE NAMES fluid fluid.exe ${FLTK_DIR}/bin )
ENDIF(MINGW)

IF(UNIX OR MINGW)
  set(FLTK_DIR $ENV{HOME} )
  INCLUDE (FindFLTK)
  FIND_PACKAGE(FLTK REQUIRED)

  FIND_LIBRARY(FLTKJPEG_LIB fltk_jpeg)
  IF(MINGW)
    FIND_LIBRARY(FLTKPNG_LIB fltk_png)
  ENDIF(MINGW)
  FIND_LIBRARY(FLTKZLIB_LIB fltk_zlib)
  FIND_LIBRARY(FLU_LIB flu flu)
  FIND_LIBRARY(FLUGL_LIB flu_gl)

ELSEIF(WIN32)

  FIND_PATH(FLTK_DIR FL/Fl.H PATH_SUFFIXES fltk-1.1.10-build )
  FIND_PROGRAM(FLTK_FLUID_EXECUTABLE fluid.exe HINTS ${FLTK_DIR}/bin/${CMAKE_BUILD_TYPE} )
  FIND_PACKAGE(FLTK REQUIRED)
  FIND_LIBRARY(FLTK_JPEG_LIB fltk_jpeg HINTS ${FLTK_DIR}/bin/${CMAKE_BUILD_TYPE} )
  FIND_LIBRARY(FLTK_PNG_LIB fltk_png HINTS ${FLTK_DIR}/bin/${CMAKE_BUILD_TYPE} )
  FIND_LIBRARY(FLTK_ZLIB_LIB fltk_zlib HINTS ${FLTK_DIR}/bin/${CMAKE_BUILD_TYPE} )
#  MESSAGE("TEST ${FLTK_LIBRARIES}")
#  MESSAGE("TEST2 ${FLTK_INCLUDE_DIR}")

  FIND_PATH(FLU_INCLUDE_DIR FLU/flu_export.h PATH_SUFFIXES FLU_2.14)
  set(FLTK_INCLUDE_DIR ${FLTK_INCLUDE_DIR};${FLU_INCLUDE_DIR})
  FIND_LIBRARY(FLU_LIBRARY flu
    HINTS ${FLU_INCLUDE_DIR}/visualc/Debug
  )
  set(FLTK_LIBRARIES ${FLTK_LIBRARIES};${FLU_LIBRARY})

ENDIF(UNIX OR MINGW)

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
  FIND_LIBRARY(FREEIMAGE_LIB NAMES freeimage FreeImage.lib)
  FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h )
ELSEIF(WIN32)
  FIND_PATH(FREEIMAGE_INCLUDE_DIR FreeImage.h PATH_SUFFIXES FreeImage/Dist)
  FIND_LIBRARY(FREEIMAGE_LIB FreeImage HINTS ${FREEIMAGE_INCLUDE_DIR} )
ENDIF(UNIX OR MINGW)


#FIND_LIBRARY(SPOOLES_LIB spooles_I32)
#FIND_PATH(SPOOLES_INCLUDE_DIR spooles/InpMtx.h)

################# LAPACK #########################
IF(UNIX OR MINGW)
  FIND_LIBRARY(LAPACK_LIB lapack)
  FIND_LIBRARY(BLAS_LIB blas)
ELSEIF(WIN32)
  FIND_LIBRARY(LAPACK_LIB lapack_win32 PATH_SUFFIXES lapack)
  FIND_LIBRARY(BLAS_LIB blas_win32 PATH_SUFFIXES lapack)
ENDIF(UNIX OR MINGW)

################# SIGC++ #########################
IF(MINGW)
  FIND_LIBRARY(SIGC_LIB sigc-2.0)
  set( sigc_LIBRARIES ${SIGC_LIB} )
  FIND_PATH(SIGC_INCLUDE_DIR sigc++/sigc++.h PATH_SUFFIXES sigc++-2.0)
  FIND_PATH(SIGC_CONFIG_DIR sigc++config.h $ENV{HOME}/lib/sigc++-2.0/include)
  set( sigc_INCLUDE_DIRS ${SIGC_INCLUDE_DIR} ${SIGC_CONFIG_DIR})
ELSEIF(UNIX)
  PKG_SEARCH_MODULE(sigc sigc++-2.0 REQUIRED)
ELSEIF(WIN32)
  FILE(GLOB sigc_DIR "${CMAKE_LIBRARY_PATH}/libsigc++-2.*[0-9].*[0-9]")
  #MESSAGE("TEST ${sigc_DIR}")
  FIND_PATH(sigc_INCLUDE_DIRS sigc++/sigc++.h HINTS ${sigc_DIR})

  IF(MSVC10)
    FIND_PATH(sigc_CONFIG_DIR  sigc++config.h HINTS ${sigc_DIR}/MSVC_Net2010)
    FIND_LIBRARY(sigc_LIBRARIES_DEBUG
	sigc-vc100-d-2_0 
        HINTS ${sigc_DIR}
        PATH_SUFFIXES MSVC_Net2010/Win32/Debug 
    )
    FIND_LIBRARY(sigc_LIBRARIES_RELEASE
	sigc-vc100-2_0 
        HINTS ${sigc_DIR}
        PATH_SUFFIXES MSVC_Net2010/Win32/Release
    )
  ENDIF(MSVC10)
  set(sigc_LIBRARIES
    debug "${sigc_LIBRARIES_DEBUG}"
    optimized "${sigc_LIBRARIES_RELEASE}"
  )
  set(sigc_INCLUDE_DIRS ${sigc_INCLUDE_DIRS} ${sigc_CONFIG_DIR})
ENDIF(MINGW)


################# pthread #########################
IF(MINGW)
ELSEIF(WIN32)
  FILE(GLOB pthread_DIR "${CMAKE_LIBRARY_PATH}/pthreads-w32-*[0-9]-*[0-9]-*[0-9]" )

  FIND_PATH(pthread_INCLUDE_DIR pthread.h 
    HINTS ${pthread_DIR}/Pre-built.2/include  
  )
  FIND_LIBRARY(pthread_LIB pthreadVSE2
    HINTS ${pthread_DIR}/Pre-built.2/lib/x86
  )
  INCLUDE_DIRECTORIES( ${pthread_INCLUDE_DIR} )  
ENDIF(MINGW)




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

IF(WIN32)
  set( zeroak_EXECUTABLE_DIR ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE} )
else(WIN32)
  set( zeroak_EXECUTABLE_DIR ${CMAKE_CURRENT_BINARY_DIR} )
ENDIF(WIN32)

add_custom_command (
  OUTPUT ${zeroak_EXECUTABLE_DIR}/index.html
  DEPENDS index.html
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/index.html ${zeroak_EXECUTABLE_DIR}/index.html
  )

add_custom_command (
  OUTPUT ${zeroak_EXECUTABLE_DIR}/torch.ico
  DEPENDS torch.ico
  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/torch.ico ${zeroak_EXECUTABLE_DIR}/torch.ico
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
  ${zeroak_EXECUTABLE_DIR}/index.html
  ${zeroak_EXECUTABLE_DIR}/torch.ico
)

MESSAGE("TEST ${zeroak_EXECUTABLE_DIR}")

#MESSAGE("VAR=${FLTK_INCLUDE_DIR}")
#MESSAGE("VAR=${sigc_INCLUDE_DIRS}")

INCLUDE_DIRECTORIES(
                    ${zeroak_SOURCE_DIR}
                    ${sigc_INCLUDE_DIRS}
                    ${FLTK_INCLUDE_DIR}
                    ${FREEIMAGE_INCLUDE_DIR}
#                    ${SPOOLES_INCLUDE_DIR}
)

IF(WIN32)
  set(zeroak_WIN32_OPTIONS "-DNOMINMAX -D_USE_MATH_DEFINES" /MP)
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
  ${FLTK_IMAGES_LIBRARY}
  ${FLTKZLIB_LIB}
  ${FLTKJPEG_LIB}
  ${FLTKPNG_LIB}
  lapackcpp
  ${LAPACK_LIB}
  ${BLAS_LIB}
  apputil
  ${sigc_LIBRARIES}
  ${FREEIMAGE_LIB}
  ${pthread_LIB}
)

ADD_DEPENDENCIES(zeroak apputil)

