/* This file is part of UAnew .
 * UAnew  is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Horse is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Horse.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************
 *
 *	UAnew
 *   authors: 
 *
 *    Marcin Dmochowski
 *    Bartosz Folta
 *    Krzysztof Nomejko
 *    Albert Aniszczyk
 * 
 *    thx Jan Kędzierski
 *
 *   Wroclaw University of Technology
 *   date: 09.10.2013
 *
 *	version: see UAnew loading preamble
 *
 *******************************************
 */

#include "uobject.h"
#include "quicksort.h"


// CSV-format files save data in comma-delimited format
#define ANEWget() get(buffer,BUFFER_SIZE,',')

// simple abs()
//#define MYABS(X,Y) (X>Y ? X-Y : Y-X)



const std::string categories_table[]={"unisex","male","female","younger","older","low_education","high_education"};






setOfValues &setOfValues::operator=(const setOfValues &arg) {
	this->mean=arg.mean;
	this->SD=arg.SD;
	this->rat=arg.rat;
	return *this;
}




rating &rating::operator=(const rating &arg) {
	int i;
	for (i=0;i<7;++i) {
		this->categories[i]=arg.categories[i];
	}
	return *this;
}




ANEWentry &ANEWentry::operator=(const ANEWentry &arg) {
	this->entry=arg.entry;
	this->valence=arg.valence;
	this->arousal=arg.arousal;
	this->dominance=arg.dominance;
	return *this;
}




 std::ostream &operator<<(std::ostream &outStrm, setOfValues arg) {
	 outStrm << UANEW << "INFO: mean value: " << arg.mean << ";" << std::endl;
	 outStrm << UANEW << "INFO: standard deviation: " << arg.SD << ";" << std::endl;
	 outStrm << UANEW << "INFO: contributing ratings: " << arg.rat << ";" << std::endl;
     return outStrm;
 }




std::ostream &operator<<(std::ostream &outStrm, rating arg) {
    int i;
    for (i=0;i<7;++i) {
		outStrm << UANEW << "INFO: category: " << categories_table[i] << ";" << std::endl;
		outStrm << arg.categories[i];
    }
    return outStrm;
}




std::ostream &operator<<(std::ostream &outStrm, ANEWentry arg) {
	outStrm << UANEW << "INFO: ANEW entry: " << arg.entry << std::endl;
	outStrm << UANEW << "INFO: values for valence: " << std::endl << arg.valence << UANEW << std::endl;
	outStrm << UANEW << "INFO: values for arousal: " << std::endl << arg.arousal << UANEW << std::endl;
	outStrm << UANEW << "INFO: values for dominance: " << std::endl << arg.dominance << UANEW << std::endl;
    outStrm << UANEW << std::endl;
    return outStrm;
}




// UAnew constructor
UAnew::UAnew(const std::string& s): urbi::UObject(s) {
	ratings=NULL;
	buffer=NULL;

    UBindFunction(UAnew, init);
    UBindFunction(UAnew, SetWord);
    UBindFunction(UAnew, ClearText);
	UBindFunction(UAnew, DisplayRating);
	UBindFunction(UAnew, DisplaySD);
	UBindFunction(UAnew, DisplayRat);
	UBindFunction(UAnew, DisplayAll);
	UBindFunction(UAnew, DisplayRatingByIndex);
	UBindFunction(UAnew, EvaluateText);
	UBindFunction(UAnew, TestFindWord);
	UBindFunction(UAnew, Help);
	UBindFunction(UAnew, HelpAbout);
	
    UBindVar(UAnew, word);
    UBindVar(UAnew, pleasure);
    UBindVar(UAnew, arousal);
    UBindVar(UAnew, dominance);
    UBindVar(UAnew, pleasureSD);
    UBindVar(UAnew, arousalSD);
    UBindVar(UAnew, dominanceSD);
    UBindVar(UAnew, pleasureRat);
    UBindVar(UAnew, arousalRat);
    UBindVar(UAnew, dominanceRat);
    UBindVar(UAnew, textPleasure);
    UBindVar(UAnew, textArousal);
    UBindVar(UAnew, textDominance);
    UBindVar(UAnew, category);
    UBindVar(UAnew, minLettersCount); 
    UBindVar(UAnew, amountOfEntries);
	UBindVar(UAnew, verbosity);

    word="";

    pleasure=0;
    arousal=0;
    dominance=0;
    pleasureSD=0;
    arousalSD=0;
    dominanceSD=0;
    pleasureRat=0;
    arousalRat=0;
    dominanceRat=0;
    textPleasure=0;
    textArousal=0;
    textDominance=0;

    category="unisex";		 

	amountOfEntries=0;
    minLettersCount=3;
	verbosity=0;

    UNotifyChange(minLettersCount, &UAnew::ClearTextAgain);
    UNotifyChange(category, &UAnew::CategoryChange);
}




