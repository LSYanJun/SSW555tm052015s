/*
COURSE: SSW555
PROJECT 3
Team 5
NAME: Yanjun Wu/Gong Cheng/Amog Bheemanakolli Gurumallappa
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

void read(vector<string> &line)
{
	string temp;
	ifstream fin("YanjunWu10392467_P01.ged");
	if (fin.good())
	{
		cout << "Reading success." << endl;
		while (getline(fin, temp))
			line.push_back(temp);
	}
}
void report(vector<string> line, vector<string> &level, vector<string> &tag)
{
	for (int i = 0; i < line.size(); i++)
	{
		stringstream s;
		s << line[i];
		string tempLvl, tempTag;
		s >> tempLvl;
		level.push_back(tempLvl);
		s >> tempTag;
		if (tempTag == "INDI" || tempTag == "NAME" || tempTag == "SEX" || tempTag == "BIRT" || tempTag == "DEAT" || tempTag == "FAMC" || tempTag == "FAMS" || tempTag == "FAM"
			|| tempTag == "MARR" || tempTag == "HUSB" || tempTag == "WIFE" || tempTag == "CHIL" || tempTag == "DIV" || tempTag == "DATE" || tempTag == "TRLR" || tempTag == "NOTE")
			tag.push_back(tempTag);
		else
			tag.push_back("Invalid tag");
	}
	ofstream fout("Report.txt");
	for (int i = 0; i < line.size(); i++)
	{
		fout << "Line " << i + 1 << ": " << line[i] << endl;
		fout << "	Level number: " << level[i] << endl;
		fout << "	Tag:" << tag[i] << endl;
	}
}

void storeInfoProcess(vector<string> line, vector<string> &indi_names, vector<string> &family_names)
{

}

void reportNames(vector<string> indi_names, vector<string> family_names)
{

}

int main()
{
	vector<string> line;
	// store each line's information
	vector<string> level;
	// store each line's level number
	vector<string> tag;
	// store each line's tag
	vector<string> indi_names;
	//store the names of each of the individuals in order by their unique identifiers
	vector<string> family_names;
	// store the names of husbands and wives of each family in order by their unique identifiers
	// format: (husbadName,wifeName)
	read(line);
	report(line, level, tag);
	storeInfoProcess(line, indi_names, family_names);
	reportNames(indi_names, family_names);
	return 0;
}