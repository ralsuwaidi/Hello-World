
#define CURL_STATICLIB

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "curl/curl.h"
#include "main.h"
#include "reddit_curl.h"
#include "nlohmann/json.hpp"


using namespace std;
using json = nlohmann::json;

// get user input and return a map
map<string, string> userInput() {
	map<string, string> userParseInput;
	string subreddit, size, saveBool, after;

	cout << "Please enter the subreddit" << endl;
	cin >> subreddit;
	cout << "The number of response (max 1000)" << endl;
	cin >> size;
	//cout << "Number of days since posted" << endl;
	//cin >> after;
	cout << "If you want to save all data or not (yes/no)" << endl;
	cin >> saveBool;

	cout << "subreddit: " << &subreddit << endl;
	cout << "size: " << size << endl;
	cout << "save all data: " << saveBool << endl;


	userParseInput.insert(pair<string, string>("subreddit", subreddit));
	userParseInput.insert(pair<string, string>("size", size));
	userParseInput.insert(pair<string, string>("saveBool", saveBool));
	//userParseInput.insert(pair<string, string>("after", after));

	return userParseInput;
}

int main()
{
	// input map to parse data
	map<string, string> userParseInput = userInput();

	string url = getUrlText(userParseInput);

	//cout << url << endl;
	
	// get string from reddit curl
	string result = getResponse(url);

	// parse string to json and get the result
	json scrapedJson = toJson(result);

	// print specific data
	//cout << scrapedJson["data"][0]["title"] << endl;

	

	//print result
	//cout << "time chosen in epoch " << dateToEpoch(2018, 0) << endl;
	
	//get list of lists from raw json
	if (userParseInput["saveBool"]=="yes") {
		listOfPosts(scrapedJson, 1);
	}
	else {
		listOfPosts(scrapedJson, 0);
	}
	


	

	return 0;
}