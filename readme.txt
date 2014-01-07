**********************************************************
*
*	UAnew
*
*	Wroclaw University of Technology
*	
*	authors:
*	Marcin Dmochowski
*	Bartosz Folta
*	Krzysztof Nomejko
*	Albert Aniszczyk
*	project supervisor: Jan Kedzierski
*
*	date: 17.12.2013
*	version: see module loading preamble
*
**********************************************************

Description:

UAnew is a URBI module implementing ANEW with word search functionality.

ANEW (Affective Norms for English Words) is a database containing valence (pleasure), arousal and dominance
ratings for a large number of English words. It can be used for evaluating a word or a set of words in terms
of feelings it is associated with by a computer.
The database must be contained within a CSV-format file.

The module was created with a purpose of simplifying such an action - it provides pleasure, arousal and dominance
ratings for searched words without the need to navigate the ANEW database file manually. The module's
functionality also includes splitting a sentence into a sequence of words. This simplifies evaluating
such a sentence in terms of PAD ratings.



**********************************************************

Complete list of available commands and slots, as presented in the module after invoking Help() method:

[UAnew] INFO: UAnew
[UAnew]
[UAnew] INFO: Available commands:
[UAnew] INFO: Help();
[UAnew] INFO: HelpAbout("command/slot");
[UAnew] INFO: SetWord("word");
[UAnew] INFO: ClearText("input text");
[UAnew] INFO: DisplayRating();
[UAnew] INFO: DisplaySD();
[UAnew] INFO: DisplayRat();
[UAnew] INFO: DisplayAll();
[UAnew] INFO: DisplayRatingByIndex(number from 0 to databaseSize-1);
[UAnew] INFO: EvaluateText();
[UAnew] INFO: TestFindWord().
[UAnew]
[UAnew] INFO: Available slots:
[UAnew] INFO: word,
[UAnew] INFO: pleasure, arousal, dominance,
[UAnew] INFO: pleasureSD, arousalSD, dominanceSD,
[UAnew] INFO: pleasureRat, arousalRat, dominanceRat,
[UAnew] INFO: textPleasure, textArousal, textDominance,
[UAnew] INFO: category,
[UAnew] INFO: minLettersCount,
[UAnew] INFO: amountOfEntries,
[UAnew] INFO: verbosity.
[UAnew]



**********************************************************

Detailed descriptions:


[UAnew] INFO: void Help():
[UAnew] INFO: displays the list of avilable commands and slots.

[UAnew] INFO: void HelpAbout("command/slot"):
[UAnew] INFO: displays detailed information about any available command or slot.

[UAnew] INFO: const bool SetWord("word"):
[UAnew] INFO: attempts to find "word" in the database and, if successful,
[UAnew] INFO: assigns values from the database to slots pleasure, arousal,
[UAnew] INFO: dominance, pleasureSD, arousalSD, dominanceSD, pleasureRat,
[UAnew] INFO: arousalRat, dominanceRat according to the current category setting.
[UAnew] INFO: Return value: true if the word was found, false otherwise.

[UAnew] INFO: std::vector<std::string> ClearText("input text"):
[UAnew] INFO: processes the given input text by extracting words which consist
[UAnew] INFO: of at least minLettersCount letters and saves them
[UAnew] INFO: in the returned std::vector container.

[UAnew] INFO: void DisplayRating():
[UAnew] INFO: displays pleasure, arousal and dominance values for the current word.

[UAnew] INFO: void DisplaySD():
[UAnew] INFO: displays standard deviation values for pleasure, arousal
[UAnew] INFO: and dominance ratings for the current word.

[UAnew] INFO: void DisplayRat():
[UAnew] INFO: displays amounts of contributing values for pleasure, arousal
[UAnew] INFO: and dominance ratings for the current word.

[UAnew] INFO: void DisplayAll():
[UAnew] INFO: displays pleasure, arousal and dominance values,
[UAnew] INFO: then standard deviation values for pleasure, arousal
[UAnew] INFO: and dominance ratings, then amounts of contributing values
[UAnew] INFO: for pleasure, arousal and dominance ratings for the current word.

[UAnew] INFO: void DisplayRatingByIndex(number from 0 to databaseSize-1):
[UAnew] INFO: displays all available information for the word found under the given index.

