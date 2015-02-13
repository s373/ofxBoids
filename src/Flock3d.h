/*
 *  Flock3d.h
 *
 *  Created by andré sier on 20130225.
 *  Copyright 2013 s373.net/x. All rights reserved.
 *
 */

/**
 * Boids
 * Simulation of autonomous agent behaviors in 2D, 3D.
 * Based on code by Craig Reynolds, Daniel Shiffman. 
 * Besides Cohesion, Separation, Alignment, adds multiple 
 * force points creating interesting targets in the simulation.
 * http://s373.net/code/boids
 *
 * Copyright (C) 2007-2013 Andre Sier http://s373.net
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General
 * Public License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place, Suite 330,
 * Boston, MA  02111-1307  USA
 * 
 * @author      Andre Sier 
 * @modified    20130225
 * @version     0.0.7a
 * @url			http://s373.net/code/boids
 */


#pragma once

#include "ofMain.h"

#include "Boid3d.h"
#include "AttractionPoint3d.h"

class Flock3d {
public:
	
	vector <Boid3d *>				boids;
	vector <AttractionPoint3d *>	attractionPoints;
	
	// public ArrayList<Team> teams; // superclass flockTeam, etc
	
	// forces
	float separate, align, cohesion;
	float distSeparation, distAlign, distCohesion;
	float maxTurn, maxSpeed, maxForce;
	
	// bounds
	float minX, minY, maxX, maxY, minZ, maxZ, boundsWidth,
								boundsHeight, boundsDepth;
	int boundmode;
	
	// new
	float dt;
	float attraction, attractiondeviation;
	
	Flock3d(){
		clear();
		separate = align = cohesion = distSeparation = distAlign = distCohesion = maxTurn =
		maxSpeed = maxForce = minX = maxX = maxY = boundsWidth = boundsHeight = 0;
		boundmode = 0;
		dt = 1.0f;
		attraction = attractiondeviation = 0.0f;		
		minZ = maxZ = boundsDepth = 0.f;
	}
	
	
	void clear(){
		clearBoids();
		clearAttrPts();
	}
	
	void clearBoids(){
		while(boids.size()>0){
			delete boids[0];
			boids.erase(boids.begin());
		}
		
	}
	
	void clearAttrPts(){
		while(attractionPoints.size()>0){
			delete attractionPoints[0];
			attractionPoints.erase(attractionPoints.begin());
		}
		
	}
	
	
	
	Flock3d * setup(int num, float lx, float ly, float lz) {
		return setup(num, lx, ly, lz, 1);
	}
	
	Flock3d * setup(int num, float lx, float ly, float lz, float dev) {
		init(num, lx, ly, lz,  dev);
		return this;
	}
	
	void init(int num, float lx, float ly, float lz, float dev) {
		//		boids = new ArrayList<Boid3d>();
		//		attractionPoints = new ArrayList<AttractionPoint3d>();
		
		for (int i = 0; i < num; i++) {
			Boid3d * b = new Boid3d(this);
			// need to be scattered or else no work
			b->setLoc(lx + ofRandom(-dev, dev),
					  ly + ofRandom(-dev, dev),
					  lz + ofRandom(-dev, dev)
					  );
			// b.setLoc(lx, ly);
			//			boids.add(b);
			boids.push_back(b);
		}
		
		defaultValues();
		
	}
	
	void defaultValues() {
		boundmode = 0;
		separate = 55.0f;
		align = 12.0f;
		cohesion = 7.0f;
		distSeparation = 50.0f;
		distAlign = 100.0f;
		distCohesion = 75.0f;
		// maxTurn, maxSpeed, maxForce;
		maxSpeed = 2.f;
		maxForce = 10000.0f;
		attraction = 1.0f;
		attractiondeviation = 0.0f;
		
		// minX = 0; minY = 0; maxX = 700; maxY, boundsWidth, boundsHeight;
//		setBounds(0, 0, 700, 700);
		setBounds(0, 0, -700, 700, 700, 0);
	}
	
	// metodos
	
	Flock3d * add(float lx, float ly, float lz) {
		Boid3d * b = new Boid3d();//(this); // first constructor is zeroing nicely
		b->setFlock(this);
		
		b->setLoc(lx, ly, lz);
		
		b->attr = attraction + ofRandom(-attractiondeviation, attractiondeviation);
		
		boids.push_back(b);//boids.add(b);
		return this;
	}
	
	
	Flock3d * setDt(const float d){
		dt = d;
		return this;
	}
	
	
	
	Flock3d * setMaxTurn(float mt) {
		maxTurn = mt;
		return this;
	}
	
	Flock3d * setMaxSpeed(float ms) {
		maxSpeed = ms;
		return this;
	}
	
	Flock3d * setMaxForce(float mf) {
		maxForce = mf;
		return this;
	}
	Flock3d * setAttraction(float mf) {
		attraction = mf;
		doAttraction();
		return this;
	}
	Flock3d * setAttractionDev(float mf) {
		attractiondeviation = mf;
		doAttraction();
		return this;
	}
	
