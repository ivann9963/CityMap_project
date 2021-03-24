#include "System.h"
#include "Edge.h"
using namespace std;

System::System(istream& in, ostream& out) : Base(in, out) {}

void System::processInput(const vector<string>& arg)
{
	if (arg[0] == "hasWay") BFS(arg);			// 1. Проверка, дали има път между две зададени кръстовища.
	if (arg[0] == "iscycled") toDFS(arg); //DFS	// 4. Проверка, дали при дадено кръстовище за начална точка е възможно да обиколим част от града и върнем обратно там, откъдето сме тръгнали.
	if (arg[0] == "reachAll") reachAllCrossways(arg); //~BFS// 6. Проверка, дали е възможно да стигнем от дадено кръстовище до всички останали.
	if (arg[0] == "istour") isTour(arg);		// 5. Проверява, дали има ойлеров цикъл(проверявайки четност на всеки връх);с дфс(от метода Euler) връща самия път с цикъл
	if (arg[0] == "deadEnds") blindAlleys(arg); // 7. Задънени улици
	if (arg[0] == "open") openFromFile(arg);
	if (arg[0] == "print") printAllCrossways(arg);
}

void System::openFromFile(const vector<string>& vsplitLine)
{
	// open 1.txt
	ifstream inputFile(vsplitLine[1]);
	if (!inputFile.is_open())
	{
		cout << "An error occured while accessing the file!" << endl;
	}
	mCrossways = fromStream(inputFile)->mCrossways;
}

void System::printAllCrossways(const vector<string>& vsplitLine)
{
	//friend ostream& operator<<(ostream &os, const Crossway& arg);
	cout << "Crossways: \n";
	for (auto it : mCrossways)
	{
		cout << it.second << endl;
	}
}

System* System::fromStream(istream& in)
{
	System* citymap = new System(in, cout);

	try
	{
		string Line;
		vector<string> vsplitLine;

		//четем ред по ред по ред от файл
		while (getline(in, Line))
		{
			vsplitLine = splitLine(Line);

			// така добавяме само първото кръстовище, тоест ако имаме А Б 120 В 130
			// ще сме добавили в нашия мап само кръстовището А
			citymap->mCrossways.insert({ vsplitLine[0], Crossway(vsplitLine[0]) });//citymap->mCrossways.insert(pair<string, Crossway>(vsplitLine[0], Crossway(vsplitLine[0])));

			// добавяме на дадено кръстовище всички свързани с него
			for (unsigned int i = 1; i < vsplitLine.size(); i += 2)
			{
				citymap->mCrossways[vsplitLine[0]].addCrossways(vsplitLine[i], stoi(vsplitLine[i + 1]));
				citymap->mCrossways.insert({ vsplitLine[i], Crossway(vsplitLine[i]) });//citymap->mCrossways.insert(pair<string, Crossway>(vsplitLine[i], Crossway(vsplitLine[i])));
				// Edge(string fromV, string toV, int nomE);
			}
		}
		return citymap;
	}
	catch (...)
	{
		delete citymap;
		throw;
	}
}


