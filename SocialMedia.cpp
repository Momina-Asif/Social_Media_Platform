#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Helper
{
public:
	static int StringLength(const char* str)
	{
		int i;
		for (i = 0; str[i] != '\0'; i++)
		{
		}
		return i;
	}
	static void StringCopy(const char* string1, char* string2)
	{
		char* tempDest = string2;
		for (const char* tempSrc = string1; *tempSrc != '\0'; tempSrc++, tempDest++)
		{
			*tempDest = *tempSrc;
		}
		*tempDest = '\0';
	}
	static char* GetStringFromBuffer(const char* buffer)
	{
		int strLen = StringLength(buffer);
		char* str = 0;

		if (strLen > 0)
		{
			str = new char[strLen + 1];
			StringCopy(buffer, str);
		}
		return str;
	}
	static bool CompareString(char* str1, const char* str2)
	{
		for (int i = 0; str1[i] != '\0' || str2[i] != '\0'; i++)
		{
			if (str1[i] != str2[i])
			{
				return false;
			}
		}
		return true;
	}
	static char* StringConcatenate(const char* string1, const char* string2)
	{
		int length1 = StringLength(string1);
		int length2 = StringLength(string2);

		int length3 = length2 + length1 + 1;
		char* tempBuffer = new char[length3];
		int i = 0, j = 0;

		for (; i < length1; i++)
		{
			tempBuffer[i] = string1[i];
		}
		for (j = 0; j < length2; i++, j++)
		{
			tempBuffer[i] = string2[j];
		}
		tempBuffer[length3 - 1] = '\0';
		return tempBuffer;
	}
};

class User;
class Helper;
class Pages;
class Memory;
class Object;
class Date;
class Post;
class Activity;

class Object
{
	char* ID;

public:
	virtual ~Object()
	{
		delete ID;
	}
	void DeleteID()
	{
		delete[]ID;
	}
	char* GetID()
	{
		return ID;
	}
	void SetID(char* id)
	{
		ID = Helper::GetStringFromBuffer(id);
	}
	virtual void AddPostToTimeline(Post*) = 0;
	virtual void print(int i) = 0;
};

class Date
{
	int day;
	int month;
	int year;

public:
	~Date()
	{
		day = 1;
		month = 1;
		year = 2000;
	}
	int GetDateDifference()
	{
		return CurrentDate.year - year;
	}
	static Date CurrentDate;
	static void SetCurrentDate(int d = 1, int m = 1, int y = 2000)
	{
		CurrentDate.day = d;
		CurrentDate.month = m;
		CurrentDate.year = y;
		cout << "Current Date is set to ";
		CurrentDate.print();
	}
	Date(int d = 1, int m = 1, int y = 2000)
	{
		day = d;
		month = m;
		year = y;
	}
	void print()
	{
		cout << "...(" << day << " " << month << " " << year << ")\n";
	}
	void ReadFromFile(fstream& fin);
	bool CompareRecentDate()
	{
		if (month == CurrentDate.month && CurrentDate.year == year && (day == (CurrentDate.day - 1) || CurrentDate.day == day))
		{
			//same month same year
			return true;
		}
		else if (month == CurrentDate.month - 1 && year == CurrentDate.year)//different month same year
		{
			if (month == 2 && day == 29 && CurrentDate.day == 1)
			{
				return true;
			}
			else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day == 31 && CurrentDate.day == 1)
			{
				return true;
			}
			else if (month == 4 || month == 6 || month == 9 || month == 11 && (day == 30 && CurrentDate.day == 1))
			{
				return true;
			}
		}
		else if (year == CurrentDate.year - 1 && (month == 12 && CurrentDate.month == 1 && day == 31 && CurrentDate.day == 1))
		{
			//different month different year
			return true;
		}
		return false;
	}
	bool CheckPastDate()
	{
		//memories on same date few years ago
		if (day == CurrentDate.day && month == CurrentDate.month && year < CurrentDate.year)
		{
			cout << CurrentDate.year - year << " years ago\n";
			return true;
		}
		return false;
	}
};
Date Date::CurrentDate = 0;
class Comments
{
	char* ID;
	Object* commentedBy;
	char* txt;
public:
	static int totalComments;
	Comments()
	{
		ID = NULL;
		commentedBy = NULL;
		txt = NULL;
		totalComments++;
	}
	~Comments()
	{
		delete[]ID;
		delete[]txt;
		totalComments = 0;
		ID = NULL;
		commentedBy = NULL;
		txt = NULL;
	}
	void SetCommentValues(char* id, Object* commentBy, char* text)
	{
		ID = Helper::GetStringFromBuffer(id);
		commentedBy = commentBy;
		txt = Helper::GetStringFromBuffer(text);
	}
	void print()
	{
		commentedBy->print(0);
		cout << " wrote: '" << txt << "'\n";
	}
	void MakeComment(const char* temp, User* userPtr, Post* postPtr);
};
int Comments::totalComments = 0;

