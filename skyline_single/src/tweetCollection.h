/*
 *  tweetCollection.h
 *  store_single
 *
 *  Created by liangjie on 2010-11-07.
 *  Copyright 2010 Feed Our Cats. All rights reserved.
 *
 */

#pragma once
#include "ofMain.h" 
#include "tweet.h"
#include <deque>

class TweetCollection
{
public:
	TweetCollection();
	int push(Tweet *t);
	Tweet *pop();
	
	deque<Tweet *> *tweets;
};
