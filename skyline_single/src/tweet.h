/*
 *  tweet.h
 *  store_single
 *
 *  Created by liangjie on 2010-11-07.
 *  Copyright 2010 Feed Our Cats. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h" 
#include "ofxTextBlock.h"

class Tweet
{
public:
	Tweet(string user, string text);
	~Tweet(){};
	string getUser(){
		return _user;
	}
	string getText(){
		return _text;
	}
	
	double lastShownTime;
	bool live;
	ofRectangle bound;
	ofxTextBlock textBlock;
	
private:
	string _user;
	string _text;
	void ProcessText();
	
};