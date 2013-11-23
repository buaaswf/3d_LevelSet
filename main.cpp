#include "vol_math_LevelSet.h"

#include "test.h"
#include <iostream>
#include <crtdbg.h> 
#include "CImg.h" 
#include "ThreeDim_LevelSet.h"
#include "Filter.h"

using namespace cimg_library;
using namespace std;




int main(int argc,char **argv)
{
	char *pt="single_well";
	int l=512,m=512,n=489,l1=0,l2=0,iter_outer=150;
	RawImage test;
	//unsigned char * indata=new unsigned char [l*m*n];
	signed int * indata=new signed int  [l*m*n];
	//Raw *inputeasy=new Raw(l,m,n);
	Raw *initial=new Raw(l,m,n);
	//for (int i=0;i<l;i++)
	//{
	//	for (int j=0;j<m;j++)
	//	{
	//		for (int k=0;k<n;k++)
	//		{
	//			if (i>l1 && j>l1 && k>l1 && i<l2 && j<l2 && k<l2)
	//			{
	//				inputeasy->put(i,j,k,20.0);

	//			}
	//			else inputeasy->put(i,j,k,0);

	//		}
	//	}
	//}
	//test.readImage(indata,"E:\\geo\\lobster.raw",301*324*56);

	//test.readImage(indata,"E:\\volume\\cthead-8bit\\cthead-8bit.raw",256*256*99);
	//test.readImage(indata,"E:\\volume\\little\\little.raw",256*256*26);
	test.readImagesi(indata,"E:\\volume\\clean\\WI_3032_P_iso_clean.raw",512*512*489);
	float *inputo=new float[l*m*n];
	for (int i = 0; i < l*m*n; i++)
	{
		inputo[i]=(float) indata[i];
	}

	Raw *input=new Raw(l,m,n,inputo);
	int width=10;
	//for (int i=0;i<l;i++)
	//{
	//	for (int j=0;j<m;j++)
	//	{
	//		for (int k=0;k<n;k++)
	//		{

	//			if (i>l1+width && j>l1+width && k>l1+width && i<l2-width && j<l2-width && k<l2-width)
	//			{
	//				initial->put(i,j,k,-2.0);
	//			} 
	//			else if (i<l1+width || j<l1+width || k < l1+width || i>l2-width || j>l2-width || k> l2-width)
	//			{
	//				initial->put(i,j,k,2.0);
	//			}
	//			else {
	//				initial->put(i,j,k,-2.0);
	//			}

	//		}
	//	}
	//}
	//int x1=84,x2=123,y1=118,y2=180,z1=19,z2=24; //test for little data
	int x1=257,x2=299,y1=345,y2=358,z1=346,z2=336; //test for colon data
	for (int i=0;i<l;i++)
	{
		for (int j=0;j<m;j++)
		{
			for (int k=0;k<n;k++)
			{

				if (i>x1 && j>y1 && k>z1 && i<x2 && j<y2 && k<z2)
				{
					initial->put(i,j,k,-2.0);
				} 
				else if (i<x1|| j<y1 || k < z1 || i>x2 || j>y2 || k> z2)
				{
					initial->put(i,j,k,2.0);
				}
				else {
					initial->put(i,j,k,-2.0);
				}

			}
		}
	}
		RawImage *write=new RawImage();
	
		ThreeDim_LevelSet *ls=new ThreeDim_LevelSet();
		//IShowraw(*input,argc,argv);
	ls->initialg(*input);	
	ls->minimal_surface(*initial,*input,5.0,0.1,-3,1.5,1,iter_outer,pt);
	IShowraw(*initial,argc,argv);
	test.writeImage(*initial);
	system("pause");
	return 0;
}