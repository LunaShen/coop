#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "GetFile.h"
#include<iostream>
using namespace cv;
using namespace std;

class Histogram{
public:
	double H[8][8*128];
	int state;
};

int main(int argc, char* argv[])
{
    char filename[1024];
    GetFile(filename, 1024);
    if (filename[0] == '\0')
    {
        fprintf(stderr, "Please select a file\n");
        return EXIT_FAILURE;
    }
    
    VideoCapture vc = VideoCapture(filename);

    Mat image_read;
	Mat image_resize;
	

	int frameNum = vc.get(CV_CAP_PROP_FRAME_COUNT);
	//image_resize =  Mat(32,32, CV_32F, 0.0);
	//cout<<frameNum<<endl;
    // Create a window
    namedWindow("Display", WINDOW_NORMAL);
	double** allI = new double* [frameNum];
	double** allIROW = new double* [frameNum];
	for(int i=0;i<frameNum;i++){
		allI[i] = new double[128];
		allIROW[i] = new double[128];
	}

	int currentFrame = 0;
	Histogram HA;
	
	HA.state = 0;
	Histogram HB;
	
	HB.state = 0;

	Histogram HAROW;
	Histogram HBROW;



    while (true)
    {
        // Get the image from the video file
        vc.read(image_read);

        // Stop if there are no more frames in the video
        if (image_read.empty()) break;

		resize(image_read, image_resize, Size(128,128));

		
		if(HA.state==0){
			for(int i=0;i<8;i++){
				for(int j=0;j<(8*128);j++){
					HA.H[i][j] = 0;
					HAROW.H[i][j] = 0;
				}
			}
			// change the pixel intensity
			//cout<<image_resize.size().width<<endl;
			//cout<<image_resize.size().height<<endl;
			// Column
			for (int col = 0; col < image_resize.size().width; col++){
				for (int row = 0; row < image_resize.size().height; row++) {	
						
					Vec3b bgrPixel = image_resize.at<Vec3b>(row, col);
					double bgr_b = bgrPixel[0];
					double bgr_g = bgrPixel[1];
					double bgr_r = bgrPixel[2];
					double r;
					double g;
					if(bgr_b==0 && bgr_g==0 && bgr_r==0){
						r=0;
						g=0;
					}
					else{
						r = bgr_r/(bgr_r+bgr_g+bgr_b);
						g = bgr_g/(bgr_r+bgr_g+bgr_b);
					}
				
					int r_temp = r*8;
					int g_temp = g*8;

					for(int i=0;i<8;i++){
						for(int j=0;j<8;j++){
							if(i==r_temp && j==g_temp){
								HA.H[i][j+8*col] ++;
							}
						}
					}
					
				
				}
				//cout<<"counter is "<<counter<<endl;
				for(int m=0; m<8; m++){
					for (int n=0; n<8; n++) {
						//cout<<HA.H[m][n+8*col]<<endl;
						HA.H[m][n+8*col] = HA.H[m][n+8*col]/128.0;
						//cout<<HA.H[m][n+8*col]<<endl;
						
					}
				}
				//cout<<"------------------------------------------------------------------------"<<endl;
				
			}

			// Row
			for (int row = 0; row < image_resize.size().width; row++){
				for (int col = 0; col < image_resize.size().height; col++) {	
						
					Vec3b bgrPixel = image_resize.at<Vec3b>(row, col);
					double bgr_b = bgrPixel[0];
					double bgr_g = bgrPixel[1];
					double bgr_r = bgrPixel[2];
					double r;
					double g;
					if(bgr_b==0 && bgr_g==0 && bgr_r==0){
						r=0;
						g=0;
					}
					else{
						r = bgr_r/(bgr_r+bgr_g+bgr_b);
						g = bgr_g/(bgr_r+bgr_g+bgr_b);
					}
				
					int r_temp = r*8;
					int g_temp = g*8;

					for(int i=0;i<8;i++){
						for(int j=0;j<8;j++){
							if(i==r_temp && j==g_temp){
								HAROW.H[i][j+8*row] ++;
							}
						}
					}
					
				
				}
				//cout<<"counter is "<<counter<<endl;
				for(int m=0; m<8; m++){
					for (int n=0; n<8; n++) {
						//cout<<HA.H[m][n+8*col]<<endl;
						HAROW.H[m][n+8*row] = HAROW.H[m][n+8*row]/128.0;
						//cout<<HA.H[m][n+8*col]<<endl;
						
					}
				}
				//cout<<"------------------------------------------------------------------------"<<endl;
				
			}
			
			HA.state=2;
		}
		else if(HB.state==0){
			for(int i=0;i<8;i++){
				for(int j=0;j<(8*128);j++){
					HB.H[i][j] = 0;
					HBROW.H[i][j] = 0;
				}
			}

			// column
			for (int col = 0; col < image_resize.size().width; col++){
				for (int row = 0; row < image_resize.size().height; row++) {	
						
					Vec3b bgrPixel = image_resize.at<Vec3b>(row, col);
					double bgr_b = bgrPixel[0];
					double bgr_g = bgrPixel[1];
					double bgr_r = bgrPixel[2];
					double r;
					double g;
					if(bgr_b==0 && bgr_g==0 && bgr_r==0){
						r=0;
						g=0;
					}
					else{
						r = bgr_r/(bgr_r+bgr_g+bgr_b);
						g = bgr_g/(bgr_r+bgr_g+bgr_b);
					}
				
					int r_temp = r*8;
					int g_temp = g*8;

					for(int i=0;i<8;i++){
						for(int j=0;j<8;j++){
							if(i==r_temp && j==g_temp){
								HB.H[i][j+8*col] ++;
							}
						}
					}	
				}
				for(int m=0; m<8; m++){
					for (int n=0; n<8; n++) {
						HB.H[m][n+8*col] = HB.H[m][n+8*col]/128.0;
						//cout<<HB.H[m][n+8*col]<<endl;
					}
				}
			}

			// row
			for (int row = 0; row < image_resize.size().width; row++){
				for (int col = 0; col < image_resize.size().height; col++) {	
						
					Vec3b bgrPixel = image_resize.at<Vec3b>(row, col);
					double bgr_b = bgrPixel[0];
					double bgr_g = bgrPixel[1];
					double bgr_r = bgrPixel[2];
					double r;
					double g;
					if(bgr_b==0 && bgr_g==0 && bgr_r==0){
						r=0;
						g=0;
					}
					else{
						r = bgr_r/(bgr_r+bgr_g+bgr_b);
						g = bgr_g/(bgr_r+bgr_g+bgr_b);
					}
				
					int r_temp = r*8;
					int g_temp = g*8;

					for(int i=0;i<8;i++){
						for(int j=0;j<8;j++){
							if(i==r_temp && j==g_temp){
								HBROW.H[i][j+8*row] ++;
							}
						}
					}	
				}
				for(int m=0; m<8; m++){
					for (int n=0; n<8; n++) {
						HBROW.H[m][n+8*row] = HBROW.H[m][n+8*row]/128.0;
						//cout<<HB.H[m][n+8*col]<<endl;
					}
				}
			}

			HB.state=2;
		}
        //Use H value
		if(HA.state==2 && HB.state==0){
			HA.state=1;
			continue;
		}
		else if(HA.state==1 && HB.state==2){
			for(int i=0;i<128;i++){
				allI[currentFrame][i]=0;
				allIROW[currentFrame][i]=0;
			}
			// col loop
			for(int k=0;k<128;k++){
				for(int i=0;i<8;i++){
					for(int j=0;j<8;j++){
						// column find min 
						if(HA.H[i][8*k+j]<=HB.H[i][8*k+j]){
							allI[currentFrame][k]=allI[currentFrame][k]+HA.H[i][8*k+j];
						}
						else{
							allI[currentFrame][k]=allI[currentFrame][k]+HB.H[i][8*k+j];
						}

						// row find min 
						if(HAROW.H[i][8*k+j]<=HBROW.H[i][8*k+j]){
							allIROW[currentFrame][k]=allIROW[currentFrame][k]+HAROW.H[i][8*k+j];
						}
						else{
							allIROW[currentFrame][k]=allIROW[currentFrame][k]+HBROW.H[i][8*k+j];
						}
					}
				}
			}
			HA.state=0;
			HB.state=1;
		}
		else if(HA.state==2 && HB.state==1){
			for(int i=0;i<128;i++){
				allI[currentFrame][i]=0;
				allIROW[currentFrame][i]=0;
			}
			// col loop
			for(int k=0;k<128;k++){
				for(int i=0;i<8;i++){
					for(int j=0;j<8;j++){
						// col find min
						if(HA.H[i][8*k+j]<=HB.H[i][8*k+j]){
							allI[currentFrame][k]=allI[currentFrame][k]+HA.H[i][8*k+j];
						}
						else{
							allI[currentFrame][k]=allI[currentFrame][k]+HB.H[i][8*k+j];
						}
						// row find min
						if(HAROW.H[i][8*k+j]<=HBROW.H[i][8*k+j]){
							allIROW[currentFrame][k]=allIROW[currentFrame][k]+HAROW.H[i][8*k+j];
						}
						else{
							allIROW[currentFrame][k]=allIROW[currentFrame][k]+HBROW.H[i][8*k+j];
						}
					}
				}
			}
			HA.state=1;
			HB.state=0;
		}

		currentFrame++;

        // Display the image 
        imshow("Display", image_resize);

        // Sleep for 30 milliseconds. Note: This function is the only method in 
        // HighGUI that can fetch and handle events,  so it needs to be called 
        // periodically for normal event processing unless HighGUI is used within 
        // an environment that takes care of event processing.
        int c = waitKey(30);

        // Quit if any key is pressed
        if (c != -1) break;
    }

	int startFrame[10];
	int startFrameState = 0;
	int endFrame[10];
	int transNum = 0;

	Mat image_output =  Mat(128,currentFrame, CV_32F, 0.0);
	for(int i=0;i<(currentFrame);i++){
		for(int j=0;j<128;j++){
			//cout<<"test 222222222222222222222222222222222222222"<<endl;
			//image_output.row(j).col(i) = 0;
			//image_output.row(j).col(i) = allI[i][j];
			/*if(allI[i][j]<0.4){
				cout<<allI[i][j]*255<<endl;
			}*/
			if(i>=1){
				if(allI[i][j]<0.5 && allI[i-1][j]>0.5){
				image_output.row(j).col(i) = 0;
				if(startFrameState == 0){
					
					startFrame[transNum] = i;
					endFrame[transNum] = i;

					startFrameState = 1;
				}
				else{
					endFrame[transNum] = i;
				}
				}
				else{
					image_output.row(j).col(i) = 1;
					if(i>(endFrame[transNum]+2) && (startFrameState == 1)){
						startFrameState = 0;
						transNum++;
					}
				}
			}
			else{
				if(allI[i][j]<0.5){
				image_output.row(j).col(i) = 0;
				if(startFrameState == 0){
					
					startFrame[transNum] = i;
					endFrame[transNum] = i;

					startFrameState = 1;
				}
				else{
					endFrame[transNum] = i;
				}
				}
				else{
					image_output.row(j).col(i) = 1;
					if(i>(endFrame[transNum]+2) && (startFrameState == 1)){
						startFrameState = 0;
						transNum++;
					}
				}
			}
			
		}
	}


	//ROW
	int startFrameROW[10];
	int startFrameStateROW = 0;
	int endFrameROW[10];
	int transNumROW = 0;

	Mat image_outputROW =  Mat(128,currentFrame, CV_32F, 0.0);
	for(int i=0;i<(currentFrame);i++){
		for(int j=0;j<128;j++){
			//cout<<"test 222222222222222222222222222222222222222"<<endl;
			//image_output.row(j).col(i) = 0;
			//image_output.row(j).col(i) = allI[i][j];
			/*if(allI[i][j]<0.4){
				cout<<allI[i][j]*255<<endl;
			}*/
			if(i>=1){
				if(allIROW[i][j]<0.5 && allIROW[i-1][j]>0.5){
					image_outputROW.row(j).col(i) = 0;
					if(startFrameStateROW == 0){
					
						startFrameROW[transNumROW] = i;
						endFrameROW[transNumROW] = i;

						startFrameStateROW = 1;
					}
					else{
						endFrameROW[transNumROW] = i;
					}
				}
				else{
					image_outputROW.row(j).col(i) = 1;
					if(i>(endFrameROW[transNumROW]+2) && (startFrameStateROW == 1)){
						startFrameStateROW = 0;
						transNumROW++;
					}
				}
			}
			else{
				if(allIROW[i][j]<0.5){
					image_outputROW.row(j).col(i) = 0;
					if(startFrameStateROW == 0){
						
						startFrameROW[transNumROW] = i;
						endFrameROW[transNumROW] = i;

						startFrameStateROW = 1;
					}
					else{
						endFrameROW[transNumROW] = i;
					}
				}
				else{
					image_outputROW.row(j).col(i) = 1;
					if(i>(endFrameROW[transNumROW]+2) && (startFrameStateROW == 1)){
						startFrameStateROW = 0;
						transNumROW++;
					}
				}
			}
			
		}
	}
	//result
	//cout<<"test 33333333333333333333333333333333333333333333"<<endl;
	namedWindow("Result Of COLUMN", WINDOW_NORMAL);
	imshow("Result Of COLUMN",image_output);

	namedWindow("Result Of ROW", WINDOW_NORMAL);
	imshow("Result Of ROW",image_outputROW);
	int coutState = 0;
	for(int i=0;i<transNum;i++){
		if((startFrame[i]+1)==(endFrame[i]+1)){
			cout<<"This transmission is an abrupt cut or a noise, not a wipe. At "<<startFrame[i]+1<<"frame"<<endl;
			cout<<"---------------------------------------------------------------------"<<endl;
			coutState = 1;
			continue;
		}
		else{
			cout<<"The HORIZONTAL wipe transmission starts from:"<<startFrame[i]+1<<"frame"<<endl;
			cout<<"The HORIZONTAL wipe transmission ends at:"<<endFrame[i]+1<<"frame"<<endl;
		
			cout<<"---------------------------------------------------------------------"<<endl;
		}
		
	}

	for(int i=0;i<transNumROW;i++){
		if((startFrameROW[i]+1)==(endFrameROW[i]+1) && coutState == 1){
			continue;
		}
		else if((startFrameROW[i]+1)==(endFrameROW[i]+1)){
			cout<<"This transmission is an abrupt cut  or a noise, not a wipe. At "<<startFrameROW[i]+1<<"frame"<<endl;
			cout<<"---------------------------------------------------------------------"<<endl;
			continue;
		}
		else{
			cout<<"The VERTICAL wipe transmission starts from:"<<startFrameROW[i]+1<<"frame"<<endl;
			cout<<"The VERTICAL wipe transmission ends at:"<<endFrameROW[i]+1<<"frame"<<endl;
			cout<<"---------------------------------------------------------------------"<<endl;
		}
		
	}
	
	int ddd = waitKey(1000000);


	return 0;

}