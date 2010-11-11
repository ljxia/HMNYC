/*
 *  tweetCollection.cpp
 *  store_single
 *
 *  Created by liangjie on 2010-11-07.
 *  Copyright 2010 Feed Our Cats. All rights reserved.
 *
 */

#include "tweetCollection.h"

TweetCollection::TweetCollection()
{
	tweets = new deque<Tweet *>();
}

int TweetCollection::push(Tweet *t)
{
	tweets->push_back(t);
	return tweets->size();
}

Tweet *TweetCollection::pop()
{
	return tweets->front();
}