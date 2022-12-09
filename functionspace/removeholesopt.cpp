#include "../headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removeholesopt(Array2D<int> &src,int &pnumThrshold, int &handlingType, int &neighbourType,int pixelThreshold,int &rows,int &cols)  {
   
    int RemoveCount=0;       
    Mat Pointlabel(rows,cols, CV_8UC1,Scalar::all(255) );  
    auto *pLablel=Pointlabel.data;
     #pragma acc enter data copyin(src,src.matImg[:src.arows][:src.acols],pLablel[:src.arows*src.acols])
     #pragma acc parallel loop collapse(2) default(present) 
        for(int i = 0; i <src.arows ; ++i)  {    
            for(int j = 0; j <src.acols; ++j) {    
                 if(src(i,j)>pixelThreshold){
                   pLablel[i*src.acols+j]=0;
                 }
            }    
        }  
         

    #pragma acc update self(pLablel[:src.arows*src.acols])
    #pragma acc exit data delete(pLablel[:src.arows*src.acols],src,src.matImg[:src.arows][:src.acols])


    vector<vector<Point>> contours; 
    vector<cv::Vec4i> hierarchy; 
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point()); 
    Point p=Point(0,0);
   if (!contours.empty() && !hierarchy.empty())	{
	   for(int z=0;z<contours.size();z++){

			
		        cv::Rect countourposition = cv::boundingRect(Mat(contours.at(z)));      	
		        double area = contourArea(contours.at(z));
			if (area < pnumThrshold) 
			{
                #pragma acc enter data copyin(src,src.matImg[:src.arows][:src.acols],pLablel[:src.arows*src.acols])
                #pragma acc parallel loop  default(present)

				
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) 
				{
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++) 
					{
						if ((int)pLablel[i*+src.acols+j] == 255) 
						{
						    pLablel[i*Pointlabel.cols+j]=2;
                                                    src(i,j)=pixelThreshold;
						}
					}
				}
			}
		}
	      #pragma acc update self(src.matImg[:src.arows][:src.acols])
              #pragma acc exit data delete(pLablel[:src.arows*src.acols],src,src.matImg[:src.arows][:src.acols])
	}

 }