	void doAttraction(){
		for(int i=0; i<boids.size(); i++){
			boids[i]->attr = attraction + ofRandom(-attractiondeviation, attractiondeviation);
		}
	}
	
	
	float getMaxTurn() {
		return maxTurn;
	}
	
	float getMaxSpeed() {
		return maxSpeed;
	}
	
	float getMaxForce() {
		return maxForce;
	}
	
	float getSeparate() {
		return separate;
	}
	
	Flock3d * setSeparate(float forceSeparate) {
		this->separate = forceSeparate;
		return this;
	}
	
	Flock3d * setAlign(float forceAlign) {
		this->align = forceAlign;
		return this;
	}
	
	Flock3d * setCohesion(float forceCohesion) {
		this->cohesion = forceCohesion;
		return this;
	}
	
	float getAlign() {
		return align;
	}
	
	float getCohesion() {
		return cohesion;
	}
	
	/**
	 * @return the distSeparation
	 */
	float getSeparation() {
		return distSeparation;
	}
	
	/**
	 * @return the distNeighborDistance
	 */
	float getDistAlign() {
		return distAlign;
	}
	
	/**
	 * @return the distNeighborDistance
	 */
	float getDistCohesion() {
		return distCohesion;
	}
	
	/**
	 * @param distSeparation
	 *            the distSeparation to set
	 */
	Flock3d * setDistSeparation(float distSeparation) {
		this->distSeparation = distSeparation;
		return this;
	}
	
	/**
	 * @return the distNeighborDistance
	 */
	Flock3d * setDistAlign(float d) {
		distAlign = d;
		return this;
	}
	
	/**
	 * @return the distNeighborDistance
	 */
	Flock3d * setDistCohesion(float d) {
		distCohesion = d;
		return this;
	}
	
	/**
	 *
	 */
	Flock3d * setBounds(float minx, float miny, float minz, float maxx,
						float maxy, float maxz) {
		minX = minx;
		minY = miny;
		maxX = maxx;
		maxY = maxy;
		minZ = minz;
		maxZ = maxz;
		boundsWidth = maxX - minX;
		boundsHeight = maxY - minY;
		boundsDepth = maxZ - minZ;
		
		return this;
	}
	
	/**
	 * @return the boundmode
	 */
	int getBoundmode() {
		return boundmode;
	}
	
	/**
	 * @param boundmode
	 *            the boundmode to set
	 */
	Flock3d * setBoundmode(int boundmode) {
		this->boundmode = boundmode;
		return this;
	}
	
	/*
	 * update func
	 */
	void update() {
		int boidsSize = boids.size();
		for (int i = 0; i < boidsSize; i++) {
			//			Boid3d *b = boids.get(i);
			boids[i]->update(dt);
		}
	}
	
	// public void interfere(Flock3d otherFlock, float amount) {
	//
	// int boidsSize = boids.size();
	// for (int i = 0; i < boidsSize; i++) {
	// Boid3d b = boids.get(i);
	// b.update(amount);
	// }
	// }
	
	// public void set() {
	// int boidsSize = boids.size();
	// for (int i = 0; i < boidsSize; i++) {
	// Boid3d b = boids.get(i);
	// b.setFlock(this);
	// }
	// }
	
	int size() {
		return boids.size();
	}
	
	Boid3d * get(int idx) {
		return boids.at(idx);
	}
	
	// / attraction points
	
	Flock3d * addAttractionPoint(float x, float y, float z, float force,
								 float sensorDist) {
		AttractionPoint3d * ap = new AttractionPoint3d(x, y, z, force, sensorDist);
		attractionPoints.push_back(ap);
		return this;
	}
	
	vector<AttractionPoint3d*>* getAttractionPoints() {
		return &attractionPoints;
	}
	
	bool hasAttractionPoints() {
		return attractionPoints.size() > 0;
	}
	
	void changeAttractionPoint(int id, float x, float y, float z, float force,
							   float sensorDist) {
		//		try {
		
		AttractionPoint3d * ap = attractionPoints[id];//.get(id);
		if(ap!=NULL){
			ap->x = x;
			ap->y = y;
			ap->z = z;
			ap->force = force;
			ap->sensorDist = sensorDist;
		} else {
			cout << " attraction point3d null at id: " << id << endl;
		}
		//		} catch (Exception e) {
		//			System.out.print("error in changeAttractionPoint \n");
		//		}
	}
	
	
	
	
	
	/***
	 
	 new stuf to incorporate in p5
	 
	 */
	
	
	void removeFirstBoid(){
		if(boids.size()>0){
			delete boids[0];
			boids.erase(boids.begin());
		}
	}
	void removeLastBoid(){
		if(boids.size()>0){
			delete boids[boids.size()-1];
			boids.erase(boids.end()-1);
		}
	}
	
	
	void removeBoid(int idx){
		if(boids.size()>idx){
			delete boids[idx];
			boids.erase(boids.begin()+idx);
		}
	}
	
	
	
	
};