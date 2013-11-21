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
	int l=256,m=256,n=99,l1=0,l2=0,iter_outer=100;
	RawImage test;
	unsigned char * indata=new unsigned char [l*m*n];

	//for (int i=0;i<l;i++)
	//{
	//	for (int j=0;j<m;j++)
	//	{
	//		for (int k=0;k<n;k++)
	//		{
	//			if (i>l1&&j>l1&&k>l1&&i<l2&&j<l2&&k<l2)
	//			{
	//				input->put(i,j,k,2.0);

	//			}
	//			else input->put(i,j,k,-2.0);

	//		}
	//	}
	//}
	//test.readImage(indata,"E:\\geo\\lobster.raw",301*324*56);

		test.readImage(indata,"E:\\volume\\cthead-8bit\\cthead-8bit.raw",256*256*99);

	
	double *inputo=new double[l*m*n];
	for (int i = 0; i < l*m*n; i++)
	{
		inputo[i]=(double) indata[i];
	}
	Raw *initial=new Raw(l,m,n);
	Raw *input=new Raw(l,m,n,inputo);
	int width=2;
	for (int i=0;i<l;i++)
	{
		for (int j=0;j<m;j++)
		{
			for (int k=0;k<n;k++)
			{
				if (i>width && j>l1+width && k>width && i<l-width && j<m-width && k<m-width)
				{
					initial->put(i,j,k,2.0);

				}
				else initial->put(i,j,k,-2.0);

			}
		}
	}
		RawImage *write=new RawImage();
	
		ThreeDim_LevelSet *ls=new ThreeDim_LevelSet();
		//IShowraw(*input,argc,argv);
	ls->initialg(*input);	
	ls->minimal_surface(*initial,*input,5.0,0.2,3,1.5,1,iter_outer,pt);
	IShowraw(*initial,argc,argv);
	test.writeImage(*initial);
	system("pause");
	return 0;
}