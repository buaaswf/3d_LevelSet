#include "vol_math_RawImage.h"
//#include"vol_math_Raw3D_Independt.h"
/*
RawImage is to change the all the three data types to double or float
*/
//=====================================================================================================
char* double2char(double *buf, long length)
{
	int i=0;
	char *imgf=new char[length];
	while(i < length)
	{
		imgf[i]= (char)buf[i++];
	}
	return imgf;
}

RawImage::RawImage(int length,int height,int width)
{
	this->height=height;
	this->length=length;
	this->width=width;
	int length1=this->getlength();
	this->buf=new PIXTYPE[length1];
}
RawImage::RawImage()
{
	this->height=0;
	this->length=0;
	this->width=0;
	this->buf=NULL;

}
void RawImage::readImage(unsigned char * buf,char const *file ,int size)
{
	FILE * op=fopen(file,"rb");
	if(op==NULL)
	{
		printf("open fail");
	}
	//unsigned char * unsignedbuf=new unsigned char[size];
	fread(buf,sizeof(unsigned char),size,op);

	fclose(op);
	printf("read is ok\n");
}
void RawImage::writeImage(Raw &destImg)
{
	FILE *p=fopen("F:\\3Dlevel.raw","wb");
	char* data = double2char(destImg.getdata(), destImg.size());
	//double *data=destImg.getdata();
	fwrite(data, sizeof(char), destImg.size(), p);
	fclose(p);
	fflush(stdout);

	delete[] data;
	printf("write is ok");
}
float* RawImage::buf2float(unsigned char *buf)
{
	unsigned char *p;
	p=buf;
	int i=0;
	long length=this->getlength();
	float *imgf=new float[length];
	while(p)
	{
		imgf[i]= (float)p[i] ;
		imgf+=i;
		p++;i++;
	}
	return imgf;
}

RawImage::~RawImage(void)
{
	delete[] buf;
}

//=====================================================================================================

Raw::Raw(void)
{
	xsize=0;
	ysize=0;
	zsize=0;
	data=NULL;
}
Raw::Raw(int xsize,int ysize,int zsize,PIXTYPE *y)
{
	//float i=0.0f;
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	this->data=y;
}
Raw::Raw(int xsize,int ysize,int zsize)
{
	this->xsize=xsize;
	this->ysize=ysize;
	this->zsize=zsize;
	this->data=new PIXTYPE[size()];
}

Raw::Raw(const Raw & src)
{
	this->xsize=src.xsize;
	this->ysize=src.ysize;
	this->zsize=src.zsize;
	this->data=new PIXTYPE[size()];
	memcpy(this->data,src.data,sizeof(PIXTYPE)*size());

}

Raw::~Raw(void)
{
	if(this->data!=NULL)
		delete [] this->data;
	data=NULL;
	//cout<<"Raw is deconstruct"<<endl;
}
void Raw::sizer(int ixsize, int iysize,int izsize) {
	if(data!=NULL)
		delete [] this->data;
	data=NULL;
	this->data = new PIXTYPE[ixsize*iysize*izsize];	// & allocate memory.
	xsize = ixsize;				// set new RawImage size,
	ysize = iysize;
	zsize=izsize;
}
void Raw::sizer(Raw* src) {
	int ix, iy,iz;

	ix = src->getXsize();
	iy = src->getYsize();
	iz = src->getZsize();
	sizer(ix,iy,iz);
}
int Raw::wipecopy(Raw* src) {
	int out=1;
	int i,imax;	

	if(getYsize() != src->getYsize() || getXsize()!=src->getXsize()) { // resize to fit 'src'.
		sizer(src);
		out=0;
	}
	imax = getXsize()*getYsize();
	for(i=0; i<imax; i++) {
		putXYZ(i,src->getXYZ(i));
	}

	return(out);
}
Raw operator /(const PIXTYPE val, const Raw &volume)
{
	Raw res(volume);

	for (int i = 0; i < res.size(); i ++ )
	{
		res.data[i]= val/volume.data[i];
	}
	return res;
}

//=====================================================================================================
RawArray::RawArray(int rawNum,Raw *src)
{
	this->rawNum=rawNum;
	this->z=src;
}
RawArray::RawArray(void)
{
	z=0;
}
RawArray::~RawArray(void)
{
	if(this->z!=NULL)
		delete [] this->z;
	z=NULL;
	//cout<<"RawArray is deconstruct"<<endl;
}
void RawArray::sizer(int ixsize, int iysize, int izsize,int rawNum) {
	int ii;
	if(z!=NULL)
		delete[]this->z;
	z = new Raw[rawNum];			// make room for the 2D objects,
	this->rawNum = 0;   //rawNum

	for(ii=0; ii< rawNum; ii++) 
		z[ii].sizer(ixsize,iysize,izsize);	// use the Raw sizer.	
}
void RawArray::sizer(RawArray* src)
{
	z=src->z;
	rawNum=src->rawNum;

}
void RawArray::wipecopy(RawArray& src) {
	int k,kmax;

	if(&src==NULL)return;
	if(src.rawNum==0) return;		// ignore empty inputs.
	if(src.getrawNum()!=rawNum || src.getZsize() != z[0].getZsize() || src.getYsize() != z[0].getYsize() ||
		src.getXsize() != getXsize()) {
			sizer(&src);
	}
	kmax = getrawNum();
	for(k=0; k< kmax; k++) {		// copy each field;
		z[k].wipecopy(&(src.z[k]));
	}
}