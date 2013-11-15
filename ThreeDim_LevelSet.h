#pragma once
#include "vol_math_LevelSet.h"
#include "CImg.h" 
#include "vol_math_RawImage.h"

class ThreeDim_LevelSet
{
public:
	ThreeDim_LevelSet(void);
	~ThreeDim_LevelSet(void);
	void ThreeDim_LevelSet::minimal_surface(Raw &phi,Raw &g,double mu,double lambda,double alfa,int timestep,int iter,char *potentialFunction,float);
	void array_surface(Raw *src);
	void NeumannBoundCond( Raw &phi );
	Raw ImageFSqrt( Raw &phi_x, Raw &phi_y,Raw &phi_z );
};

