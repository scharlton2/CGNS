/*
   Sample CGIO test program to build files illustrated
   in example database figure.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#ifdef _WIN32
#include <io.h>
#define unlink _unlink
#else
#include <unistd.h>
#endif

#include "cgns_io.h"
#include "cgnslib.h"

void print_child_list(int cgio_num,double node_id);

#define DIM0 10
#define NUMBER_OF_STRING DIM0
#define MAX_STRING_SIZE 5

int main (int argc, char **argv)
{
  /* --- Node header character strings */
  char label[CGIO_MAX_LABEL_LENGTH+1];
  char label_r[CGIO_MAX_LABEL_LENGTH+1];
  char data_type[CGIO_MAX_DATATYPE_LENGTH+1];
  char data_type_r[CGIO_MAX_DATATYPE_LENGTH+1];

  /* --- Database identifier */
  int cgio_num;

  /* --- Node id variables */
  double root_id,parent_id,child_id,tmp_id;

  /* --- Data to be stored in database */
  cgsize_t c1_dimensions = 1;
  cgsize_t mt_dimensions[1] = {DIM0};
  cgsize_t i4_dimensions[1] = {DIM0};
  cgsize_t i8_dimensions[1] = {DIM0};
  cgsize_t u4_dimensions[1] = {DIM0};
  cgsize_t u8_dimensions[1] = {DIM0};
  cgsize_t r4_dimensions[1] = {DIM0};
  cgsize_t r8_dimensions[1] = {DIM0};
  cgsize_t b1_dimensions[1] = {DIM0};

  char               c1[1] = "C";
  int                i4[DIM0];
  long long          i8[DIM0];
  unsigned int       u4[DIM0];
  unsigned long long u8[DIM0];
  float              r4[DIM0];
  double             r8[DIM0];
  unsigned char      b1[DIM0];

  /* Read variables */
  cgsize_t c1_dimensions_r[1];
  cgsize_t mt_dimensions_r[1];
  cgsize_t i4_dimensions_r[1];
  cgsize_t i8_dimensions_r[1];
  cgsize_t u4_dimensions_r[1];
  cgsize_t u8_dimensions_r[1];
  cgsize_t r4_dimensions_r[1];
  cgsize_t r8_dimensions_r[1];
  cgsize_t b1_dimensions_r[1];

  char               c1_r[1];
  int                i4_r[DIM0];
  long long          i8_r[DIM0];
  unsigned int       u4_r[DIM0];
  unsigned long long u8_r[DIM0];
  float              r4_r[DIM0];
  double             r8_r[DIM0];
  unsigned char      b1_r[DIM0];


  /* --- miscellaneous variables */
  int i, j, n;
  int error_state = 1;
  int num_dims,num_dims_r;
  int file_type, file_type_r;
  int write_file = 0;

  for (n = 1; n < argc; n++) {
    i = 0;
    if (argv[n][i] == '-') i++;
    if (argv[n][i] == 'w' || argv[n][i] == 'W')
      write_file = 1;
  }

  for (i = 0; i < DIM0; i++) {
    i4[i] = (pow(2,31) - 1) - DIM0 + (int)i; 
    u4[i] = (pow(2,32) - 1) - DIM0 + (unsigned int)i;
    i8[i] = (pow(2,50) - 1) - DIM0 + (long long)(i); 
    u8[i] = (pow(2,51) - 1) - DIM0 + (unsigned long long)(i);
    r4[i] = (float)(i)*0.1;
    r8[i] = (double)(i)*0.1;
    b1[i] = 0;
    b1[i] |= (i & 0x03) << 2;
    b1[i] |= (i & 0x03 ) << 6;
  }

  /* ------ begin source code ----- */

  /* --- set database error flag to abort on error */
   cgio_error_abort(error_state);

  /* -------- build file: file_two.cgio ---------- */

   if(cgio_is_supported(CGIO_FILE_HDF5) == 0) {
     file_type = CGIO_FILE_HDF5;
   } else {
     return 0;
   }

   /* option to generate a reference file to be stored in the "data" directory */

   if(write_file) {

     if( cgio_open_file("cgio_hdf.cgio",CGIO_MODE_WRITE,file_type,&cgio_num))
       cg_error_exit();

     if( cgio_get_root_id(cgio_num,&root_id))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"C1",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"character data"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"C1", 1, &c1_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,c1))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"MT",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"empty data"))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"I4",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"32-bit integer"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"I4", 1, i4_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,i4))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"I8",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"64-bit integer"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"I8", 1, i8_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,i8))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"U4",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"32-bit unsigned integer"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"U4", 1, u4_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,u4))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"U8",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"64-bit unsigned integer"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"U8", 1, u8_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,u8))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"R4",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"32-bit real"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"r4", 1, r4_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,r4))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"R8",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"64-bit real"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"r8", 1, r8_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,r8))
       cg_error_exit();

     if( cgio_create_node(cgio_num,root_id,"B1",&tmp_id))
       cg_error_exit();
     if( cgio_set_label(cgio_num,tmp_id,"Byte data"))
       cg_error_exit();
     if( cgio_set_dimensions(cgio_num,tmp_id,"B1", 1, b1_dimensions))
       cg_error_exit();
     if( cgio_write_all_data(cgio_num,tmp_id,b1))
       cg_error_exit();

     /* ----------------- finished building file ------------- */
     if( cgio_close_file(cgio_num))
       cg_error_exit();
   
   }

   /* Reading portion of test */

   if( cgio_open_file("cgio_hdf.cgio",CGIO_MODE_READ,file_type,&cgio_num)) {
     printf("FAILED to open cgio_hdf.cgio \n");
     cg_error_exit();
   }

   if( cgio_get_root_id(cgio_num,&root_id))
     cg_error_exit();

  /* ------------- verify written data  --------------- */
   if( cgio_get_node_id(cgio_num,root_id,"I4",&tmp_id) )
     cg_error_exit();
   if( cgio_get_label(cgio_num,tmp_id,label_r) )
     cg_error_exit();
   if( cgio_get_data_type(cgio_num,tmp_id,data_type_r) )
     cg_error_exit();
   if( cgio_get_dimensions(cgio_num,tmp_id,&num_dims_r,i4_dimensions_r) )
     cg_error_exit();
   if( cgio_read_all_data_type(cgio_num,tmp_id,"I4",i4_r) )
     cg_error_exit();
   if(strcmp(label_r,"32-bit integer") != 0)
     cg_error_exit();
   if(strcmp(data_type_r,"I4") != 0)
     cg_error_exit();
   if(num_dims_r != 1)
     cg_error_exit();
   if(i4_dimensions_r[0] != DIM0)
     cg_error_exit();
   for (i=0; i< DIM0; i++) {
     if (i4_r[i] != i4[i])
       cg_error_exit();
   }

   if( cgio_get_node_id(cgio_num,root_id,"I8",&tmp_id) )
     cg_error_exit();
   if( cgio_get_label(cgio_num,tmp_id,label_r) )
     cg_error_exit();
   if( cgio_get_data_type(cgio_num,tmp_id,data_type_r) )
     cg_error_exit();
   if( cgio_get_dimensions(cgio_num,tmp_id,&num_dims_r,i8_dimensions_r) )
     cg_error_exit();
   if( cgio_read_all_data_type(cgio_num,tmp_id,"I8",i8_r) )
     cg_error_exit();
   if(strcmp(label_r,"64-bit integer") != 0)
     cg_error_exit();
   if(strcmp(data_type_r,"I8") != 0)
     cg_error_exit();
   if(num_dims_r != 1)
     cg_error_exit();
   if(i8_dimensions_r[0] != DIM0)
     cg_error_exit();
   for (i=0; i< DIM0; i++) {
     if (i8_r[i] != i8[i])
       cg_error_exit();
   }

   if( cgio_get_node_id(cgio_num,root_id,"U4",&tmp_id) )
     cg_error_exit();
   if( cgio_get_label(cgio_num,tmp_id,label_r) )
     cg_error_exit();
   if( cgio_get_data_type(cgio_num,tmp_id,data_type_r) )
     cg_error_exit();
   if( cgio_get_dimensions(cgio_num,tmp_id,&num_dims_r,u4_dimensions_r) )
     cg_error_exit();
   if( cgio_read_all_data_type(cgio_num,tmp_id,"U4",u4_r) )
     cg_error_exit();
   if(strcmp(label_r,"32-bit unsigned integer") != 0)
     cg_error_exit();
   if(strcmp(data_type_r,"U4") != 0)
     cg_error_exit();
   if(num_dims_r != 1)
     cg_error_exit();
   if(u4_dimensions_r[0] != DIM0)
     cg_error_exit();
   for (i=0; i< DIM0; i++) {
     if (u4_r[i] != u4[i])
       cg_error_exit();
   }

   if( cgio_get_node_id(cgio_num,root_id,"U8",&tmp_id) )
     cg_error_exit();
   if( cgio_get_label(cgio_num,tmp_id,label_r) )
     cg_error_exit();
   if( cgio_get_data_type(cgio_num,tmp_id,data_type_r) )
     cg_error_exit();
   if( cgio_get_dimensions(cgio_num,tmp_id,&num_dims_r,u8_dimensions_r) )
     cg_error_exit();
   if( cgio_read_all_data_type(cgio_num,tmp_id,"U8",u8_r) )
     cg_error_exit();
   if(strcmp(label_r,"64-bit unsigned integer") != 0)
     cg_error_exit();
   if(strcmp(data_type_r,"U8") != 0)
     cg_error_exit();
   if(num_dims_r != 1)
     cg_error_exit();
   if(u8_dimensions_r[0] != DIM0)
     cg_error_exit();
   for (i=0; i< DIM0; i++) {
     if (u8_r[i] != u8[i])
       cg_error_exit();
   }

   if( cgio_get_node_id(cgio_num,root_id,"B1",&tmp_id) )
     cg_error_exit();
   if( cgio_get_label(cgio_num,tmp_id,label_r) )
     cg_error_exit();
   if( cgio_get_data_type(cgio_num,tmp_id,data_type_r) )
     cg_error_exit();
   if( cgio_get_dimensions(cgio_num,tmp_id,&num_dims_r,b1_dimensions_r) )
     cg_error_exit();
   if( cgio_read_all_data_type(cgio_num,tmp_id,"B1",b1_r) )
     cg_error_exit();
   if(strcmp(label_r,"Byte data") != 0)
     cg_error_exit();
   if(strcmp(data_type_r,"B1") != 0)
     cg_error_exit();
   if(num_dims_r != 1)
     cg_error_exit();
   if(b1_dimensions_r[0] != DIM0)
     cg_error_exit();
   for (i=0; i< DIM0; i++) {
     if (b1_r[i] != b1[i])
       cg_error_exit();
   }

   if( cgio_get_node_id(cgio_num,root_id,"C1",&tmp_id) )
     cg_error_exit();
   if( cgio_get_label(cgio_num,tmp_id,label_r) )
     cg_error_exit();
   if( cgio_get_data_type(cgio_num,tmp_id,data_type_r) )
     cg_error_exit();
   if( cgio_get_dimensions(cgio_num,tmp_id,&num_dims_r,c1_dimensions_r) )
     cg_error_exit();
   if( cgio_read_all_data_type(cgio_num,tmp_id,"C1",c1_r) )
     cg_error_exit();
   if(strcmp(label_r,"character data") != 0)
     cg_error_exit();
   if(strcmp(data_type_r,"C1") != 0)
     cg_error_exit();
   if(num_dims_r != 1)
     cg_error_exit();
   if(c1_dimensions_r[0] != 1)
     cg_error_exit();
   if (strncmp(c1_r, c1, 1) != 0)
     cg_error_exit();

   if( cgio_close_file(cgio_num))
       cg_error_exit();

   return 0;
}


