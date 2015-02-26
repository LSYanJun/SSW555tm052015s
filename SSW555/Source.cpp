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
	char sex;     // m, f
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

void check(vector<string> line, vector<string> &level, vector<string> &tag, vector<string> &argu)
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

	//US03 Invalid date of birth/death

	//US04 Invalid gender format

	//US05 Invalid name format

	//

}
void validInfo(vector<Individual *> &indi, vector<Family *> &fami)//after store info process
{

}
void storeInfoProcess(vector<string> line, vector<string> &level, vector<string> &tag, vector<Individual *> &indi, vector<Family *> &fami)
{
	for (int i = 0; i < line.size();)  //store individual information
	{
		if (level[i] == "0" && tag[i] == "INDI")
		{
			Individual * nindi = new Individual;
			stringstream s;
			string val1, val2, val3;
			s << line[i];
			s >> val1 >> val2;
			if (val2 != "INDI")
				nindi->setid(val2);
			i++;
			s.sync();
			while (level[i] != "0" && i < line.size())
			{
				if (tag[i] == "NAME")
				{
					nindi->setname(line[i].substr(7));
				}
				else if (tag[i] == "SEX")
				{
					nindi->setsex(line[i].substr(6)[0]);
				}
				else if (tag[i] == "BIRT")
				{
					if (i + 1 < line.size())
					{
						i++;
						if (tag[i] == "DATE")
							nindi->setbirt(line[i].substr(7));
					}
				}
				else if (tag[i] == "DEAT")
				{
					if (i + 1 < line.size())
					{
						i++;
						if (tag[i] == "DATE")
							nindi->setdeat(line[i].substr(7));
					}
				}
				i++;
			}
			indi.push_back(nindi);
		}
		else i++;
	}
	for (int i = 0; i < line.size();)  //store family information and linked all related individuals and families together
	{
		if (level[i] == "0" && tag[i] == "FAM")
		{
			Family * nfam = new Family;
			stringstream s;
			string val1, val2, val3;
			s << line[i];
			s >> val1 >> val2;
			if (val2 != "FAM")
				nfam->setid(val2);
			i++;
			s.sync();
			while (level[i] != "0" && i < line.size())
			{
				if (tag[i] == "HUSB")
				{
					for (int m = 0; m < indi.size(); m++)
					{
						if (indi[m]->getid() == line[i].substr(7))
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
						if (indi[m]->getid() == line[i].substr(7))
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
						if (indi[m]->getid() == line[i].substr(7))
						{
							nfam->addchild(indi[m]);
							indi[m]->setfamc(nfam);
							break;
						}
					}
				}
				else if (tag[i] == "MARR")
				{
					if (i + 1 < line.size())
					{
						i++;
						if (tag[i] == "DATE")
							nfam->setmarr(line[i].substr(7));
					}
				}
				else if (tag[i] == "DIV")
				{
					if (i + 1 < line.size())
					{
						i++;
						if (tag[i] == "DATE")
							nfam->setdiv(line[i].substr(7));
					}
				}
				i++;
			}
			fami.push_back(nfam);
		}
		else i++;
	}
}

void report(vector<string> line, vector<string> level, vector<string> tag)  // report of the tag information
{
	// output to txt file named Report#1.txt
	ofstream fout("report#1.txt");
	for (int i = 0; i < line.size(); i++)
	{
		fout << "Line " << i + 1 << ": " << line[i] << endl;
		fout << "	Level number: " << level[i] << endl;
		fout << "	Tag:" << tag[i] << endl;
	}
	fout.close();
}

void report(vector<Individual *> indi, vector<Family *> fami)   // report of the sorted individuals and familes
{
	// output to txt file named Report.txt
	ofstream fout("report.txt");
	/*
	for (int i = 0; i < indi.size(); i++)
	{
		fout << "id " << i + 1 << ": " << indi[i]->getid() << " Name " << i + 1 << ": " << indi[i]->getname() << " Sex " << i + 1 << ": " << indi[i]->getsex() << " BIRT " << i + 1 << ": " << indi[i]->getbirt() << " Deat " << i + 1 << ": " << indi[i]->getdeat();
		if (indi[i]->getfams())
			fout << " Fams " << i + 1 << ": " << indi[i]->getfams()->getid();
		if (indi[i]->getfamc())
			fout << " Famc " << i + 1 << ": " << indi[i]->getfamc()->getid();
		fout << endl;
	}
	for (int i = 0; i < fami.size(); i++)
	{
		fout << "id " << i + 1 << ": " << fami[i]->getid() << " marr " << i + 1 << ": " << fami[i]->getmarr() << " div " << i + 1 << ": " << fami[i]->getdiv() << " husb " << i + 1 << ": " << fami[i]->gethusb()->getname() << " wife " << i + 1 << ": " << fami[i]->getwife()->getname();
		for (int j = 0; j < fami[i]->getchild().size(); j++)
			fout << " Child " << j + 1 << ": " << fami[i]->getchild()[j]->getname();
		fout << endl;
	}*/
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
	// format: (husbadName,wifeName)
	read(line);
	check(line, level, tag, argu);
	/*report(line, level, tag);
	storeInfoProcess(line, level, tag, indi, fami);
	report(indi, fami);*/
	return 0;
}