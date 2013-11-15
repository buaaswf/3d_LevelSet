#include "ThreeDim_LevelSet.h"
#include <iostream>
#define pi 3.141592653
#include<math.h>
using namespace cimg_library;
using namespace std;
PIXTYPE *p;
PIXTYPE	*q;
int i,j,k;
Raw del2( Raw &phi ) 
{
	int m=phi.getXsize();
	int n=phi.getYsize();
	int l=phi.getZsize();
	Raw ret2(m,n,l);
	for (int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)
		{
			for (int k=0;k<l;k++)
			{
				if (i+1< m && j+1< n &&k+1< l && i-1>=0 && j-1 >= 0 && k-1>= 0)
				{
					PIXTYPE value = (1.0/6.0)*(phi.get(i+1, j, k) + phi.get(i-1, j, k) + phi.get(i, j-1, k) + phi.get(i, j+1, k) + phi.get(i,j,k+1)+phi.get(i,j,k-1)- 6*(phi.get(i,j,k)));
					//if(value!=0)
					//	cout<<value<<endl;
					ret2.put(i, j,k, (PIXTYPE)value);
				}
				else 
				{
					ret2.put(i, j,k,0);
				}
			}

			
		}
	}
}

Raw gradientxgc( Raw &g ) 
{
	int n=g.getXsize();
	int m=g.getYsize();
	int l=g.getZsize();
	Raw* ret=new Raw(n, m,l);
	int i,j,k,temp1,temp2;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			for ( k=0;k < l;k++)
			{
				if(j>0)
					temp1=j-1;
				else
					temp1=0;
				if (j<m-1)
					temp2=j+1;
				else 
					temp2=m-1;
				ret->put(i,j,k,0.5*(g.get(i,temp2,k)-g.get(i,temp1,k)));
			}			
		}
	}
	return ret;
}

Raw gradientygc( Raw & g ) 
{
	int n=g.getXsize();
	int m=g.getYsize();
	int l=g.getZsize();
	Raw ret(n, m,l);
	int i,j,k,temp1,temp2;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			for ( k = 0;k < l;k++)
			{
				if(i>0)
					temp1=n-1;
				else
					temp1=0;
				if (i<n-1)
					temp2=i+1;
				else 
					temp2=n-1;
				ret.put(i,j,k,0.5*(g.get(temp2,j,k)-g.get(temp1,j,k)));
			}			
		}
	}
	return ret;
	
}
Raw  gradientzgc( Raw &g ) 
{
	int n=g.getXsize();
	int m=g.getYsize();
	int l=g.getZsize();
	Raw ret(n, m,l);
	int i,j,k,temp1,temp2;
	for(i=0;i<n;i++)
	{
		for(j=0;j<m;j++)
		{
			for ( k = 0;k < l;k++)
			{
				if(k>0)
					temp1=l-1;
				else
					temp1=0;
				if (k<l-1)
					temp2=k+1;
				else 
					temp2=l-1;
				ret.put(i,j,k,0.5*(g.get(i,j,temp2)-g.get(i,j,temp1)));
			}			
		}
	}
	return ret;
}
Raw cos(Raw &x)
{
	Raw ret=new Raw(x);
	for (int i=0;i<x.getXsize();i++)
	{
		for (int j=0;j< x.getYsize();j++)
		{
			for (int k=0;k< x.getZsize();k++)
			{
				ret.put(i,j,k,cos(x.get(i,j,k)));
			}
		}
	}
	return ret;
}
Raw div(Raw &x,Raw &y,Raw &z)
{
	return gradientxgc(x)+gradientygc(y)+gradientzgc(z);
}
void ThreeDim_LevelSet::array_surface(Raw *src)
{
	for (i=0;i<src->getZsize();i++)
	{

		
	}
}
Raw regFunction(Raw &s,double m,double n)
{
	int x = s.getXsize(),
		y = s.getYsize(),
		z = s.getZsize();
	Raw ss(x,y,z);
	PIXTYPE val=0;
	for (i=0;i<x;i++)
	{
		for(j=0;j<y;j++)
		{
			for (int k= 0;k<z;k++)
			{
				val=s.get(i,j,k);
				if(val>=m && val<=n )
				{
					//ss->put(i,j,255);//unsigned char version
					ss.put(i,j,k,1);
				}
				else if(s.get(i,j,k)==m||s.get(i,j,k)==n) 
				{
					ss.put(i,j,k,0);
				}
				else 
				{
					ss.put(i,j,k,0);
				}
			}
			
		}
	}

	return ss;
}
Raw  Dirac( Raw & x, double sigma ) 
{
	Raw ret(x);
	PIXTYPE temp=((1.0/2.0)/sigma);
	double temp2=(cos((2/sigma)*pi)+1)*temp;
	Raw f= (cos((ret/sigma)*pi)+1)*temp;
	Raw b = regFunction(ret, -sigma, sigma);
	//IShowImg(b);
	ret = f*b;
	//IShowImg(ret);

	return ret;
}

Raw distReg_p2( Raw  &phi ) 
{
	throw std::exception("The method or operation is not implemented.");
}

