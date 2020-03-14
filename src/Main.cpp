
#define CURL_STATICLIB

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "curl/curl.h"
#include "main.h"
#include "reddit_curl.h"
#include "json.hpp"


using namespace std;
using json = nlohmann::json;

// get user input and return a map
map<string, string> userInput(int argc, char *argv[]) {
	map<string, string> userParseInput;
	
	// take user input and find how many inpts are given
	// then act accordingly
	if ((argc != 1) && (argc != 4))
	{
		cout << "you entered " << argc << " variables" << endl;
		cout << "please add three variables" << endl;
		exit(0);

	} else if (argc == 1){

			map<string, string> userParseInput;
			string subreddit, size, saveBool, after;

			cout << "Please enter the subreddit" << endl;
			cin >> subreddit;
			cout << "The number of response (max 1000)" << endl;
			cin >> size;
			cout << "If you want to save all data or not (yes/no)" << endl;
			cin >> saveBool;

			cout << "subreddit: " << &subreddit << endl;
			cout << "size: " << size << endl;
			cout << "save all data: " << saveBool << endl;

			userParseInput.insert(pair<string, string>("subreddit", subreddit));
			userParseInput.insert(pair<string, string>("size", size));
			userParseInput.insert(pair<string, string>("saveBool", saveBool));

			return userParseInput;

	} else
	{

		cout << argv[1] << argv[2] << argv[3] << endl;

		userParseInput.insert(pair<string, string>("subreddit", argv[1]));
		userParseInput.insert(pair<string, string>("size", argv[2]));
		userParseInput.insert(pair<string, string>("saveBool", argv[3]));

		return userParseInput;
	};
	
}

int main(int argc, char *argv[])
{
	// input map to parse data
	map<string, string> userParseInput = userInput(argc, argv);

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