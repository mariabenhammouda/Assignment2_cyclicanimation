//
//  Circles.hpp
//  Assignment2_cyclicanimation
//
//  Created by Maria  on 25/04/2022.
//

#define Circles_hpp

#pragma once
#include "ofMain.h"

class circles {

public:
  circles();
  void update();
  void draw();
  
  void setRadius(float radius);
  void setPosAmp(ofVec3f pos_amp);
  void setRotAmp(ofVec3f rot_amp);
  void setSpeedAmp(float speed_amp);
    void setcolor();
  
  
  
  
private:
  
  float radius;
  ofPoint pos;
  ofVec3f rotate;
  
  float speed;
  float speed_noise;
  float speed_amp;
  
  ofVec3f pos_noise;
  ofVec3f pos_amp;
  ofVec3f rot_noise;
  ofVec3f rot_amp;
    
  
  
};