UAnew::~UAnew() {
	if (ratings!=NULL) {
		delete [] ratings;
	}
}




// initialise UAnew object
int UAnew::init(std::string inputFile) {
    std::cout <<"[UAnew] ******************************************************" << std::endl;
    std::cout <<"[UAnew] ** UAnew ver. " << _PROJECT_MAJOR_VER << "." << _PROJECT_MINOR_VER << " build ";
	std::cout << _PROJECT_BUILD << std::endl;
    std::cout <<"[UAnew] ******************************************************" << std::endl;
	std::cout <<"[UAnew] ** Wroclaw University of Technology" << std::endl;
    std::cout <<"[UAnew] ** Copyright 2013 by" << std::endl;
	std::cout <<"[UAnew] **  Marcin Dmochowski," << std::endl;
	std::cout <<"[UAnew] **  Bartosz Folta," << std::endl;
	std::cout <<"[UAnew] **  Krzysztof Nomejko," << std::endl;
	std::cout <<"[UAnew] **  Albert Aniszczyk;" << std::endl;
	std::cout <<"[UAnew] **  project supervisor: Jan Kedzierski." << std::endl;
	std::cout <<"[UAnew] ******************************************************" << std::endl;
	std::cout <<"[UAnew] ** List of available commands and slots" << std::endl;
	std::cout <<"[UAnew] ** is contained within \"Help()\" method." << std::endl;
    std::cout <<"[UAnew] ******************************************************" << std::endl;

	// open and read the ratings database
    ratingsFile.open(inputFile.c_str());
    if (!ratingsFile.is_open()) {
		std::cerr << "[UAnew] ERROR: Could not open the ratings database file \"" << inputFile << "\".\r\n" << std::endl;
		return 1;
    }
    else {
		if (static_cast<int>(verbosity)!=0) {
			std::cout << "[UAnew] INFO: Ratings database file \"" << inputFile << "\" opened successfully." << std::endl;
		}
    }
	
    buffer=new char[BUFFER_SIZE];
    ratings=new ANEWentry[MAX_ANEW_ENTRIES];
    int i, j;
	
    ratingsFile.getline(buffer,BUFFER_SIZE); // first line - discard
    ratingsFile.ANEWget(); // index - discard
    ratingsFile.ignore(1,EOF); // comma - discard

    for (i=0;i<MAX_ANEW_ENTRIES;++i) {
		ratingsFile.ANEWget(); // word (entry)
		ratingsFile.ignore(1,EOF);
		ratings[i].entry.assign(buffer);
		
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].valence.categories[0].mean=atof(buffer);
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].valence.categories[0].SD=atof(buffer);
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].valence.categories[0].rat=atoi(buffer);

		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].arousal.categories[0].mean=atof(buffer);
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].arousal.categories[0].SD=atof(buffer);
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].arousal.categories[0].rat=atoi(buffer);

		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].dominance.categories[0].mean=atof(buffer);
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].dominance.categories[0].SD=atof(buffer);
		ratingsFile.ANEWget();
		ratingsFile.ignore(1,EOF);
		ratings[i].dominance.categories[0].rat=atoi(buffer);

		for (j=1;j<6;j+=2) {
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].valence.categories[j].mean=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].valence.categories[j].SD=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].valence.categories[j].rat=atoi(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].valence.categories[j+1].mean=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].valence.categories[j+1].SD=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].valence.categories[j+1].rat=atoi(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].arousal.categories[j].mean=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].arousal.categories[j].SD=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].arousal.categories[j].rat=atoi(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].arousal.categories[j+1].mean=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].arousal.categories[j+1].SD=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].arousal.categories[j+1].rat=atoi(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].dominance.categories[j].mean=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].dominance.categories[j].SD=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].dominance.categories[j].rat=atoi(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].dominance.categories[j+1].mean=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].dominance.categories[j+1].SD=atof(buffer);
			ratingsFile.ANEWget();
			ratingsFile.ignore(1,EOF);
			ratings[i].dominance.categories[j+1].rat=atoi(buffer);
		}
		if (ratingsFile.eof()) {
			break;
		}
    }

	ratingsFile.close();

	databaseSize=i+1;
	amountOfEntries=databaseSize;

	if (static_cast<int>(verbosity)!=0) {
		std::cout << "[UAnew] INFO: Ratings database file read and closed successfully." << std::endl;
		std::cout << "[UAnew] INFO: The database contains " << databaseSize << " entries." << std::endl;
	}

	SortQuicksort(ratings, databaseSize);

	if (static_cast<int>(verbosity)!=0) {
		std::cout << "[UAnew] INFO: Ratings database sorted successfully." << std::endl;
	}

    delete [] buffer;
	buffer=NULL;


    return 0;
}




