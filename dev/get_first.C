/*
 * This file was originially part of /scr/rrd.c in te
 */

#include <rrd.h>
#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <stdio.h>


/* gets the first timestamp for the RRA identified by cfIn and stepIn in filenameIn  
 * 
 */
SEXP get_first(SEXP filenameIn, SEXP cfIn, SEXP stepIn)  {
  const char *cf;
  
  unsigned long step;
  unsigned long curStep;
  
  rrd_info_t *rrdInfo;
  
  rra_info* rra_info_list;
  rra_info* rra_info_tmp;
  
  int i;
  int rraCnt;
  
  SEXP out;
  
  char *filename = (char *)CHAR(asChar(filenameIn));
  
  if (access(filename, F_OK) == -1) {
    Rprintf("file does not exist\n");
    return R_NilValue;
  }
  
  cf = CHAR(asChar(cfIn));
  
  curStep  = (unsigned long) asInteger(stepIn);
  rrdInfo = rrd_info_r(filename);
  
  if (rrdInfo == NULL) {
    Rprintf("error getting rrd info");
    return R_NilValue;
  }
  
  rra_info_list = get_rra_info(rrdInfo, &rraCnt, &step);
  
  if (rra_info_list == NULL) {
    Rprintf("error getting rrd info");
    free(rrdInfo);
    return R_NilValue;
  }
  
  rra_info_tmp = rra_info_list;
  
  i = 0;
  while (rra_info_tmp) {
    if (!strcmp(cf, rra_info_tmp->cf) && (curStep == step * rra_info_tmp->pdp_per_row)) {
      break;
    }
    i++;
    rra_info_tmp = rra_info_tmp->next;
  }
  
  out = PROTECT(allocVector(INTSXP, 1));
  if (i < rraCnt) {
    INTEGER(out)[0] = rrd_first_r(filename, i);
  } else {
    out = R_NilValue;
  }
  
  free_rra_info(rra_info_list);
  free(rrdInfo);
  UNPROTECT(1);
  
  return out;
}