void dfs(map<string, vector<Edge>>& vE, string beg, stack<string> & tmp, vector<bool>& used)
{
	tmp.push(beg);
	for (auto it : vE[beg])
	{
		if (!used[it.getNom()])
		{
			used[it.getNom()] = true;

			dfs(vE, it.getTo(), tmp, used);
			break;
		}
	}
	
}
/*
void dfs(vector<vector<Edge>>& vE, int beg, stack<int>& tmp, vector<bool> &used, stack<string>& from)
{
	tmp.push(beg);
	//cout << vE[beg][0].getFrom() << "(dfs) ";
	//from.push(vE[beg][0].getFrom());
	for (size_t i = 0; i < vE[beg].size(); i++)
	{
		Edge edge = vE[beg][i];
		if (!used[edge.getNom()])
		{
			used[edge.getNom()] = true;

			//tmp.push(vE[beg][i].getEndV());			
			dfs(vE, vE[beg][i].getEndV(), tmp, used, from);
			break;
		}
	}
}*/
void Euler(map<string, vector<Edge>>& vE, string beg)
{
	int countE = 0;
	vector<bool> used;
	for (auto it : vE)
		countE += it.second.size();
	used.resize(countE, 0);
	stack<string> tmp;
	stack<string> way;
	dfs(vE, beg, tmp, used);
	while ((!tmp.empty()))
	{
		string top = tmp.top();
		bool visitNow = false;
		for (auto it : vE[top])
		{
			if (used[it.getNom()])
				continue;					
			visitNow = true;
			used[it.getNom()] = true;
			dfs(vE, it.getTo(), tmp, used);
			break;
		}
		if (!visitNow)
		{
			way.push(top);
			tmp.pop();
		}
	}
	cout << "WAY: ";
	while (!way.empty())
	{
		cout << way.top() << " ";
		way.pop();
	}
}
/*
void Euler(vector<vector<Edge>>& vE, int beg)
{
	//cout << "EULER from " << beg << endl;
	vector<bool> used;
	used.resize(vE.size() * 2, 0);
	stack<int> tmp;
	stack<int> way;
	stack<string> from;
	dfs(vE, beg, tmp, used, from);
	while (!tmp.empty())
	{
		int topV = tmp.top();                           /// само поглежда върха, без да го изтрива от tmp!!!!

		bool visitNow = false;
		for (size_t i = 0; i < vE[topV].size(); i++)   /// търси непосетени ребра, свързани с поредния връх
		{
			if (used[vE[topV][i].getNom()]) continue;

			Edge edge = vE[topV][i];

			visitNow = true;
			used[edge.getNom()] = true;
			//cout << edge.getFrom() << "->" << edge.getTo() << endl;
			dfs(vE, edge.getEndV(), tmp, used, from);    //dfs(edge.getTo());
			break;                                      /// работи и без този break
		}
		if (!visitNow)                                /// ако topV не е посетен при този ход, го премества от tmp в way
		{
			way.push(topV);
			from.push(vE[topV][0].getFrom());
			tmp.pop();
		}
	}

	cout << "WAY: ";
	while (!from.empty())                                 /// извежда Ойлеровия път
	{
		cout << from.top() << " ";
		from.pop();
	}
	cout << endl;
}
*/

bool System::isTour(const vector<string>& vsplitLine)
{
	try {
		map<string, vector<Edge> > vE;       /// вектор с ребрата
		map<string, int> InOut;
		int nom = 0;
		int j;
		for (auto it : mCrossways)
		{
			j = 0;
			for (auto p : it.second.getLinkedCrossways() )
			{
				vE[it.first].push_back(Edge(it.first, p.first, nom));
				if(!vE[it.first].empty())
					cout << "("<< it.first << "->" << p.first << "_" << nom << ") ";
				nom++;
			}
			cout << endl;
		}
		for (auto it : mCrossways)
		{
			InOut[it.first] = it.second.getLinkedCrossways().size();
		}

		for (auto it : mCrossways)
		{
			for (auto p : it.second.getLinkedCrossways())
			{
				InOut[p.first]--;
			}
		}/*
		for (auto it : mCrossways)
		{
			cout << it.first << ": ";
			for (auto p : it.second.getLinkedCrossways())
			{
				cout << p.first << "_(" << InOut[p.first] << ") ";
			}
			cout << endl;
		}*/
		map<string, vector<Edge>>::iterator start = vE.begin();
		string beg = start->first;
		int countOne = 0, countNOne = 0;

		{

			for (auto it : InOut)
			{
			 // ne e nujno vseki put no trqbwa da rabotiap
				if (it.second != 0 && it.second != 1 && it.second != -1)
				{
					cout << "NO EULER CYCLE!!!\n";
					return false;
				}
				else if (it.second == 1)
				{

					beg = it.first;									//beg = vE[k][m].getNom(); kudeto k,m sa takiva che it.first = vE[k][m].getFrom()
					countOne++;
				}
				else if (it.second == -1)
					countNOne++;
			}

			if (countOne == 1 && countNOne == 1)
			{
				cout << "EULER PATH " << endl;
				Euler(vE, beg);
			}
			else if (countOne == 0 && countNOne == 0)
			{

				cout << "EULER CYCLE :)))\n";
				Euler(vE, beg);
			}
		}
	}
	catch (...)
	{
		throw;
	}
	return false;
}

