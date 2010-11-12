/*
 *  tweetListenerThread.h
 *  store_single
 *
 *  Created by liangjie on 2010-11-11.
 *  Copyright 2010 Feed Our Cats. All rights reserved.
 *
 */

#pragma once

#include "ofMain.h"
#include "ofxRuiThread.h"
#include "tweet.h"
#include "tweetCollection.h"

class tweetListenerThread:public ofxRuiThread{
public:
	
	ofxOscReceiver *receiver;
	TweetCollection *tweets;
	TweetCollection *tweetsOnShow;
	
	ofTrueTypeFont  defaultFont;
	ofTrueTypeFont	doubleSizedFont;
	ofTrueTypeFont	superSizedFont;
	
	int activeColumn;
	double lastTweetTime; 
	
	tweetListenerThread()
	{
		activeColumn = 0;
		lastTweetTime = 0;
		
		defaultFont.loadFont("Coolvetica.ttf", 30, true, true);
		doubleSizedFont.loadFont("Coolvetica.ttf", 30 * 2, true, true);
		superSizedFont.loadFont("Coolvetica.ttf", 30 * 3, true, true);
	}
	
	void updateThread(){
		//cout << "thread " << activeColumn << endl;
		activeColumn ++;
	}
};  