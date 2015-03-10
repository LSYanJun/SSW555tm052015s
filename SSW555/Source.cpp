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

	void invalidAge() // Gong Cheng
	{
		for (int i = 0; i < indi.size(); i++)
		{
			if (indi[i]->getbirt() == "") continue;
			int birt = atoi(indi[i]->getbirt().substr(indi[i]->getbirt().length() - 4).c_str());
			int deat = cy;
			if (indi[i]->getdeat()!="")
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
			if (compareDate(cy,cm,cd,indi[i]->getbirt()) == false)
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
				if (compareDate(cy,cm,cd,indi[i]->getdeat()) == false)
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
				if (compareDate(indi[i]->getdeat(),indi[i]->getbirt()) == false)
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
			if (compareDate(cy,cm,cd,fami[i]->getmarr()) == false) //invalid marriage date
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
							+"(" +fami[i]->getchild()[k]->getbirt() + ")";
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
	bool compareDate(string firDate, string secDate)
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
		inexistID();
		unmatchedPointers();
		invalidDate();
		invalidFamilyMember();
		invalidGender();
		invalidAge();
		multipleRoles();
		elderAgeRule();
		deathBeforeMarr();
		marrigeBeforeBirth();
		divorceBeforeMarrige();
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