/*
 *  Boid3d.cpp
 *
 *  Created by andré sier on 20130225.
 *  Copyright 2013 s373.net/x. All rights reserved.
 *
 */




#include "Boid3d.h"

#include "Flock3d.h"



Boid3d::Boid3d(Flock3d * flock) {
	Boid3d();
	this->flockPtr = flock;
}




Boid3d * Boid3d::setFlock(Flock3d * flock) {
	this->flockPtr = flock;
	return this;
}




void Boid3d::bounds() {
	switch (flockPtr->boundmode) {
		case 0: // CLAMP
			if (x < flockPtr->minX) {
				x = flockPtr->minX;
				vx = -vx;
			}
			if (x > flockPtr->maxX) {
				x = flockPtr->maxX;
				vx = -vx;
			}
			if (y < flockPtr->minY) {
				y = flockPtr->minY;
				vy = -vy;
			}
			if (y > flockPtr->maxY) {
				y = flockPtr->maxY;
				vy = -vy;
			}
			if (z < flockPtr->minZ) {
				z = flockPtr->minZ;
				vz = -vz;
			}
			if (z > flockPtr->maxZ) {
				z = flockPtr->maxZ;
				vz = -vz;
			}
			break;
		case 1: // WRAP
			if (x < flockPtr->minX) {
				x += flockPtr->boundsWidth;
			}
			if (x > flockPtr->maxX) {
				x -= flockPtr->boundsWidth;
			}
			if (y < flockPtr->minY) {
				y += flockPtr->boundsHeight;
			}
			if (y > flockPtr->maxY) {
				y -= flockPtr->boundsHeight;
			}
			if (z < flockPtr->minZ) {
				z += flockPtr->boundsDepth;
			}
			if (z > flockPtr->maxZ) {
				z -= flockPtr->boundsDepth;
			}
			break;
	}
	
}









void Boid3d:: update(const float amount) {
	
	// float vec[] = flock(amount);// flockfull(amount);
	//float * vec = flockfull(amount);
	
	// reset acc on begin 2 draw
	ax = 0;
	ay = 0;
	az = 0;
	
	
	
	float *vec = new float[3];	
	vec[0] = 0.0f;
	vec[1] = 0.0f;
	vec[2] = 0.0f;
	
	//	flock(amount, vec);
	flockfull(amount, vec);
	
	ax += vec[0];// *amount;
	ay += vec[1];// *amount;
	az += vec[2];
	
	delete [] vec;
	
	// change this to allow flock flock interaction
	// accX = vec[0];
	// accY = vec[1];
	
	// limit force
	float distMaxForce = ABS(ax) + ABS(ay) + ABS(az);
	if (distMaxForce > flockPtr->maxForce) {
		distMaxForce = flockPtr->maxForce / distMaxForce;
		ax *= distMaxForce;
		ay *= distMaxForce;
		az *= distMaxForce;
	}
	
	vx += ax;
	vy += ay;
	vz += az;
	
	// limit speed
	float distMaxSpeed = ABS(vx) + ABS(vy) + ABS(vz);
	if (distMaxSpeed > flockPtr->maxSpeed) {
		distMaxSpeed = flockPtr->maxSpeed / distMaxSpeed;
		vx *= distMaxSpeed;
		vy *= distMaxSpeed;
		vz *= distMaxSpeed;
	}
	
	x += vx * amount;
	y += vy * amount;
	z += vz * amount;
	
	bounds();
	
//	// reset acc on end
//	ax = 0;
//	ay = 0;
//	az = 0;
}










float* Boid3d::steer(float* target, float amount){ //, float *steervec) {
	
	//	float steer[] = {0.f, 0.f}; //new float[2];
	//float *dir =new float[2];
	float dir[3] = {0.f,0.f,0.f};
	
//	dir[0] = 0.0f;
//	dir[1] = 0.0f;
	
	
	dir[0] = target[0] - x;
	dir[1] = target[1] - y;
	dir[2] = target[1] - z;
	float d = ABS(dir[0]) + ABS(dir[1]) +  ABS(dir[2]);
	
	if (d > 2) {
		float invDist = 1.f / d;
		dir[0] *= invDist;
		dir[1] *= invDist;
		dir[2] *= invDist;
		// steer, desired - vel
		target[0] = dir[0] - vx;
		target[1] = dir[1] - vy;
		target[2] = dir[2] - vz;
		float steerLen = ABS(target[0]) + ABS(target[1]) + ABS(target[2]);
		if (steerLen > 0) {
			float invSteerLen = amount / steerLen;// 1f / steerLen;
			target[0] *= invSteerLen;
			target[1] *= invSteerLen;
			target[2] *= invSteerLen;
		}
	}
	
//	delete [] dir;
	
	return target;
	
}






