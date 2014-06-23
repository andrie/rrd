#define RRD_EXPORT_DEPRECATED

#include <rrd.h>
//#include <rrd_format.h>
#include <R.h>
#include <Rdefines.h>
#include <Rinternals.h>
#include <stdio.h>
/*#include "rrd_tool.h"*/
/*#include "rrd_rpncalc.h"*/
/*#include "rrd_client.h"*/


#define DEBUG

#define RRD_READONLY    (1<<0)
#define RRD_READWRITE   (1<<1)
#define RRD_CREAT       (1<<2)
#define RRD_READAHEAD   (1<<3)
#define RRD_COPY        (1<<4)
#define RRD_EXCL        (1<<5)


SEXP exposeArray(char c){
    int array[5] = {1,2,3,4,5};
    int size = sizeof (array) / sizeof (*array);
    SEXP out = PROTECT(allocVector(INTSXP, size));
    for (int i = 0; i < size; i++){
	printf("iterating.. i = %d len = %d\n", i, size);
	INTEGER(out)[i] = array[i];
    }
    UNPROTECT(1);

    return out;
}

/*SEXP importRRD(const char* filename){*/
    /*rrd_t rrd;*/
    /*unsigned int i, ii, ix, iii = 0;*/
    /*rrd_file_t *rrd_file;*/
    /*rrd_init(&rrd);*/
    /*rrd_value_t my_cdp;*/
    /*off_t     rra_base, rra_start, rra_next;*/

    /*rrd_file = rrd_open(filename, &rrd, RRD_READONLY | RRD_READAHEAD);*/
    /*if (rrd_file == NULL) {*/
        /*rrd_free(&rrd);*/
        /*return (-1);*/
    /*}*/
    /*rra_base = rrd_file->header_len;*/
    /*rra_next = rra_base;*/

    /*for (i = 0; i < rrd.stat_head->rra_cnt; i++) {*/

        /*long      timer = 0;*/

        /*rra_start = rra_next;*/
        /*rra_next += (rrd.stat_head->ds_cnt*/
                     /** rrd.rra_def[i].row_cnt * sizeof(rrd_value_t));*/



        /*rrd_seek(rrd_file, (rra_start + (rrd.rra_ptr[i].cur_row + 1)*/
                            /** rrd.stat_head->ds_cnt*/
                            /** sizeof(rrd_value_t)), SEEK_SET);*/

        /*ii = rrd.rra_ptr[i].cur_row;*/

	/*//for each archive*/
        /*for (ix = 0; ix < rrd.rra_def[i].row_cnt; ix++) {*/
            /*ii++;*/
            /*if (ii >= rrd.rra_def[i].row_cnt) {*/
                /*rrd_seek(rrd_file, rra_start, SEEK_SET);*/
                /*ii = 0; [> wrap if max row cnt is reached <]*/
            /*}*/

	    /*//for each data source */
            /*for (iii = 0; iii < rrd.stat_head->ds_cnt; iii++) {*/
                /*rrd_read(rrd_file, &my_cdp, sizeof(rrd_value_t) * 1);*/
                /*if (isnan(my_cdp)) {*/
		/*//TODO put symbol R_NaReal*/
                /*} else {*/
		/*//put number*/
                /*}*/
            /*}*/
        /*}*/
    /*}*/


    /*rrd_free(&rrd);*/

    /*rrd_close(rrd_file);*/

/*}*/


