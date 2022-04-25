#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    //Load mp3 audio to app
    sound.load("Sound.mp3");
    sound.play();
    //keep looping the audio while app is running
    sound.setLoop(true);
    recenttime=ofGetSystemTimeMillis();
   // ofBackground(0);
  ofSetFrameRate(40);
  ofSetBackgroundAuto(false);
  ofSetCircleResolution(60);
  //  planet.load("planet.png"); //load the image into xcode
   // planet.getTexture().setTextureWrap(GL_REPEAT,GL_REPEAT);
  //set up gui with the parameters of speed, position, planet, volume, volumedecay and radius
  gui.setup();
  gui.add(circles_num.set("number of circles", 1, 1,10));
    gui.add(volume.set("volume", 0.5, 0.0,1.0));
    gui.add(decay.set("Decay", 0.5, 0.0,1.0));
  gui.add(radius.set("radius", ofGetHeight()/4, 1, ofGetHeight()/2));
  gui.add(pos.set("pos",
                  ofVec3f(0),
                  ofVec3f(0),
                  ofVec3f(ofGetWidth()/2, ofGetHeight()/2, 1000)));
  gui.add(rot.set("rot",
                  ofVec3f(0,0,0),
                  ofVec3f(0),
                  ofVec3f(720, 720, 720)));
  gui.add(speed.set("speed", 0, 0.01, 0.1));
    gui.add(bluePlanet.set("Neptune",true));
    gui.add(greyPlanet.set("Mercury",false));
    gui.add(yellowPlanet.set("Venus",false));
    recenttime=ofGetSystemTimeMillis();

  guidraw = true;
    fft= new float[128];
    band=64;
}

//--------------------------------------------------------------
void ofApp::update(){
    //update the sound information at each fram
        ofSoundUpdate();
    //assing the current volume from gui to the volume of sound
    sound.setVolume(volume);
    //get the range of band from the audio
    soundSpectrum= ofSoundGetSpectrum(band);
    //store the sound data to an array
    for(int i=0; i<band; i++){
        fft[i]*=decay;
        if(fft[i]<soundSpectrum[i]){
            fft[i]=soundSpectrum[i];
        }
    }
    float time = ofGetElapsedTimef()/10; //Get time in seconds
    float value = sin( time * M_TWO_PI );
    //Map value from [-1,1] to [0,255]
    //set changing background color based on the time elapsed
    float r = ofMap( value, -1, 1, 0, 75 );
    float g = ofMap( value, -1, 1, 0, 90 );
    float b = ofMap( value, -1, 1, 0, 200 );
    ofBackground( r, g, b );
  //  ofBackground(col);
   /* if(ofGetSystemTimeMillis()-recenttime >10){
        if( counter< 200){
            counter+=1;
            
        }else
            counter =0;
    
        col.set(counter%50,counter%255,counter%255);
       
        recenttime=ofGetSystemTimeMillis();
        
    }*/
    
    //if the number of elements in circle array are less than the max circles then create circle, if not then erease the first circle created
  while (circle.size() != circles_num){
    if (circle.size() < circles_num) {
      circles s;
        circle.push_back(s);
    } else if (circle.size() > circles_num) {
        circle.erase(circle.begin());
    }
  }
// create the circle, set radius, pos, rot
  for (int i = 0; i < circle.size(); i++) {
      
     
      circle[i].update();
    
      circle[i].setRadius(radius);
      circle[i].setPosAmp(pos);
      circle[i].setRotAmp(rot);
      circle[i].setSpeedAmp(speed);
      
     
      
  }
    //assign texture based on the toggle in gui
    if(greyPlanet){
        planet.load("mercury.jpeg"); //load the image into xcode
          planet.getTexture().setTextureWrap(GL_REPEAT,GL_REPEAT); //assign the texture to object planet then wrap texture
        
        
    }
    else if(bluePlanet){
        planet.load("neptune.jpeg"); //load the image into xcode
        planet.getTexture().setTextureWrap(GL_REPEAT,GL_REPEAT);//assign the texture to object planet then wrap texture
        
    }
   
    else if(yellowPlanet){
        planet.load("venus.jpeg"); //load the image into xcode
          planet.getTexture().setTextureWrap(GL_REPEAT,GL_REPEAT);//assign the texture to object planet then wrap texture
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
 
  
    //save the current scene positions and details
    ofPushMatrix();
    //create color palette through a vector of type color
    vector<ofColor> color_list = { ofColor(111, 29, 27), ofColor(187, 148, 87), ofColor(67, 40, 24),ofColor(153, 88, 42),ofColor(255, 230, 167) };
    //sound reactive drawing
    ofPushStyle();
    for(int i=0; i<band;i++){
        
        ofSetColor(color_list[i]);
        //assign the radius of the circle based on the volume of the audio
        ofDrawCircle(ofRandom(ofGetWidth()), ofRandom(ofGetHeight()), fft[i]*100);
        //int x=ofRandom(ofGetWidth()/1000);
       // int y=ofRandom(ofGetHeight()/1000);
      //  ofDrawTriangle(x, y, x*y, x*fft[i], y*fft[i], x*y*fft[i]);
    }
    ofPopStyle();
    //move to the center of the screen
    ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
    //create a sphere fo type sphereprimitive then assign it a texture a
    ofSpherePrimitive sphere;
    sphere.mapTexCoordsFromTexture(planet.getTexture());
   
    ofSetColor(255);
    planet.getTexture().bind();
    sphere.setRadius(ofGetWidth()/10);
 
    sphere.draw();
    planet.getTexture().unbind();
  


    ofPushStyle();
  for (int i = 0; i < circle.size(); i++) {
     
      //draw gold ring for the central planet
      ofSetColor(248, 222, 126);
      circle[i].draw();
      
  }
    ofPopStyle(); //restore back to previous drawing settings
    
  
  ofPopMatrix();
  
  if(guidraw) {
    gui.draw();
  }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

  //hide gui at press of key h
  if (key == 'h') {
    guidraw = false;
  }
    if (key == 'g') {
      guidraw = true;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){

}
void ofApp::audioReceived( float *input, int bufferSize, int nChannels ){
 //... use input array here
}