//float* Boid3d::cohesion(vector<Boid3d*>* b, float *vec) {
float* Boid3d::cohesion( float *vec) {
	
	float cohesiondist = flockPtr->distCohesion;
	//	float vec[] = {0.f, 0.f};//new float[2];
	int count = 0;
	
	for (int i = 0; i < flockPtr->boids.size(); i++) {
		Boid3d * other = flockPtr->boids.at(i);
		float dx = other->x - x;
		float dy = other->y - y;
		float dz = other->z - z;
		float d = ABS(dx) + ABS(dy)+ ABS(dz);
		if (d > 0 && d < cohesiondist) {
			count++;
			vec[0] += other->x;// dx;
			vec[1] += other->y;// dy;
			vec[2] += other->z;// dy;
		}
	}
	
	if (count > 0) {
		float invCount = 1.f / count;
		vec[0] *= invCount;
		vec[1] *= invCount;
		vec[2] *= invCount;
		steer(vec, 1);
	}
	
	return vec;
}








float* Boid3d::align( float *vec) {
	
	float aligndist = flockPtr->distAlign;
	//	float vec[] = {0.f, 0.f};//new float[2];
	int count = 0;
	
	for (int i = 0; i < flockPtr->boids.size(); i++) {
		Boid3d * other = flockPtr->boids.at(i);
		float dx = other->x - x;
		float dy = other->y - y;
		float dz = other->z - z;
		float d = ABS(dx) + ABS(dy)+ ABS(dz);

		if (d > 0 && d < aligndist) {
			count++;
			vec[0] += other->vx;// dx;
			vec[1] += other->vy;// dy;
			vec[2] += other->vz;// dy;
		}
	}
	
	if (count > 0) {
		float invCount = 1.f / count;
		vec[0] *= invCount;
		vec[1] *= invCount;
		vec[2] *= invCount;
	}
	
	return vec;
	
}





float* Boid3d::separate(float *vec) {
	
	float separatedist = flockPtr->distSeparation;
	//	float vec[] = {0.f, 0.f}; //new float[2];
	int count = 0;
	
	for (int i = 0; i < flockPtr->boids.size(); i++) {
		Boid3d * other = flockPtr->boids.at(i);
		float dx = other->x - x;
		float dy = other->y - y;
		float dz = other->z - z;
		float d = ABS(dx) + ABS(dy)+ ABS(dz);
		
		if (d > 0 && d < flockPtr->distAlign) {
			count++;
			// / mais longe influenciam mais?
			// vec[0] += -dx;
			// vec[1] += -dy;
			float invD = 1.f / d;
			vec[0] += -dx * invD;
			vec[1] += -dy * invD;
			vec[2] += -dz * invD;
		}
	}
	
	if (count > 0) {
		float invCount = 1.f / count;
		vec[0] *= invCount;
		vec[1] *= invCount;
		vec[2] *= invCount;
	}
	
	return vec;
}







float* Boid3d::flock(const float amount, float *vec) {
	
	//	float * vec = new float[2];
	
	float *sep = new float[3];
	float *ali = new float[3];
	float *coh = new float[3];
	
	sep[0] = 0.0f;
	sep[1] = 0.0f;
	sep[2] = 0.0f;
	ali[0] = 0.0f;
	ali[1] = 0.0f;
	ali[2] = 0.0f;
	coh[0] = 0.0f;
	coh[1] = 0.0f;
	coh[2] = 0.0f;
	
	separate(sep);
	align( ali);
	cohesion( coh);
	
	// System.out.print("boid flock sep " + sep[0] + " " + sep[1] + " "
	// + flock.forceSeparate + "\n");
	
	sep[0] *= flockPtr->separate;
	sep[1] *= flockPtr->separate;
	sep[2] *= flockPtr->separate;
	
	ali[0] *= flockPtr->align;
	ali[1] *= flockPtr->align;
	ali[2] *= flockPtr->align;
	
	coh[0] *= flockPtr->cohesion;
	coh[1] *= flockPtr->cohesion;
	coh[2] *= flockPtr->cohesion;
	
	vec[0] = sep[0] + ali[0] + coh[0];
	vec[1] = sep[1] + ali[1] + coh[1];
	vec[2] = sep[2] + ali[2] + coh[2];
	float d =ABS(vec[0]) + ABS(vec[1]) + ABS(vec[2]);
	float invDist = 1.f;
	if (d > 0)
		invDist = amount / d;// 1f / d;
	vec[0] *= invDist;
	vec[1] *= invDist;
	vec[2] *= invDist;
	
	
	delete[] sep;
	delete[] ali;
	delete[] coh;
	
	
	return vec;
}