void UAnew::Help() const {
	std::cout << UANEW << std::endl;
	std::cout << UANEW << "INFO: UAnew" << std::endl;
	std::cout << UANEW << std::endl;
	std::cout << UANEW << "INFO: Available commands:" << std::endl;
	std::cout << UANEW << "INFO: Help();" << std::endl;
	std::cout << UANEW << "INFO: HelpAbout(\"command/slot\");" << std::endl;
	std::cout << UANEW << "INFO: SetWord(\"word\");" << std::endl;
	std::cout << UANEW << "INFO: ClearText(\"input text\");" << std::endl;
	std::cout << UANEW << "INFO: DisplayRating();" << std::endl;
	std::cout << UANEW << "INFO: DisplaySD();" << std::endl;
	std::cout << UANEW << "INFO: DisplayRat();" << std::endl;
	std::cout << UANEW << "INFO: DisplayAll();" << std::endl;
	std::cout << UANEW << "INFO: DisplayRatingByIndex(number from 0 to databaseSize-1);" << std::endl;
	std::cout << UANEW << "INFO: EvaluateText();" << std::endl;
	std::cout << UANEW << "INFO: TestFindWord()." << std::endl;
	std::cout << UANEW << std::endl;
	std::cout << UANEW << "INFO: Available slots:" << std::endl;
	std::cout << UANEW << "INFO: word," << std::endl;
	std::cout << UANEW << "INFO: pleasure, arousal, dominance," << std::endl;
	std::cout << UANEW << "INFO: pleasureSD, arousalSD, dominanceSD," << std::endl;
	std::cout << UANEW << "INFO: pleasureRat, arousalRat, dominanceRat," << std::endl;
	std::cout << UANEW << "INFO: textPleasure, textArousal, textDominance," << std::endl;
	std::cout << UANEW << "INFO: category," << std::endl;
	std::cout << UANEW << "INFO: minLettersCount," << std::endl;
	std::cout << UANEW << "INFO: amountOfEntries," << std::endl;
	std::cout << UANEW << "INFO: verbosity." << std::endl;
	std::cout << UANEW << std::endl;
	std::cout << UANEW << "INFO: For more information about any of these, invoke HelpAbout(\"command/slot\")." << std::endl;
	std::cout << UANEW << std::endl;
}