class Post
{
	int type;
	Date sharedDate;
	char* ID;
	char* text;
	Object* sharedBy;
	Object** likedBy;
	Activity* activity;
	Comments** comment;
	int numOfLikes;
	int numOfComments;
public:
	void ReadDataFromPost(fstream&);
	Post();
	void SetDate()
	{
		sharedDate = Date::CurrentDate;
	}
	char* GetID()
	{
		return ID;
	}
	void printMem(bool, bool);

	Post(Post& rhs) {

		type = rhs.type;
		sharedDate = rhs.sharedDate;
		ID = Helper::GetStringFromBuffer(rhs.ID);
		text = Helper::GetStringFromBuffer(rhs.text);
		sharedBy = rhs.sharedBy;
		for (int i = 0; i < rhs.numOfLikes; i++)
		{
			likedBy[i] = rhs.likedBy[i];
		}
		activity = rhs.activity;
		for (int i = 0; i < rhs.numOfLikes; i++)
		{
			comment[i] = rhs.comment[i];
		}
		numOfLikes = rhs.numOfLikes;
		numOfComments = rhs.numOfComments;
	}
	Post& operator=(Post& rhs)
	{
		cout << "\n\npossssssssssssst  ============\n\n";
		type = rhs.type;
		sharedDate = rhs.sharedDate;
		ID = Helper::GetStringFromBuffer(rhs.ID);
		text = Helper::GetStringFromBuffer(rhs.text);
		sharedBy = rhs.sharedBy;
		for (int i = 0; i < rhs.numOfLikes; i++)
		{
			likedBy[i] = rhs.likedBy[i];
		}
		activity = rhs.activity;
		for (int i = 0; i < rhs.numOfLikes; i++)
		{
			comment[i] = rhs.comment[i];
		}
		numOfLikes = rhs.numOfLikes;
		numOfComments = rhs.numOfComments;
	}
	~Post()
	{
		if (likedBy)
			delete likedBy;
		if (ID)
			delete ID;
		if (text)
			delete text;
		if (activity)
			delete activity;
		numOfLikes = 0;
		for (int i = 0; i < numOfComments; i++)
		{
			delete comment[i];
			comment[i] = NULL;
		}
		if (comment)
			delete[] comment;
		ID = 0;
		text = NULL;
		activity = NULL;
		comment = NULL;
		numOfComments = 0;
	}
	void SetSharedBy(Object*);
	void SetLikedBy(Object*);
	void ViewLikedBy();
	void ViewPage();
	void AddComment(Comments*);
	virtual void print(bool date, bool comments);
	Date GetSharedDate()
	{
		return sharedDate;
	}
	Post(const char* txt, User* userPtr);
};
class Memory : public Post
{
	Post* originalPost;
public:
	Memory()
	{
		originalPost = NULL;
	}
	void SetOriginalPost(Post* p)
	{
		originalPost = p;
	}
	void print(bool date = false, bool comments = false)
	{
		this->printMem(true, false);
		cout << "\t\t(" << originalPost->GetSharedDate().GetDateDifference() << " years ago)\n" << endl;
		originalPost->print(true, comments);
		this->printMem(false, true);
	}
	Memory(Post* post, const char* txt, User* userPtr) : Post(txt, userPtr)
	{
		originalPost = post;
	}
	Memory(Memory& rhs)
	{
		cout << "\n\npagessssssssstttttttttttttttttt\n\n";

	}
	Memory& operator=(Memory& rhs)
	{
		cout << "\n\paggggeeesssssst  ============\n\n";

	}
};
class Activity
{
	int type;
	char* value;
public:
	Activity();
	void ReadData(fstream& fin);
	void print()
	{
		if (type == 1)
		{
			cout << " is feeling " << value << endl;
		}
		else if (type == 2)
		{
			cout << " is thinking about " << value << endl;
		}
		else if (type == 3)
		{
			cout << " is Making " << value << endl;
		}
		else if (type == 4)
		{
			cout << " is celebrating " << value << endl;
		}
	}
	~Activity()
	{
		delete[]value;
		type = 0;
		value = NULL;
	}
};
class Pages :public Object
{
private:
	char* title;
	Post** timeline;
	int numOfPostinTimeline;
public:
	Pages();
	void ReadFromPageFile(fstream&);
	void print(int);
	void AddPostToTimeline(Post*);
	~Pages()
	{
		if (title)
			delete[]title;
		for (int i = 0; i < numOfPostinTimeline; i++)
		{
			if (timeline[i] != NULL)
			{
				delete timeline[i];
				timeline[i] = NULL;
			}
		}
		if (timeline != NULL)
		{
			delete[] timeline;
			timeline = NULL;
		}
	}
	void CheckPost()
	{
		for (int i = 0; i < numOfPostinTimeline; i++)
		{
			if (timeline[i]->GetSharedDate().CompareRecentDate())
			{
				timeline[i]->print(false, true);
				cout << endl;
			}
		}
	}
	Pages(Pages& rhs)
	{
		cout << "\n\npagessssssssstttttttttttttttttt\n\n";

	}
	Pages& operator=(Pages& rhs)
	{
		cout << "\n\paggggeeesssssst  ============\n\n";

	}
};
class User :public Object
{
	char* firstName;
	char* lastName;
	int numOfLikedPages;
	int numOfFriends;
	Pages** pages;
	User** friendList;
	Post** timeline;
	int numOfPostinTimeline;
public:

	void AddPostToTimeline(Post*);
	void printLikedPages();
	~User();
	//User(User&);
	//User& operator=(User& rhs);
	void AddMemoryToTimeline(Memory* obj);
	void ReadFromUserFile(fstream&);
	void AddFriend(User* p);
	void LikedPage(Pages* p);
	void print(int);
	User()
	{
		lastName = NULL;
		friendList = NULL;
		firstName = NULL;
		numOfLikedPages = 0;
		numOfFriends = 0;
		numOfPostinTimeline = 0;
		pages = NULL;
		timeline = NULL;
	}
	void ViewHomePage();
	void CheckPost()
	{
		for (int i = 0; i < numOfPostinTimeline; i++)
		{
			if (timeline[i]->GetSharedDate().CompareRecentDate())
			{
				timeline[i]->print(true, true);
				cout << endl;
			}
		}
	}

	void ViewTimeline();
	void ViewFriendList();
	Post** CheckTimeline()
	{
		cout << "Command:\tView See Memories\n\n--------------------------------------\n\n";
		Post** temp = new Post * [numOfPostinTimeline];
		int j = 0;
		for (int i = 0; i < numOfPostinTimeline; i++)
		{
			Date postDate = timeline[i]->GetSharedDate();
			if (postDate.CheckPastDate())
			{
				temp[j] = timeline[i];
				j++;
			}
			temp[j] = NULL;
		}
		Post** memories = new Post * [j + 1];
		for (int i = 0; i < j; i++)
		{
			memories[i] = temp[i];
			memories[i]->print(true, true);
		}
		memories[j] = NULL;
		cout << "\n\n--------------------------------------\n\n";
		return memories;
	}
};
class Facebook
{
	User** users;
	Pages** pages;
	static int totalUser;
	static int totalPages;
	static int totalPosts;
	static int totalComments;
	Date currentDate;
	Post** posts;
public:
	void LoadPosts();
	void Load();
	void LoadUser();
	void LoadLikedPages();
	Facebook();
	Pages* SearchPageByID(char* temp);
	User* SearchUserByID(const char*);
	~Facebook();
	Object* SearchObjectByID(char* temp);
	void LoadComments();
	static int GetTotalPages()
	{
		return totalPages;
	}
	Post* SearchPostByID(const char*);
	Post* GetPostID(int i)
	{
		return posts[i];
	}
	void Run();
};