float* Boid3d::flockfull(const float amount, float *vec) {
	//	float * vec = new float[2];
	
	float *sep = new float[3];
	float *ali = new float[3];
	float *coh = new float[3];
	float *attrForce = new float[3];
	
	sep[0] = 0.0f;
	sep[1] = 0.0f;
	sep[2] = 0.0f;
	ali[0] = 0.0f;
	ali[1] = 0.0f;
	ali[2] = 0.0f;
	coh[0] = 0.0f;
	coh[1] = 0.0f;
	coh[2] = 0.0f;
	attrForce[0] = 0.0f;
	attrForce[1] = 0.0f;
	attrForce[2] = 0.0f;
	
	
	
	//	float attrForce[] = {0.f, 0.f}; //new float[2];
	int countsep = 0, countali = 0, countcoh = 0;
	
	float separatedist = flockPtr->distSeparation;
	float aligndist = flockPtr->distAlign;
	float cohesiondist = flockPtr->distCohesion;
	float invD = 0;
	
	// boolean hasAttractionPoints = flock.hasAttractionPoints();
	
	// main full loop track all forces boid other boids
	for (int i = 0; i < flockPtr->boids.size(); i++) {
		Boid3d * other = flockPtr->boids.at(i);
		float dx = other->x - x;
		float dy = other->y - y;
		float dz = other->z - z;
		float d = ABS(dx) + ABS(dy)+ ABS(dz);
		if (d <= 1e-7)
			continue;
		
		// sep
		if (d < separatedist) {
			countsep++;
			invD = 1.f / d;
			sep[0] -= dx * invD;
			sep[1] -= dy * invD;
			sep[2] -= dz * invD;
		}
		
		// coh
		if (d < cohesiondist) {
			countcoh++;
			coh[0] += other->x;
			coh[1] += other->y;
			coh[2] += other->z;
		}
		
		// ali
		if (d < aligndist) {
			countali++;
			ali[0] += other->vx;
			ali[1] += other->vy;
			ali[2] += other->vz;
		}
		
	}
	
	if (countsep > 0) {
		const float invForSep = flockPtr->separate / (float) countsep;
		sep[0] *= invForSep;
		sep[1] *= invForSep;
		sep[2] *= invForSep;
	}
	if (countali > 0) {
		// final float invForAli = 1f / (float) countali;
		const float invForAli = flockPtr->align / (float) countali;
		ali[0] *= invForAli;
		ali[1] *= invForAli;
		ali[2] *= invForAli;
	}
	if (countcoh > 0) {
		const float invForCoh = flockPtr->cohesion / (float) countcoh;
		coh[0] *= invForCoh;
		coh[1] *= invForCoh;
		coh[2] *= invForCoh;
		coh = steer(coh, 1);
	}
	
	// if using extra forces, place here
	
	// sep[0] *= flock.separate;
	// sep[1] *= flock.separate;
	//
	// ali[0] *= flock.align;
	// ali[1] *= flock.align;
	//
	// coh[0] *= flock.cohesion;
	// coh[1] *= flock.cohesion;
	
	// other forces
	if (flockPtr->hasAttractionPoints()) {
		for (int i = 0; i < flockPtr->attractionPoints.size(); i++) {
			AttractionPoint3d * point = flockPtr->attractionPoints.at(i);
			float dx = point->x - x;
			float dy = point->y - y;
			float dz = point->z - z;
			float d = ABS(dx) + ABS(dy)+ ABS(dz);
			if (d <= 1e-7)
				continue;
			if (d > point->sensorDist)
				continue;
			
			// inbounds, calc
			float invForce = point->force  / d  * attr;// newww   ////flockPtr->attraction     ; // neww
			dx *= invForce;
			dy *= invForce;
			dz *= invForce;
			
			attrForce[0] += dx;
			attrForce[1] += dy;
			attrForce[2] += dz;
		}
		
	}
	
	vec[0] = sep[0] + ali[0] + coh[0] + attrForce[0];
	vec[1] = sep[1] + ali[1] + coh[1] + attrForce[1];
	vec[2] = sep[2] + ali[2] + coh[2] + attrForce[2];
	const float d = ABS(vec[0]) + ABS(vec[1]) + ABS(vec[2]);
	if (d > 0) {
		float invDist = amount / d;
		vec[0] *= invDist;
		vec[1] *= invDist;
		vec[2] *= invDist;
	}
	
	
	
	vec[0] *= amount;
	vec[1] *= amount;
	vec[2] *= amount;
	
	
	delete[] sep;
	delete[] ali;
	delete[] coh;	
	delete[] attrForce;
	
	
	
	return vec;
}


