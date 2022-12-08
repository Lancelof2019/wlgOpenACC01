#include "../headerspace/WatershedAlg.h"
using namespace cv;
#define ZERO 0
 void WatershedAlg::removeholesopt(Array2D<int> &src,int &pnumThrshold, int &handlingType, int &neighbourType,int pixelThreshold,int &rows,int &cols)  {
   
  /* 
    int RemoveCount=0;       
    Mat Pointlabel(rows,cols, CV_8UC1,Scalar::all(255) );  
 
 
	#pragma omp parallel for 
        for(int i = 0; i < rows; ++i)  {    
             #pragma omp parallel for 
            for(int j = 0; j < cols; ++j) {    
                 if(src(i,j)>pixelThreshold){
                 Pointlabel.at<uchar>(i,j)=0;
                 }
            }    
        }  


    vector<vector<Point>> contours; 
    vector<cv::Vec4i> hierarchy; 
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point()); 
    Point p=Point(0,0);
   if (!contours.empty() && !hierarchy.empty())	{
           #pragma omp parallel for      
	   for(int z=0;z<contours.size();z++){

			
		//	cv::Rect countourposition = cv::boundingRect(Mat(*itc));
		        cv::Rect countourposition = cv::boundingRect(Mat(contours.at(z)));      	
		//	double area = contourArea(*itc);
		        double area = contourArea(contours.at(z));
		//	int y_ordi=countourposition.y;
		//	int h_ordi=countourposition.height;
		//	int x_ordi=countourposition.x;
		//	int w_ordi=countourposition.width;
		
			if (area < pnumThrshold) 
			{
				//#pragma omp parallel for collapse(2) simd nowait
				
				#pragma omp parallel for
				
				for (int i = countourposition.y; i < countourposition.y + countourposition.height; i++) 
			
			     //  for (int i = y_ordi; i < y_ordi+h_ordi; i++)
				{
					//uchar *output_data = dst.ptr<uchar>(i);
					#pragma omp parallel for
         
					for (int j = countourposition.x; j < countourposition.x + countourposition.width; j++) 
				//	for (int j = x_ordi; j < x_ordi+w_ordi; j++) 
					{
						
						if ((int)Pointlabel.at<uchar>(i,j) == 255) 
						{
						    Pointlabel.at<uchar>(i,j) = 2;
                                                    src(i,j)=pixelThreshold;

						}
					}
				}
			}
			//itc++;
		}
	}


       for(int i=0;i<Pointlabel.rows;i++){
           for(int j=0;j<Pointlabel.cols;j++){
              fout34<<(int)Pointlabel.at<uchar>(i,j)<<",";
             

         }
           fout34<<endl;
      }
           fout34.close();

*/


/*


    for(int i=0;i<contours.size();i++)  
    {  
        //contours[i]代表的是第i个轮廓，contours[i].size()代表的是第i个轮廓上所有的像素点数  
        for(int j=0;j<contours[i].size();j++)   
        {  
            //绘制出contours向量内所有的像素点  
           p=Point(contours[i][j].x,contours[i][j].y);  
            contouroutput.at<uchar>(p)=255;  
        }  
  
        //输出hierarchy向量内容  
       // char ch[256];  
       // sprintf(ch,"%d",i);  
       // string str=ch;  
       // cout<<"向量hierarchy的第" <<str<<" 个元素内容为："<<endl<<hierarchy[i]<<endl<<endl;  
  
        //绘制轮廓  
        drawContours(imageContours,contours,i,Scalar(255),1,8,hierarchy);  
    }  
    
     
    imshow("Point of Contours :contouroutput",contouroutput);   //向量contours内保存的所有轮廓点集  
    waitKey(0);  
    imshow("Contours Image:imageContours",imageContours); //轮廓  
    waitKey(0); 







*/

     /*  for(int i=0;i<dulpPointlabel.rows;i++){
           for(int j=0;j<dulpPointlabel.cols;j++){
              fout33<<(int)dulpPointlabel.at<uchar>(i,j)<<",";
             

         }
           fout33<<endl;
      }
           fout33.close();




       */










  int RemoveCount=0;

    Mat Pointlabel(rows,cols, CV_8UC1,Scalar::all(255) );

/*
     auto  __restrict *srcstart=src.data;
	 auto __restrict *plstart=Pointlabel.data;
	 int srcrows=src.rows;
	 int srccols=src.cols;

        #pragma acc enter data copyin(srcstart[:srcrows*srccols],plstart[:srcrows*srccols],pixelThreshold)
        #pragma acc parallel loop default(present)
		for(int i=0;i<srcrows*srccols;i++){

			if(srcstart[i]>pixelThreshold){
				plstart[i]=0;
			}

		}

		#pragma acc update self(srcstart[:srcrows*srccols],plstart[:srcrows*srccols])


*/


        auto __restrict *plstart=Pointlabel.data;


//        #pragma acc enter data copyin(src,plstart[:rows*cols])
  //      #pragma acc parallel loop default(present)
	  for(int i = 0; i < rows; ++i)  {
            for(int j = 0; j < cols; ++j) {
                 if(src(i,j)>pixelThreshold){
               //  Pointlabel.at<uchar>(i,j)=0;
                 plstart[i*rows+j]=0;

                 }
            }
        }
    //    #pragma acc update self(plstart[:rows*cols])
    vector<vector<Point>> contours;
    vector<cv::Vec4i> hierarchy;
    findContours(Pointlabel,contours,hierarchy,RETR_TREE,CHAIN_APPROX_SIMPLE,Point());
    Mat imageContours=Mat::zeros(Pointlabel.size(),CV_8UC1);
    Mat contouroutput=Mat::zeros(Pointlabel.size(),CV_8UC1);
    Point p=Point(0,0);



   if (!contours.empty() && !hierarchy.empty())
	{
		vector<vector<Point> >::const_iterator itc = contours.begin();

		while (itc != contours.end())
		{

			cv::Rect countourposition = cv::boundingRect(Mat(*itc));//number of countourposition

			double area = contourArea(*itc);
			int countoury=countourposition.y;
			int countourx=countourposition.x;
			int countourybd=countourposition.y + countourposition.height;
			int countourxbd=countourposition.x + countourposition.width;

			if (area < pnumThrshold)
			{

				//


			//	#pragma acc enter data copyin(src,plstart[:rows*cols])
			//	#pragma acc parallel loop collapse(2) default(present)
				for (int i = countoury; i < countourybd; i++)
				{


					for (int j = countourx; j < countourxbd; j++) {
						if((int)plstart[i*countourxbd+j]==255){
						plstart[i*+countourxbd+j]=2;
					        src(i,j)=pixelThreshold;

						}

					}
				}
			//	#pragma acc update self(src,plstart[:rows*cols])
			//	#pragma acc exit data delete(src,plstart[:rows*cols])
			}//if
			itc++;
		}//while
	}//if

 }

 