void UAnew::HelpAbout(std::string topic) const {
	if (topic=="Help") {
		std::cout << UANEW << "INFO: void Help():" << std::endl;
		std::cout << UANEW << "INFO: displays the list of avilable commands and slots." << std::endl;
	}
	else if (topic=="HelpAbout") {
		std::cout << UANEW << "INFO: void HelpAbout(\"command/slot\"):" << std::endl;
		std::cout << UANEW << "INFO: displays detailed information about any available command or slot." << std::endl;
		std::cout << UANEW << "INFO: We really do hope you invoked HelpAbout(\"HelpAbout\") just as a joke." << std::endl;
	}
	else if (topic=="SetWord") {
		std::cout << UANEW << "INFO: const bool SetWord(\"word\"):" << std::endl;
		std::cout << UANEW << "INFO: attempts to find \"word\" in the database and, if successful," << std::endl;
		std::cout << UANEW << "INFO: assigns values from the database to slots pleasure, arousal," << std::endl;
		std::cout << UANEW << "INFO: dominance, pleasureSD, arousalSD, dominanceSD, pleasureRat," << std::endl;
		std::cout << UANEW << "INFO: arousalRat, dominanceRat according to the current category setting." << std::endl;
		std::cout << UANEW << "INFO: Return value: true if the word was found, false otherwise." << std::endl;
	}
	else if (topic=="ClearText") {
		std::cout << UANEW << "INFO: std::vector<std::string> ClearText(\"input text\"):" << std::endl;
		std::cout << UANEW << "INFO: processes the given input text by extracting words which consist" << std::endl;
		std::cout << UANEW << "INFO: of at least minLettersCount letters and saves them" << std::endl;
		std::cout << UANEW << "INFO: in the returned std::vector container." << std::endl;
	}
	else if (topic=="DisplayRating") {
		std::cout << UANEW << "INFO: void DisplayRating():" << std::endl;
		std::cout << UANEW << "INFO: displays pleasure, arousal and dominance values for the current word." << std::endl;
	}
	else if (topic=="DisplaySD") {
		std::cout << UANEW << "INFO: void DisplaySD():" << std::endl;
		std::cout << UANEW << "INFO: displays standard deviation values for pleasure, arousal" << std::endl;
		std::cout << UANEW << "INFO: and dominance ratings for the current word." << std::endl;
	}
	else if (topic=="DisplayRat") {
		std::cout << UANEW << "INFO: void DisplayRat():" << std::endl;
		std::cout << UANEW << "INFO: displays amounts of contributing values for pleasure, arousal" << std::endl;
		std::cout << UANEW << "INFO: and dominance ratings for the current word." << std::endl;
	}
	else if (topic=="DisplayAll") {
		std::cout << UANEW << "INFO: void DisplayAll():" << std::endl;
		std::cout << UANEW << "INFO: displays pleasure, arousal and dominance values," << std::endl;
		std::cout << UANEW << "INFO: then standard deviation values for pleasure, arousal" << std::endl;
		std::cout << UANEW << "INFO: and dominance ratings, then amounts of contributing values" << std::endl;
		std::cout << UANEW << "INFO: for pleasure, arousal and dominance ratings for the current word." << std::endl;
	}
	else if (topic=="DisplayRatingByIndex") {
		std::cout << UANEW << "INFO: void DisplayRatingByIndex(number from 0 to databaseSize-1):" << std::endl;
		std::cout << UANEW << "INFO: displays all available information for the word found under the given index." << std::endl;
	}
	else if (topic=="EvaluateText") {
		std::cout << UANEW << "INFO: void EvaluateText():" << std::endl;
		std::cout << UANEW << "INFO: calculates the mean value of pleasure, arousal and dominance ratings" << std::endl;
		std::cout << UANEW << "INFO: for the list of words acquired via ClearText(\"input text\") method" << std::endl;
		std::cout << UANEW << "INFO: and stores these in textPleasure, textArousal, textDominance slots." << std::endl;
		std::cout << UANEW << "INFO: This method does not take any arguments as the std::vector container" << std::endl;
		std::cout << UANEW << "INFO: returned by ClearText is also stored internally." << std::endl;
	}
	else if (topic=="TestFindWord") {
		std::cout << UANEW << "INFO: void TestFindWord():" << std::endl;
		std::cout << UANEW << "INFO: tests the functionality of FindWord function, which is responsible" << std::endl;
		std::cout << UANEW << "INFO: for looking up words in the database, by attempting to find every" << std::endl;
		std::cout << UANEW << "INFO: word present in the database." << std::endl;
	}
	else if (topic=="word") {
		std::cout << UANEW << "INFO: word:" << std::endl;
		std::cout << UANEW << "INFO: contains the most recent word looked up which was found in the database." << std::endl;
	}
	else if (topic=="pleasure") {
		std::cout << UANEW << "INFO: pleasure:" << std::endl;
		std::cout << UANEW << "INFO: contains the pleasure rating for the current word." << std::endl;
	}
	else if (topic=="arousal") {
		std::cout << UANEW << "INFO: arousal:" << std::endl;
		std::cout << UANEW << "INFO: contains the arousal rating for the current word." << std::endl;
	}
	else if (topic=="dominance") {
		std::cout << UANEW << "INFO: dominance:" << std::endl;
		std::cout << UANEW << "INFO: contains the dominance rating for the current word." << std::endl;
	}
	else if (topic=="pleasureSD") {
		std::cout << UANEW << "INFO: pleasureSD:" << std::endl;
		std::cout << UANEW << "INFO: contains the standard deviation value for pleasure rating" << std::endl;
		std::cout << UANEW << "INFO: for the current word." << std::endl;
	}
	else if (topic=="arousalSD") {
		std::cout << UANEW << "INFO: arousalSD:" << std::endl;
		std::cout << UANEW << "INFO: contains the standard deviation value for arousal rating" << std::endl;
		std::cout << UANEW << "INFO: for the current word." << std::endl;
	}
	else if (topic=="dominanceSD") {
		std::cout << UANEW << "INFO: dominanceSD:" << std::endl;
		std::cout << UANEW << "INFO: contains the standard deviation value for dominance rating" << std::endl;
		std::cout << UANEW << "INFO: for the current word." << std::endl;
	}
	else if (topic=="pleasureRat") {
		std::cout << UANEW << "INFO: pleasureRat:" << std::endl;
		std::cout << UANEW << "INFO: contains the amount of contributing values for pleasure rating" << std::endl;
		std::cout << UANEW << "INFO: for the current word." << std::endl;
	}
	else if (topic=="arousalRat") {
		std::cout << UANEW << "INFO: arousalRat:" << std::endl;
		std::cout << UANEW << "INFO: contains the amount of contributing values for arousal rating" << std::endl;
		std::cout << UANEW << "INFO: for the current word." << std::endl;
	}
	else if (topic=="dominanceRat") {
		std::cout << UANEW << "INFO: dominanceRat:" << std::endl;
		std::cout << UANEW << "INFO: contains the amount of contributing values for dominance rating" << std::endl;
		std::cout << UANEW << "INFO: for the current word." << std::endl;
	}
	else if (topic=="textPleasure") {
		std::cout << UANEW << "INFO: textPleasure:" << std::endl;
		std::cout << UANEW << "INFO: contains the mean value of pleasure ratings for the list of words" << std::endl;
		std::cout << UANEW << "INFO: acquired via ClearText(\"input text\") method." << std::endl;
	}
	else if (topic=="textArousal") {
		std::cout << UANEW << "INFO: textArousal:" << std::endl;
		std::cout << UANEW << "INFO: contains the mean value of arousal ratings for the list of words" << std::endl;
		std::cout << UANEW << "INFO: acquired via ClearText(\"input text\") method." << std::endl;
	}
	else if (topic=="textDominance") {
		std::cout << UANEW << "INFO: textDominance:" << std::endl;
		std::cout << UANEW << "INFO: contains the mean value of dominance ratings for the list of words" << std::endl;
		std::cout << UANEW << "INFO: acquired via ClearText(\"input text\") method." << std::endl;
	}
	else if (topic=="category") {
		std::cout << UANEW << "INFO: category:" << std::endl;
		std::cout << UANEW << "INFO: defines the current category choice." << std::endl;
		std::cout << UANEW << "INFO: All ratings are picked from the database using this setting." << std::endl;
		std::cout << UANEW << "INFO: Allowed values:" << std::endl;
		std::cout << UANEW << "INFO: \"unisex\", \"male,\", \"female\", \"younger\"," << std::endl;
		std::cout << UANEW << "INFO: \"older\", \"low_education\", \"high_education\"." << std::endl;
		std::cout << UANEW << "INFO: Default value: \"unisex\"." << std::endl;
	}
	else if (topic=="minLettersCount") {
		std::cout << UANEW << "INFO: minLettersCount:" << std::endl;
		std::cout << UANEW << "INFO: used in ClearText(\"input text\") method." << std::endl;
		std::cout << UANEW << "INFO: Defines the minimal amount of letters for the words from" << std::endl;
		std::cout << UANEW << "INFO: input text to be included in the returned std::vector container." << std::endl;
		std::cout << UANEW << "INFO: Default value: 3." << std::endl;
	}
	else if (topic=="amountOfEntries") {
		std::cout << UANEW << "INFO: amountOfEntries:" << std::endl;
		std::cout << UANEW << "INFO: contains the amount of entries in the currently loaded database." << std::endl;
		std::cout << UANEW << "INFO: Changing this value does not break the module's functionality." << std::endl;
	}
	else if (topic=="verbosity") {
		std::cout << UANEW << "INFO: verbosity:" << std::endl;
		std::cout << UANEW << "INFO: defines whether text communicates in ClearText(\"input text\")," << std::endl;
		std::cout << UANEW << "INFO: SetWord(\"word\") and EvaluateText() methods should appear" << std::endl;
		std::cout << UANEW << "INFO: on screen or not." << std::endl;
		std::cout << UANEW << "INFO: Values: 0 (none displayed), non-zero (all displayed)." << std::endl;
		std::cout << UANEW << "INFO: Default value: 0." << std::endl;
	}
	else {
		std::cout << UANEW << "INFO: invalid option." << std::endl;
		std::cout << UANEW << "INFO: Invoke Help() method to see the list of available commands and slots." << std::endl;
	}
}




