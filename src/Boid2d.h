/*
 *  Boid2d.h
 *  flockTextParts
 *
 *  Created by andré sier on 20130225.
 *  Copyright 2013 __MyCompanyName__. All rights reserved.
 *
 */



#pragma once



class Flock2d;

class Boid2d {
public:
	
	float x, y, vx, vy, ax, ay;
	int life;
	
	float attr;
	
	Flock2d * flockPtr;
	
	// public Team team;
	// public int om;
	// public float forceSeparate, forceAlign, forceCohesion;
	// public float maxTurn, maxSpeed, maxForce;
	
	Boid2d() {
		x = y = vx = vy = ax = ay = 0.0f;
		life = 0;
		flockPtr = NULL;
		attr = 0.0f;
	}
	
	Boid2d(Flock2d * flock);
	
	Boid2d * setFlock(Flock2d * flock);
	
	Boid2d * setLoc(float lx, float ly) {
		x = lx;
		y = ly;
		return this;
	}
	
	Boid2d * setVel(float velx, float vely) {
		vx = velx;
		vy = vely;
		return this;
	}
	
	void bounds();
	
	/*
	 * main funcs
	 */
	
	void update(const float amount);		
		
	float* flock(const float amount, float *vec) ;
	
	
	float* steer(float* target, float amount);//   , float *steervec);
	
//	float* cohesion(vector<Boid2d*>* b, float *vec);
//	
//	float* align(vector<Boid2d*>* b, float *vec) ;	
//	
//	float* separate(vector<Boid2d*>* b, float *vec) ;

	float* cohesion( float *vec);	
	float* align( float *vec) ;		
	float* separate( float *vec) ;
	
	
	
	
	/*
	 * integration of all forces in single eq now with attraction points builtin
	 */
	
	float* flockfull(const float amount, float *vec) ;	
		
};
