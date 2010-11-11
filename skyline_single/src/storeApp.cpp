#include "storeApp.h"


storeApp::storeApp(int port):ofBaseApp()
{
	this->oscClientPort = port;
}
//--------------------------------------------------------------
void storeApp::setup() {
	// initialize app
	ofSetFrameRate(30);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);

	setupOSCListener(this->oscClientPort);
	
	tweetFont.loadFont("HelveticaLight.ttf",80);
	tweet = "...";
	
	tweets = new TweetCollection();
	lastTweetTime = 0;
	
	myText.init("HeadlineA.ttf", 40);
}

//--------------------------------------------------------------
void storeApp::setupOSCListener(int port)
{
	receiver.setup(port);
}

//--------------------------------------------------------------
void storeApp::update() {
	
	while( receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		if ( m.getAddress() == "/test" )
		{
			
		}
		else if ( m.getAddress() == "/tweet" )
		{
			string msg_string;
			msg_string = m.getAddress();
			msg_string += ": ";
			
			if (m.getNumArgs() >= 2)
			{
				string user = "";
				if (m.getArgType(0) == OFXOSC_TYPE_STRING)
				{
					user = m.getArgAsString(0);
				}
				string text = "";
				if (m.getArgType(1) == OFXOSC_TYPE_STRING)
				{
					text = m.getArgAsString(1);
				}
				
				if (user != "" && text!= "") {
					//ofDrawBitmapString( user + ": " + text, 80, 200 );
					tweet = user + ": " + text;					
					tweets->push(Tweet(user, text));
				}
			}
		}
		
	}
	
	
	if (ofGetElapsedTimef() - lastTweetTime > 3)
	{
		if (tweets->tweets->size() > 0)
		{
			myText.setText(tweets->pop().getText());
			
			
			cout << endl << "------" << endl;
			cout << tweets->pop().getText() << endl;
			
			tweets->tweets->pop_front();
			
			myText.wrapTextInWidthHM(400);
			
			
			
			
			lastTweetTime = ofGetElapsedTimef();
			
			//cout << tweets->tweets->size();
			//cout << " tweet in queue\n";
		}
		
	}
}

//--------------------------------------------------------------
void storeApp::draw() {
    // clear the screen
	ofBackground(0, 0, 0);
	myText.setColor(255, 255, 255, 255);
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofRect(20, 0, 400-40, ofGetHeight());
	
	myText.drawJustifiedHM(20, 0, 400);
	
	
	ofNoFill();
	ofSetColor(255, 0, 0);
	ofRect(500 + 20, 0, 400, ofGetHeight());
	
	myText.drawLeftHM(500 + 20,0);
}

//--------------------------------------------------------------
void storeApp::keyPressed(int key) {
}

//--------------------------------------------------------------
void storeApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void storeApp::mouseMoved(int x, int y) {
}

//--------------------------------------------------------------
void storeApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void storeApp::mousePressed(int x, int y, int button) {
}

//--------------------------------------------------------------
void storeApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void storeApp::windowResized(int w, int h) {
}

