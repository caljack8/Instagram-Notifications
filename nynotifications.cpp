#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <stack>
#include <list>
#include "Notification.h"

void make_output(Notification* noti, std::list<Notification*>&  aggregate, std::stack<std::string>& output){

    //if the list is empty add this notification to the list
    if(aggregate.empty()){
        aggregate.push_front(noti);
        return;
    }

    //if the notification is the same type as what's in the list add it to the list and return
    if(noti->get_type() == aggregate.front()->get_type()){
        aggregate.push_front(noti);
        return;
    }

    //if the size of the aggregate notifications is bigger than 3 make the aggregate output add it to the stack
    //and make this notifications output and add it to the stack
    if(aggregate.size() > 3){

        std::string agg_output = aggregate.back()->make_aggregate(aggregate);
        output.push(agg_output);

        //delete the dynamic memory from the list
        while(!aggregate.empty()){
            delete aggregate.back();
            aggregate.back() = NULL;
            aggregate.pop_back();
        }

        aggregate.push_front(noti);
        return;
    }

    //if it's less then 3 go through the list and add each notifications output to the output stack
    while(!aggregate.empty()){
        std::string noti_output = aggregate.back()->make_string();
        output.push(noti_output);

        //delete the dynamic memory from the list
        delete aggregate.back();
        aggregate.back() = NULL;

        aggregate.pop_back();
    }

    //add this notification to the list to start a new chck of aggregate notifications
    aggregate.push_front(noti);
}

