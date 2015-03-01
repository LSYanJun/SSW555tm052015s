/*
COURSE: SSW555
Project: Gedcom
Repository: SSW555tm052015s
Team 5
NAME: Yanjun Wu/Gong Cheng/Amog Bheemanakolli Gurumallappa
*/
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include < map>
#include <ctime>
using namespace std;

class Genealogy
{
private:
	class Individual;
	// individual information
	class Family;
	// family information
	vector<string> line;
	// store each line's information
	vector<string> level;
	// store each line's level number
	vector<string> tag;
	// store each line's tag
	vector<string> argu;
	// store each line's argument
	vector<Individual *> indi;
	//store the names of each of the individuals in order by their unique identifiers
	vector<Family *> fami;
	// store the names of husbands and wives of each family in order by their unique identifiers
	vector<string> errorMsg;

	class Individual
	{
	private:
		string id;
		string name;
		char sex;     // M, F
		string birt; // date
		string deat; // date
		vector<string> sfamc;
		vector<string> sfams;
		vector<Family *> famc;
		vector<Family *> fams;
	public:
		Individual()
		{
			this->id = "";
			this->name = "";
			this->sex = NULL;
			this->birt = "";
			this->deat = "";
		}
		~Individual()
		{
		}
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
		void setsfamc(string sfamc)
		{
			this->sfamc.push_back(sfamc);
		}
		vector<string> getsfamc()
		{
			return sfamc;
		}
		void addsfams(string sfams)
		{
			this->sfams.push_back(sfams);
		}
		vector<string> getsfams()
		{
			return this->sfams;
		}
		void setfamc(Family *famc)
		{
			this->famc.push_back(famc);
		}
		vector<Family *> getfamc()
		{
			return this->famc;
		}
		void addfams(Family *fams)
		{
			this->fams.push_back(fams);
		}
		vector<Family *> getfams()
		{
			return this->fams;
		}
	};

