#ifndef _STORE_APP
#define _STORE_APP

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxTextSuite.h"
#include "tweetCollection.h"
#include "tweetListenerThread.h"

class storeApp : public ofBaseApp{

public:
	storeApp(int port);
	void setup();
	void setupOSCListener(int port);
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);
		
	tweetListenerThread tweetListener;

	ofTrueTypeFont  defaultFont;
	ofTrueTypeFont	doubleSizedFont;
	ofTrueTypeFont	superSizedFont;

private:
	int oscClientPort;
	ofxOscReceiver	receiver;
	string tweet;
	TweetCollection *tweets;
	TweetCollection *tweetsOnShow;
	
	double lastTweetTime; 
	int activeColumn;
    
};

#endif

