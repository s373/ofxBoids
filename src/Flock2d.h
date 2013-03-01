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

#include "Boid2d.h"
#include "AttractionPoint2d.h"

class Flock2d {
public:
	
	vector <Boid2d *>				boids;
	vector <AttractionPoint2d *>	attractionPoints;

	// public ArrayList<Team> teams; // superclass flockTeam, etc

	// forces
	float separate, align, cohesion;
	float distSeparation, distAlign, distCohesion;
	float maxTurn, maxSpeed, maxForce;

	// bounds
	float minX, minY, maxX, maxY, boundsWidth, boundsHeight;
	int boundmode;
	
	// new
	float dt;
	float attraction, attractiondeviation;

	Flock2d(){
		clear();
		separate = align = cohesion = distSeparation = distAlign = distCohesion = maxTurn =
		maxSpeed = maxForce = minX = maxX = maxY = boundsWidth = boundsHeight = 0;
		boundmode = 0;
		dt = 1.0f;
		attraction = attractiondeviation = 0.0f;
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
	
	
	Flock2d * setup(int num, float lx, float ly) {
		return setup(num, lx, ly, 1);
	}

	Flock2d * setup(int num, float lx, float ly, float dev) {
		init(num, lx, ly, dev);
		return this;
	}

	void init(int num, float lx, float ly, float dev) {

		for (int i = 0; i < num; i++) {
			Boid2d * b = new Boid2d(this);
			// need to be scattered or else no work
			b->setLoc(lx + ofRandom(-dev, dev),
					ly + ofRandom(-dev, dev));
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
		setBounds(0, 0, 700, 700);
	}

	// metodos

	Flock2d * add(float lx, float ly) {
		Boid2d * b = new Boid2d();//(this); // first constructor is zeroing nicely
		b->setFlock(this);
		
		b->setLoc(lx, ly);
		
		b->attr = attraction + ofRandom(-attractiondeviation, attractiondeviation);
		
		boids.push_back(b);//boids.add(b);
		return this;
	}

	
	Flock2d * setDt(const float d){
		dt = d;
		return this;
	}
	
	
	
	Flock2d * setMaxTurn(float mt) {
		maxTurn = mt;
		return this;
	}

	Flock2d * setMaxSpeed(float ms) {
		maxSpeed = ms;
		return this;
	}

	Flock2d * setMaxForce(float mf) {
		maxForce = mf;
		return this;
	}
	Flock2d * setAttraction(float mf) {
		attraction = mf;
		doAttraction();
		return this;
	}
	Flock2d * setAttractionDev(float mf) {
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

	Flock2d * setSeparate(float forceSeparate) {
		this->separate = forceSeparate;
		return this;
	}

	Flock2d * setAlign(float forceAlign) {
		this->align = forceAlign;
		return this;
	}

	Flock2d * setCohesion(float forceCohesion) {
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
	Flock2d * setDistSeparation(float distSeparation) {
		this->distSeparation = distSeparation;
		return this;
	}

	/**
	 * @return the distNeighborDistance
	 */
	Flock2d * setDistAlign(float d) {
		distAlign = d;
		return this;
	}

	/**
	 * @return the distNeighborDistance
	 */
	Flock2d * setDistCohesion(float d) {
		distCohesion = d;
		return this;
	}

	/**
	 *
	 */
	Flock2d * setBounds(float minx, float miny, float maxx, float maxy) {
		minX = minx;
		minY = miny;
		maxX = maxx;
		maxY = maxy;
		boundsWidth = maxX - minX;
		boundsHeight = maxY - minY;

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
	Flock2d * setBoundmode(int boundmode) {
		this->boundmode = boundmode;
		return this;
	}

	/*
	 * update func
	 */
	void update() {
		int boidsSize = boids.size();
		for (int i = 0; i < boidsSize; i++) {
//			Boid2d *b = boids.get(i);
			boids[i]->update(dt);
		}
	}

	// public void interfere(Flock2d otherFlock, float amount) {
	//
	// int boidsSize = boids.size();
	// for (int i = 0; i < boidsSize; i++) {
	// Boid2d b = boids.get(i);
	// b.update(amount);
	// }
	// }

	// public void set() {
	// int boidsSize = boids.size();
	// for (int i = 0; i < boidsSize; i++) {
	// Boid2d b = boids.get(i);
	// b.setFlock(this);
	// }
	// }

	int size() {
		return boids.size();
	}

	Boid2d * get(int idx) {
		return boids.at(idx);
	}

	// / attraction points

	Flock2d * addAttractionPoint(float x, float y, float force,
			float sensorDist) {
		AttractionPoint2d * ap = new AttractionPoint2d(x, y, force, sensorDist);
		attractionPoints.push_back(ap);
		return this;
	}

	vector<AttractionPoint2d*>* getAttractionPoints() {
		return &attractionPoints;
	}

	bool hasAttractionPoints() {
		return attractionPoints.size() > 0;
	}

	void changeAttractionPoint(int id, float x, float y, float force,
			float sensorDist) {
//		try {
		
		AttractionPoint2d * ap = attractionPoints[id];//.get(id);
		if(ap!=NULL){
			ap->x = x;
			ap->y = y;
			ap->force = force;
			ap->sensorDist = sensorDist;
		} else {
			cout << " attraction point null at id: " << id << endl;
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