int main(int argc, char* argv[]){

	//check the correct amount of arguments
	if(argc != 6 ){
		std::cerr << "Not the correct amount of arguments, Goodbye." << std::endl;
		exit(1);
	}

	std::ofstream ofile(argv[4]);
	//checks if the out file opened correctly
  	try{
        if(!ofile.good()) { 
    	   throw std::string("Failed to open ");
        }
    }
    catch(std::string& error){
        std::cerr << error << argv[4] << std::endl;
        exit(1);
    }

    std::ifstream userFile(argv[2]);
	//checks if the user file opened correctly
    try{
        if(!userFile.good()) { 
           throw std::string("Failed to open ");
        }
    }
    catch(std::string& error){
        std::cerr << error << argv[2] << std::endl;
        exit(1);
    }

    std::ifstream postFile(argv[1]);
	//checks if the posts file opened correctly
    try{
        if(!postFile.good()) { 
           throw std::string("Failed to open ");
        }
    }
    catch(std::string& error){
        std::cerr << error << argv[1] << std::endl;
        exit(1);
    }

    std::ifstream eventsFile(argv[3]);
	//checks if the events file opened correctly
    try{
        if(!eventsFile.good()) { 
           throw std::string("Failed to open ");
        }
    }
    catch(std::string& error){
        std::cerr << error << argv[3] << std::endl;
        exit(1);
    }

    //put the users name into a string
    std::string username = argv[5];

    //make bools to know what information is needed from the events
    bool get_likes = false;
    bool get_tags = false;
    bool get_comments = false;
    bool get_newfollow = false;
    bool get_messagerequest = false;

    //read in the information from the user file
    std::string userline;
    while (std::getline(userFile, userline)) {
		
		//if you find the users username int this line, get the information from the line and break	
        if(userline.find(username) != std::string::npos){

        	//get the starting positions for the preferences of the user
        	int pause_pos = userline.find("\"pauseAll\": \"")+13;
            int like_pos = userline.find("\"likes\": \"")+10;
            int tag_pos = userline.find("\"tags\": \"")+9;
            int comment_pos = userline.find("\"comments\": \"")+13;
            int follow_pos = userline.find("\"newFollowers\": \"")+17;
            int message_pos  = userline.find("\"messageRequests\": \"")+20;

            //get the string for the preferences of the user
            std::string pause = userline.substr(pause_pos, userline.find("\"", pause_pos) - pause_pos);
            std::string like = userline.substr(like_pos, userline.find("\"", like_pos) - like_pos);
            std::string tag = userline.substr(tag_pos, userline.find("\"", tag_pos) - tag_pos);
            std::string comment = userline.substr(comment_pos, userline.find("\"", comment_pos) - comment_pos);
            std::string follow = userline.substr(follow_pos, userline.find("\"", follow_pos) - follow_pos);
            std::string message = userline.substr(message_pos, userline.find("\"", message_pos) - message_pos);

            //if the user doesn't want notifications end the program
            if(pause == "true"){
            	return 0;
            }

            //set the bools of the useres preferences to true if the strings are true
            if(like == "true"){
            	get_likes = true;
            }

            if(tag == "true"){
            	get_tags = true;
            }

            if(comment == "true"){
            	get_comments = true;
            }

            if(follow == "true"){
            	get_newfollow = true;
            }

            if(message == "true"){
            	get_messagerequest = true;
            }

            break;
        }
    }

    //don't need the user file anymore, so close it
    userFile.close();

    //again if they want no notifications output nothing
    if(!get_likes && !get_tags && !get_comments && !get_newfollow && !get_messagerequest){
        return 0;
    }

    //set of the post id's correspoding to our users posts
    std::set<std::string> user_posts;

    //read in the information from the post file
    while (std::getline(postFile, userline)){

        //find the owner of the posts username
        int owner_username_pos = userline.find("\"ownerUsername\":\"")+17;
        std::string owner_username = userline.substr(owner_username_pos, userline.find("\"", owner_username_pos) - owner_username_pos);

    	//if you find the users username int this line, get the id from it and add it to the set of posts
        if(username == owner_username){
        	//get the users post  id and add it to the set of ids
        	int id_pos = userline.find("\"id\":\"")+6;
        	std::string id = userline.substr(id_pos, userline.find("\"", id_pos) - id_pos);
        	user_posts.insert(id);
        }
    }

    //don't need the posts file anymore so close it
    postFile.close();

    //strings to take in the information from the events file
    std::string user, command, reciever;

    //make the stack which will hold the strings to output and the list to hold aggregate Notifications
    std::stack<std::string> output;
    std::list<Notification*> aggregate;

    //go through the events file and add the output to the stack if the user wants it
    while(eventsFile >> user >> command >> reciever){

        //if the recievers username is our users or if it's not one of their posts skip this line
        if(reciever != username && user_posts.find(reciever) == user_posts.end()){
            continue;
        }

        //otherwise find the notification that is happening and make the output for it
        else if(command == "likes" && get_likes){
            Like* noti = new Like (user);
            make_output(noti, aggregate, output);
            continue;
        }

        else if(command == "tags" && get_tags){
            Tag* noti = new Tag (user);
            make_output(noti, aggregate, output);
            continue;
        }

        else if(command == "comments_on" && get_comments){
            Comment* noti = new Comment (user);
            make_output(noti, aggregate, output);
            continue;
        }

        else if(command == "follows" && get_newfollow){
            NewFollower* noti = new NewFollower (user);
            make_output(noti, aggregate, output);
            continue;
        }

        else if(command == "messageRequests" && get_messagerequest){
            MessageRequest* noti = new MessageRequest (user);
            make_output(noti, aggregate, output);
            continue;
        }
    }

    //don;t need the events file anymore so close it
    eventsFile.close();

    //if there are leftover notifications in the list of aggregate add them to the stack of strings
    if(aggregate.size() > 3){
        std::string agg_output = aggregate.back()->make_aggregate(aggregate);
        output.push(agg_output);
        
        //delete the dynamic memory from the list
        while(!aggregate.empty()){
            delete aggregate.back();
            aggregate.back() = NULL;
            aggregate.pop_back();
        }
    }

    else{
        
        //if it's less then 3 go through the list and add each notifications output to the output stack
        while(!aggregate.empty()){
            std::string noti_output = aggregate.back()->make_string();
            output.push(noti_output);

            //delete the dynamic memory
            delete aggregate.back();
            aggregate.back() = NULL;

            aggregate.pop_back();
        }
    }

    //variable to count how many lines have been output
    int line_count = 0;

    //output the strings in the stack while it;s not empty and you have done less that 101 linea in all
    while(!output.empty() && line_count < 100){
        ofile << output.top() << std::endl;
        output.pop();
        line_count++;
    }

    ofile.close();

    return 0;
}