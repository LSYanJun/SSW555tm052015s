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
	time_t tt = time(NULL);
	tm* t = localtime(&tt);
	int cy = t->tm_year + 1900; // current year
	int cm = t->tm_mon + 1;// current month
	int cd = t->tm_mday;// current day

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
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") is a spouse of an inexistent Family " + indi[i]->getsfams()[m] + ".";
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

	void invalidAge() // Gong Cheng
	{
		for (int i = 0; i < indi.size(); i++)
		{
			if (indi[i]->getbirt() == "") continue;
			int birt = atoi(indi[i]->getbirt().substr(indi[i]->getbirt().length() - 4).c_str());
			int deat = cy;
			if (indi[i]->getdeat() != "")
			{
				deat = atoi(indi[i]->getdeat().substr(indi[i]->getdeat().length() - 4).c_str());
			}
			if (deat - birt >= 150)
			{
				string temp = "Individual ";
				if (indi[i]->getdeat() == "")
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") is older than 150 years old. Birth date(" + indi[i]->getbirt() + "), not dead.";
				else
					temp = temp + indi[i]->getid() + "(" + indi[i]->getname() + ") was older than 150 years old. Birth date(" + indi[i]->getbirt() + "), deat date(" + indi[i]->getdeat() + ").";
				errorMsg.push_back(temp);
			}
		}
	}

	void multipleRoles()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			vector<Individual *> t;
			vector<string> role;
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				t.push_back(fami[i]->gethusb()[j]);
				role.push_back("husband");
			}
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				t.push_back(fami[i]->getwife()[j]);
				role.push_back("wife");
			}
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				t.push_back(fami[i]->getchild()[j]);
				role.push_back("child");
			}
			for (int j = t.size() - 1; j >= 0; j--)
			{
				int max = 0;
				int flag = j;
				for (int k = 0; k <= j; k++)
				{
					string id = t[k]->getid();
					int nid = atoi(id.substr(1, id.length() - 1).c_str());
					if (nid > max)
					{
						max = nid;
						flag = k;
					}
				}
				Individual *temp = t[j];
				string r = role[j];
				t[j] = t[flag];
				role[j] = role[flag];
				t[flag] = temp;
				role[flag] = r;
			}
			bool flag = false;
			string temp;
			for (int j = 1; j < t.size(); j++)
			{
				if (t[j] == t[j - 1])
				{
					if (!flag)
					{
						temp = "Individual " + t[j]->getid() + "(" + t[j]->getname() + ") plays multiple roles in Family " + fami[i]->getid() + ": " + role[j - 1] + ", " + role[j];
					}
					else
					{
						temp = temp + ", " + role[j];
					}
					flag = true;
				}
				else
				{
					if (flag)
					{
						errorMsg.push_back(temp);
					}
					flag = false;
				}
			}
			if (flag)
			{
				errorMsg.push_back(temp);
			}
		}
	}


	void deathBeforeGivingBirth()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				string wifeDeath = fami[i]->getwife()[j]->getdeat();
				if (wifeDeath == "") continue;
				for (int m = 0; m < fami[i]->getchild().size(); m++)
				{
					string childBirth = fami[i]->getchild()[m]->getbirt();
					if (childBirth == "") continue;
					if (!compareDate(wifeDeath, childBirth))
					{
						string temp = "In Family " + fami[i]->getid() + ", wife " + fami[i]->getwife()[j]->getid() + "(" + fami[i]->getwife()[j]->getname()
							+ ")'s death date(" + wifeDeath + ") is < her child " + fami[i]->getchild()[m]->getid() + "(" + fami[i]->getchild()[m]->getname() + ")'s birth date(" + childBirth + ")";
						errorMsg.push_back(temp);
					}
				}
			}
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				string husbDeath = fami[i]->gethusb()[j]->getdeat();
				if (husbDeath == "") continue;
				string hy, hm, hd;
				stringstream s(husbDeath);
				s >> hd >> hm >> hy;
				int mon = monthMap(hm);
				switch (mon)
				{
				case 1:
				{
					hm = "NOV";
					break;
				}
				case 2:
				{
					hm = "DEC";
					break;
				}
				case 3:
				{
					hm = "JAN";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 4:
				{
					hm = "FEB";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 5:
				{
					hm = "MAR";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 6:
				{
					hm = "APR";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 7:
				{
					hm = "MAY";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 8:
				{
					hm = "JUN";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 9:
				{
					hm = "JUL";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 10:
				{
					hm = "AUG";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 11:
				{
					hm = "SEP";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				case 12:
				{
					hm = "OCT";
					hy = to_string(atoi(hy.c_str()) + 1);
					break;
				}
				}
				string husbDeath2 = hd + " " + hm + " " + hy + " ";
				for (int m = 0; m < fami[i]->getchild().size(); m++)
				{
					string childBirth = fami[i]->getchild()[m]->getbirt();
					if (childBirth == "") continue;
					if (!compareDate(husbDeath2, childBirth))
					{
						string temp = "In Family " + fami[i]->getid() + ", husband " + fami[i]->gethusb()[j]->getid() + "(" + fami[i]->gethusb()[j]->getname()
							+ ")'s death date(" + husbDeath + ") + 10 months is < his child " + fami[i]->getchild()[m]->getid() + "(" + fami[i]->getchild()[m]->getname() + ")'s birth date(" + childBirth + ")";
						errorMsg.push_back(temp);
					}
				}
			}
		}
	}

	void polygamy()
	{
		for (int i = 0; i < indi.size(); i++)
		{
			vector<Family *> countF;
			vector<Individual *> countI;
			for (int j = 0; j < indi[i]->getfams().size(); j++)
			{
				if (indi[i]->getfams()[j]->getdiv() == "")
				{
					for (int m = 0; m < indi[i]->getfams()[j]->gethusb().size(); m++)
					{
						if (indi[i]->getfams()[j]->gethusb()[m] == indi[i])
						{
							for (int n = 0; n < indi[i]->getfams()[j]->getwife().size(); n++)
							{
								countF.push_back(indi[i]->getfams()[j]);
								countI.push_back(indi[i]->getfams()[j]->getwife()[n]);
							}
						}
					}
					for (int m = 0; m < indi[i]->getfams()[j]->getwife().size(); m++)
					{
						if (indi[i]->getfams()[j]->getwife()[m] == indi[i])
						{
							for (int n = 0; n < indi[i]->getfams()[j]->gethusb().size(); n++)
							{
								countF.push_back(indi[i]->getfams()[j]);
								countI.push_back(indi[i]->getfams()[j]->gethusb()[n]);
							}
						}
					}
				}
			}
			if (countF.size() > 1)
			{
				string temp = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") has more than one spouse currently: ";
				for (int j = 0; j < countF.size() - 1; j++)
				{
					temp = temp + countI[j]->getid() + "(" + countI[j]->getname() + ") in Family " + countF[j]->getid() + ", ";
				}
				temp = temp + countI[countF.size() - 1]->getid() + "(" + countI[countF.size() - 1]->getname() + ") in Family " + countF[countF.size() - 1]->getid() + ". ";
				errorMsg.push_back(temp);
			}
		}
	}

	void childInFamily()
	{
		for (int i = 0; i < indi.size(); i++)
		{
			if (indi[i]->getfamc().size() > 1)
			{
				string temp = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") is the child of multiple families: ";
				for (int j = 0; j < indi[i]->getfamc().size() - 1; j++)
				{
					temp += "Family " + indi[i]->getfamc()[j]->getid() + ", ";
				}
				temp += "Family " + indi[i]->getfamc()[indi[i]->getfamc().size() - 1]->getid() + ".";
				errorMsg.push_back(temp);
			}
		}
	}

	void uniqueInformation()
	{
		vector<string> name, sex, birthD, deathD, marrD, divD;
		string bdmd = "";
		string zero = "";
		string id = "";
		for (int i = 0; i < level.size(); i++)
		{
			if (level[i] == "0")
			{
				if (zero == "INDI")
				{
					if (name.size() > 1)
					{
						string temp = "Individual " + id + " has more than one name tag: ";
						for (int j = 0; j < name.size() - 1; j++)
						{
							temp += name[j] + ", ";
						}
						temp += name[name.size() - 1] + ". ";
						errorMsg.push_back(temp);
					}
					else if (name.size() == 0)
					{
						string temp = "Individual " + id + " does not have a name tag. ";
						errorMsg.push_back(temp);
					}
					if (sex.size() > 1)
					{
						string temp = "Individual " + id + " has more than one sex tag: ";
						for (int j = 0; j < sex.size() - 1; j++)
						{
							temp += sex[j] + ", ";
						}
						temp += sex[sex.size() - 1] + ". ";
						errorMsg.push_back(temp);
					}
					else if (sex.size() == 0)
					{
						string temp = "Individual " + id + " does not have a sex tag. ";
						errorMsg.push_back(temp);
					}
					if (birthD.size() > 1)
					{
						string temp = "Individual " + id + " has more than one birthday tag: ";
						for (int j = 0; j < birthD.size() - 1; j++)
						{
							temp += birthD[j] + ", ";
						}
						temp += birthD[birthD.size() - 1] + ". ";
						errorMsg.push_back(temp);
					}
					else if (birthD.size() == 0)
					{
						string temp = "Individual " + id + " does not have a birthday tag. ";
						errorMsg.push_back(temp);
					}
					if (deathD.size() > 1)
					{
						string temp = "Individual " + id + " has more than one death date tag: ";
						for (int j = 0; j < deathD.size() - 1; j++)
						{
							temp += deathD[j] + ", ";
						}
						temp += deathD[deathD.size() - 1] + ". ";
						errorMsg.push_back(temp);
					}
				}
				else if (zero == "FAM")
				{
					if (marrD.size() > 1)
					{
						string temp = "Family " + id + " has more than one marriage date tag: ";
						for (int j = 0; j < marrD.size() - 1; j++)
						{
							temp += marrD[j] + ", ";
						}
						temp += marrD[marrD.size() - 1] + ". ";
						errorMsg.push_back(temp);
					}
					else if (marrD.size() == 0)
					{
						string temp = "Family " + id + " does not have a marriage date tag. ";
						errorMsg.push_back(temp);
					}
					if (divD.size() > 1)
					{
						string temp = "Family " + id + " has more than one divorce date tag: ";
						for (int j = 0; j < divD.size() - 1; j++)
						{
							temp += divD[j] + ", ";
						}
						temp += divD[divD.size() - 1] + ". ";
						errorMsg.push_back(temp);
					}
				}
				if (tag[i] == "INDI" || tag[i] == "FAM")
				{
					zero = tag[i];
					id = argu[i].substr(1, argu[i].length() - 2);
				}
				else
				{
					zero = "";
					id = "";
				}
				name.resize(0);
				sex.resize(0);
				birthD.resize(0);
				deathD.resize(0);
				marrD.resize(0);
				divD.resize(0);
			}
			else
			{
				if (tag[i] == "BIRT" || tag[i] == "DEAT" || tag[i] == "MARR" || tag[i] == "DIV")
				{
					bdmd = tag[i];
				}
				else
				{
					if (tag[i] == "NAME")
						name.push_back(argu[i]);
					else if (tag[i] == "SEX")
						sex.push_back(argu[i]);
					else if (tag[i] == "DATE")
					{
						if (bdmd == "BIRT")
							birthD.push_back(argu[i]);
						else if (bdmd == "DEAT")
							deathD.push_back(argu[i]);
						else if (bdmd == "MARR")
							marrD.push_back(argu[i]);
						else if (bdmd == "DIV")
							divD.push_back(argu[i]);
					}
					bdmd = "";
				}
			}
		}
		if (zero == "INDI")
		{
			if (name.size() > 1)
			{
				string temp = "Individual " + id + " has more than one name tag: ";
				for (int j = 0; j < name.size() - 1; j++)
				{
					temp += name[j] + ", ";
				}
				temp += name[name.size() - 1] + ". ";
				errorMsg.push_back(temp);
			}
			else if (name.size() == 0)
			{
				string temp = "Individual " + id + " does not have a name tag. ";
				errorMsg.push_back(temp);
			}
			if (sex.size() > 1)
			{
				string temp = "Individual " + id + " has more than one sex tag: ";
				for (int j = 0; j < sex.size() - 1; j++)
				{
					temp += sex[j] + ", ";
				}
				temp += sex[sex.size() - 1] + ". ";
				errorMsg.push_back(temp);
			}
			else if (sex.size() == 0)
			{
				string temp = "Individual " + id + " does not have a sex tag. ";
				errorMsg.push_back(temp);
			}
			if (birthD.size() > 1)
			{
				string temp = "Individual " + id + " has more than one birthday tag: ";
				for (int j = 0; j < birthD.size() - 1; j++)
				{
					temp += birthD[j] + ", ";
				}
				temp += birthD[birthD.size() - 1] + ". ";
				errorMsg.push_back(temp);
			}
			else if (birthD.size() == 0)
			{
				string temp = "Individual " + id + " does not have a birthday tag. ";
				errorMsg.push_back(temp);
			}
			if (deathD.size() > 1)
			{
				string temp = "Individual " + id + " has more than one death date tag: ";
				for (int j = 0; j < deathD.size() - 1; j++)
				{
					temp += deathD[j] + ", ";
				}
				temp += deathD[deathD.size() - 1] + ". ";
				errorMsg.push_back(temp);
			}
		}
		else if (zero == "FAM")
		{
			if (marrD.size() > 1)
			{
				string temp = "Family " + id + " has more than one marriage date tag: ";
				for (int j = 0; j < marrD.size() - 1; j++)
				{
					temp += marrD[j] + ", ";
				}
				temp += marrD[marrD.size() - 1] + ". ";
				errorMsg.push_back(temp);
			}
			else if (marrD.size() == 0)
			{
				string temp = "Family " + id + " does not have a marriage date tag. ";
				errorMsg.push_back(temp);
			}
			if (divD.size() > 1)
			{
				string temp = "Family " + id + " has more than one divorce date tag: ";
				for (int j = 0; j < divD.size() - 1; j++)
				{
					temp += divD[j] + ", ";
				}
				temp += divD[divD.size() - 1] + ". ";
				errorMsg.push_back(temp);
			}
		}
	}

	void lastNameRule()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				string husbName = fami[i]->gethusb()[j]->getname();
				int posS = husbName.find_first_of("/");
				int posL = husbName.find_last_of("/");
				string husbLastName = "";
				if (posS != string::npos) husbLastName = husbName.substr(posS, posL);
				for (int k = 0; k < fami[i]->getchild().size(); k++)
				{
					string childName = fami[i]->getchild()[k]->getname();
					posS = childName.find_first_of("/");
					posL = childName.find_last_of("/");
					string childLastName;
					if (posS != string::npos) childLastName = childName.substr(posS, posL);
					if (husbLastName != childLastName)
					{
						string temp = "In Family " + fami[i]->getid() + ", husband " + fami[i]->gethusb()[j]->getid() + "("
							+ fami[i]->gethusb()[j]->getname() + ") and child " + fami[i]->getchild()[k]->getid() + "("
							+ fami[i]->getchild()[k]->getname() + ") don't have the same last name.";
						errorMsg.push_back(temp);
					}
				}
			}
		}
	}

	void multipleBirthsRule()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			vector<vector <Individual *> > multiBirth;
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				string birt = fami[i]->getchild()[j]->getbirt();
				if (birt == "") continue;
				for (int k = 0; k < multiBirth.size() + 1; k++)
				{
					if (k == multiBirth.size())
					{
						vector<Individual *> child;
						child.push_back(fami[i]->getchild()[j]);
						multiBirth.push_back(child);
						break;
					}
					else
					{
						if (birt == multiBirth[k][0]->getbirt())
						{
							multiBirth[k].push_back(fami[i]->getchild()[j]);
							break;
						}
					}
				}
			}
			for (int j = 0; j < multiBirth.size(); j++)
			{
				if (multiBirth[j].size() > 4)
				{
					string temp = "In Family " + fami[i]->getid() + ", there are more than 4 children born on the same day: ";
					for (int k = 0; k < multiBirth[j].size() - 1; k++)
					{
						temp += multiBirth[j][k]->getid() + "(" + multiBirth[j][k]->getname() + "), ";
					}
					temp += "and " + multiBirth[j][multiBirth[j].size() - 1]->getid() 
						+ "(" + multiBirth[j][multiBirth[j].size() - 1]->getname() + "). ";
					errorMsg.push_back(temp);
				}
			}
		}
	}

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
				temp = temp + fami[i]->gethusb()[husb - 1]->getid() + "(" + fami[i]->gethusb()[husb - 1]->getname() + ").";
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
	void invalidGender()
	{
		string ERRMSG;
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				if (fami[i]->gethusb()[j]->getsex() != 'M')
				{
					ERRMSG = "Famil " + fami[i]->getid() + "'s husdband " + fami[i]->gethusb()[j]->getid()
						+ "(" + fami[i]->gethusb()[j]->getname() + ")" + " is not MALE.";
					errorMsg.push_back(ERRMSG);
				}

			}
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				if (fami[i]->getwife()[j]->getsex() != 'F')
				{
					ERRMSG = "Famil " + fami[i]->getid() + "'s wife " + fami[i]->getwife()[j]->getid()
						+ "(" + fami[i]->getwife()[j]->getname() + ")" + " is not FEMALE.";
					errorMsg.push_back(ERRMSG);
				}
			}
		}
	}

	void marrigeBeforeBirth()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			string marr = fami[i]->getmarr();
			if (marr == "") continue;
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				string bir = fami[i]->getwife()[j]->getbirt();
				if (bir == "") continue;
				if (compareDate(bir, marr))
				{
					string temp = "Individual ";
					temp = temp + fami[i]->getwife()[j]->getid() + "(" + fami[i]->getwife()[j]->getname() + ")'s marrige(" + fami[i]->getmarr() + ") before birth(" + fami[i]->getwife()[j]->getbirt() + ").";
					errorMsg.push_back(temp);
				}
			}
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				string bir = fami[i]->gethusb()[j]->getbirt();
				if (bir == "") continue;
				if (compareDate(bir, marr))
				{
					string temp = "Individual ";
					temp = temp + fami[i]->gethusb()[j]->getid() + "(" + fami[i]->gethusb()[j]->getname() + ")'s marrige(" + fami[i]->getmarr() + ") before birth(" + fami[i]->gethusb()[j]->getbirt() + ").";
					errorMsg.push_back(temp);
				}
			}
		}
	}

	void divorceBeforeMarrige()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			string marr = fami[i]->getmarr();
			string div = fami[i]->getdiv();
			if (marr == "" || div == "") continue;
			if (compareDate(marr, div))
			{
				string temp = "Family ";
				temp = temp + fami[i]->getid() + "'s divorce date(" + fami[i]->getdiv() + ") before marrige date(" + fami[i]->getmarr() + ").";
				errorMsg.push_back(temp);
			}
		}
	}

	void amountOfFamilyMembers()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			int amount = fami[i]->getchild().size() + fami[i]->getwife().size() + fami[i]->gethusb().size();
			if (amount > 8)
			{
				string err = "Family " + fami[i]->getid() + " has more than 8 members (" + to_string(amount) + ").";
				errorMsg.push_back(err);
			}
		}
	}

	void ageGap()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			vector<Individual *> children;
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				string birth = fami[i]->getchild()[j]->getbirt();
				string birthBefore, birthAfter;
				string by, bm, bd;
				stringstream ss(birth);
				ss >> bd >> bm >> by;
				by = to_string(atoi(by.c_str()) - 1);
				birthBefore = bd + " " + bm + " " + by;
				by = to_string(atoi(by.c_str()) + 2);
				birthAfter = bd + " " + bm + " " + by;
				for (int m = 0; m < children.size(); m++)
				{
					if (birth != children[m]->getbirt() && compareDate(children[m]->getbirt(), birthBefore) && compareDate(birth, children[m]->getbirt()))
					{
						string err = "In Family " + fami[i]->getid() + ", child " + fami[i]->getchild()[j]->getid() + "(" + fami[i]->getchild()[j]->getname() + ") and child "
							+ children[m]->getid() + "(" + children[m]->getname() + ") are not multiple births but born within one year.";
						errorMsg.push_back(err);
					}
					if (birth != children[m]->getbirt() && compareDate(children[m]->getbirt(), birth) && compareDate(birthAfter, children[m]->getbirt()))
					{
						string err = "In Family " + fami[i]->getid() + ", child " + fami[i]->getchild()[j]->getid() + "(" + fami[i]->getchild()[j]->getname() + ") and child "
							+ children[m]->getid() + "(" + children[m]->getname() + ") are not multiple births but born within one year.";
						errorMsg.push_back(err);
					}
				}
				children.push_back(fami[i]->getchild()[j]);
			}
		}
	}
	void pregnancyLimit()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				//fami[i]->getwife()[j]->get
				if (fami[i]->getwife()[j]->getbirt() == "") continue;
				string wd, wm, wy;
				stringstream s(fami[i]->getwife()[j]->getbirt());
				s >> wd >> wm >> wy;
				int wbirt = atoi(wy.c_str());
				for (int k = 0; k < fami[i]->getchild().size(); k++)
				{
					if (fami[i]->getchild()[k]->getbirt() == "") continue;
					string cd, cm, cy;
					stringstream ss(fami[i]->getchild()[k]->getbirt());
					ss >> cd >> cm >> cy;
					int cbirt = atoi(cy.c_str());
					if (cbirt - wbirt>50 || cbirt - wbirt < 18)
					{
						string temp = "In Family " + fami[i]->getid() + ", wife " + fami[i]->getwife()[j]->getid() +
							"(" + fami[i]->getwife()[j]->getname() + ") gave birth to child " + fami[i]->getchild()[k]->getid() +
							"(" + fami[i]->getchild()[k]->getname() + ") when she was " + to_string(cbirt - wbirt) + "(not between 18 and 50)";
						errorMsg.push_back(temp);
					}
				}
			}
		}
	}

	void divorceBeforeGivingBirth()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			string div = fami[i]->getdiv();
			if (div == "") continue;
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				string bir = fami[i]->getchild()[j]->getbirt();
				if (bir == "") continue;
				if (compareDate(bir, div))
				{
					string temp = "Family ";
					temp = temp + fami[i]->getid() + " divorce Date is(" + fami[i]->getdiv() + ") and child's birth Date is (" +fami[i]->getchild()[j]->getbirt() + ").";
					errorMsg.push_back(temp);
				}
			}
		}
	}
	void birthDateLimit()
	{
		for (int i = 0; i < indi.size(); i++)
		{
			string bir = indi[i]->getbirt();
			if (bir == "") continue;
			stringstream s(bir);
			string birtD, birtM, birtY;
			s >> birtD >> birtM >> birtY;
			if (atoi(birtY.c_str()) < 1900)
			{
				string err = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") is an ancient people born before 1900.";
				errorMsg.push_back(err);
			}
		}
	}
	void mayDecMarr()
	{
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				string bir = fami[i]->gethusb()[j]->getbirt();
				if (bir == "") continue;
				stringstream s(bir);
				string birtD, birtM, birtY;
				s >> birtD >> birtM >> birtY;
				int husbY = atoi(birtY.c_str());
				for (int m = 0; m < fami[i]->getwife().size(); m++)
				{
					bir = fami[i]->getwife()[m]->getbirt();
					if (bir == "") continue;
					stringstream ss(bir);
					ss >> birtD >> birtM >> birtY;
					int wifeY = atoi(birtY.c_str());
					if (husbY - wifeY>30 || wifeY - husbY > 30)
					{
						string err = "In family " + fami[i]->getid() + ", husband " + fami[i]->gethusb()[j]->getid() + "("
							+ fami[i]->gethusb()[j]->getname() + ") and wife " + fami[i]->getwife()[m]->getid() + "("
							+ fami[i]->getwife()[m]->getname() + ") has a age gap greater than 30 years.";
						errorMsg.push_back(err);
					}
				}
			}
		}
	}
	void invalidDate()//Yanjun Wu
	{
		string ERRMSG = "";
		bool isBirtLeap, isDeatLeap, invBirtD, invDeatD, isDead;
		for (int i = 0; i < indi.size(); i++)
		{
			//cout << indi[i]->getbirt() << " " << indi[i]->getdeat() << endl;
			if (indi[i]->getbirt() == "") continue;
			if (indi[i]->getdeat() == "")
				isDead = false;
			else
				isDead = true;
			//			isBirtLeap = leapYear(indi[i]->getbirt());
			//			isDeatLeap = leapYear(indi[i]->getdeat());
			invBirtD = inexistDate(indi[i]->getbirt());
			if (isDead)
				invDeatD = inexistDate(indi[i]->getdeat());
			//US03
			//if (cy < by || (cy == by && cm < bm) || (cy == by && cm == bm && cd < bd)) //invalid birth date
			if (compareDate(cy, cm, cd, indi[i]->getbirt()) == false)
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
				if (compareDate(cy, cm, cd, indi[i]->getdeat()) == false)
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
				if (compareDate(indi[i]->getdeat(), indi[i]->getbirt()) == false)
				{
					ERRMSG = "Individual " + indi[i]->getid() + "(" + indi[i]->getname() + ") death before birth. " + "Birth: " + indi[i]->getbirt() + " Death: " + indi[i]->getdeat();
					errorMsg.push_back(ERRMSG);
				}
			}
		}
		for (int i = 0; i < fami.size(); i++)
		{
			bool isDiv, isMarrLeap, isDivLeap, invMarrD, invDivD;
			if (fami[i]->getmarr() == "") continue;
			if (fami[i]->getdiv() == "")
				isDiv = false;
			else
				isDiv = true;
			//			isMarrLeap = leapYear(fami[i]->getmarr());
			//			isDivLeap = leapYear(fami[i]->getdiv());
			invMarrD = inexistDate(fami[i]->getmarr());
			if (isDiv)
				invDivD = inexistDate(fami[i]->getdiv());
			//US03
			if (compareDate(cy, cm, cd, fami[i]->getmarr()) == false) //invalid marriage date
			{
				ERRMSG = "Family " + fami[i]->getid() + " has an invalid marriage date("
					+ fami[i]->getmarr() + ")." + " Marriage date before current date.";
				errorMsg.push_back(ERRMSG);
			}
			if (invMarrD == false)
			{
				ERRMSG = "Family " + fami[i]->getid() + " has an invalid marriage date("
					+ fami[i]->getmarr() + ")." + " Marriage date doesn't exist.";
				errorMsg.push_back(ERRMSG);
			}
			if (isDiv == true)
			{
				if (compareDate(cy, cm, cd, fami[i]->getdiv()) == false) //invalid divorce date
				{
					ERRMSG = "Family " + fami[i]->getid() + " has an invalid divorce date("
						+ fami[i]->getdiv() + ")." + " Divorce date before current date.";
					errorMsg.push_back(ERRMSG);
				}
				if (invDivD == false)
				{
					ERRMSG = "Family " + fami[i]->getid() + " has an invalid divorce date("
						+ fami[i]->getdiv() + ")." + " Divorce date doesn't exist.";
					errorMsg.push_back(ERRMSG);
				}
			}
		}
	}
	void elderAgeRule()
	{
		string ERRMSG = "";
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				for (int k = 0; k < fami[i]->getchild().size(); k++)
				{
					if (compareDate(fami[i]->gethusb()[j]->getbirt(), fami[i]->getchild()[k]->getbirt()))
					{
						ERRMSG = "Husband " + fami[i]->gethusb()[j]->getid() + "(" + fami[i]->gethusb()[j]->getname() + ") of family " + fami[i]->getid()
							+ "(" + fami[i]->gethusb()[j]->getbirt() + ")" + " is not older than the child " + fami[i]->getchild()[k]->getid() + "(" + fami[i]->getchild()[k]->getname() + ")"
							+ "(" + fami[i]->getchild()[k]->getbirt() + ")";
						errorMsg.push_back(ERRMSG);
					}
				}
			}
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				for (int k = 0; k < fami[i]->getchild().size(); k++)
				{
					if (compareDate(fami[i]->getwife()[j]->getbirt(), fami[i]->getchild()[k]->getbirt()))
					{
						ERRMSG = "Wife " + fami[i]->getwife()[j]->getid() + "(" + fami[i]->getwife()[j]->getname() + ") of family " + fami[i]->getid()
							+ "(" + fami[i]->getwife()[j]->getbirt() + ")" + " is not older than the child " + fami[i]->getchild()[k]->getid() + "(" + fami[i]->getchild()[k]->getname() + ")"
							+ "(" + fami[i]->getchild()[k]->getbirt() + ")";
						errorMsg.push_back(ERRMSG);
					}
				}
			}
		}
	}
	void deathBeforeMarr()
	{
		string ERRMSG = "";
		for (int i = 0; i < fami.size(); i++)
		{
			if (fami[i]->getmarr() != "")
			{
				for (int j = 0; j < fami[i]->gethusb().size(); j++)
				{
					if (fami[i]->gethusb()[j]->getdeat() != "")
					{
						if (compareDate(fami[i]->getmarr(), fami[i]->gethusb()[j]->getdeat()))
						{
							ERRMSG = "Family " + fami[i]->getid() + ", husband " + fami[i]->gethusb()[j]->getid()
								+ "(" + fami[i]->gethusb()[j]->getname() + ") death (" + fami[i]->gethusb()[j]->getdeat()
								+ ") before marriage (" + fami[i]->getmarr() + ")";
							errorMsg.push_back(ERRMSG);
						}
					}
				}
				for (int j = 0; j < fami[i]->getwife().size(); j++)
				{
					if (fami[i]->getwife()[j]->getdeat() != "")
					{
						if (compareDate(fami[i]->getmarr(), fami[i]->getwife()[j]->getdeat()))
						{
							ERRMSG = "Family " + fami[i]->getid() + ", wife " + fami[i]->getwife()[j]->getid()
								+ "(" + fami[i]->getwife()[j]->getname() + ") death (" + fami[i]->getwife()[j]->getdeat()
								+ ") before marriage (" + fami[i]->getmarr() + ")";
							errorMsg.push_back(ERRMSG);
						}
					}
				}
			}
		}
	}
	void illegalSpouse()
	{
		string ERRMSG = "";
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->getchild().size(); j++)
				for (int k = j + 1; k < fami[i]->getchild().size(); k++)
					for (int m = 0; m < fami[i]->getchild()[j]->getfams().size(); m++)
						for (int n = 0; n < fami[i]->getchild()[k]->getfams().size(); n++)
						{
							if (fami[i]->getchild()[j]->getfams()[m]->getid() == fami[i]->getchild()[k]->getfams()[n]->getid())
							{
								ERRMSG = "Individual " + fami[i]->getchild()[j]->getid() + "(" + fami[i]->getchild()[j]->getname()
									+ ") and Individual " + fami[i]->getchild()[k]->getid() + "(" + fami[i]->getchild()[k]->getname() + ") are siblings in family " + fami[i]->getid()
									+ " but they get married in family " + fami[i]->getchild()[j]->getfams()[m]->getid();
								errorMsg.push_back(ERRMSG);
							}
						}
		}
	}

	void illegalMarriageAge()
	{
		string ERRMSG = "";
		for (int i = 0; i < fami.size(); i++)
		{
			if (fami[i]->getmarr() == "") continue;
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				if (calcAge(fami[i]->gethusb()[j]->getbirt(), fami[i]->getmarr()) < 20)
				{
					ERRMSG = "Individual " + fami[i]->gethusb()[j]->getid() + "(" + fami[i]->gethusb()[j]->getname() + ")'s birthday is "
						+ fami[i]->gethusb()[j]->getbirt() + " and he got married when he was uder 20. Marriage date is " + fami[i]->getmarr() + ".";
					errorMsg.push_back(ERRMSG);
				}
			}
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				if (calcAge(fami[i]->getwife()[j]->getbirt(), fami[i]->getmarr()) < 18)
				{
					ERRMSG = "Individual " + fami[i]->getwife()[j]->getid() + "(" + fami[i]->getwife()[j]->getname() + ")'s birthday is "
						+ fami[i]->getwife()[j]->getbirt() + " and she got married when she was uder 18. Marriage date is " + fami[i]->getmarr() + ".";
					errorMsg.push_back(ERRMSG);
				}
			}
		}
	}

	void familyRule()
	{
		string ERRMSG = "";
		for (int i = 0; i < indi.size(); i++)
		{
			if (indi[i]->getfamc().size() == 0 && indi[i]->getfams().size() == 0)
			{
				ERRMSG = "Individual " + indi[i]->getid() + " (" + indi[i]->getname() + ") " + "doesn't belong to any family.";
				errorMsg.push_back(ERRMSG);
			}
		}
	}

	void completeInfo()
	{
		string ERRMSG = "";
		for (int i = 0; i < indi.size(); i++)
		{
			if (indi[i]->getname() == "")
			{
				ERRMSG = "Individual " + indi[i]->getid() + " doesn't complete information(missing name).";
				errorMsg.push_back(ERRMSG);
			}
			else if (indi[i]->getsex() == NULL )
			{
				ERRMSG = "Individual " + indi[i]->getid() + " (" + indi[i]->getname() + ") " + " doesn't complete information(missing gender).";
				errorMsg.push_back(ERRMSG);
			}
			else if (indi[i]->getbirt() == "")
			{
				ERRMSG = "individual " + indi[i]->getid() + " (" + indi[i]->getname() + ") " + " doesn't complete information(missing birth date).";
				errorMsg.push_back(ERRMSG);
			}
		}
		for (int i = 0; i < fami.size(); i++)
		{
			if (fami[i]->getmarr() == "")
			{
				ERRMSG = "Family " + fami[i]->getid() + " doesn't complete information(missing marriage date).";
				errorMsg.push_back(ERRMSG);
			}
		}
	}

	void giveBirBeforeMarr()
	{
		string ERRMSG = "";
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				if (compareDate(fami[i]->getchild()[j]->getbirt(),fami[i]->getmarr()) == false)
				{
					ERRMSG = "Child " + fami[i]->getchild()[j]->getid() + " (" + fami[i]->getchild()[j]->getname() + ") " + " of family " + fami[i]->getid() 
						+ " was born ( " + fami[i]->getchild()[j]->getbirt() + ") " + " before before parents' marriage." + "(" + fami[i]->getmarr() + ")";
					errorMsg.push_back(ERRMSG);
				}
			}
		}
	}

	void marrRule()
	{
		string ERRMSG = "";
		for (int i = 0; i < fami.size(); i++)
		{
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				for (int k = 0; k < fami[i]->getchild()[j]->getfams().size(); k++)
				{
					if (fami[i]->getchild()[j]->getfams()[k]->getmarr() == "")
						continue;
					if (compareDate(fami[i]->getchild()[j]->getfams()[k]->getmarr(), fami[i]->getmarr()) == false)
					{
						ERRMSG = "Child " + fami[i]->getchild()[j]->getid() + " (" + fami[i]->getchild()[j]->getname() + ") " + " of family " + fami[i]->getid() + " was married ("
							+ fami[i]->getchild()[j]->getfams()[k]->getmarr() + ") " + " before before parents' marriage." + "(" + fami[i]->getmarr() + ")";
						errorMsg.push_back(ERRMSG);
					}
				}
			}
		}
	}

	int calcAge(string birt, string marr)
	{
		int year, month, day, myear, mmonth, mday;
		string y, m, d, my, mm, md;
		stringstream ss;
		stringstream s;
		ss << birt;
		s << marr;
		ss >> d;
		ss >> m;
		ss >> y;
		s >> md;
		s >> mm;
		s >> my;
		day = atoi(d.c_str());
		month = monthMap(m);
		year = atoi(y.c_str());
		mday = atoi(md.c_str());
		mmonth = monthMap(mm);
		myear = atoi(my.c_str());
		if (mmonth < month || (mmonth < month && mday < day))
			return myear - year;
		else
			return myear - year - 1;
	}
	int monthMap(string month)
	{
		if (month == "JAN") return 1;
		else if (month == "FEB") return 2;
		else if (month == "MAR") return 3;
		else if (month == "APR") return 4;
		else if (month == "MAY") return 5;
		else if (month == "JUN") return 6;
		else if (month == "JUL") return 7;
		else if (month == "AUG") return 8;
		else if (month == "SEP") return 9;
		else if (month == "OCT") return 10;
		else if (month == "NOV") return 11;
		else if (month == "DEC") return 12;
	}
	bool leapYear(string date)
	{
		stringstream ss;
		int year;
		string var1, var2, var3;
		ss << date;
		ss >> var1;
		ss >> var2;
		ss >> var3;
		year = atoi(var3.c_str());
		if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
			return true;
		else
			return false;
	}
	bool inexistDate(string date)
	{
		int mon[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
		stringstream ss;
		int year, month, day;
		string var1, var2, var3;
		ss << date;
		ss >> var1;
		ss >> var2;
		ss >> var3;
		year = atoi(var3.c_str());
		month = monthMap(var2);
		day = atoi(var1.c_str());
		//cout << day << " " << month << " " << year << endl;
		if (leapYear(date))
			mon[1] = 29;
		if (day > 0 && day <= mon[month - 1])
			return true;
		else
			return false;
	}
	bool compareDate(int cy, int cm, int cd, string dateArgu)
	{
		int year, month, day;
		string y, m, d;
		stringstream ss;
		ss << dateArgu;
		ss >> d;
		ss >> m;
		ss >> y;
		day = atoi(d.c_str());
		month = monthMap(m);
		year = atoi(y.c_str());
		if (cy < year || (cy == year && cm < month) || (cy == year && cm == month && cd < day))
			return false;
		else
			true;
	}
	bool compareDate(string firDate, string secDate)  // first < second return false, else return true
	{
		int firYear, firMonth, firDay, secYear, secMonth, secDay;
		string fy, fm, fd, sy, sm, sd;
		stringstream fs, ss;
		fs << firDate;
		ss << secDate;
		fs >> fd;
		fs >> fm;
		fs >> fy;
		ss >> sd;
		ss >> sm;
		ss >> sy;
		firYear = atoi(fy.c_str());
		firMonth = monthMap(fm);
		firDay = atoi(fd.c_str());
		secYear = atoi(sy.c_str());
		secMonth = monthMap(sm);
		secDay = atoi(sd.c_str());
		if (firYear < secYear || (firYear == secYear && firMonth < secMonth) || (firYear == secYear && firMonth == secMonth && firDay < secDay))
			return false;
		else
			true;
	}

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
		errorMsg.push_back("\n========================Sprint 1========================\n");
		inexistID();
		unmatchedPointers();
		invalidDate(); // US03 & US05
		invalidFamilyMember();
		invalidGender();
		errorMsg.push_back("\n========================Sprint 2========================\n");
		invalidAge();
		multipleRoles();
		elderAgeRule();
		deathBeforeMarr();
		marrigeBeforeBirth();
		divorceBeforeMarrige();
		errorMsg.push_back("\n========================Sprint 3========================\n");
		deathBeforeGivingBirth();
		polygamy();
		illegalSpouse();
		illegalMarriageAge();
		amountOfFamilyMembers();
		ageGap();
		errorMsg.push_back("\n========================Sprint 4========================\n");
		childInFamily();
		uniqueInformation();
		pregnancyLimit();
		divorceBeforeGivingBirth();
		familyRule();
		completeInfo();
		errorMsg.push_back("\n========================Sprint 5========================\n");
		lastNameRule();
		multipleBirthsRule();
		birthDateLimit();
		mayDecMarr();
		giveBirBeforeMarr();
		marrRule();
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
				while (i < level.size() && level[i] != "0" && i < level.size())
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
				while (i < level.size() && level[i] != "0" && i < level.size())
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
		for (int i = 0; i < fami.size(); i++)
		{
			fout << "ID : " << fami[i]->getid();
			for (int j = 0; j < fami[i]->gethusb().size(); j++)
			{
				if (j == 0)
					fout << ", HUSBAND : " << fami[i]->gethusb()[j]->getname();
				else
					fout << ", " << fami[i]->gethusb()[j]->getname();
			}
			for (int j = 0; j < fami[i]->getwife().size(); j++)
			{
				if (j == 0)
					fout << ", WIFE : " << fami[i]->getwife()[j]->getname();
				else
					fout << ", " << fami[i]->getwife()[j]->getname();
			}
			for (int j = 0; j < fami[i]->getchild().size(); j++)
			{
				if (j == 0)
					fout << ", CHILDREN : " << fami[i]->getchild()[j]->getname();
				else
					fout << ", " << fami[i]->getchild()[j]->getname();
			}
			fout << endl;
		}
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