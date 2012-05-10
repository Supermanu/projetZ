#include <iostream>
#include <cmath>
#include <vector>

using namespace std;


vector<float> boost(vector<float> p_i,vector<float> b)
{
    float b2=b[0]*b[0]+b[1]*b[1]+b[2]*b[2];
    float bx=b[0];
    float by=b[1];
    float bz=b[2];
    float g=1/sqrt(1-b2);
    float L[4][4]={{  g,        -bx*g,            -by*g,             -bz*g},
                   {-bx*g,  1+(g-1)*(bx*bx/b2), (g-1)*bx*by/b2, (g-1)*bx*bz/b2},
		   {-by*g, (g-1)*bx*by/b2,     1+(g-1)*by*by/b2,  (g-1)*bz*by/b2},
		   { -bz*g,  (g-1)*bx*bz/b2, (g-1)*bz*by/b2,    1+(g-1)*bz*bz/b2},
                  };
                  
    vector<float> p_i_boosted;            
     
    //boost             
    float P_temp[4];
	
    for (unsigned int i=0; i<4; i++) 
    {
	P_temp[i]=0; 
	
	for (unsigned int j=0; j<4; j++)
	{
	    P_temp[i] += L[i][j]*p_i[j];
	}
    }
    
    for (unsigned int i=0; i<4; i++) 
    {
	p_i_boosted.push_back(P_temp[i]);	
    }
    return p_i_boosted;
     
}