void System::blindAlleys(const vector<string>& vsplitLine)
{
	bool marker = false;
	for (auto it : mCrossways)
	{
		for (auto t : it.second.getLinkedCrossways())
		{
			if (mCrossways[t.first].getLinkedCrossways().size() == 0)
			{
				std::cout << "Dead ends: \n";
				std::cout << it.first << " " << t.first << std::endl;
				marker = true;
			}
		}
	}
	if (!marker) cout << "No dead ends \n";
}


bool System::BFS(const vector<string>& vsplitLine)
{
	string start = vsplitLine[1];
	string end = vsplitLine[2];

	if (start == end)
	{
		cout << "There is always a path from a Crossway to the same Crossway\n";
		return true;
		// "There is always a path from a Crossway to the same Crossway" 
	}


	map<string, bool> visited;

	for (auto it : mCrossways)
	{
		visited.insert({ it.first, false });	// visited[it.first]=false; // visited.insert(make_pair(it.first, false)); // visited.insert(pair<string, bool>(it.first, false)); 
	}

	queue<string> q;
	visited[start] = true;
	q.push(start);


	while (!q.empty())
	{
		start = q.front();
		q.pop();

		for (auto it : mCrossways[start].getLinkedCrossways())
		{
			if (it.first == end)
			{
				cout << "Path exists!\n";
				return true;
			}
			// visited <pair <bool, string >>
			// намираме текущия връх и проверяваме дали е бил посетен
			if (!visited[it.first])
			{
				visited[it.first] = true;
				q.push(mCrossways[it.first].getName());//push-ваме съседа
			}
		}
	}
	cout << "No path!\n";
	return false;
}


void System::toDFS(const vector<string>& vsplitLine)
{
	map<string, bool> visited;
	/*
	// можем да си спестим този цикъл - работи и без него, защото е mapи при map, ако индексираме по key, който не съществува, го добавя с празно value или със стойност, която сме задали,
	// например, вместо visited.insert({it.first, false});  можем да пишем  visited[it.first] = false; или visited[it.first]=true;
	for (auto it : mCrossways)
	{
		visited.insert({ it.first, false });		// visited.insert(make_pair(it.first, false)); // visited.insert(pair<string, bool>(it.first, false));
	}
	*/

	// searching for vsplitLine[1] in mCrossways and if it's find, starting DFS for him
	bool found = false;
	for (auto it : mCrossways)
	{
		if (it.first != vsplitLine[1]) continue;
		found = true;
		if (DFS(it.first, visited, it.first))
		{
			cout << "cross " << vsplitLine[1] << " FOUND, exists cycle\n";
			return;
		}
	}
	if (!found) cout << "cross " << vsplitLine[1] << " NOT FOUND \n";
	else cout << "cross " << vsplitLine[1] << " FOUND, but no cycle \n";
}

bool System::DFS(string curr, map<string, bool>& visited, string par)
{
	visited[curr] = true;				// понеже е map, когато инделсираме несъществуващ key, го добавя, като нов елемент
	for (auto it : mCrossways[curr].getLinkedCrossways())
	{
		if (!visited[it.first])		// в случая моче и с такава проверка --> if ( visited.count(it.first) == 0 )
		{
			return DFS(it.first, visited, par);
		}
		else if (it.first == par)
		{
			return true;
		}
	}
	return false;
}

bool System::reachAllCrossways(const vector<string>& vsplitLine)
{
	// vsplitLine[1] -> start Crossway, vsplitLine[2] -> end Crossway
	string start = vsplitLine[1];

	map<string, bool> visited;
	for (auto it : mCrossways)
	{
		visited.insert({ it.first, false });// visited.insert(pair<string, bool>(it.first, false));
	}

	queue<Crossway> q;
	visited[start] = true;
	q.push(Crossway(start));

	while (!q.empty())
	{
		start = q.front().getName();
		q.pop();

		// it тук ни минава за всеки връх( кръстовище ) - start по всички негови съседни върхове
		// типа е map
		for (auto it : mCrossways[start].getLinkedCrossways())
		{
			// visited <pair <bool, string >>
			// намираме текущия въх и проверяваме дали е бил посетен
			if (!visited[it.first])
			{
				visited[it.first] = true;
				//push-ваме съседите
				q.push(mCrossways[it.first]);
			}
		}
	}
	for (auto it : visited)
	{
		// ако има някое, което не е било посетено
		if (it.second == false)
		{
			cout << "Not possible" << endl;
			return false;
		}
	}
	cout << "Possible" << endl;
	return true;
}