	class Family
	{
	private:
		string id;
		string marr; // date
		vector<string> shusb;
		vector<string> swife;
		vector<Individual *> husb;
		vector<Individual *> wife;
		vector<string> schil;
		vector<Individual *> chil;
		string div; // date
	public:
		Family()
		{
			this->id = "";
			this->marr = "";
			this->div = "";
		}
		~Family()
		{
		}
		void setid(string id)
		{
			this->id = id;
		}
		string getid()
		{
			return this->id;
		}
		void setmarr(string marr)
		{
			this->marr = marr;
		}
		string getmarr()
		{
			return this->marr;
		}
		void setshusb(string shusb)
		{
			this->shusb.push_back(shusb);
		}
		vector<string> getshusb()
		{
			return this->shusb;
		}
		void setswife(string swife)
		{
			this->swife.push_back(swife);
		}
		vector<string> getswife()
		{
			return this->swife;
		}
		void sethusb(Individual *husb)
		{
			this->husb.push_back(husb);
		}
		vector<Individual *> gethusb()
		{
			return this->husb;
		}
		void setwife(Individual *wife)
		{
			this->wife.push_back(wife);
		}
		vector<Individual *> getwife()
		{
			return this->wife;
		}
		void addschild(string schil)
		{
			this->schil.push_back(schil);
		}
		vector<string> getschild()
		{
			return this->schil;
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

	void sort()  // sort the individuals and families by ID
	{
		for (int j = indi.size() - 1; j >= 0; j--)
		{
			int max = 0;
			int flag = j;
			for (int i = 0; i <= j; i++)
			{
				string id = indi[i]->getid();
				int nid = atoi(id.substr(1, id.length() - 1).c_str());
				if (nid > max)
				{
					max = nid;
					flag = i;
				}
			}
			Individual *temp = indi[j];
			indi[j] = indi[flag];
			indi[flag] = temp;
		}		
		for (int j = fami.size() - 1; j >= 0; j--)
		{
			int max = 0;
			int flag = j;
			for (int i = 0; i <= j; i++)
			{
				string id = fami[i]->getid();
				int nid = atoi(id.substr(1, id.length() - 1).c_str());
				if (nid > max)
				{
					max = nid;
					flag = i;
				}
			}
			Family *temp = fami[j];
			fami[j] = fami[flag];
			fami[flag] = temp;
		}
	}

	//user stories
	void inexistID() //Gong Cheng
	{
		for (int i = 0; i < indi.size(); i++)
		{
			for (int m = 0; m < indi[i]->getsfamc().size(); m++)
			if (indi[i]->getsfamc()[m] != "")
			{
				int j = 0;
				for (j = 0; j < fami.size(); j++)
				{
					if (fami[j]->getid() == indi[i]->getsfamc()[m])
					{
						indi[i]->setfamc(fami[j]);
						break;
					}
				}
				if (j == fami.size())
				{
					string temp = "Individual ";
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") is a child of an inexistent Family " + indi[i]->getsfamc()[m] + ".";
					errorMsg.push_back(temp);
				}
			}
			for (int m = 0; m < indi[i]->getsfams().size(); m++)
			{
				int j = 0;
				for (j = 0; j < fami.size(); j++)
				{
					if (fami[j]->getid() == indi[i]->getsfams()[m])
					{
						indi[i]->addfams(fami[j]);
						break;
					}
				}
				if (j == fami.size())
				{
					string temp = "Individual ";
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") is a spouse of an inexistent Family " + indi[i]->getsfams()[m] +".";
					errorMsg.push_back(temp);
				}
			}
		}
		for (int i = 0; i < fami.size(); i++)
		{
			for (int m = 0; m < fami[i]->getshusb().size(); m++)
			if (fami[i]->getshusb()[m] != "")
			{
				int j = 0;
				for (j = 0; j < indi.size(); j++)
				{
					if (indi[j]->getid() == fami[i]->getshusb()[m])
					{
						fami[i]->sethusb(indi[j]);
						break;
					}
				}
				if (j == indi.size())
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + " has a husband who is an inexistent Individual " + fami[i]->getshusb()[m] + ".";
					errorMsg.push_back(temp);
				}
			}
			for (int m = 0; m < fami[i]->getswife().size(); m++)
			if (fami[i]->getswife()[m] != "")
			{
				int j = 0;
				for (j = 0; j < indi.size(); j++)
				{
					if (indi[j]->getid() == fami[i]->getswife()[m])
					{
						fami[i]->setwife(indi[j]);
						break;
					}
				}
				if (j == indi.size())
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + " has a wife who is an inexistent Individual " + fami[i]->getswife()[m] + ".";
					errorMsg.push_back(temp);
				}
			}
			for (int m = 0; m < fami[i]->getschild().size(); m++)
			{
				int j = 0;
				for (j = 0; j < indi.size(); j++)
				{
					if (indi[j]->getid() == fami[i]->getschild()[m])
					{
						fami[i]->addchild(indi[j]);
						break;
					}
				}
				if (j == indi.size())
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + " has a child who is an inexistent Individual " + fami[i]->getschild()[m] + ".";
					errorMsg.push_back(temp);
				}
			}
		}
	}

	void unmatchedPointers()//Gong Cheng
	{
		for (int i = 0; i < indi.size(); i++)
		{

			for (int m = 0; m < indi[i]->getfamc().size(); m++)
			{
				int j = 0;
				for (j = 0; j < indi[i]->getfamc()[m]->getchild().size(); j++)
				{
					if (indi[i]->getfamc()[m]->getchild()[j] == indi[i]) break;
				}
				if (j == indi[i]->getfamc()[m]->getchild().size())
				{
					string temp = "Individual ";
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") is a child of Family " + indi[i]->getfamc()[m]->getid() + ", but Family " + indi[i]->getfamc()[m]->getid() + " does not have the child of " + indi[i]->getid() + "(" + indi[i]->getname() + ").";
					errorMsg.push_back(temp);
				}
			}
			for (int m = 0; m < indi[i]->getfams().size(); m++)
			{
				bool flag = false;
				for (int n = 0; n < indi[i]->getfams()[m]->gethusb().size(); n++)
				if (indi[i] == indi[i]->getfams()[m]->gethusb()[n])
				{
					flag = true;
					break;
				}
				if (!flag)
				for (int n = 0; n < indi[i]->getfams()[m]->getwife().size(); n++)
				if (indi[i] == indi[i]->getfams()[m]->getwife()[n])
				{
					flag = true;
					break;
				}
				if (!flag)
				{
					string temp = "Individual ";
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") is a spouse of Family " + indi[i]->getfams()[m]->getid() + ", but Family " + indi[i]->getfams()[m]->getid() + " does not have the spouse of " + indi[i]->getid() + "(" + indi[i]->getname() + ").";
					errorMsg.push_back(temp);
				}
			}
		}
		for (int i = 0; i < fami.size(); i++)
		{

			for (int m = 0; m < fami[i]->gethusb().size(); m++)
			{
				int j = 0;
				for (j = 0; j < fami[i]->gethusb()[m]->getfams().size(); j++)
				{
					if (fami[i]->gethusb()[m]->getfams()[j] == fami[i]) break;
				}
				if (j == fami[i]->gethusb()[m]->getfams().size())
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + "'s husband is Individual " + fami[i]->gethusb()[m]->getid() + "(" + fami[i]->gethusb()[m]->getname() + "), but Individual " + fami[i]->gethusb()[m]->getid() + "(" + fami[i]->gethusb()[m]->getname() + ") is not the husband of Family " + fami[i]->getid() + ".";
					errorMsg.push_back(temp);
				}
			}
			for (int m = 0; m < fami[i]->getwife().size(); m++)
			{
				int j = 0;
				for (j = 0; j < fami[i]->getwife()[m]->getfams().size(); j++)
				{
					if (fami[i]->getwife()[m]->getfams()[j] == fami[i]) break;
				}
				if (j == fami[i]->getwife()[m]->getfams().size())
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + "'s wife is Individual " + fami[i]->getwife()[m]->getid() + "(" + fami[i]->getwife()[m]->getname() + "), but Individual " + fami[i]->getwife()[m]->getid() + "(" + fami[i]->getwife()[m]->getname() + ") is not the wife of Family " + fami[i]->getid() + ".";
					errorMsg.push_back(temp);
				}
			}
			for (int m = 0; m < fami[i]->getchild().size(); m++)
			{
				int n = 0;
				for (n = 0; n < fami[i]->getchild()[m]->getfamc().size(); n++)
				if (fami[i] == fami[i]->getchild()[m]->getfamc()[n])
				{
					break;
				}
				if (n == fami[i]->getchild()[m]->getfamc().size())
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + " has a child who is Individual " + fami[i]->getchild()[m]->getid() + "(" + fami[i]->getchild()[m]->getname() + "), but Individual " + fami[i]->getchild()[m]->getid() + "(" + fami[i]->getchild()[m]->getname() + ") is not a child of Family " + fami[i]->getid() + ".";
					errorMsg.push_back(temp);
				}
			}
		}
	}