const int UAnew::FindWord(int idx_bot, int idx_top, const std::string arg) const {
	int idx_mid;
	while (idx_top>=idx_bot) {
		//idx_mid=(idx_top+idx_bot)/2;
		idx_mid=idx_bot+((idx_top-idx_bot)/2);

		if (ratings[idx_mid].entry==arg) {
			return idx_mid;
		}
		if (ratings[idx_mid].entry<arg) {
			idx_bot=idx_mid+1;
		}
		else {
			idx_top=idx_mid-1;
		}
	}
	return -1;
}




const bool UAnew::SetWord(const std::string arg) {
	int i, categ_nr=0;

    int found_idx=FindWord(0,databaseSize-1,arg);

	for (i=0;i<7;++i) {
		if (categories_table[i]==static_cast<std::string>(category)) {
			categ_nr=i;
		}
	}

    if (found_idx>=0) {
		if (static_cast<int>(verbosity)!=0) {
			std::cout << UANEW << "INFO: requested word found in the database." << std::endl;
		}

		pleasure=ratings[found_idx].valence.categories[categ_nr].mean;
		arousal=ratings[found_idx].arousal.categories[categ_nr].mean;
		dominance=ratings[found_idx].dominance.categories[categ_nr].mean;
		pleasureSD=ratings[found_idx].valence.categories[categ_nr].SD;
		arousalSD=ratings[found_idx].arousal.categories[categ_nr].SD;
		dominanceSD=ratings[found_idx].dominance.categories[categ_nr].SD;
		pleasureRat=ratings[found_idx].valence.categories[categ_nr].rat;
		arousalRat=ratings[found_idx].arousal.categories[categ_nr].rat;
		dominanceRat=ratings[found_idx].dominance.categories[categ_nr].rat;
		word=arg;

		if (static_cast<int>(verbosity)!=0) {
			std::cout << UANEW << "INFO: Rating values for the chosen category are available in slots pleasure, arousal, dominance." << std::endl;
			DisplayRating();
		}

		return true;
    }
	else {
		if (static_cast<int>(verbosity)!=0) {
			std::cout << UANEW << "INFO: requested word not found in the database." << std::endl;
		}
	}
    return false;
}




