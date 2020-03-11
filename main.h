#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <windows.data.json.h>
#include "nlohmann/json.hpp"
#include <vector>
#include <array>
#include <fstream>
#include <ctime>


// for convenience
using json = nlohmann::json;
using namespace std;


// write to file
void writeToFile(string textToFile, string filename="scrape_data.txt"){
	

	ofstream writeFile;
	writeFile.open(filename);
	writeFile << textToFile;
	writeFile.close();
}

/*
	JSON
*/

// converts string to json
json toJson(std::string jsonString) {
	json jsonObj;
	std::stringstream(jsonString) >> jsonObj;

	return jsonObj;
}

// parse json and get values as a list
void listOfPosts(json jsonResult, bool alwaysWrite) {
	ofstream writeToFile;
	string filenameSubreddit = jsonResult["data"][0]["subreddit"];
	writeToFile.open("top_"+filenameSubreddit +".csv");
	
	writeToFile << "Title,score,date created, subreddit, author, url" << endl;
	for (int i = 0; i < jsonResult["data"].size(); i++)
	{
		
		string title = jsonResult["data"][i]["title"];
		int score = jsonResult["data"][i]["score"];
		int created_utc = jsonResult["data"][i]["created_utc"];
		string url = jsonResult["data"][i]["url"];
		string subreddit = jsonResult["data"][i]["subreddit"];
		string author = jsonResult["data"][i]["author"];
		
		if (((url.find("mega") != std::string::npos) || (url.find("hub.") != std::string::npos)) && !alwaysWrite ) {
			writeToFile << title << "," << score << "," << created_utc << "," << subreddit << "," << author << "," << url << endl;
		}

		if (alwaysWrite) {
			writeToFile << title << "," << score << "," << created_utc << "," << subreddit << "," << author << "," << url << endl;
		}
	}

	writeToFile.close();

}

// return url string given an input map
string getUrlText(map<string, string> urlMap) {
	string newUrl = "https://api.pushshift.io/reddit/search/submission/?sort=desc&sort_type=score";

	string size = "&size=" + urlMap["size"];
	string subreddit = "&subreddit=" + urlMap["subreddit"];
	//string after = "&after=" + urlMap["after"]+"d";
	string updatedUrl = newUrl + size + subreddit;
	
	return updatedUrl;
}

// return epoch given year and month
time_t dateToEpoch(int year, int month) {
	struct tm t = { 0 };
	t.tm_year = year - 1900;
	t.tm_mon = month;

	time_t timeSinceEpoch = mktime(&t);
	return timeSinceEpoch;
}