/*SEXP rrd_fetch(const char *filename, const char* cf,  time_t *start, time_t *end, unsigned long *step)  {*/
/*SEXP importRRD(const char* filename, time_t start, time_t end, unsigned long step)  {*/
SEXP importRRD(SEXP filenameIn, SEXP cfIn, SEXP startIn, SEXP endIn, SEXP stepIn)  {

    rrd_value_t *data;
    //this should complain if data needs to be initialized
    //hmm... think we need to initialize
    


    /*const char filename[] = "/var/lib/ganglia/rrds/__SummaryInfo__/boottime.rrd";*/
    const char *filename = CHAR(asChar(filenameIn));



    /*const char cf[] = "AVERAGE";*/
    const char *cf = CHAR(asChar(cfIn));

    /*time_t start = 0;*/
    time_t start = (time_t) asInteger(startIn);

    /*time_t end = 0;*/
    time_t end = (time_t) asInteger(endIn);


    /*unsigned long step = 1;*/
    unsigned long step = (unsigned long) asInteger(stepIn);

    unsigned long ds_cnt;
    char** ds_namv;

    printf("we are about to call rrdfetch\n");
    fflush(stdout);
    int status = rrd_fetch_r(filename, cf, &start, &end, &step, &ds_cnt, &ds_namv, &data);
    printf("we just did\n");
    printf("size of data %d start %d end %d step %d ds_cnt %d\n", sizeof(data)/sizeof(rrd_value_t), start, end, step, ds_cnt);
    fflush(stdout);
    int size = (end - start)/step;

    SEXP out = PROTECT(allocVector(VECSXP, ds_cnt));
    SEXP vec;
    for (int ds = 0; ds < ds_cnt; ds++){
	vec = PROTECT(allocVector(REALSXP, size));
	for (int i = 0; i < size; i++){
	    /*printf("iterating.. i = %d\n", i);*/
	    /*REAL(out)[i] = *(data)[0][0];*/
	    /*REAL(out)[i] = data[i];*/
	    /*REAL(vec)[i] = (&data)[ds][i];*/
	    REAL(vec)[i] = data[i + ds];
	}
	SET_VECTOR_ELT(out, ds, vec);
	/*newdata += ds_cnt;*/
    }

    UNPROTECT(ds_cnt + 1);

    return out;


}




typedef struct _rraInfo {
    char cf[80];
    unsigned long rows;
    unsigned long perRow;
    struct _rraInfo* next;
} rraInfo; 


void freeRraInfo(rraInfo* rraInfoOut) {
    while (rraInfoOut) {
	rraInfo* tmp = rraInfoOut;
	rraInfoOut = rraInfoOut->next;
	free(tmp);

    }
    rraInfoOut = NULL;
}

void printRraInfo(rraInfo* rraInfoIn) {

    rraInfo* rraInfoTmp = rraInfoIn;

    while (rraInfoTmp) {

	printf("rows %d\n", rraInfoTmp->rows);
	printf("perRow %d\n", rraInfoTmp->perRow);
	printf("cf %s\n", rraInfoTmp->cf);

	rraInfoTmp = rraInfoTmp->next;

    }
}

//TODO return rraCnt as a pass-by-ref
rraInfo* getRraInfo (rrd_info_t* rrdInfoIn, int *rraCntOut, unsigned long *stepOut){
    unsigned long step = 0;
    int rraCnt = 0;

    char cfKey[80];
    char rowsKey[80];
    char perRowKey[80];

    printf("sprinting\n");
    sprintf(cfKey, "rra[%d].cf", 0);
    sprintf(rowsKey, "rra[%d].rows", 0);
    sprintf(perRowKey, "rra[%d].pdp_per_row", 0);


    rraInfo* rraInfoOut = malloc(sizeof(rraInfo)); 

    rraInfo *rraInfoTmp = rraInfoOut;



    printf("entering loop\n");
    while(rrdInfoIn) {
	printf("looping\n");

	if (!strcmp(rrdInfoIn->key, "step")){
	    printf("matching step\n");
	    step = rrdInfoIn->value.u_cnt;
	}


	if (!strcmp(rrdInfoIn->key, cfKey)){
	    printf("matching cfkey\n");

	    if (rraCnt > 0) {
		printf("rraCnt > 0\n");

		rraInfoTmp->next = malloc(sizeof(rraInfo));
		rraInfoTmp = rraInfoTmp->next;
		rraInfoTmp->next = NULL;
	    }

	    printf("copying string\n");
	    printf("copying string %s\n", rrdInfoIn->value.u_str);
	    strcpy(rraInfoTmp->cf, rrdInfoIn->value.u_str);
	    printf("copied string\n");

	}

	if (!strcmp(rrdInfoIn->key, rowsKey)){
	    printf("matching rowsKey\n");
	    rraInfoTmp->rows = rrdInfoIn->value.u_cnt;

	}

	if (!strcmp(rrdInfoIn->key, perRowKey)){
	    printf("matching perRowKey\n");
	    rraInfoTmp->perRow = rrdInfoIn->value.u_cnt;
	    rraCnt ++;

	    sprintf(cfKey, "rra[%d].cf", rraCnt);
	    sprintf(rowsKey, "rra[%d].rows", rraCnt);
	    sprintf(perRowKey, "rra[%d].pdp_per_row", rraCnt);

	}


	rrdInfoIn = rrdInfoIn->next;
    }

    if (rraCnt == 0) {
	free(rraInfoOut);
	rraInfoOut = NULL;
    }


    //TODO check if everything looks allright
    *rraCntOut = rraCnt;
    *stepOut = step;

    printf("rraInfoOut %p\n", rraInfoOut);
    return rraInfoOut;
}



