/*
 *  tweet.cpp
 *  store_single
 *
 *  Created by liangjie on 2010-11-07.
 *  Copyright 2010 Feed Our Cats. All rights reserved.
 *
 */
#include "tweet.h"
#include "Poco/Exception.h"
#include "Poco/RegularExpression.h"

using Poco::Exception;
using Poco::RegularExpression;

Tweet::Tweet(string user, string text)
{
	_user = user;
	_text = text;
	
	ProcessText();
}

void Tweet::ProcessText()
{
	if (!_text.empty())
	{
		try 
		{
			RegularExpression reMention("(@\\w+)",RegularExpression::RE_CASELESS);
			RegularExpression::MatchVec matches;
			reMention.match(_text, 0, matches);
			
			//re.subst(_text, "", RegularExpression::RE_GLOBAL);
			
			if (matches.size())
			{
				//cout << _text.substr(matches[1].offset, matches[1].length) << endl;
			}
			
			
			RegularExpression reUrl("((https?|ftp|gopher|telnet|file|notes|ms-help):((//)|(\\\\))+[\\w\\d:#@%/;$()~_?\\+-=\\\\\\.&]*)");
			reUrl.match(_text, 0, matches);
			
			//re.subst(_text, "", RegularExpression::RE_GLOBAL);
			
			if (matches.size())
			{
				//cout << _text.substr(matches[1].offset, matches[1].length) << endl;
			}
			
			reUrl.subst(_text, "", RegularExpression::RE_GLOBAL);
			
			
		}
		catch (Exception& exc)
		{
			std::cerr << exc.displayText() << std::endl;
		}

		
	}
}