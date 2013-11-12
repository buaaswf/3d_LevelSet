#pragma once
#include "vol_math_LevelSet.h"
#include "CImg.h" 

class ThreeDim_LevelSet
{
public:
	ThreeDim_LevelSet(void);
	~ThreeDim_LevelSet(void);
	void ThreeDim_LevelSet::minimal_surface(Raw3D *phi,Raw3D *g,double mu,double lambda,double alfa,int timestep,int iter,char *potentialFunction);
	void array_surface(Raw3D *src);
	void NeumannBoundCond( Raw3D* phi );
	Raw3D ImageFSqrt( Raw3D phi_x, Raw3D phi_y,Raw3D phi_z );
};