SEXP smartImportRRD(SEXP filenameIn){
    printf("we are in\n");
	
//TODO get info
//TODO get first and last
//TODO get identifiers for each rra
//TODO get info for each DS
//TODO get resolution and size for each rra
//TODO get  consolidation function for each rra
//TODO print all stuff and create a list of (cf, res)->ds
//TODO stick to row/column convention


    time_t first;
    time_t last;
    time_t start;
    time_t end;
    unsigned long curStep;
    unsigned long ds_cnt;

    unsigned long step;
    int rraCnt;
    time_t *startAr;

    rraInfo* rraInfoList;

    const char *filename = CHAR(asChar(filenameIn));
    rrd_info_t *rrdInfo;

    printf("calling rrd_last\n");
    last = rrd_last_r(filename);
    printf("calling rrd_info\n");
    rrdInfo = rrd_info_r(filename);



    printf("calling getrrainfo\n");
    rraInfoList = getRraInfo(rrdInfo, &rraCnt, &step);
    printf("called getrrainfo\n");

    
    printf("rraCnt %d step %d last %d rraInfoList %p\n", rraCnt, step, last, rraInfoList);
    printRraInfo(rraInfoList);

    if (rraInfoList == NULL) {
	printf("getting rra info failed\n");
	//handle error

    }


    startAr = malloc(rraCnt * sizeof(time_t));



    //TODO do that for each in a loop
    
    for (int i = 0; i < rraCnt; i++) {
	startAr[i] = rrd_first_r(filename, i);
    }
    

    rraInfo* rraInfoTmp = rraInfoList;

    SEXP out = PROTECT(allocVector(VECSXP, rraCnt));

    int i = 0;

    printf("entering loop\n");
    while (rraInfoTmp) {

	//TODO move declarations out of the loop
	start = startAr[i];
	end = last;
	curStep = step * rraInfoTmp->perRow;
	char **ds_namv;
	//TODO how/when do we deallocate the data? is the data copied by value in R?
	rrd_value_t *data;


	int status = rrd_fetch_r(filename, rraInfoTmp->cf, &start, &end, &curStep, &ds_cnt, &ds_namv, &data);

	printf("size of data %d start %d end %d step %d ds_cnt %d\n", sizeof(data)/sizeof(rrd_value_t), start, end, curStep, ds_cnt);
	fflush(stdout);

	int size = (end - start)/curStep;
	printf("size %d\n", size);

	SEXP rraSexpList = PROTECT(allocVector(VECSXP, ds_cnt));


	SEXP vec;
	//TODO stick to row/columns convention
	for (int ds = 0; ds < ds_cnt; ds++){
	    vec = PROTECT(allocVector(REALSXP, size));
	    for (int j = 0; j < size; j++){

		//REAL(vec)[i] = data[i + ds];
		REAL(vec)[j] = data[ds + j*ds_cnt];
	    }


	  SET_VECTOR_ELT(rraSexpList, ds, vec);
	}

	SET_VECTOR_ELT(out, i, rraSexpList);

	rraInfoTmp = rraInfoTmp->next;

	//TODO push RRA into RRD class/data structure
	i++;
	free(data);
    }

    //TODO unprotect how many times?



    freeRraInfo(rraInfoList);
    free(startAr);
    UNPROTECT(ds_cnt*rraCnt + 1);




    return out;

}