int Facebook::totalUser = 0;
int Facebook::totalPages = 0;
int Facebook::totalComments = 0;
int Facebook::totalPosts = 0;
Activity::Activity()
{
	type = 0;
	value = NULL;
}
Post::Post()
{
	type = 0;
	ID = NULL;
	text = NULL;
	numOfLikes = NULL;
	comment = NULL;
	activity = NULL;
	likedBy = NULL;
	sharedBy = NULL;
	numOfComments = 0;
}
User::~User()
{
	delete[]firstName;
	delete[]lastName;
	delete[]pages;
	delete[]friendList;
	for (int i = 0; i < numOfPostinTimeline; i++)
	{
		if (timeline[i] != NULL)
		{
			delete timeline[i];
			timeline[i] = NULL;
		}
	}
	if (timeline != NULL)
	{
		delete[] timeline;
		timeline = NULL;
	}
}
Facebook::~Facebook()
{
	for (int i = 0; i < totalUser; i++)
	{
		delete users[i];
	}
	delete[]users;
	for (int i = 0; i < totalPages; i++)
	{
		delete pages[i];
	}
	delete[]pages;
}
Facebook::Facebook()
{
	users = NULL;
	pages = NULL;
	posts = NULL;
}
void Comments::MakeComment(const char* text, User* userPtr, Post* postPtr)
{
	cout << "Command:\tPost Comment(" << text << ")\n\n--------------------------------------\n\n";
	//int n = totalComments;//Facebook::GetTotalPages()
	//int j, k;
	//n++;
	char temp2[] = "c";// temp1[100];
	//for (j = 1, k = n; k > 0;)
	//{
	//	k /= 10;
	//	j *= 10;
	//}
	//j /= 10;
	//for (int i = 0; n > 0; i++)
	//{
	//	temp1[i] = n / j + '0';
	//	temp1[i + 1] = '\0';
	//	n = n % j;
	//	j /= 10;
	//}
	string temp = to_string(totalComments);
	const char* temp1 = temp.c_str();
	ID = Helper::StringConcatenate(temp2, temp1);
	txt = Helper::GetStringFromBuffer(text);
	commentedBy = userPtr;
	postPtr->AddComment(this);
}
void User::AddPostToTimeline(Post* obj)
{
	if (!numOfPostinTimeline)
	{
		timeline = new Post * [10];
	}
	if (numOfPostinTimeline < 10)
	{
		timeline[numOfPostinTimeline] = obj;
		numOfPostinTimeline++;
	}
}
void User::AddMemoryToTimeline(Memory* obj)
{
	timeline[numOfPostinTimeline] = obj;
	numOfPostinTimeline++;
}
void Pages::AddPostToTimeline(Post* obj)
{
	if (!numOfPostinTimeline)
	{
		timeline = new Post * [10];
	}
	timeline[numOfPostinTimeline] = obj;
	numOfPostinTimeline++;
}
Pages* Facebook::SearchPageByID(char* temp)
{
	for (int i = 0; i < totalPages; i++)
	{
		if (Helper::CompareString(pages[i]->GetID(), temp))
		{
			return pages[i];
		}
	}
}

