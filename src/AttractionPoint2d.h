#pragma once


class AttractionPoint2d {
public:
	
	float x, y, force, sensorDist;

	float halfDist;
	
	AttractionPoint2d() {
		x = y = force = sensorDist = halfDist = 0.0f;
	}

	AttractionPoint2d(float _x, float _y, float _f, float _sensor) {
		x = _x;
		y = _y;
		force = _f;
		sensorDist = _sensor;
		halfDist = sensorDist / 2.0f;
	}
	
	void draw(){
		ofRect(x-halfDist, y-halfDist, sensorDist, sensorDist);
		ofRect(x,y,3,3);
	}
	
	
};
