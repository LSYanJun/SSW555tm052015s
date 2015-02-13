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

class Individual;
// individual information
class Family;
// family information

class Individual
{
private:	
	string id;
	string name;
	char sex;     // m, f
	string birt; // date
	string deat; // date
	Family *famc;
	Family *fams;
public:
	void setid(string id)
	{
		this->id = id;
	}
	string getid()
	{
		return this->id;
	}
	void setname(string name)
	{
		this->name = name;
	}
	string getname()
	{
		return this->name;
	}
	void setsex(char sex)
	{
		this->sex = sex;
	}
	char getsex()
	{
		return this->sex;
	}
	void setbirt(string birt)
	{
		this->birt = birt;
	}
	string getbirt()
	{
		return this->birt;
	}
	void setdeat(string deat)
	{
		this->deat = deat;
	}
	string getdeat()
	{
		return this->deat;
	}
	void setfamc(Family *famc)
	{
		this->famc = famc;
	}
	Family *getfamc()
	{
		return this->famc;
	}
	void setfams(Family *fams)
	{
		this->fams = fams;
	}
	Family *getfams()
	{
		return this->fams;
	}
};

class Family
{
private:
	string id;
	string marr; // date
	Individual *husb;
	Individual *wife;
	vector<Individual *> chil;
	string div; // date
public:
	void setid(string id)
	{
		this->id = id;
	}
	string getid()
	{
		return this->id;
	}
	void setmarr()
	{
		this->marr = marr;
	}
	string getmarr()
	{
		return this->marr;
	}
	void sethusb(Individual *husb)
	{
		this->husb = husb;
	}
	Individual *gethusb()
	{
		return this->husb;
	}
	void setwife(Individual *wife)
	{
		this->wife = wife;
	}
	Individual *getwife()
	{
		return this->wife;
	}
	void addchild(Individual *chil)
	{
		this->chil.push_back(chil);
	}
	vector<Individual *> getchild()
	{
		return this->chil;
	}
	void setdiv(string div)
	{
		this->div = div;
	}
	string getdiv()
	{
		return this->div;
	}
};

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
	fin.close();
}

void check(vector<string> line, vector<string> &level, vector<string> &tag)
{
	for (int i = 0; i < line.size(); i++)
	{
		stringstream s;
		s << line[i];
		string val1,val2,val3,val4;
		s >> val1;
		level.push_back(val1);
		s >> val2;
		s >> val3;
		if (val1 == "0")
		{
			bool flag = false;
			if (val2 == "TRLR" || val2 == "NOTE")
			{
				flag = true;
				tag.push_back(val2);
			}
			if (val3 == "INDI" || val3 == "FAM")
			{
				flag = true;
				tag.push_back(val3);
			}
			if (flag == false)
				tag.push_back("Invalid tag");
		}
		if (val1 == "1")
		{
			if (val2 == "NAME" || val2 == "SEX" || val2 == "BIRT" || val2 == "DEAT"
				|| val2 == "FAMC" || val2 == "FAMS"
				|| val2 == "MARR" || val2 == "HUSB" || val2 == "WIFE" || val2 == "CHIL" || val2 == "DIV")
				tag.push_back(val2);
			else
				tag.push_back("Invalid tag");
		}	
		if (val1 == "2")
		{
			if (val2 == "DATE")
				tag.push_back(val2);
			else
				tag.push_back("Invalid tag");
		}
	}
}

void storeInfoProcess(vector<string> line, vector<Individual> &indi, vector<Family> &fami)
{

}

void report(vector<string> line, vector<string> level, vector<string> tag)
{
	// output to txt file named nameReport.txt
	ofstream fout("report#1.txt");
	for (int i = 0; i < line.size(); i++)
	{
		fout << "Line " << i + 1 << ": " << line[i] << endl;
		fout << "	Level number: " << level[i] << endl;
		fout << "	Tag:" << tag[i] << endl;
	}
	fout.close();
}

void report(vector<Individual> indi, vector<Family> fami)
{
	// output to txt file named nameReport.txt
	ofstream fout("report.txt");

	fout.close();
}

int main()
{
	vector<string> line;
	// store each line's information
	vector<string> level;
	// store each line's level number
	vector<string> tag;
	// store each line's tag
	vector<Individual> indi;
	//store the names of each of the individuals in order by their unique identifiers
	vector<Family> fami;
	// store the names of husbands and wives of each family in order by their unique identifiers
	// format: (husbadName,wifeName)
	read(line);
	check(line, level, tag);
	report(line, level, tag);
	storeInfoProcess(line, indi, fami);
	report(indi, fami);
	return 0;
}