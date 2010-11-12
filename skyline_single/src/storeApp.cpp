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
	
	tweets = new TweetCollection();
	tweetsOnShow = new TweetCollection();
	lastTweetTime = 0;
	activeColumn = 0;
	
	
	defaultFont.loadFont("Coolvetica.ttf", 30, true, true);
	doubleSizedFont.loadFont("Coolvetica.ttf", 30 * 2, true, true);
	superSizedFont.loadFont("Coolvetica.ttf", 30 * 3, true, true);
	
	tweetListener.initAndRun();
//	tweetListener.tweets = tweets;
//	tweetListener.tweetsOnShow = tweetsOnShow;
}

//--------------------------------------------------------------
void storeApp::setupOSCListener(int port)
{
	receiver.setup(port);
}

//--------------------------------------------------------------
void storeApp::update() {
	double timestamp = ofGetElapsedTimeMillis();
	while(receiver.hasWaitingMessages() )
	{
		// get the next message
		ofxOscMessage m;
		receiver.getNextMessage( &m );
		
		if ( m.getAddress() == "/test" )
		{
			
		}
		else if ( m.getAddress() == "/tweet" )
		{
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
					//tweet = user + ": " + text;
					if (tweets->tweets->size() < 100)
					{
						tweets->push(new Tweet(user, text));
					}					
				}
			}
		}
		
	}
	
	if (ofGetElapsedTimeMillis() - timestamp > 10)
		cout << "msg parsed in " << ofGetElapsedTimeMillis() - timestamp << endl;
	
	if (ofGetElapsedTimeMillis() - lastTweetTime > 200)
	{
		if (tweets->tweets->size() > 0)
		{
			float margin = 20;
			Tweet *t = tweets->pop();
			string text = t->getUser() + ": " + t->getText();
			
			
			timestamp = ofGetElapsedTimeMillis();
			Tweet *newTweet = new Tweet(t->getUser(), t->getText());
			newTweet->textBlock.init(&defaultFont, &doubleSizedFont, &superSizedFont);
			newTweet->textBlock.setText(text);
			newTweet->textBlock.wrapTextInWidthHM(ofGetWidth()/6 - margin*2);
			newTweet->textBlock.setColor(255, 255, 255, 255);
			newTweet->bound = ofRectangle(
										  activeColumn * ofGetWidth()/6 + margin,
										  margin,
										  ofGetWidth()/6 - margin * 2,
										  ofGetHeight() - margin * 2
										  );
			newTweet->lastShownTime = ofGetElapsedTimeMillis();
			newTweet->live = true;
			
			tweetsOnShow->push(newTweet);
			//cout << "tweets on show: " << tweetsOnShow->tweets->size() << endl;
			
			tweets->tweets->pop_front();
			activeColumn = (activeColumn+1) % 6;
			
			if (tweetsOnShow->tweets->size() > 6)
			{
				tweetsOnShow->tweets->pop_front();
			}
			
			lastTweetTime = ofGetElapsedTimeMillis();
			
			cout << "new tweet init'd in " << ofGetElapsedTimeMillis() - timestamp << endl;
			
			//cout << tweets->tweets->size();
			//cout << " tweet in queue\n";
		}
		
	}
}

//--------------------------------------------------------------
void storeApp::draw() {
    // clear the screen
	ofBackground(0, 0, 0);
	
	ofSetColor(255, 0, 0);
	
	ofDrawBitmapString(ofToString(ofGetFrameRate(), 2), 20, ofGetHeight() - 20);
	
	//	cout<<"drawing " << tweetsOnShow->tweets->size() << " tweets" << endl;
	
	double timestamp = ofGetElapsedTimeMillis();
	for (int i=0; i<tweetsOnShow->tweets->size(); i++) {
		Tweet *t = tweetsOnShow->tweets->at(i);
		if (t->live)
		{
			ofRectangle rect = t->bound;
			//cout << "draw tweet at: " << rect.x << "," << rect.y << ","  << " with width " << rect.width << endl;
			t->textBlock.setColor(255, 255, 255,255);//ofMap(ofGetElapsedTimeMillis() - t->lastShownTime, 0, 600, 0, 255)
			t->textBlock.drawJustifiedHM(rect.x, rect.y, rect.width);
		}
	}
	cout << "drawing finished in " << ofGetElapsedTimeMillis() - timestamp << endl;
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