const bool UAnew::EvaluateWord(const std::string arg) {
	int i, categ_nr=0;

    int found_idx=FindWord(0,databaseSize-1,arg);

	for (i=0;i<7;++i) {
		if (categories_table[i]==static_cast<std::string>(category)) {
			categ_nr=i;
		}
	}

    if (found_idx>=0) {
		pleasure=ratings[found_idx].valence.categories[categ_nr].mean;
		arousal=ratings[found_idx].arousal.categories[categ_nr].mean;
		dominance=ratings[found_idx].dominance.categories[categ_nr].mean;
		pleasureSD=ratings[found_idx].valence.categories[categ_nr].SD;
		arousalSD=ratings[found_idx].arousal.categories[categ_nr].SD;
		dominanceSD=ratings[found_idx].dominance.categories[categ_nr].SD;
		pleasureRat=ratings[found_idx].valence.categories[categ_nr].rat;
		arousalRat=ratings[found_idx].arousal.categories[categ_nr].rat;
		dominanceRat=ratings[found_idx].dominance.categories[categ_nr].rat;
		word=arg;
		return true;
    }
    return false;
}




const bool UAnew::CategoryChange() {
    return SetWord(static_cast<std::string>(word));
}




std::vector<std::string> UAnew::ClearText(std::string text) {
    std::stringstream str;
    std::string buffer;
    size_t i;

    textLocalCopy=text;
	
	clearedTextVector.clear();

    for (i=0;i<text.length();++i) {
		if (!((text[i]>=65 && text[i]<=90) || (text[i]>=97 && text[i]<=122))) {
			text[i]=' ';
		}
    }

	if (text.length()>0) {
		while (text[text.length()-1]==' ') {
			text.erase(text.begin()+text.length()-1);
			if (text.length()==0) {
				break;
			}
		}
	}

	if (static_cast<int>(verbosity)!=0) {
		std::cout << UANEW << "INFO: List of words in the input text containing at least " << static_cast<int>(minLettersCount) << " letters:" << std::endl;
	}

    str << text; // write all of the text into stringstream buffer
    while (str.good()) {
		str >> buffer; // read every word one after another from the stringstream buffer
		if(buffer.size()>=static_cast<int>(minLettersCount)) {
			clearedTextVector.push_back(buffer);
			if (static_cast<int>(verbosity)!=0) {
				std::cout << buffer << std::endl;
			}
		}
    }
	
	if (static_cast<int>(verbosity)!=0) {
		std::cout << UANEW << "INFO: Done extracting words." << std::endl;
	}
    return clearedTextVector;
}