<<<<<<< HEAD
	void invalidFamilyMember()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			int husb = fami[i]->gethusb().size();
			if (husb == 0)
			{
				string temp = "Family ";
				temp = temp + fami[i]->getid() + " does not have a husband.";
				errorMsg.push_back(temp);
			}
			if (husb > 1)
			{
				string temp = "Family ";
				temp = temp + fami[i]->getid() + " has " + to_string(husb) + " husbands: ";
				for (int j = 0; j < husb - 1; j++)
				{
					temp = temp + fami[i]->gethusb()[j]->getid() + "(" + fami[i]->gethusb()[j]->getname() + "), ";
				}
				temp = temp + fami[i]->gethusb()[husb-1]->getid() + "(" + fami[i]->gethusb()[husb-1]->getname() + ").";
				errorMsg.push_back(temp);
			}
		}
		for (int i = 0; i < fami.size(); i++)
		{
			int wife = fami[i]->getwife().size();
			if (wife == 0)
			{
				string temp = "Family ";
				temp = temp + fami[i]->getid() + " does not have a wife.";
				errorMsg.push_back(temp);
			}
			if (wife > 1)
			{
				string temp = "Family ";
				temp = temp + fami[i]->getid() + " has " + to_string(wife) + " wives: ";
				for (int j = 0; j < wife - 1; j++)
				{
					temp = temp + fami[i]->getwife()[j]->getid() + "(" + fami[i]->getwife()[j]->getname() + "), ";
				}
				temp = temp + fami[i]->getwife()[wife - 1]->getid() + "(" + fami[i]->getwife()[wife - 1]->getname() + ").";
				errorMsg.push_back(temp);
			}
		}
	}
	