[UAnew] INFO: void EvaluateText():
[UAnew] INFO: calculates the mean value of pleasure, arousal and dominance ratings
[UAnew] INFO: for the list of words acquired via ClearText("input text") method
[UAnew] INFO: and stores these in textPleasure, textArousal, textDominance slots.
[UAnew] INFO: This method does not take any arguments as the std::vector container
[UAnew] INFO: returned by ClearText is also stored internally.

[UAnew] INFO: void TestFindWord():
[UAnew] INFO: tests the functionality of FindWord function, which is responsible
[UAnew] INFO: for looking up words in the database, by attempting to find every
[UAnew] INFO: word present in the database.

[UAnew] INFO: word:
[UAnew] INFO: contains the most recent word looked up which was found in the database.

[UAnew] INFO: pleasure:
[UAnew] INFO: contains the pleasure rating for the current word.

[UAnew] INFO: arousal:
[UAnew] INFO: contains the arousal rating for the current word.

[UAnew] INFO: dominance:
[UAnew] INFO: contains the dominance rating for the current word.

[UAnew] INFO: pleasureSD:
[UAnew] INFO: contains the standard deviation value for pleasure rating
[UAnew] INFO: for the current word.

[UAnew] INFO: arousalSD:
[UAnew] INFO: contains the standard deviation value for arousal rating
[UAnew] INFO: for the current word.

[UAnew] INFO: dominanceSD:
[UAnew] INFO: contains the standard deviation value for dominance rating
[UAnew] INFO: for the current word.

[UAnew] INFO: pleasureRat:
[UAnew] INFO: contains the amount of contributing values for pleasure rating
[UAnew] INFO: for the current word.

[UAnew] INFO: arousalRat:
[UAnew] INFO: contains the amount of contributing values for arousal rating
[UAnew] INFO: for the current word.

[UAnew] INFO: dominanceRat:
[UAnew] INFO: contains the amount of contributing values for dominance rating
[UAnew] INFO: for the current word.

[UAnew] INFO: textPleasure:
[UAnew] INFO: contains the mean value of pleasure ratings for the list of words
[UAnew] INFO: acquired via ClearText("input text") method.

[UAnew] INFO: textArousal:
[UAnew] INFO: contains the mean value of arousal ratings for the list of words
[UAnew] INFO: acquired via ClearText("input text") method.

[UAnew] INFO: textDominance:
[UAnew] INFO: contains the mean value of dominance ratings for the list of words
[UAnew] INFO: acquired via ClearText("input text") method.

[UAnew] INFO: category:
[UAnew] INFO: defines the current category choice.
[UAnew] INFO: All ratings are picked from the database using this setting.
[UAnew] INFO: Allowed values:
[UAnew] INFO: "unisex", "male,", "female", "younger",
[UAnew] INFO: "older", "low_education", "high_education".
[UAnew] INFO: Default value: "unisex".

[UAnew] INFO: minLettersCount:
[UAnew] INFO: used in ClearText("input text") method.
[UAnew] INFO: Defines the minimal amount of letters for the words from
[UAnew] INFO: input text to be included in the returned std::vector container.
[UAnew] INFO: Default value: 3.

[UAnew] INFO: amountOfEntries:
[UAnew] INFO: contains the amount of entries in the currently loaded database.
[UAnew] INFO: Changing this value does not break the module's functionality.

[UAnew] INFO: verbosity:
[UAnew] INFO: defines whether text communicates in ClearText("input text"),
[UAnew] INFO: SetWord("word") and EvaluateText() methods should appear
[UAnew] INFO: on screen or not.
[UAnew] INFO: Values: 0 (none displayed), non-zero (all displayed).
[UAnew] INFO: Default value: 0.



**********************************************************

Urbiscript usage examples:

loadModule("UAnew");
var UAnew_module=UAnew.new("ratings.csv");
UAnew_module.SetWord("chicken");
UAnew_module.DisplayRating();
UAnew_module.DisplayAll();
var vectorOfWordsFromSentence=UAnew_module.ClearText("Among the lush forests of Bali is one remarkable village.");
UAnew_module.EvaluateText();
UAnew_module.textPleasure;
UAnew_module.textArousal;
UAnew_module.textDominance;
UAnew_module.verbosity=1;
UAnew_module.EvaluateText();