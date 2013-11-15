#include <stdio.h>
#include <stdlib.h>
#include "vol_math_RawImage.h"
#include "vol_math_trilateralfilter.h"


int main()
{
	RawImage *img=new RawImage(281,481,2501);
	img->readImage(img->buf,"F:\\lab\\VTKproj\\mig.raw",img->getlength());
	trilateralfilter f(img);
	f.TrilateralFilter(1);
	delete img;
	system("pause");
	return 0;
}