=======
	void invalidDate()//Yanjun Wu
	{
		string ERRMSG = "";
		time_t tt = time(NULL);
		tm* t = localtime(&tt);
		int cy = t->tm_year + 1900;
		int cm = t->tm_mon + 1;
		int cd = t->tm_mday;
		map<string, int> monthMap;
		monthMap["JAN"] = 1;
		monthMap["FEB"] = 2;
		monthMap["MAR"] = 3;
		monthMap["APR"] = 4;
		monthMap["MAY"] = 5;
		monthMap["JUN"] = 6;
		monthMap["JUL"] = 7;
		monthMap["AUG"] = 8;
		monthMap["SEP"] = 9;
		monthMap["OCT"] = 10;
		monthMap["NOV"] = 11;
		monthMap["DEC"] = 12;
		bool isBirtLeap;
		bool isDeatLeap;
		bool invBirtD;
		bool invDeatD;
		bool isDead = false;
		for (int i = 0; i < indi.size(); i++)
		{
			cout << indi[i]->getbirt() << " " << indi[i]->getdeat() << endl;
			stringstream birt;
			stringstream deat;
			if (indi[i]->getdeat() == "")
				isDead = false;
			else
			{
				isDead = true;
				//cout << indi[i]->getid() << " " << indi[i]->getname() << endl;
			}
			birt << indi[i]->getbirt();
			deat << indi[i]->getdeat();
			string bday, bmonth, byear, dday, dmonth, dyear;
			birt >> bday;
			birt >> bmonth;
			birt >> byear;
			deat >> dday;
			deat >> dmonth;
			deat >> dyear;
			int bd, bm, by, dd, dm, dy;
			bd = atoi(bday.c_str());
			bm = monthMap[bmonth];
			by = atoi(byear.c_str());
			dd = atoi(dday.c_str());
			dm = monthMap[dmonth];
			dy = atoi(dyear.c_str());
			isBirtLeap = leapYear(by);
			isDeatLeap = leapYear(dy);
			invBirtD = outOfRange(bm, bd, isBirtLeap);
			invDeatD = outOfRange(dm, dd, isDeatLeap);
			//US03
			if (cy < by || (cy == by && cm < bm) || (cy == by && cm == bm && cd < bd)) //invalid birth date
			{
				ERRMSG = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") has an invalid birth date(" 
					+ indi[i]->getbirt() + ")." + " Birthday before current date.";
				errorMsg.push_back(ERRMSG);
			}
			if (invBirtD == false)
			{
				ERRMSG = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") has an invalid birth date("
					+ indi[i]->getbirt() + ")." + " Birthday doesn't exist.";
				errorMsg.push_back(ERRMSG);
			}
			if (isDead == true)
			{
				if (cy < dy || (cy == dy && cm < dm) || (cy == dy && cm == dm && cd < dd)) //invalid death date
				{
					ERRMSG = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") has an invalid death date("
						+ indi[i]->getdeat() + ")." + "Death date before current date.";
					errorMsg.push_back(ERRMSG);
				}
				if (invDeatD == false)
				{
					ERRMSG = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") has an invalid death date.("
						+ indi[i]->getdeat() + ")." + " Death date doesn't exist.";
					errorMsg.push_back(ERRMSG);
				}
			}
		
			//US05 death before birth
			if (isDead == true)
			{
				if (dy < by || (dy == by && dm < bm) || (dy == by && dm == bm && dd < bd))
				{
					ERRMSG = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") death before birth. " + "Birth: " + indi[i]->getbirt() + " Death: " + indi[i]->getdeat();
					errorMsg.push_back(ERRMSG);
				}
			}
		}
	}
	bool leapYear(int year)
	{
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;
		else
			return false;
	}
	bool outOfRange(int month, int day, bool isLeapYear)
	{
		int mon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		if (isLeapYear == true)
			mon[1] = 29;
		if (day > 0 && day <= mon[month - 1])
			return true;
		else
			return false;
	}
	void invalidFamMember()//Yanjun Wu
	{

	}

