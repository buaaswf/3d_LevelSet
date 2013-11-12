#include "ThreeDim_LevelSet.h"

#include <iostream>
#define pi 3.141592653
#include<math.h>
using namespace cimg_library;
using namespace std;
PIXTYPE *p;
PIXTYPE	*q;
int i,j;

Raw3D* del2( Raw3D *src ) 
{
	throw std::exception("The method or operation is not implemented.");
}

Raw3D* gradientxgc( Raw3D* g ) 
{
	throw std::exception("The method or operation is not implemented.");
}

Raw3D * gradientygc( Raw3D * g ) 
{
	throw std::exception("The method or operation is not implemented.");
}
Raw3D * gradientzgc( Raw3D * g ) 
{
	throw std::exception("The method or operation is not implemented.");
}
Raw3D* div(Raw3D *x,Raw3D *y,Raw3D *z)
{

}
void ThreeDim_LevelSet::array_surface(Raw3D *src)
{
	for (i=0;i<src->getZsize();i++)
	{
		
	}
}
Raw3D * operator +(Raw3D *x,Raw3D *y)
{

}
void ThreeDim_LevelSet::minimal_surface(Raw3D *phi,Raw3D *g,double mu,double lambda,double alfa,int timestep,int iter,char *potentialFunction)
{
	int m=g->getXsize();
	int n=g->getYsize();
	int l=g->getZsize();
	//IShowImg(g);
	Raw3D *vx=gradientxgc(g);
	Raw3D *vy=gradientygc(g);
	*vx=(*vx);
	*vy=(*vy);
	//IShowImg(*vx);
	//IShowImg(*vy);
	Raw3D *diracPhi;
	Raw3D *areaTerm;
	Raw3D *volumeTerm;
	Raw2D *src;
	Raw3D *distRegTerm = new Raw3D(l,src);
	CImg <double> sourceimage(phi->getXsize(),phi->getYsize(),1,1,0);
	CImgDisplay disp(256,256,"",1);
	for(int i=0;i<iter;i++)
	{
		NeumannBoundCond(phi);
		Raw3D *phi_x = gradientxgc(phi);
		Raw3D *phi_y = gradientygc(phi);
		Raw3D *phi_z = gradientzgc(phi);
		Raw3D s = ImageFSqrt(*phi_x, *phi_y,*phi_x);
		float smallNumber=1e-10;
		Raw3D *Nx = new Raw3D(*phi_x/(s + smallNumber));
		Raw3D *Ny = new Raw3D(*phi_y/(s + smallNumber));
		Raw3D *Nz = new Raw3D(*phi_z/(s + smallNumber));
		Raw3D *curvature = new Raw3D(div(Nx,Ny,Nz));
	
		char *p1="single_well";
		if (0 == strcmp(potentialFunction, p1))
		{
			/*
			 compute distance regularization term in equation (13) 
			 with the single-well potential p1.
			 */
		*distRegTerm= ((*del2(phi))*4.0 - (*curvature));
		}
		else if (0 == strcmp(potentialFunction, "double_well"))
		{
			*distRegTerm=distReg_p2(phi);  // compute the distance regularization term in eqaution (13) with the double-well potential p2.
		}
		else printf("EEROR");
		diracPhi=new Raw3D(Dirac(phi,epsilon));
		areaTerm=new Raw3D(( (*g) *(*diracPhi))); 
		volumeTerm=new Raw3D(m,n);
		//Raw3D edge1=(*diracPhi) * ((*vx) * (*Nx)+(*vy) * (*Ny));
		//Raw3D edge2=(*diracPhi) * ( (*g) * (*curvature));

		*areaTerm =edge1+edge2;
		*phi=*phi +((*distRegTerm)*mu* double(timestep) +(*areaTerm)*lambda + (*volumeTerm)*alfa);
		//IShowImg(*distRegTerm);
		//IShowImg(*edgeTerm);
		//IShowImg(*areaTerm);
		//IShowImg(*vx);
		//IShowImg(*vx);
		////IShowImg(*phi);
	
		/*IShowImg(*curvature);*/
		//IShowImg(*phi_x);
		//IShowImg(*phi_y);
		//IShowImg(*Nx);
		//IShowImg(*Ny);
		//IShowImg(*g);
		//IShowImg(s);

		//phi_0=*phi;
		//IShowImg(*phi);
		
		cimg_for_insideXY(sourceimage,x,y,0)
	{
		PIXTYPE val=phi->get(x,y);
		if (val>0&&val<1)
		{
			sourceimage(x,y,0)=(double)(val);
		}
		else if (val>=1)
		{
			sourceimage(x,y,0)=(double)(1);
	}

	}
		sourceimage.display(disp.wait(20));
		delete phi_x;
		delete phi_y;
	}	
	//IShowImg(*diracPhi);
	//IShowImg(*edgeTerm);
	//IShowImg(*areaTerm);
	//initialg(phi);
	IShowImg(*phi);
	//IShowImg(*distRegTerm);
	delete vx;
	delete vy;
}
ThreeDim_LevelSet::ThreeDim_LevelSet(void)
{
}


ThreeDim_LevelSet::~ThreeDim_LevelSet(void)
{
}

void ThreeDim_LevelSet::NeumannBoundCond( Raw3D* phi )
{
	throw std::exception("The method or operation is not implemented.");
}

Raw3D ThreeDim_LevelSet::ImageFSqrt( Raw3D phi_x, Raw3D phi_y,Raw3D phi_z )
{
	throw std::exception("The method or operation is not implemented.");
}
