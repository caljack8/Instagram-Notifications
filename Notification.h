#ifndef Notification_h
#define Notification_h
#include <string>
#include <list>

//declare Notification class
class Notification {

public:

	//Notification constructor
	Notification(const std::string& auser);

	virtual ~Notification() {};

	//accesor for every notification and all of it's children
	const std::string& get_user() {return user;}

	//accesor for Notification children
	virtual const std::string get_type() const {return "notification";}

	//functions for notification children to help printing
	virtual const std::string make_string();
	virtual const std::string make_aggregate(std::list<Notification*> aggregate);

protected:

	//person who notifys you username name
	std::string user;
};

//Declares the like class as a child of the Notifcations classs
class Like : public Notification {

public:

	//Like constructor
	Like(const std::string& auser) : Notification(auser) {};

	~Like() {};

	//accessors
	const std::string get_type() const {return "like";}

	//for printing
	const std::string make_string();
	const std::string make_aggregate(std::list<Notification*> aggregate);
};

//Declares the Tag class as a child of the Notifations class
class Tag : public Notification {

public:

	//Tag Constructor
	Tag(const std::string& auser) : Notification(auser) {};

	~Tag() {};
	
	//accessor
	const std::string get_type() const {return "tag";}

	//for printing
	const std::string make_string();
	const std::string make_aggregate(std::list<Notification*> aggregate);
};

//declares the Comment class as a child of the Notifcations class
class Comment : public Notification {

public:

	//Comment constructor
	Comment(const std::string& auser) : Notification(auser) {};

	~Comment() {};

	//accessors
	const std::string get_type() const {return "comment";}

	//for printing
	const std::string make_string();
	const std::string make_aggregate(std::list<Notification*> aggregate);
};


//declares the new follower classs as a child of the Notification class
class NewFollower : public Notification {

public:

	//NewFollower constructor
	NewFollower(std::string auser) : Notification(auser) {};

	~NewFollower() {};

	//accessor
	const std::string get_type() const {return "newfollower";}

	//for printing
	const std::string make_string();
	const std::string make_aggregate(std::list<Notification*> aggregate);
};

//declares the messageRequest class as a child of the notification class
class MessageRequest : public Notification {

public:

	//Message Request constructor
	MessageRequest(const std::string& auser) : Notification(auser) {};

	~MessageRequest() {};

	//accessor
	const std::string get_type() const {return "messagerequest";}

	//for printing
	const std::string make_string();
	const std::string make_aggregate(std::list<Notification*> aggregate);
};

#endif