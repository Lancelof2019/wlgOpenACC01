
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
     #pragma acc enter data copyin(threshMat,threshMat.matImg[:threshMat.arows][:threshMat.acols])
     #pragma acc parallel loop collapse(2) default(present)
	//copyin(antimat,antimat.matImg[:rows][:cols])
	for(int i = 0; i < threshMat.arows; i++) {
            for(int j = 0; j < threshMat.acols; j++) {
                if( threshMat(i,j) == ZERO ) {
                   threshMat(i,j) = ZERO;
                } else {
                    threshMat(i,j) = ONE;
                }
            }
        }
      #pragma acc update self(threshMat.matImg[:threshMat.arows][:threshMat.acols])
      #pragma acc exit data delete(threshMat,threshMat.matImg[:threshMat.arows][:threshMat.acols])
      return threshMat;
    }
