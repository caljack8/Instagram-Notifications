#include "Notification.h"
#include <string>
#include <list>

//Notification constructor
Notification::Notification(const std::string& auser){

	user = auser;
}

//make string and aggregate string for a base notofcation
const std::string Notification::make_string(){
	return user+" has notified you.";
}

const std::string Notification::make_aggregate(std::list<Notification*> aggregate){

	//add the most recent user to the string and pop it out of the list
	std::string agg_output = aggregate.front()->get_user() + ", ";
	aggregate.pop_front();

	//add the second most recent user to the output string along with the size
	agg_output = agg_output + aggregate.front()->get_user() + " and " + std::to_string(aggregate.size()-1) + " others has notified you.";

	//return the string
	return agg_output;
}

//make string and aggregate string for like class
const std::string Like::make_string(){
	return user+" liked your post."; 
}

const std::string Like::make_aggregate(std::list<Notification*> aggregate){

	//add the most recent user to the string and pop it out of the list
	std::string agg_output = aggregate.front()->get_user() + ", ";
	aggregate.pop_front();

	//add the second most recent user to the output string along with the size
	agg_output = agg_output + aggregate.front()->get_user() + " and " + std::to_string(aggregate.size()-1) + " others liked your post.";

	//return the string
	return agg_output;
}

//make string and aggregate string for tag class
const std::string Tag::make_string(){
	return user+" tagged you in a post."; 
}

const std::string Tag::make_aggregate(std::list<Notification*> aggregate){

	//add the most recent user to the string and pop it out of the list
	std::string agg_output = aggregate.front()->get_user() + ", ";
	aggregate.pop_front();

	//add the second most recent user to the output string along with the size
	agg_output = agg_output + aggregate.front()->get_user() + " and " + std::to_string(aggregate.size()-1) + " others tagged you in a post.";

	//return the string
	return agg_output;
}

//make string and aggregate string for comment class
const std::string Comment::make_string(){
	return user+" commented on your post."; 
}

const std::string Comment::make_aggregate(std::list<Notification*> aggregate){

	//add the most recent user to the string and pop it out of the list
	std::string agg_output = aggregate.front()->get_user() + ", ";
	aggregate.pop_front();

	//add the second most recent user to the output string along with the size
	agg_output = agg_output + aggregate.front()->get_user() + " and " + std::to_string(aggregate.size()-1) + " others commented on your post.";

	//return the string
	return agg_output;
}

//make string and aggregate string for newfollower class
const std::string NewFollower::make_string(){
	return user+" started following you."; 
}

const std::string NewFollower::make_aggregate(std::list<Notification*> aggregate){

	//add the most recent user to the string and pop it out of the list
	std::string agg_output = aggregate.front()->get_user() + ", ";
	aggregate.pop_front();

	//add the second most recent user to the output string along with the size
	agg_output = agg_output + aggregate.front()->get_user() + " and " + std::to_string(aggregate.size()-1) + " others started following you.";

	//return the string
	return agg_output;
}

//make string and aggregate string for message request class
const std::string MessageRequest::make_string(){
	return user+" wants to send you a message."; 
}

const std::string MessageRequest::make_aggregate(std::list<Notification*> aggregate){

	//add the most recent user to the string and pop it out of the list
	std::string agg_output = aggregate.front()->get_user() + ", ";
	aggregate.pop_front();

	//add the second most recent user to the output string along with the size
	agg_output = agg_output + aggregate.front()->get_user() + " and " + std::to_string(aggregate.size()-1) + " others wants to send you a message.";

	//return the string
	return agg_output;
}