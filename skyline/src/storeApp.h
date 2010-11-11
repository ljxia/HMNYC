#ifndef _STORE_APP
#define _STORE_APP

#include "ofMain.h"
#include "mpeClientTCP.h"
#include "Ball.h"
#include "ofxOsc.h"

class storeApp : public ofBaseApp, public mpeClientListener {

	public:
        void setup();
		void setupOSCListener(string _fileString);
        void update();
        void draw();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);
        
        void frameEvent();
	
	
		ofTrueTypeFont tweetFont;
    
    private:
		ofxOscReceiver	receiver;
        mpeClientTCP  client;
        vector<Ball*> balls;
		string tweet;
    
};

#endif

