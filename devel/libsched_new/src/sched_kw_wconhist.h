#ifndef __SCHED_KW_WCONHIST_H__
#define __SCHED_KW_WCONHIST_H__
#include <stdbool.h>
#include <sched_macros.h>

typedef struct sched_kw_wconhist_struct sched_kw_wconhist_type;


sched_kw_wconhist_type * sched_kw_wconhist_fscanf_alloc( FILE *, bool *, const char *);
void                     sched_kw_wconhist_free(sched_kw_wconhist_type * );
void                     sched_kw_wconhist_fprintf(const sched_kw_wconhist_type * , FILE *);
void                     sched_kw_wconhist_fwrite(const sched_kw_wconhist_type *, FILE *);
sched_kw_wconhist_type * sched_kw_wconhist_fread_alloc( FILE *);
//void                     sched_kw_wconhist_fprintf_rates(const sched_kw_wconhist_type * , const char *  , const char * , int );
//void                     sched_kw_wconhist_make_history(const sched_kw_wconhist_type * , int , history_type * );



/*******************************************************************/



KW_FSCANF_ALLOC_HEADER(wconhist)
KW_FWRITE_HEADER(wconhist)
KW_FREAD_ALLOC_HEADER(wconhist)
KW_FREE_HEADER(wconhist)
KW_FPRINTF_HEADER(wconhist)

#endif
