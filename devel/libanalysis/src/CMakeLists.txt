# Common libanalysis library
set( source_files analysis_module.c enkf_linalg.c std_enkf.c sqrt_enkf.c cv_enkf.c bootstrap_enkf.c null_enkf.c fwd_step_enkf.c )
set( header_files analysis_module.h enkf_linalg.h analysis_table.h std_enkf.h fwd_step_enkf.h)
add_library( analysis  SHARED ${source_files} )
set_target_properties( analysis PROPERTIES COMPILE_DEFINITIONS INTERNAL_LINK)
set_target_properties( analysis PROPERTIES VERSION 1.0 SOVERSION 1.0 )

target_link_libraries( analysis ert_util )
target_link_libraries( analysis dl )

if (USE_RUNPATH)
   add_runpath( analysis )
endif()


#-----------------------------------------------------------------

if (INSTALL_ERT)
   install(TARGETS analysis DESTINATION ${CMAKE_INSTALL_LIBDIR})
   #install(TARGETS rml_enkf DESTINATION ${CMAKE_INSTALL_LIBDIR})
   foreach(header ${header_files})
       install(FILES ../include/ert/analysis/${header} DESTINATION ${CMAKE_INSTALL_PREFIX}/include/ert/analysis)
   endforeach()
endif()