Post::Post(const char* txt, User* userPtr)
{
	type = 0;
	text = Helper::GetStringFromBuffer(txt);
	sharedDate = Date::CurrentDate;
	sharedBy = userPtr;
	likedBy = NULL;
	activity = NULL;
	comment = NULL;
	numOfLikes = 0;
	numOfComments = 0;
	int n = Facebook::GetTotalPages(), j, k;
	n++;
	char temp[] = "post", temp2[100];
	for (j = 1, k = n; k > 0;)
	{
		k /= 10;
		j *= 10;
	}
	j /= 10;
	for (int i = 0; n > 0; i++)
	{
		temp2[i] = n / j + '0';
		temp2[i + 1] = '\0';
		n = n % j;
		j /= 10;
	}
	ID = Helper::StringConcatenate(temp, temp2);
}
Pages::Pages()
{
	title = NULL;
	numOfPostinTimeline = 0;
}
void User::printLikedPages()
{
	cout << "Command:\tView Liked Page List\n\n--------------------------------------\n\n";
	cout << firstName << "-" << lastName << " Page List\n\n";

	for (int i = 0; i < numOfLikedPages; i++)
	{
		pages[i]->print(0);
		cout << endl;
	}
	cout << "\n\n--------------------------------------\n\n";
}
void User::ViewTimeline()
{
	cout << "Command:\tView Time Line\n\n--------------------------------------\n\n";
	cout << firstName << " " << lastName << " - Time Line\n\n";
	for (int i = 0; i < numOfPostinTimeline; i++)
	{
		timeline[i]->print(true, true);
		cout << endl;
	}
	cout << "\n\n--------------------------------------\n\n";
}
void Post::ViewLikedBy()
{
	cout << "Command:\tView Liked List(" << ID << " )\n\n--------------------------------------\n\n";
	for (int i = 0; i < numOfLikes; i++)
	{
		likedBy[i]->print(1);
		cout << endl;
	}
	cout << "\n\n--------------------------------------\n\n";
}
void Post::ViewPage()
{
	cout << "Command:\tView Post(" << ID << " )\n\n--------------------------------------\n\n";
	this->print(false, true);
	cout << "\n\n--------------------------------------\n\n";
}
void Post::print(bool date = false, bool comments = false)
{
	cout << "---";
	sharedBy->print(0);
	if (type == 2)
	{
		activity->print();
	}
	else
		cout << " shared\n";
	cout << "\n\t'" << text << "'";
	if (date)
	{
		sharedDate.print();
	}
	cout << "\n";
	if (comments)
	{
		for (int i = 0; i < numOfComments; i++)
		{
			cout << "\t";
			comment[i]->print();
		}
	}
}
void Post::printMem(bool date, bool comments)
{
	if (date)
	{
		cout << "---";
		sharedBy->print(0);
		if (type == 2)
		{
			activity->print();
		}
		else
			cout << " shared a memory\n\t\t";
		cout << "\n\t'" << text << "'";
		if (date)
		{
			sharedDate.print();
		}
		cout << "\n";
	}
	if (comments)
	{
		for (int i = 0; i < numOfComments; i++)
		{
			cout << "\t";
			comment[i]->print();
		}
	}
}
void User::ViewFriendList()
{
	cout << "Command:\tView Friend List\n\n--------------------------------------\n\n";
	for (int i = 0; i < numOfFriends; i++)
	{
		friendList[i]->print(1);
		cout << endl;
	}
	cout << "\n\n--------------------------------------\n\n";
}
void User::ViewHomePage()
{
	cout << "Command:\tView Homepage\n\n--------------------------------------\n\n";
	cout << firstName << " " << lastName << " - Home Page\n\n";
	for (int i = 0; i < numOfFriends; i++)
	{
		friendList[i]->CheckPost();
	}
	for (int i = 0; i < numOfLikedPages; i++)
	{
		pages[i]->CheckPost();
	}
	cout << "\--------------------------------------\n\n";
}
void User::print(int i)
{
	if (i)
	{
		cout << GetID() << " - ";
	}
	cout << firstName << " " << lastName;
}
void Pages::print(int i)
{
	if (i)
	{
		cout << GetID() << " - ";
	}
	cout << title;
}
Post* Facebook::SearchPostByID(const char* temp)
{
	bool isPresent;
	for (int i = 0; i < totalPosts; i++)
	{
		char* ID = posts[i]->GetID();
		if (Helper::CompareString(ID, temp))
		{
			return posts[i];
		}
	}
	return 0;
}
User* Facebook::SearchUserByID(const char* temp)
{
	for (int i = 0; i < totalUser; i++)
	{
		if (Helper::CompareString(users[i]->GetID(), temp))
		{
			return users[i];
		}
	}
	return 0;
}
Object* Facebook::SearchObjectByID(char* temp)
{
	Object* objPtr = 0;
	if (temp[0] == 'u')
		objPtr = SearchUserByID(temp);
	else if (temp[0] == 'p')
		objPtr = SearchPageByID(temp);
	return objPtr;
}
void Post::AddComment(Comments* ptr)
{
	if (!numOfComments)
	{
		comment = new Comments * [10];
	}
	if (numOfComments < 10)
	{
		comment[numOfComments] = ptr;
		numOfComments++;
	}
}
void Post::SetSharedBy(Object* obj)
{
	sharedBy = obj;
}
void Post::SetLikedBy(Object* obj)
{
	if (!numOfLikes)
	{
		likedBy = new Object * [10];
	}
	bool flag = true;
	for (int i = 0; i < numOfLikes; i++)
	{
		if (likedBy[i] == obj)
		{
			flag = false;
		}
	}
	if (numOfLikes < 10 && flag)
	{
		likedBy[numOfLikes] = obj;
		numOfLikes++;
	}
}
void User::AddFriend(User* p)
{
	if (!numOfFriends)
	{
		friendList = new User * [10];
	}
	if (numOfFriends < 10)
	{
		friendList[numOfFriends] = p;
		numOfFriends++;
	}
}
void User::LikedPage(Pages* p)
{
	if (!numOfLikedPages)
	{
		pages = new Pages * [10];
	}
	if (numOfLikedPages < 10)
	{
		pages[numOfLikedPages] = p;
		numOfLikedPages++;
	}
}
void Facebook::LoadUser()
{
	fstream fin;
	fin.open("User.txt");
	if (fin)
	{
		fin >> totalUser;
		char*** tempFriend = new char** [totalUser], temp[15];
		users = new User * [totalUser];
		int j;

		for (int i = 0; i < totalUser; i++)
		{
			users[i] = new User;
			users[i]->ReadFromUserFile(fin);

			fin >> temp;
			if (!Helper::CompareString(temp, "-1"))
			{
				for (j = 0; !Helper::CompareString(temp, "-1"); j++)
				{
					if (!j)
					{
						tempFriend[i] = new char* [10];
					}
					tempFriend[i][j] = Helper::GetStringFromBuffer(temp);
					fin >> temp;
				}
				tempFriend[i][j] = NULL;
			}
			else
				tempFriend[i] = NULL;
			fin >> temp;
			Pages* pagePtr = 0;
			for (int j = 0; !Helper::CompareString(temp, "-1"); j++)
			{
				pagePtr = SearchPageByID(temp);
				users[i]->LikedPage(pagePtr);
				fin >> temp;
			}
		}
		User* userPtr;
		for (int i = 0; i < totalUser; i++)
		{
			if (tempFriend[i] != NULL)
			{
				for (int j = 0; tempFriend[i][j] != NULL; j++)
				{
					userPtr = SearchUserByID(tempFriend[i][j]);
					users[i]->AddFriend(userPtr);
				}
			}
		}
		for (int i = 0; i < totalUser; i++)
		{
			if (tempFriend[i] != NULL)
			{
				for (int j = 0; tempFriend[i][j] != NULL; j++)
				{
					delete[] tempFriend[i][j];
				}
			}
			delete[] tempFriend[i];
		}
		delete[] tempFriend;
		fin.close();
	}

}
void Facebook::Load()
{
	LoadLikedPages();
	LoadUser();
	LoadPosts();
	LoadComments();
}
void Facebook::LoadComments()
{
	fstream fin;
	fin.open("Comments.txt");
	if (fin)
	{
		char temp[100], temp2[100], temp3[100];
		fin >> totalComments;
		for (int i = 0; i < totalComments; i++)
		{
			Comments* commentPtr = new Comments;
			fin >> temp;
			fin >> temp2;
			Post* postPtr = SearchPostByID(temp2);
			postPtr->AddComment(commentPtr);
			fin >> temp2;
			Object* objPtr = SearchObjectByID(temp2);
			fin.getline(temp2, 100);
			commentPtr->SetCommentValues(temp, objPtr, temp2);
		}
		fin.close();
	}
}
void Facebook::LoadPosts()
{
	char temp[20];
	fstream fin;
	fin.open("Posts.txt");
	if (fin)
	{
		fin >> totalPosts;
		posts = new Post * [totalPosts];
		for (int i = 0; i < totalPosts; i++)
		{
			posts[i] = new Post;
			posts[i]->ReadDataFromPost(fin);
			fin >> temp;
			Object* objPtr = SearchObjectByID(temp);
			posts[i]->SetSharedBy(objPtr);
			objPtr->AddPostToTimeline(posts[i]);
			fin >> temp;
			for (int j = 0; !Helper::CompareString(temp, "-1"); j++)
			{
				Object* objPtr = SearchObjectByID(temp);
				posts[i]->SetLikedBy(objPtr);
				fin >> temp;
			}
		}
	}
	fin.close();

}
void Post::ReadDataFromPost(fstream& fin)
{
	char temp[100];
	fin >> type;
	fin.getline(temp, 100);
	ID = Helper::GetStringFromBuffer(temp);
	sharedDate.ReadFromFile(fin);
	fin >> temp;
	fin.getline(temp, 100);
	text = Helper::GetStringFromBuffer(temp);

	if (type == 2)
	{
		activity = new Activity;
		activity->ReadData(fin);
	}
}
void Date::ReadFromFile(fstream& fin)
{
	fin >> day;
	fin >> month;
	fin >> year;
}
void Activity::ReadData(fstream& fin)
{
	char temp[50];
	fin >> type;
	fin.getline(temp, 50);
	value = Helper::GetStringFromBuffer(temp);
}
void Facebook::LoadLikedPages()
{
	fstream fin;
	fin.open("LikedPages.txt");
	if (fin)
	{
		fin >> totalPages;
		pages = new Pages * [totalPages];

		for (int i = 0; i < totalPages; i++)
		{
			pages[i] = new Pages;
			pages[i]->ReadFromPageFile(fin);
		}
		fin.close();
	}
}
void Pages::ReadFromPageFile(fstream& finPage)
{
	char temp[50];
	finPage >> temp;
	SetID(temp);
	finPage.getline(temp, 50);
	title = Helper::GetStringFromBuffer(temp);
}
void User::ReadFromUserFile(fstream& finUser)
{
	char temp[50];
	finUser >> temp;
	SetID(temp);
	finUser >> temp;
	firstName = Helper::GetStringFromBuffer(temp);
	finUser >> temp;
	lastName = Helper::GetStringFromBuffer(temp);
}
void Facebook::Run()
{
	User* userptr;
	Post* postPtr;
	Comments* commentPtr = new Comments;
	userptr = SearchUserByID("u4");
	if (userptr)
	{
		userptr->print(0);
		cout << " successfully set as current user\n\n--------------------------------------\n";

		userptr->ViewFriendList();
		userptr->printLikedPages();
		userptr->ViewHomePage();
		userptr->ViewTimeline();

		//MAKE COMMENT
		postPtr = SearchPostByID("post5");
		if (postPtr)
		{
			commentPtr->MakeComment("hello", userptr, postPtr);
			postPtr->print(false, true);
		}

		postPtr = SearchPostByID("post5");

		if (postPtr)
		{
			postPtr->ViewPage();
			postPtr->SetLikedBy(userptr);
		}

		if (postPtr)
		{
			postPtr = SearchPostByID("post5");
			postPtr->ViewLikedBy();
		}


		Post** postPtr1 = userptr->CheckTimeline();

		for (int i = 0; postPtr1[i] != NULL; i++)
		{
			Memory* memory = new Memory(postPtr1[0], "memory", userptr);
			totalPosts++;
			userptr->AddPostToTimeline(memory);
			if (postPtr1[i])
			{
				memory->print(false, false);
			}
			Post** temp = new Post * [totalPosts];
			for (int i = 0; i < totalPosts; i++)
			{
				temp[i] = posts[i];
			}
			delete posts;
			posts = temp;
			posts[totalPosts - 1] = memory;
			postPtr = SearchPostByID("post13");
			Comments* commentPtr1 = new Comments;
			commentPtr1->MakeComment("Hello", userptr, postPtr);
			userptr->ViewTimeline();
		}
	}
	else
	{
		cout << "User not found\n";
	}
}
void main()
{
	Date::SetCurrentDate(15, 11, 2017);
	Facebook fb;
	fb.Load();
	fb.Run();
}
