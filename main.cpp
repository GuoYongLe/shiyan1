#include "cv.h"
#include "highgui.h"
#include <math.h>
#include <string.h>
#include <iostream>

int thresh = 50;
IplImage* img =NULL;
IplImage* img0 = NULL;
IplImage * pImg8u=NULL;

CvMemStorage* storage =NULL;
const char * wndname = "Բ�μ��  Demo";
char* names[] = { "aa.png","bb.png","pic8.png","pic7.png","pic3.png","pic9.png","pic10.png",    
"pic11.png","pic12.png","pic13.png","pic14.png",0};

void HoughCircle()
{

 CvSeq * circles=NULL;
 pImg8u=cvCreateImage(cvGetSize(img),8,1);
 CvMemStorage* storage = cvCreateMemStorage(0);
 cvCvtColor(img,pImg8u,CV_BGR2GRAY);
 //�����cvSmoothһ�£��ٵ���cvHoughCircles
 cvSmooth(pImg8u,pImg8u,CV_GAUSSIAN,7,7);
 circles=cvHoughCircles(pImg8u,storage,CV_HOUGH_GRADIENT,
  2,   //��С�ֱ��ʣ�Ӧ��>=1
  pImg8u->height/4,   //�ò��������㷨���������ֵ�������ͬԲ֮�����С����
  140,   //����Canny�ı�Ե��ֵ���ޣ����ޱ���Ϊ���޵�һ��
  118,    //�ۼ����ķ�ֵ
  2,  //��СԲ�뾶 
  120  //���Բ�뾶
  );

 int k;
 for (k=0;k<circles->total;k++)
 {
  float *p=(float*)cvGetSeqElem(circles,k);
  //cvCircle( img, cvPoint(cvRound(p[0]),cvRound(p[1])), 3, CV_RGB(0,255,0), -1, 8, 0 );
  cvCircle(img,cvPoint(cvRound(p[0]),cvRound(p[1])),cvRound(p[2]),CV_RGB(0,0,0),3,CV_AA,0);
 }

 cvClearMemStorage( storage );

}

int main(int argc, char** argv)
{
 int i, c;
 // create memory storage that will contain all the dynamic data


 for( i = 0; names[i] != 0; i++ )
 {
  img0 = cvLoadImage( names[i], 1 );
  if( !img0 )
  {
   cout<<"��������"<<names[i]<<"������һ��ͼƬ"<<endl;
   continue;
  }
  img = cvCloneImage( img0 );

  HoughCircle();
  cvNamedWindow( wndname, 1 );
  cvShowImage(wndname,img);

  c = cvWaitKey(0);

  cvReleaseImage( &img );
  cvReleaseImage( &img0 );
  cvReleaseImage(&pImg8u);


  if( (char)c == 27 )
   break;
 }

 cvDestroyWindow( wndname );
 return 0;
}
