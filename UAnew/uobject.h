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
 *   You should have received a copy of the GNU General Public License
 *  along with Horse.  If not, see <http://www.gnu.org/licenses/>.
 *******************************************
 *
 *	UAnew 
 *   Description
 *   author: Botki, Wroclaw University of Technology
 *   date: 09.10.2013
 *	ver: (see defines below)
 *
 *******************************************
 */

//#ifndef _WIN32_WINNT            // Specifies that the minimum required platform is Windows Vista.
//#define _WIN32_WINNT 0x0600     // Change this to the appropriate value to target other versions of Windows.
//#endif

#ifndef __UOBJECT_ANEW_H__
#define __UOBJECT_ANEW_H__

// project version defines - do not modify _PROJECT_BUILD if using the build_version_control.sh script
#define _PROJECT_MAJOR_VER 1
#define _PROJECT_MINOR_VER 0
#define _PROJECT_BUILD 118


#include <urbi/uobject.hh>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <boost/algorithm/string.hpp>

// object-specific defines
#define BUFFER_SIZE 800
#define MAX_ANEW_ENTRIES 13915
#define UANEW "[UAnew] "



// category labels
extern const std::string categories_table[];



// structure for mean value, standard deviation and the amount of contributing ratings
// of a single category and for a single type (P/A/D)
typedef struct setOfValues {
    double mean;
    double SD;
    int rat;
	setOfValues &operator=(const setOfValues &arg);
} setOfValues;


// structure holding P or A or D values for all categories
typedef struct rating {
    setOfValues categories[7]; // unisex, male, female, youger, older, low education, high education
	rating &operator=(const rating &arg);
} rating;


// structure for a single ANEW entry: the word and its PAD ratings
typedef struct ANEWentry {
    std::string entry;
    rating valence, arousal, dominance;
	ANEWentry &operator=(const ANEWentry &arg);
} ANEWentry;



// overloaded << operators for printing ANEWentry structures
std::ostream &operator<<(std::ostream &outStrm, setOfValues arg);
std::ostream &operator<<(std::ostream &outStrm, rating arg);
std::ostream &operator<<(std::ostream &outStrm, ANEWentry arg);



// UAnew class
class UAnew: public urbi::UObject {
 public:
    UAnew(const std::string& str);
	~UAnew();
	int init(std::string inputFile);
	void Help(void) const;
	void HelpAbout(std::string topic) const;
	const int FindWord(int idx_bot, int idx_top, const std::string arg) const;
    const bool SetWord(const std::string myword);
    const bool EvaluateWord(const std::string myword);
    const bool CategoryChange(void);
	std::vector<std::string> ClearText(std::string text);
	std::vector<std::string> ClearTextAgain(void);
	void DisplayRating(void) const;
	void DisplaySD(void) const;
	void DisplayRat(void) const;
	void DisplayAll(void) const;
	void DisplayRatingByIndex(const int idx) const;
	void EvaluateText(void);
	void TestFindWord(void) const;

    char *buffer;
    ANEWentry *ratings;
    std::vector<std::string> clearedTextVector;
    std::ifstream ratingsFile;
	std::string textLocalCopy;
	int databaseSize;

    urbi::UVar word;
    urbi::UVar pleasure, arousal, dominance;
    urbi::UVar pleasureSD, arousalSD, dominanceSD;
    urbi::UVar pleasureRat, arousalRat, dominanceRat;
    urbi::UVar textPleasure, textArousal, textDominance;
    urbi::UVar category;
    urbi::UVar minLettersCount;
	urbi::UVar amountOfEntries;
	urbi::UVar verbosity;
};

#endif // __UOBJECT_ANEW_H__
