#include "storeApp.h"

//--------------------------------------------------------------
void storeApp::setup() {
	// initialize app
	ofSetFrameRate(30);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
	ofSetBackgroundAuto(false);
    
	client.setup("settings.xml", this, false);
	setupOSCListener("config.xml");
	
	
	tweetFont.loadFont("HelveticaLight.ttf",80);
	tweet = "...";
	
    // set the random seed
	ofSeedRandom(1);
    
    // add a "randomly" placed ball
    Ball* ball = new Ball(ofRandom(0, client.getMWidth()), ofRandom(0, client.getMHeight()), client.getMWidth(), client.getMHeight());
    balls.push_back(ball);
    
	// start client
    client.start();
}

//--------------------------------------------------------------
void storeApp::setupOSCListener(string _fileString)
{
	cout << ("Loading OSC settings from file " + _fileString);
    
	ofxXmlSettings xmlReader;
    if (!xmlReader.loadFile(_fileString)) 
        cerr << ("ERROR loading XML file!");
	
	int port = xmlReader.getValue("settings:osc:port", 13000, 0);
	receiver.setup(port);
}

//--------------------------------------------------------------
void storeApp::update() {	
}

//--------------------------------------------------------------
void storeApp::draw() {
    if (client.isRendering()) {
        // before we do anything, the client must place itself within the 
        //  larger display (this is done with translate, so use push/pop if 
        //  you want to overlay any info on all screens)
        client.placeScreen();
        // clear the screen
        ofBackground(255, 255, 255);
        
        // move and draw all the balls
        for (int i = 0; i < balls.size(); i++) {
            balls[i]->calc();
            balls[i]->draw();
        }
		
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
						
					}
				}
			}
			
		}
        tweetFont.drawString(tweet, 20, 100);
		tweetFont.drawString(tweet, 20, 200);
		tweetFont.drawString(tweet, 20, 300);
		tweetFont.drawString(tweet, 20, 400);
		tweetFont.drawString(tweet, 20, 500);
		tweetFont.drawString(tweet, 20, 600);
		tweetFont.drawString(tweet, 20, 700);
		tweetFont.drawString(tweet, 20, 800);
		tweetFont.drawString(tweet, 20, 900);
		tweetFont.drawString(tweet, 20, 1000);
		tweetFont.drawString(tweet, 20, 1100);
		tweetFont.drawString(tweet, 20, 1200);
		tweetFont.drawString(tweet, 20, 1300);
		tweetFont.drawString(tweet, 20, 1400);
        // alert the server that you've finished drawing a frame
        client.done();
    }
}

//--------------------------------------------------------------
// Because we are NOT running in auto mode, no drawing can be
//  made in this callback function!
//--------------------------------------------------------------
void storeApp::frameEvent() {
    // read any incoming messages
    if (client.messageAvailable()) {
        vector<string> msg = client.getDataMessage();
        vector<string> xy = ofSplitString(msg[0], ",");
        float x = ofToInt(xy[0]);
        float y = ofToInt(xy[1]);
        Ball* ball = new Ball(x, y, client.getMWidth(), client.getMHeight());
        balls.push_back(ball);
    }
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
    // never include a ":" when broadcasting your message
    x += client.getXoffset();
    y += client.getYoffset();
    client.broadcast(ofToString(x) + "," + ofToString(y));
}

//--------------------------------------------------------------
void storeApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void storeApp::windowResized(int w, int h) {
}

