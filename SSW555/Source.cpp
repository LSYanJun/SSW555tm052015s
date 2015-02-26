/*
COURSE: SSW555
Project: Gedcom
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
	char sex;     // M, F
	string birt; // date
	string deat; // date
	Family *famc;
	Family *fams;
public:
	Individual()
	{
		this->id = "";
		this->name = "";
		this->sex = NULL;
		this->birt = "";
		this->deat = "";
		this->famc = nullptr;
		this->fams = nullptr;
	}
	~Individual()
	{
		delete famc;
		delete fams;
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
	Family()
	{
		this->id = "";
		this->marr = "";
		this->husb = nullptr;
		this->wife = nullptr;
		this->div = "";
	}
	~Family()
	{
		while (chil.size())
		{
			Individual *temp = chil.back();
			chil.pop_back();
			delete temp;
		}
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

void storeVec(vector<string> line, vector<string> &level, vector<string> &tag, vector<string> &argu)
{
	string temp;
	string tags[2] ;
	tags[0] = "";
	tags[1] = "";
	for (int i = 0; i < line.size(); i++)
	{
		stringstream s;
		s << line[i];
		string val1,val2;
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
				if (tags[0] == "INDI" && (tags[1] == "BIRT" || tag[1] == "DEAT"))
				{
					tag.push_back(val2);
					argu.push_back(temp);
				}
				else if (tags[0] == "FAM" && (tags[1] == "MARR" || tag[1] == "DIV"))
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
	for (int i = 0; i < line.size(); i++)
	{
		cout << level[i] << " " << tag[i] << " " << argu[i] << endl;
	}
}
void validFormat(vector<string> &level, vector<string> &tag, vector<string> &argu)//before store info process
{
	//US01 Invalid date format

	//US02 Invalid ID format

	//US03 Invalid date

	//US04 Invalid gender format
	//Implemented by Amog

	//US05 Invalid name format

	//US09 Invalid age of an individual
	//Implemented by Amog

}
void validInfo(vector<Individual *> &indi, vector<Family *> &fami)//after store info process
{

}
void storeInfoProcess(vector<string> &level, vector<string> &tag, vector<string> &argu, vector<Individual *> &indi, vector<Family *> &fami)
{
	for (int i = 0; i < level.size();)  //store individual information
	{
		if (level[i] == "0" && tag[i] == "INDI")
		{
			Individual * nindi = new Individual;
			nindi->setid(argu[i]);
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
				i++;
			}
			indi.push_back(nindi);
		}
		else i++;
	}
	for (int i = 0; i < level.size();)  //store family information and linked all related individuals and families together
	{
		if (level[i] == "0" && tag[i] == "FAM")
		{
			Family * nfam = new Family;
			nfam->setid(argu[i]);
			i++;
			while (level[i] != "0" && i < level.size())
			{
				if (tag[i] == "HUSB")
				{
					for (int m = 0; m < indi.size(); m++)
					{
						if (indi[m]->getid() == argu[i])
						{
							nfam->sethusb(indi[m]);
							indi[m]->setfams(nfam);
							break;
						}
					}
				}
				else if (tag[i] == "WIFE")
				{
					for (int m = 0; m < indi.size(); m++)
					{
						if (indi[m]->getid() == argu[i])
						{
							nfam->setwife(indi[m]);
							indi[m]->setfams(nfam);
							break;
						}
					}
				}
				else if (tag[i] == "CHIL")
				{
					for (int m = 0; m < indi.size(); m++)
					{
						if (indi[m]->getid() == argu[i])
						{
							nfam->addchild(indi[m]);
							indi[m]->setfamc(nfam);
							break;
						}
					}
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
}

void report(vector<Individual *> indi, vector<Family *> fami)   // report of the sorted individuals and familes
{
	// output to txt file named Report.txt
	ofstream fout("report.txt");

	for (int j = indi.size() - 1; j >= 0; j--)
	{
		int max = 0;
		int flag = j;
		for (int i = 0; i <= j; i++)
		{
			string id = indi[i]->getid();
			int nid = atoi(id.substr(2, id.length() - 3).c_str());
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
	fout << "Individuals: " << endl;
	for (int i = 0; i < indi.size(); i++)
		fout << "ID : " << indi[i]->getid() << ", NAME : " << indi[i]->getname() << endl;

	for (int j = fami.size() - 1; j >= 0; j--)
	{
		int max = 0;
		int flag = j;
		for (int i = 0; i <= j; i++)
		{
			string id = fami[i]->getid();
			int nid = atoi(id.substr(2, id.length() - 3).c_str());
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
	fout << "Families: " << endl;
	for (int i = 0; i < fami.size(); i++)
		fout << "ID : " << fami[i]->getid() << ", HUSB : " << fami[i]->gethusb()->getname() << ", WIFE : " << fami[i]->getwife()->getname() << endl;
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
	vector<string> argu;
	// store each line's argument
	vector<Individual *> indi;
	//store the names of each of the individuals in order by their unique identifiers
	vector<Family *> fami;
	// store the names of husbands and wives of each family in order by their unique identifiers
	read(line);
	storeVec(line, level, tag, argu);
	//storeInfoProcess(level, tag, argu, indi, fami);
	//report(indi, fami);
	return 0;
}