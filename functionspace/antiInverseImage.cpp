
#include "../headerspace/WatershedAlg.h"
using namespace cv;

Array2D<int> &WatershedAlg::antiInverseImage(Array2D<int>&threshMat,int &rows,int &cols) {
     
      //clock_t start2,end2;
     // double start3,end3;
      //start2=clock();
     // start3=omp_get_wtime();
     //
     //
     //    auto *startImg=image.data;
    // int imgrows=image.rows;
    // int imgcols=image.cols;
     #pragma acc enter data copyin(threshMat,threshMat.matImg[:rows][:cols])
     #pragma acc parallel loop collapse(2) default(present)//copyin(antimat,antimat.matImg[:rows][:cols])
	for(int i = 0; i < rows; i++) {
            for(int j = 0; j < cols; j++) {
                if( threshMat(i,j) == ZERO ) {
                   threshMat(i,j) = ZERO;
                } else {
                    threshMat(i,j) = ONE;
                }
            }
        }
      #pragma acc update self(threshMat.matImg[:rows][:cols])
      #pragma acc exit data delete(threshMat.matImg[:rows][:cols])
      return threshMat;
    }
