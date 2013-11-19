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
	int l=100,m=100,n=100,l1=20,l2=50,iter_outer=5;
	Raw *input=new Raw(100,100,100);
	for (int i=0;i<l;i++)
	{
		for (int j=0;j<m;j++)
		{
			for (int k=0;k<n;k++)
			{
				if (i>l1&&j>l1&&k>l1&&i<l2&&j<l2&&k<l2)
				{
					input->put(i,j,k,2.0);

				}
				else input->put(i,j,k,-2.0);

			}
		}
	}
	Raw *initial=new Raw(l,m,n);
	int width=-10;
	for (int i=0;i<l;i++)
	{
		for (int j=0;j<m;j++)
		{
			for (int k=0;k<n;k++)
			{
				if (i>l1+width && j>l1+width && k>l1+width && i<l2-width && j<l2-width && k<l2-width)
				{
					initial->put(i,j,k,2.0);

				}
				else initial->put(i,j,k,-2.0);

			}
		}
	}
		RawImage *write=new RawImage();
	
		ThreeDim_LevelSet *ls=new ThreeDim_LevelSet();
	IShowraw(*input,argc,argv);
	ls->initialg(*input);	
	ls->minimal_surface(*initial,*input,5.0,0.2,-3,1.5,1,iter_outer,pt);
	IShowraw(*initial,argc,argv);
	RawImage test;
	IShowraw(*input,argc,argv);
	test.writeImage(*initial);
	system("pause");
	return 0;
}