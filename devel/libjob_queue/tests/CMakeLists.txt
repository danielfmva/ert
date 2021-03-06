add_executable( job_loadOK job_loadOK.c )
add_executable( job_loadFail job_loadFail.c )
add_executable( create_file create_file.c )
add_executable( job_workflow_test job_workflow_test.c )
add_executable( ext_joblist_test ext_joblist_test.c )

target_link_libraries( job_workflow_test job_queue test_util )
target_link_libraries( create_file job_queue  test_util )
target_link_libraries( job_loadOK job_queue  test_util )
target_link_libraries( job_loadFail job_queue  test_util )
target_link_libraries( ext_joblist_test job_queue  test_util )

add_test( job_workflow_test ${EXECUTABLE_OUTPUT_PATH}/job_workflow_test ${EXECUTABLE_OUTPUT_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/data/internal_job)

add_test( job_loadOK1 ${EXECUTABLE_OUTPUT_PATH}/job_loadOK ${CMAKE_CURRENT_SOURCE_DIR}/data/internalOK)
add_test( job_loadOK2 ${EXECUTABLE_OUTPUT_PATH}/job_loadOK ${CMAKE_CURRENT_SOURCE_DIR}/data/externalOK)
add_test( job_loadOK3 ${EXECUTABLE_OUTPUT_PATH}/job_loadOK ${CMAKE_CURRENT_SOURCE_DIR}/data/internalOK ${CMAKE_CURRENT_SOURCE_DIR}/data/externalOK)

add_test( job_loadFail1 ${EXECUTABLE_OUTPUT_PATH}/job_loadFail ${CMAKE_CURRENT_SOURCE_DIR}/data/internalFail)
add_test( job_loadFail2 ${EXECUTABLE_OUTPUT_PATH}/job_loadFail ${CMAKE_CURRENT_SOURCE_DIR}/data/externalFail)
add_test( job_loadFail3 ${EXECUTABLE_OUTPUT_PATH}/job_loadFail ${CMAKE_CURRENT_SOURCE_DIR}/data/internalFail ${CMAKE_CURRENT_SOURCE_DIR}/data/externalFail)


add_test( ext_joblist_test ${EXECUTABLE_OUTPUT_PATH}/ext_joblist_test ${CMAKE_CURRENT_SOURCE_DIR}/data/jobs/util ${CMAKE_CURRENT_SOURCE_DIR})

add_executable( job_program_output job_program_output.c )
target_link_libraries( job_program_output util test_util)

add_executable( job_queue_test job_job_queue_test.c )
target_link_libraries( job_queue_test job_queue test_util )
add_test( job_queue_test ${EXECUTABLE_OUTPUT_PATH}/job_queue_test ${EXECUTABLE_OUTPUT_PATH}/job_program_output )

add_executable( job_queue_driver_test job_queue_driver_test.c )
target_link_libraries( job_queue_driver_test job_queue test_util )
add_test( job_queue_driver_test ${EXECUTABLE_OUTPUT_PATH}/job_queue_driver_test )


# This should be a space separated list of servers which will be 
# tried out when testing the LSF submit capability. The test program
# will interpret the special strings 'NULL' and 'LOCAL' as follows:
#
#   NULL:  Submit using the linked in library functions.
#   LOCAL: Submit using shell commands on the current server
#
set(LSF_SERVER "" CACHE STRING  "List of LSF servers for testing")

if (HAVE_LSF_LIBRARY)
   add_executable( job_lsf_test job_lsf_test.c )
   target_link_libraries( job_lsf_test job_queue util test_util )
   add_test( job_lsf_test ${EXECUTABLE_OUTPUT_PATH}/job_lsf_test )
endif()



if (HAVE_LSF_LIBRARY)
   add_executable( job_lsb job_lsb.c )
   target_link_libraries( job_lsb job_queue util test_util )
   add_test( job_lsb ${EXECUTABLE_OUTPUT_PATH}/job_lsb )
endif()

add_executable( job_lsf_remote_submit_test job_lsf_remote_submit_test.c )
target_link_libraries( job_lsf_remote_submit_test job_queue util test_util )

add_executable( job_lsf_library_submit_test job_lsf_library_submit_test.c )
target_link_libraries( job_lsf_library_submit_test job_queue util )

add_executable( job_program job_program.c )

if (LSF_SERVER)
   add_test( job_lsf_remote_submit_test ${EXECUTABLE_OUTPUT_PATH}/job_lsf_remote_submit_test ${EXECUTABLE_OUTPUT_PATH}/job_program ${LSF_SERVER} NULL LOCAL)
else()
   add_test( job_lsf_remote_submit_test ${EXECUTABLE_OUTPUT_PATH}/job_lsf_remote_submit_test ${EXECUTABLE_OUTPUT_PATH}/job_program NULL LOCAL)
endif()
set_property( TEST job_lsf_remote_submit_test PROPERTY LABELS StatoilData)


add_executable( job_torque_test job_torque_test.c )
target_link_libraries( job_torque_test job_queue util test_util )
add_test( job_torque_test ${EXECUTABLE_OUTPUT_PATH}/job_torque_test )

add_executable( job_queue_manager job_queue_manager.c )
target_link_libraries( job_queue_manager job_queue util test_util )
add_test( job_queue_manager ${EXECUTABLE_OUTPUT_PATH}/job_queue_manager )

add_executable( job_torque_submit_test job_torque_submit_test.c )
target_link_libraries( job_torque_submit_test job_queue util test_util )
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/data/qsub_emulators/ DESTINATION ${EXECUTABLE_OUTPUT_PATH})
add_test(NAME job_torque_submit_test WORKING_DIRECTORY ${EXECUTABLE_OUTPUT_PATH} COMMAND ${EXECUTABLE_OUTPUT_PATH}/job_torque_submit_test dummyparam)
set_property(TEST job_torque_submit_test PROPERTY ENVIRONMENT “setenv PATH ${EXECUTABLE_OUTPUT_PATH}:$PATH”)
set_property(TEST ext_joblist_test PROPERTY LABELS StatoilData )


# The test program is installed - actually running the test must be
# handled completely on the outside of this build system.
if (INSTALL_ERT)
   install(TARGETS job_program job_lsf_library_submit_test DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
endif()
