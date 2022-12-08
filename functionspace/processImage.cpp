#include "../headerspace/WatershedAlg.h"
using namespace cv;
void WatershedAlg::processImage(Mat &image,Mat &duplImage,Array2D<int> &threshmat0,Array2D<int> & markers,Array2D<bool> &visArr,Array1D &plotx,Array1D &ploty,Array2D<int>& plots,Array2D<bool> &inprioq,Array2D<int> &markerMap,Array2D<int> &temp,Array2D<int>& nextSet,int**** arr4D,int**** mat4D,Bool2D &visBool,Array2D<int>&shouldBeZeroImage,Array2D<int>&threshMat,Array2D<int>&antiMat,Array2D<int>&distanMat) {
     
       	image = makeImageGrayScale(image);


     //  vector< vector<int> > erosionTargetThree{{1, 1, 1}, {1, 1, 1}, {1, 1, 1}, };
      /* int erosionTree[3][3]={
	        {1, 1, 1}, 
		{1, 1, 1}, 
		{1, 1, 1}
        };
     */
       int **erosionTree=new int*[3];

       for(int i=0;i<3;i++){
            erosionTree[i]=new int[3];
	    for(int j=0;j<3;j++){
               erosionTree[i][j]=1;

	    }
         }
      
       


       int trows=3;
       int tcols=3;
       image = erosion(image, erosionTree,trows,tcols,shouldBeZeroImage);

       // int** __restrict threshmat;
        
      //  #pragma acc enter data copyin(threshmat0,threshmat0.matImg[:threshmat0.arows][:threshmat0.acols]) 
       threshMat=thresholdMeasure(image,threshmat0);

       //int** __restrict antimat;

       antiMat=antiInverseImage(threshMat,image.rows,image.cols);

	//int** __restrict matimage;
       distanMat=distanceTransform(threshmat0,markers,image.rows,image.cols,plots,visArr,plotx,ploty);
       
       image = watershed(threshmat0, markers,duplImage,image.rows,image.cols,inprioq,markerMap,temp,nextSet);
      // cv::imshow("watershed result",image);
      // cv::waitKey(0);

    }