>>>>>>> origin/master
public:
	Genealogy()
	{

	}
	~Genealogy()
	{
		while (indi.size())
		{
			Individual *temp = indi.back();
			indi.pop_back();
			delete temp;
		}
		while (fami.size())
		{
			Family *temp = fami.back();
			fami.pop_back();
			delete temp;
		}
	}
	void read(string path)
	{
		string temp;
		ifstream fin(path);
		if (fin.good())
		{
			cout << "Reading success." << endl;
			while (getline(fin, temp))
				line.push_back(temp);
		}
		fin.close();
	}

	void storeVec()
	{
		string temp;
		string tags[2];
		tags[0] = "";
		tags[1] = "";
		for (int i = 0; i < line.size(); i++)
		{
			stringstream s;
			s << line[i];
			string val1, val2;
			s >> val1;
			if (val1 == "0" || val1 == "1" || val1 == "2")
				level.push_back(val1);
			else
				level.push_back("Invalid level");
			s >> val2;
			getline(s, temp);
			temp.erase(0, temp.find_first_not_of(" "));
			//cout << temp << endl;
			if (val1 == "0")
			{
				if (temp == "INDI")
				{
					tags[0] = "INDI";
					tag.push_back(temp);
					argu.push_back(val2);
				}
				else if (temp == "FAM")
				{
					tags[0] = "FAM";
					tag.push_back(temp);
					argu.push_back(val2);
				}
				else if (val2 == "NOTE")
				{
					tag.push_back(val2);
					argu.push_back(temp);
				}
				else if (val2 == "TRLR")
				{
					tag.push_back(val2);
					argu.push_back("NONE");
				}
				else
				{
					tag.push_back("Invalid tag");
					argu.push_back("Invalid argument");
				}
			}
			else if (val1 == "1")
			{
				if (tags[0] == "INDI")
				{
					if (val2 == "NAME" || val2 == "SEX" || val2 == "FAMS" || val2 == "FAMC")
					{
						tag.push_back(val2);
						argu.push_back(temp);
					}
					else if (val2 == "BIRT")
					{
						tags[1] = "BIRT";
						tag.push_back(val2);
						argu.push_back("NONE");
					}
					else if (val2 == "DEAT")
					{
						tags[1] = "DEAT";
						tag.push_back(val2);
						argu.push_back("NONE");
					}
					else
					{
						tag.push_back("Invalid tag");
						argu.push_back("Invalid argument");
					}
				}
				else if (tags[0] == "FAM")
				{
					if (val2 == "HUSB" || val2 == "WIFE" || val2 == "CHIL")
					{
						tag.push_back(val2);
						argu.push_back(temp);
					}
					else if (val2 == "MARR")
					{
						tags[1] = "MARR";
						tag.push_back(val2);
						argu.push_back("NONE");
					}
					else if (val2 == "DIV")
					{
						tags[1] = "DIV";
						tag.push_back(val2);
						argu.push_back("NONE");
					}
					else
					{
						tag.push_back("Invalid tag");
						argu.push_back("Invalid argument");
					}
				}
				else
				{
					tag.push_back("Invalid tag");
					argu.push_back("Invalid argument");
				}
			}
			else if (val1 == "2")
			{
				if (val2 == "DATE")
				{
					if (tags[0] == "INDI" && (tags[1] == "BIRT" || tags[1] == "DEAT"))
					{
						tag.push_back(val2);
						argu.push_back(temp);
					}
					else if (tags[0] == "FAM" && (tags[1] == "MARR" || tags[1] == "DIV"))
					{
						tag.push_back(val2);
						argu.push_back(temp);
					}
					else
					{
						tag.push_back("Invalid tag");
						argu.push_back("Invalid argument");
					}
				}
				else
				{
					tag.push_back("Invalid tag");
					argu.push_back("Invalid argument");
				}
			}
			else
			{
				tag.push_back("Invalid tag");
				argu.push_back("Invalid argument");
			}
		}
	/*	for (int i = 0; i < line.size(); i++)
		{
			cout << level[i] << " " << tag[i] << " " << argu[i] << endl;
		}*/
	}

	void test()
	{
		ofstream fout("testResult.txt");
		fout << "Error Messages: " << endl;
		inexistID();
		unmatchedPointers();
<<<<<<< HEAD
		invalidFamilyMember();
=======
		invalidDate();
		invalidFamMember();
>>>>>>> origin/master
		for (int i = 0; i < errorMsg.size(); i++)
		{
			fout << errorMsg[i] << endl;
		}
		fout.close();
	}

	void storeInfoProcess()
	{
		for (int i = 0; i < level.size();)  //store individual information
		{
			if (level[i] == "0" && tag[i] == "INDI")
			{
				Individual * nindi = new Individual;
				nindi->setid(argu[i].substr(1, argu[i].length() - 2));
				i++;
				while (level[i] != "0" && i < level.size())
				{
					if (tag[i] == "NAME")
					{
						nindi->setname(argu[i]);
					}
					else if (tag[i] == "SEX")
					{
						nindi->setsex(argu[i][0]);
					}
					else if (tag[i] == "BIRT")
					{
						if (i + 1 < level.size())
						{
							i++;
							if (tag[i] == "DATE")
								nindi->setbirt(argu[i]);
						}
					}
					else if (tag[i] == "DEAT")
					{
						if (i + 1 < level.size())
						{
							i++;
							if (tag[i] == "DATE")
								nindi->setdeat(argu[i]);
						}
					}
					else if (tag[i] == "FAMC")
					{
						nindi->setsfamc(argu[i].substr(1, argu[i].length() - 2));
					}
					else if (tag[i] == "FAMS")
					{
						nindi->addsfams(argu[i].substr(1, argu[i].length() - 2));
					}
					i++;
				}
				indi.push_back(nindi);
			}
			else i++;
		}
		for (int i = 0; i < level.size();)  //store family information
		{
			if (level[i] == "0" && tag[i] == "FAM")
			{
				Family * nfam = new Family;
				nfam->setid(argu[i].substr(1, argu[i].length() - 2));
				i++;
				while (level[i] != "0" && i < level.size())
				{
					if (tag[i] == "HUSB")
					{
						nfam->setshusb(argu[i].substr(1, argu[i].length() - 2));
					}
					else if (tag[i] == "WIFE")
					{

						nfam->setswife(argu[i].substr(1, argu[i].length() - 2));
					}
					else if (tag[i] == "CHIL")
					{

						nfam->addschild(argu[i].substr(1, argu[i].length() - 2));
					}
					else if (tag[i] == "MARR")
					{
						if (i + 1 < level.size())
						{
							i++;
							if (tag[i] == "DATE")
								nfam->setmarr(argu[i]);
						}
					}
					else if (tag[i] == "DIV")
					{
						if (i + 1 < level.size())
						{
							i++;
							if (tag[i] == "DATE")
								nfam->setdiv(argu[i]);
						}
					}
					i++;
				}
				fami.push_back(nfam);
			}
			else i++;
		}
		sort();
	}

	void report(string path)   // report of the sorted individuals and familes
	{
		// output to txt file named Report.txt
		ofstream fout(path);

		fout << "Individuals: " << endl;
		for (int i = 0; i < indi.size(); i++)
			fout << "ID : " << indi[i]->getid() << ", NAME : " << indi[i]->getname() << endl;


		fout << "Families: " << endl;
	//	for (int i = 0; i < fami.size(); i++)
	//		fout << "ID : " << fami[i]->getid() << ", HUSB : " << fami[i]->getshusb() << ", WIFE : " << fami[i]->getswife() << endl;
		fout.close();
	}

};

int main()
{
	Genealogy gene;
	gene.read("test.ged");
	gene.storeVec();
	gene.storeInfoProcess();
	gene.test();
	gene.report("report.txt");
	return 0;
}