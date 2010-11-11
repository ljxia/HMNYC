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

class Tweet
{
public:
	Tweet(string user, string text);
	string getUser(){
		return _user;
	}
	string getText(){
		return _text;
	}
	
private:
	string _user;
	string _text;
	void ProcessText();
	
};