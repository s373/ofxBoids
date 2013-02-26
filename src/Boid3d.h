/*
 *  Boid3d.h
 *  flockHelloBoidsAttr
 *
 *  Created by andré sier on 20130225.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */

/*
 *  Boid3d.h
 *  flockTextParts
 *
 *  Created by andré sier on 20130225.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once



class Flock3d;

class Boid3d {
public:
	
	float x, y, z, vx, vy, vz,  ax, ay, az;
	int life;
	
	float attr;
	
	Flock3d * flockPtr;
	
	// public Team team;
	// public int om;
	// public float forceSeparate, forceAlign, forceCohesion;
	// public float maxTurn, maxSpeed, maxForce;
	
	Boid3d() {
		x = y = z = vz = az = vx = vy = ax = ay = 0.0f;
		life = 0;
		flockPtr = NULL;
		attr = 0.0f;
	}
	
	Boid3d(Flock3d * flock);
	
	Boid3d * setFlock(Flock3d * flock);
	
	Boid3d * setLoc(float lx, float ly, float lz) {
		x = lx;
		y = ly;
		z = lz;
		return this;
	}
	
	Boid3d * setVel(float velx, float vely, float velz) {
		vx = velx;
		vy = vely;
		vz = velz;
		return this;
	}
	
	void bounds();
	
	/*
	 * main funcs
	 */
	
	void update(const float amount);		
	
	float* flock(const float amount, float *vec) ;
	
	
	float* steer(float* target, float amount);//   , float *steervec);
	
	//	float* cohesion(vector<Boid3d*>* b, float *vec);
	//	
	//	float* align(vector<Boid3d*>* b, float *vec) ;	
	//	
	//	float* separate(vector<Boid3d*>* b, float *vec) ;
	
	float* cohesion( float *vec);	
	float* align( float *vec) ;		
	float* separate( float *vec) ;
	
	
	
	
	/*
	 * integration of all forces in single eq now with attraction points builtin
	 */
	
	float* flockfull(const float amount, float *vec) ;	
	
};
