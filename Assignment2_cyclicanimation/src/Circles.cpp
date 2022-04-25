//
//  Circles.cpp
//  Assignment2_cyclicanimation
//
//  Created by Maria  on 25/04/2022.
//

#include "Circles.hpp"
circles::circles() {
    //class of circles to allow control of radius, position, rotation and more through the .set function of vectors and class functions
    
    //initialize the parameters
  radius = ofGetHeight()/4;
  pos.set(0, 0, 0);
  rotate.set(0, 0, 0);
  
  speed = 0.001;
  speed_noise = ofRandom(10);
  speed_amp = ofRandom(10)/10000;
  pos_noise.set(ofRandom(10), ofRandom(10), ofRandom(10));
  pos_amp.set(0, 0, 0);
  rot_noise.set(ofRandom(10), ofRandom(10), ofRandom(10));
  rot_amp.set(0, 0, 0);
}

void circles::update() {
    //circles parameters should be updates with each frame, assign the speed to of noise with noise seed
  speed = ofNoise(speed_noise)*speed_amp;
  //vec3f allows the usage of .set .get functions, vec3f is used despite the artwork being 2d
    //of noise ot control position
  pos.set((ofNoise(pos_noise.x)*2-1)*pos_amp.x,
          (ofNoise(pos_noise.y)*2-1)*pos_amp.y,
          (ofNoise(pos_noise.z)*2-1)*pos_amp.z);
    //of noise ot control rotation
  rotate.set((ofNoise(rot_noise.x)*2-1)*rot_amp.x,
             (ofNoise(rot_noise.y)*2-1)*rot_amp.y,
             (ofNoise(rot_noise.z)*2-1)*rot_amp.z);
  //increment the speed, pos, rot noise seed after each update
  speed_noise += 0.01;
  
  pos_noise.x += speed;
  pos_noise.y += speed;
  pos_noise.z += speed;
  
  rot_noise.x += speed;
  rot_noise.y += speed;
  rot_noise.z += speed;

}

void circles::draw() {
  ofNoFill();
  ofPushMatrix();
  ofTranslate(pos);
    //rotate by the angle controlled from the gui
  ofRotateX(rotate.x);
  ofRotateY(rotate.y);
  ofRotateZ(rotate.z);

    ofSetLineWidth(3);
    //draw the planet ring of radius controlled by gui slider
    ofDrawCircle(0, 0, 0, radius);
    
  
  ofPopMatrix();
}
//creates functions in circles class to allow to update the parametes from gui in app.cpp
void circles::setRadius(float _radius) {
  radius = _radius;
}

void circles::setPosAmp(ofVec3f _pos_amp) {
  pos_amp = _pos_amp;
}

void circles::setRotAmp(ofVec3f _rot_amp) {
  rot_amp = _rot_amp;
}

void circles::setSpeedAmp(float _speed_amp) {
  speed_amp = _speed_amp;
}