void ThreeDim_LevelSet::minimal_surface(Raw &phi,Raw &g,double mu,double lambda,double alfa,int timestep,int iter,char *potentialFunction,float epsilon )
{
	int m=g.getXsize();
	int n=g.getYsize();
	int l=g.getZsize();
	Raw vx=gradientxgc(g);
	Raw vy=gradientygc(g);
	Raw vz=gradientzgc(g);
	//*vx=(*vx);
	//*vy=(*vy);
	//*vz=(*vz);
	Raw diracPhi;
	Raw areaTerm;
	Raw volumeTerm;
	Raw src;
	Raw distRegTerm = new Raw();
	//CImg <double> sourceimage(phi.getXsize(),phi.getYsize(),1,1,0);
	for(int i=0;i<iter;i++)
	{
		NeumannBoundCond(phi);
		Raw phi_x = gradientxgc(phi);
		Raw phi_y = gradientygc(phi);
		Raw phi_z = gradientzgc(phi);
		Raw s = ImageFSqrt(phi_x, phi_y,phi_z);
		float smallNumber=1e-10;
		Raw Nx = new Raw(phi_x/(s + smallNumber));
		Raw Ny = new Raw(phi_y/(s + smallNumber));
		Raw Nz = new Raw(phi_z/(s + smallNumber));
		Raw curvature = new Raw(div(Nx,Ny,Nz));
	
		char *p1="single_well";
		if (0 == strcmp(potentialFunction, p1))
		{
			/*
			 compute distance regularization term in equation (13) 
			 with the single-well potential p1.
			 */
		distRegTerm= ((del2(phi))*6.0 - (curvature));
		}
		else if (0 == strcmp(potentialFunction, "double_well"))
		{
			distRegTerm=distReg_p2(phi);  // compute the distance regularization term in eqaution (13) with the double-well potential p2.
		}
		else printf("EEROR");
		diracPhi=new Raw(Dirac(phi,epsilon));
		areaTerm=new Raw(( (g) *(diracPhi))); 
		volumeTerm=new Raw(m,n,l);
		Raw edge1=(diracPhi) * ((vx) * (Nx)+(vy) * (Ny)+(vz)*(Nz));
		Raw edge2=(diracPhi) * ( (g) * (curvature));

		areaTerm =edge1+edge2;
		phi=phi +((distRegTerm)*mu* double(timestep) +(areaTerm)*lambda + (volumeTerm)*alfa);


	//cimg_for_insideXY(sourceimage,x,y,0)
	//{
	//	PIXTYPE val=phi->get(x,y,z);
	//	if (val>0&&val<1)
	//	{
	//		sourceimage(x,y,0)=(double)(val);
	//	}
	//	else if (val>=1)
	//	{
	//		sourceimage(x,y,0)=(double)(1);
	//}

	//}
		//sourceimage.display(disp.wait(20));
		/*delete phi_x;
		delete phi_y;
		delete phi_z;*/
	}	
	//IShowImg(*diracPhi);
	//IShowImg(*edgeTerm);
	//IShowImg(*areaTerm);
	//initialg(phi);
	//IShowImg(*phi);
	//IShowImg(*distRegTerm);
	//delete vx;
	//delete vy;
	//delete vz;
}
ThreeDim_LevelSet::ThreeDim_LevelSet(void)
{



}


ThreeDim_LevelSet::~ThreeDim_LevelSet(void)
{
}

void ThreeDim_LevelSet::NeumannBoundCond( Raw &img )
{
	int nrow=img.getXsize();
	int ncol=img.getYsize();
	int ndepth=img.getZsize();
	int i,j,k;
	//the eight point SDF
	img.putXYZ(0,img.getXYZ(2*ncol+2));
	img.putXYZ(ncol-1,img.get(2,ncol-3,k));
	img.putXYZ((nrow-1)*ncol,img.getXYZ((nrow-3)*ncol+2));
	img.putXYZ(nrow*ncol-1,img.get(nrow-3,ncol-3,ndepth-3));
	//first and the last column SDF
	for(i=2;i<nrow-2;i++)
	{
		img.putXYZ((i-1)*ncol,img.getXYZ((i-1)*ncol+2));
		img.putXYZ(ncol*(i-1)+ncol-1,img.getXYZ(ncol*(i-1)-3));

	}
	//first and last row SDF
	for(j=2;j<ncol-2;j++)
	{
		img.putXYZ(j,img.getXYZ(2*ncol+j));
		img.putXYZ(ncol*(nrow-2)+j,img.getXYZ(ncol*(nrow-4)+j));
	}
	for (i=0;i<nrow;i++)
	{
		for(j=0;j<ncol;j++)
		{
			img.put(i,j,k,img.get(i,j,k));
		}
	}
	
}

Raw ThreeDim_LevelSet::ImageFSqrt( Raw &phi_x, Raw &phi_y,Raw &phi_z )
{
	//return sqrt(phi_x*phi_x+phi_y*phi_y+phi_z*phi_z);
	int m=phi_x.getXsize();
	int n=phi_x.getYsize();
	int l=phi_x.getZsize();
	Raw ret(m,n,l);
	for (int i=0;i< m; i++)
	{
		for ( int j = 0; j< n; j++)
		{
			for ( int k = 0; k< l; k++)
			{
				ret.put(i,j,k,sqrt(phi_x.get(i,j,k)*phi_x.get(i,j,k)+phi_y.get(i,j,k)*phi_y.get(i,j,k)+phi_z.get(i,j,k)*phi_z.get(i,j,k)));
			}
		}
	}
	return ret;
}