std::vector<std::string> UAnew::ClearTextAgain() {
	return ClearText(textLocalCopy);
}




void UAnew::DisplayRating() const {
	std::cout << UANEW << "INFO: Ratings for current word in current category (P, A, D): " << static_cast<double>(pleasure) 
		<< "; " << static_cast<double>(arousal) << "; " << static_cast<double>(dominance) << "." << std::endl;
}




void UAnew::DisplaySD() const {
	std::cout << UANEW << "INFO: Standard deviation values for ratings for current word (P, A, D): " 
		<< static_cast<double>(pleasureSD) << "; " << static_cast<double>(arousalSD) << "; "
		<< static_cast<double>(dominanceSD) << "." << std::endl;
}




void UAnew::DisplayRat() const {
	std::cout << UANEW << "INFO: Amount of contributing ratings for current word (P, A, D): " << static_cast<int>(pleasureRat)
		<< "; " << static_cast<int>(arousalRat) << "; " << static_cast<int>(dominanceRat) << "." << std::endl;
}




void UAnew::DisplayAll() const {
	DisplayRating();
	DisplaySD();
	DisplayRat();
}




void UAnew::DisplayRatingByIndex(const int idx) const {
	std::cout << ratings[idx];
}




void UAnew::EvaluateText() {
	int i, numWords=static_cast<int>(clearedTextVector.size());
	std::string tmp;
	double takenWords=0.0;

	textPleasure=0.0;
	textArousal=0.0;
	textDominance=0.0;

	for (i=0;i<numWords;++i) {
		if (!EvaluateWord(clearedTextVector[i])) {
			if (static_cast<int>(verbosity)!=0) {
				std::cout << UANEW << "INFO: Could not find word \"" << clearedTextVector[i] << "\" in the database. Trying lowercase." << std::endl;
			}
			tmp=clearedTextVector[i];
			boost::algorithm::to_lower(tmp);
			if (!EvaluateWord(tmp)) {
				if (static_cast<int>(verbosity)!=0) {
					std::cout << UANEW << "INFO: Could not find word \"" << tmp << "\" in the database either." << std::endl;
				}
			}
			else {
				if (static_cast<int>(verbosity)!=0) {
					std::cout << UANEW << "INFO: Word \"" << tmp << "\" found in the database." << std::endl;
				}
				takenWords+=1.0;
				textPleasure=static_cast<double>(textPleasure)+static_cast<double>(pleasure);
				textArousal=static_cast<double>(textArousal)+static_cast<double>(arousal);
				textDominance=static_cast<double>(textDominance)+static_cast<double>(dominance);
			}
		}
		else {
			if (static_cast<int>(verbosity)!=0) {
				std::cout << UANEW << "INFO: Word \"" << clearedTextVector[i] << "\" found in the database." << std::endl;
			}
			takenWords+=1.0;
			textPleasure=static_cast<double>(textPleasure)+static_cast<double>(pleasure);
			textArousal=static_cast<double>(textArousal)+static_cast<double>(arousal);
			textDominance=static_cast<double>(textDominance)+static_cast<double>(dominance);
		}
	}
	
	if (static_cast<int>(verbosity)!=0) {
		std::cout << UANEW << "INFO: Done evaluating the text." << std::endl;
		std::cout << UANEW << "INFO: Results are available in slots textPleasure, textArousal, textDominance." << std::endl;
	}
	textPleasure=static_cast<double>(textPleasure)/takenWords;
	textArousal=static_cast<double>(textArousal)/takenWords;
	textDominance=static_cast<double>(textDominance)/takenWords;
}




void UAnew::TestFindWord() const {
	int found_idx, i;
	for (i=0;i<databaseSize;++i) {
		found_idx=FindWord(0,databaseSize-1,ratings[i].entry);
		if (found_idx!=i) {
			std::cerr << UANEW << std::endl;
			std::cerr << UANEW << "ERROR: FindWord is not working properly after all. It broke down trying to find:" << std::endl;
			std::cerr << UANEW << "ERROR: " << ratings[i].entry << " (ratings[" << i << "])." << std::endl;
			std::cerr << UANEW << std::endl;
			return;
		}
	}
	std::cout << UANEW << "INFO: Test of FindWord completed succesfully." << std::endl;
	std::cout << UANEW << "INFO: All of the " << databaseSize << " words in the database" << std::endl;
	std::cout << UANEW << "INFO: were found using the FindWord function." << std::endl;
}




UStart(UAnew);
