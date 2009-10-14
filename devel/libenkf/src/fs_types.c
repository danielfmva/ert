#include <string.h>
#include <stdlib.h>
#include <fs_types.h>
#include <util.h>


fs_driver_impl fs_types_lookup_string_name(const char * driver_name) {
  if (strcmp(driver_name , "PLAIN") == 0)
    return PLAIN_DRIVER_ID;
  else if (strcmp(driver_name , "SQLITE") == 0)
    return SQLITE_DRIVER_ID;
  else if (strcmp(driver_name , "BLOCK_FS") == 0)
    return BLOCK_FS_DRIVER_ID;
  else {
    util_abort("%s: could not determine driver type for input:%s \n",__func__ , driver_name);
    return INVALID_DRIVER_ID;
  }
}



const char * fs_types_get_driver_name(fs_driver_type driver_type) {
  switch( driver_type ) {
  case(DRIVER_PARAMETER):
    return "PARAMETER";
    break;
  case(DRIVER_STATIC):
    return "STATIC";
    break;
  case(DRIVER_DYNAMIC_FORECAST):
    return "FORECAST";
    break;
  case(DRIVER_DYNAMIC_ANALYZED):
    return "ANALYZED";
    break;
  default:
    util_abort("%s: driver_id:%d not recognized. \n",__func__ , driver_type );
    return NULL;
  }
}
