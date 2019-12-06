#include <cstring>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <conio.h>

int comp1(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}
struct node
{
	explicit node(int idx) :index(idx), loop(0), eccentricity(-1), deg_to(0), deg_from(0){}
	node(node const& a) :index(a.index), loop(a.loop), eccentricity(a.eccentricity), deg_to(a.deg_to), deg_from(a.deg_from)
	{
		if (a.deg_to > 0)
			connect_to = a.connect_to;
		if (a.deg_from > 0)
			connect_from = a.connect_from;
	}
	void adding_connec(int idx, bool mode, bool way = false);
	void remove_connec(int idx, bool mode, bool way = false);
	int get_deg(bool mode,bool way = false)
	{
		if (!mode||!way)
			return deg_to;
		else
			return deg_from;
	}
	void link_to_list(std::vector <int> &copy,bool way = false)
	{
		if (!way)
			copy = connect_to;
		else
			copy = connect_from;
	}
	bool no_loop()
	{
		return !loop;
	}
	int get_idx()
	{
		return index;
	}
	void change_idx(int new_idx)
	{
		index = new_idx;
	}
	int get_eccent()
	{
		return eccentricity;
	}
	void change_eccent(int value)
	{
		eccentricity = value;
	}
	
private:
	int index;
	bool loop;
	int eccentricity;
	int deg_to;//if there is non-directed graph - using deg_to and conect_to as just deg and connections
	int deg_from;
	std::vector<int> connect_to;
	std::vector<int> connect_from;
};

void node::adding_connec(int idx, bool mode, bool way)//way(0) - to,way(1) - from
{
	if (!mode || !way)
	{
		connect_to.push_back(idx);
		deg_to++;
		//add_edge(idx);
		if (index == idx)
		{
			loop = true;
			if (!mode)
				deg_to++;
		}
	}
	else
	{
		connect_from.push_back(idx);
		deg_from++;
	}
}
void node::remove_connec(int idx, bool mode, bool way) //way(0) - to,way(1) - from
{
	if (!mode || !way)
	{
		for (int i = 0; i < connect_to.size(); i++)
		{
			if (connect_to[i] == idx)
			{
				
				connect_to.erase(connect_to.begin() + i);
				deg_to = connect_to.size();
				if (index == idx)
				{
					loop = false;
					if (!mode)
						deg_to--;
				}
			}
		}
		//std::cout << "No such connection to remove!" << std::endl;
	}
	else
	{
		for (int i = 0; i < connect_from.size(); i++)
		{
			if (connect_from[i] = idx)
			{
				connect_from.erase(connect_from.begin() + i);
				deg_from = connect_from.size();
			}
		}
		//std::cout << "No such connection to remove!" << std::endl;
	}
}

struct graph
{
	graph(int idx) :INDEX(idx),last_idx(0), Type_of_Graph(0), Num_of_Vertex(0), Num_of_Edges(0), Rad(-1), Diam(-1), center(-1),UPD(0), UPD_ECNTRI(0),MoA(0), MoI(0), LoA(0)
	{
		Matrix_of_adjacent = new int* [1];
		Matrix_of_adjacent[0] = new int [1];
		Matrix_of_adjacent[0][0] = 0;
		Matrix_of_incidence = new int* [1];
		Matrix_of_incidence[0] = new int [1];
		Matrix_of_incidence[0][0] = 0;
	}
	graph(graph const& a)
	{
		INDEX = a.INDEX;
		last_idx = a.last_idx;
		Type_of_Graph = a.Type_of_Graph;
		Num_of_Vertex = a.Num_of_Vertex;
		Num_of_Edges = a.Num_of_Edges;
		Rad = a.Rad;
		Diam = a.Diam;
		center = a.center;
		UPD= a.UPD;
		UPD_ECNTRI = a.UPD_ECNTRI;
		MoI = a.MoI;
		MoA = a.MoA;
		LoA = a.LoA;
		arr_of_Vrtx = a.arr_of_Vrtx;
		List_of_adjacent = a.List_of_adjacent;
		Matrix_of_adjacent = new int* [a.Num_of_Vertex];
		Matrix_of_incidence = new int* [a.Num_of_Vertex];
		for (int i = 0; i < a.Num_of_Vertex; i++)
			Matrix_of_adjacent[i] = new int[a.Num_of_Vertex];
		for (int i = 0; i < a.Num_of_Vertex; i++)
			Matrix_of_incidence[i] = new int[a.Num_of_Edges];

		for (int i = 0; i < a.Num_of_Vertex; i++)
			for (int j = 0; j < a.Num_of_Vertex; j++)
				Matrix_of_adjacent[i][j] = a.Matrix_of_adjacent[i][j];
		for (int i = 0; i < a.Num_of_Vertex; i++)
			for (int j = 0; j < a.Num_of_Edges; j++)
				Matrix_of_incidence[i][j] = a.Matrix_of_incidence[i][j];
	}
	int get_INDEX()
	{
		return INDEX;
	}
	int find_by_idx(int idx);//Searching in array of vertexes a vertex with index = idx
	void create_by_MoI(int** matrix, int n, int m);//creating by using matrix of incidence
	void create_by_MoA(int** matrix, int n);//creating by using matrix of adjacent
	void create_by_LoA(std::vector<std::string>& List, int n);//creating by using list of adjacent
	
	void add_Vertex();//adding vertex
	void rem_Vertex(int idx);//removing vertex
	void add_Edges(int idx_1,int idx_2);//adding edge betwin two vertexes
	void rem_Edges(int idx_1, int idx_2);//removing edge betwin two vertexes

	int get_distance(int idx1, int idx2, bool printing = false);//If true - will output the way from '1' to '2'
	void search_eccent()
	{
		int  min = 2000000, max = -1, temp = 0;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			temp = get_eccentricity(arr_of_Vrtx[i].get_idx());
			if (temp > max)
				max = temp;
			if (temp < min && temp > 0)
				min = temp;
		}
		Rad = min;
		Diam = max;
		UPD_ECNTRI = false;
	}
	void UPD_Forms(int OldV);
	void convert_to_all_forms(int way = 0);//After creating by any way.way(0)- by MoA,way(1) - by LoA,way(2) - by MoI
	void show_MoI()// show matrix of incidence
	{
		if (MoI)
		{
			if (UPD)
			{
				UPD_Forms(Num_of_Vertex);
			}
			else
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					std::cout << arr_of_Vrtx[i].get_idx() << ": ";
					for (int j = 0; j < Num_of_Edges; j++)
					{
						std::cout << Matrix_of_incidence[i][j] << " ";
					}
					std::cout << std::endl;
				}
		}
		else
			std::cout << "No Matrix to Show" << std::endl;
	}
	void show_MoA()// show matrix of adjacent
	{
		if (MoA)
		{
			if (UPD)
			{
				UPD_Forms(Num_of_Vertex);
			}
			else
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					std::cout << arr_of_Vrtx[i].get_idx() << ": ";
					for (int j = 0; j < Num_of_Vertex; j++)
					{
						std::cout << Matrix_of_adjacent[i][j] << " ";
					}
					std::cout << std::endl;
				}
		}
		else
			std::cout <<"No Matrix to Show"<< std::endl;
		
	}
	void show_LoA()// show list of adjacent
	{
		if (LoA)
		{
			if (UPD)
			{
				UPD_Forms(Num_of_Vertex);
			}
			else
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					std::cout << arr_of_Vrtx[i].get_idx()  << ": ";
					std::cout << List_of_adjacent[i] << std::endl;
				}
		}
		else
			std::cout << "No List to Show" << std::endl;
	}

	 
	void show_Vertex_deg(int idx)//show vertex degree
	{
		for (int i = 0; i < Num_of_Vertex; i++)
			if (arr_of_Vrtx[i].get_idx() == idx)
			{
				if(!Type_of_Graph)
					std::cout << "Degree of Vertex " << idx <<  " = " << arr_of_Vrtx[i].get_deg(Type_of_Graph) << std::endl;
				else
				{
					std::cout << "Outgree of Vertex " << idx << " = " << arr_of_Vrtx[i].get_deg(Type_of_Graph) << std::endl;
					std::cout << "Indegree of Vertex " << idx << " = " << arr_of_Vrtx[i].get_deg(Type_of_Graph, true) << std::endl;
				}
				return;
			}
		std::cout << "No such vertex" << std::endl;
	}
	void show_idx()
	{
		std::cout << "Index of this Graph = " << INDEX << std::endl;
	}

	void show_type()
	{
		if (!Type_of_Graph)
			std::cout << "Graph non-directed" << std::endl;
		else
			std::cout << "Graph directed" << std::endl;
	}
	void show_NoV()//Just show num of Vertex
	{
		std::cout << "Number of Vertexes for this Graph = " << Num_of_Vertex << std::endl;
	}
	void show_NoE()//Just show num of Edges
	{
		std::cout << "Number of egdes for this Graph = " << Num_of_Edges << std::endl;
	}

	void show_chain_of_deg()
	{
		int* arr_deg = new int[Num_of_Vertex];
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if(!Type_of_Graph)
				arr_deg[i] = arr_of_Vrtx[i].get_deg(Type_of_Graph);
			else
				arr_deg[i] = arr_of_Vrtx[i].get_deg(Type_of_Graph)+ arr_of_Vrtx[i].get_deg(Type_of_Graph,true);
		}
		qsort(arr_deg, Num_of_Vertex, sizeof(int), comp1);
		std::cout << "Sequence of numbers:" << std::endl;
		for (int i = 0; i < Num_of_Vertex; i++)
			std::cout << arr_deg[i] << " " ;
		std::cout << std::endl;
	}

	int get_eccentricity(int idx)//using for searching max and min eccentricity
	{
		int res = -1;
		int index = find_by_idx(idx), other = -1;
		if (index == -1)
		{
			std::cout << "No such vertex" << std::endl;
			return -1;
		}
		int cur_ecc = arr_of_Vrtx[index].get_eccent();
		for (int i = 0; i < Num_of_Vertex; i++)
		{	
			if (i != index)
			{
				other = arr_of_Vrtx[i].get_idx();
				res = get_distance(idx, other);
				if (res > cur_ecc)
					cur_ecc = res;
			}
		}
		arr_of_Vrtx[index].change_eccent(cur_ecc);
		return cur_ecc;
	}
	void show_rad()//checking or searching. While searching adding eccenricity for each vertex
	{
		if (UPD_ECNTRI)
		{
			search_eccent();
			std::cout << "Radius of this graph = " << Rad << std::endl;
		}
		else
			std::cout << "Radius of this graph = " << Rad << std::endl;
	}
	void show_diam()//checking or searching.while searching adding eccenricity for each vertex
	{
		if (UPD_ECNTRI)
		{
			search_eccent();
			std::cout << "Diametr of this graph = " << Diam << std::endl;
		}
		else
			std::cout << "Diametr of this graph = " << Diam << std::endl;
	}
	void show_center()//checking or searching for vertex with eccentricity = rad
	{
		if (UPD_ECNTRI)
		{
			search_eccent();
			UPD_ECNTRI = false;
			std::cout << "Vertex of this graph which could be center:" << std::endl;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				if (arr_of_Vrtx[i].get_eccent() == Rad)
					std::cout << arr_of_Vrtx[i].get_idx() << std::endl;
			}
		}
		else
		{
			std::cout << "Vertex of this graph which could be center:" << std::endl;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				if (arr_of_Vrtx[i].get_eccent() == Rad)
					std::cout << arr_of_Vrtx[i].get_idx() << std::endl;
			}
		}
	}
	void show_hang_isol_vertex()//just searching for vertex with deg <2
	{
		std::cout << "Isolated or Hanged vertexes:" << std::endl;
		int deg = -1;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (!Type_of_Graph)
			{
				deg = arr_of_Vrtx[i].get_deg(Type_of_Graph);
				if(deg < 2 || ((deg == 3 || deg == 2) && !arr_of_Vrtx[i].no_loop()))
					std::cout <<"Vertex " << arr_of_Vrtx[i].get_idx() << ". Degree = " << deg << std::endl;
			}
			else
			{
				deg = arr_of_Vrtx[i].get_deg(Type_of_Graph,true);
				if (deg < 1 )
					std::cout << "Source Vertex " << arr_of_Vrtx[i].get_idx() << std::endl;
				deg = arr_of_Vrtx[i].get_deg(Type_of_Graph);
				if (deg < 1)
					std::cout << "Sink Vertex " << arr_of_Vrtx[i].get_idx() << std::endl;
			}
		}
	}
	void show_peripheral()////just searching for vertex with eccentricity = diam
	{
		if (UPD_ECNTRI)
		{
			search_eccent();
			UPD_ECNTRI = false;
			std::cout << "Peripheral Vertexes:" << std::endl;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				if (arr_of_Vrtx[i].get_eccent() == Diam)
					std::cout << arr_of_Vrtx[i].get_idx() << std::endl;
			}
		}
		else
		{
			std::cout << "Peripheral Vertexes:" << std::endl;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				if (arr_of_Vrtx[i].get_eccent() == Diam)
					std::cout << arr_of_Vrtx[i].get_idx() << std::endl;
			}
		}
	}
	void show_complement_of_graph()//invertible matrix to  MoA
	{
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			for (int j = 0; j < Num_of_Vertex; j++)
			{
				if (Matrix_of_adjacent[i][j] > 0 || i == j)
					std::cout << "0 ";
				else
					std::cout << "1 ";
			}
			std::cout << std::endl;
		}
	}
	void output_graph()
	{
		std::ofstream out;          // поток дл€ записи
		out.open("Output.txt"); // окрываем файл дл€ записи
		if (out.is_open())
		{
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				out << '{';
				//out << arr_of_Vrtx[i].get_idx() << " ";
				out << arr_of_Vrtx[i].get_idx()<<" : ";
				out << List_of_adjacent[i];
				out << '}';
			}
			std::cout << "List of adjacent saved in file!" << std::endl;
		}
		out.close();
	}

	void edge_subdivision(int idx1, int idx2)
	{
		add_Vertex();
		rem_Edges(idx1, idx2);
		add_Edges(last_idx, idx1);
		add_Edges(last_idx, idx2);
	}
	void vertex_contraction(int idx1, int idx2)//ст€гивание вершин
	{
		if (idx1 == idx2)
		{
			std::cout << "Vertexes should be different" << std::endl;
			return;
		}
		int v1 = 0;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx1)
			{
				v1 = i;
				break;
			}
		}
		std::vector<int>list_1;
		arr_of_Vrtx[v1].link_to_list(list_1);
		std::vector<int>list_2;
		arr_of_Vrtx[v1].link_to_list(list_2,true);
		bool connected = false;
		for (int i = 0; i < list_1.size(); i++)
			if (list_1[i] == idx2)
				connected = true;

		if(Type_of_Graph)
			for (int i = 0; i < list_2.size(); i++)
				if (list_2[i] == idx2)
					connected = true;
		if (connected)
			vertex_identification(idx1, idx2);
		else
			std::cout << "Vertexes should be connected" << std::endl;
	}
	void vertex_identification(int idx1, int idx2)//отождествление вершин
	{
		if (idx1 == idx2)
		{
			std::cout << "Vertexes should be different"<<std::endl;
			return;
		}
		int v1 = 0, v2 = 0;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx1)
				v1 = i;
			if (arr_of_Vrtx[i].get_idx() == idx2)
				v2 = i;
		}
		std::vector<int>list_1;
		arr_of_Vrtx[v1].link_to_list(list_1);
		std::vector<int>list_2;
		arr_of_Vrtx[v2].link_to_list(list_2);

		add_Vertex();

		for (int i = 0; i < list_1.size(); i++)
		{
			if(list_1[i] != idx2)
				add_Edges(last_idx, list_1[i]);
		}
		bool covered = false;
		for (int i = 0; i < list_2.size(); i++)
		{
			for (int j = 0; j < list_1.size(); j++)
				if (list_1[j] == list_2[i])
					covered = true;
			if(!covered)
				add_Edges(last_idx, list_2[i]);
			covered = false;
		}
		if (Type_of_Graph)
		{
			arr_of_Vrtx[v1].link_to_list(list_1,true);
			arr_of_Vrtx[v2].link_to_list(list_2,true);
			for (int i = 0; i < list_1.size(); i++)
				add_Edges(list_1[i], last_idx);
			for (int i = 0; i < list_2.size(); i++)
			{
				for (int j = 0; j < list_1.size(); j++)
					if (list_1[j] == list_2[i])
						covered = true;
				if (!covered)
					add_Edges(list_2[i], last_idx);
				covered = false;
			}
		}
		rem_Vertex(idx1);
		rem_Vertex(idx2);
	}
	void vertex_duplicate(int idx)
	{
		int v1 = 0;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx)
			{
				v1 = i;
				break;
			}
		}
		std::vector<int>list_1;
		arr_of_Vrtx[v1].link_to_list(list_1);
		std::vector<int>list_2;
		arr_of_Vrtx[v1].link_to_list(list_2, true);

		add_Vertex();
		for (int i = 0; i < list_1.size(); i++)
			add_Edges(last_idx, list_1[i]);
			

		if (Type_of_Graph)
			for (int i = 0; i < list_2.size(); i++)
				add_Edges(list_2[i], last_idx);
	}
	void vertex_cleaving(int idx)
	{
		vertex_duplicate(idx);
		add_Edges(last_idx, idx);
		if (Type_of_Graph)
			add_Edges(idx, last_idx);
	}
	void graph_union(graph const& a)
	{
		int start = Num_of_Vertex,temp = 0,ad_idx = -1;
		std::vector<int> list;
		std::vector<node> arr = a.arr_of_Vrtx;
		int from = 0, to = 0;
		if (a.Type_of_Graph)
			Type_of_Graph = a.Type_of_Graph;
		for (int i = 0; i < a.Num_of_Vertex; i++)
			add_Vertex();
		if (Type_of_Graph)
		{
			for (int i = 0; i < a.Num_of_Vertex; i++)
			{
				arr[i].link_to_list(list);
				for (int j = 0; j < list.size(); j++)
				{
					from = arr_of_Vrtx[i + start].get_idx();
					for (int k = 0; k < arr.size(); k++)
						if (arr[k].get_idx() == list[j])
							to = arr_of_Vrtx[k + start].get_idx();
					add_Edges(from, to);
				}
			}
		}
		else
		{
			for (int i = 0; i < a.Num_of_Vertex; i++)//проходим по всем вершинаб добавл€емого графа
			{
				arr[i].link_to_list(list);// ѕолучаем список соединений конкретной вершины
				ad_idx = arr[i].get_idx();
				for (int j = 0; j < list.size(); j++)//ѕроходимс€ по этому списку
				{
					if (list[j] < ad_idx)
						continue;
					from = arr_of_Vrtx[i + start].get_idx();
					for (int k = 0; k < arr.size(); k++)// ѕолучаем пор€док вершины в втором графе, чтобы понимать его смещение в новом
						if (arr[k].get_idx() == list[j])
							to = arr_of_Vrtx[k + start].get_idx();
					add_Edges(from, to);
				}
			}
		}
	}
	void graph_connection(graph const& a)
	{
		int start = Num_of_Vertex, from_ = 0, to_ = 0;
		graph_union(a);

		for (int i = 0; i < start; i++)
		{
			from_ = arr_of_Vrtx[i].get_idx();
			for (int j = start; j < Num_of_Vertex; j++)
			{
				to_ = arr_of_Vrtx[j].get_idx();
				add_Edges(from_,to_);
				if(Type_of_Graph)
					add_Edges(to_, from_);
			}
		}
	}
	void graph_mul(graph const& a)
	{
		int mul = Num_of_Vertex * (a.Num_of_Vertex - 1);
		int modul = Num_of_Vertex;
		int step;
		int idx = -1;
		std::vector<int> list;
		int from = 0, to = 0;
		for (int i = 0; i < mul; i++)
			add_Vertex();
		for (int i = 0; i < modul; i++)
		{
			arr_of_Vrtx[i].link_to_list(list);
			for (int k = 0; k < list.size(); k++)
			{
				idx = find_by_idx(list[k]);
				if (!Type_of_Graph && idx < i)
					continue;
				for (int j = i + modul, step = modul; j < Num_of_Vertex; j += modul,step+=modul)
				{
					from = arr_of_Vrtx[j].get_idx();
					to = arr_of_Vrtx[idx+step].get_idx();
					add_Edges(from, to);
				}
				
			}
		}

		std::vector<node> arr = a.arr_of_Vrtx;
		std::vector<int> list2;
		//show_LoA();
		for (int i = 0; i < a.Num_of_Vertex; i++)
		{
			arr[i].link_to_list(list);
			if (Type_of_Graph)
				arr[i].link_to_list(list2,true);
			for (int k = 0; k < list.size(); k++)
			{
				for (int j = 0; j < arr.size(); j++)
					if (arr[j].get_idx() == list[k])
						idx = j;
				if (!Type_of_Graph && idx < i)
					continue;
				for (int j = 0; j < modul; j++)
				{
					from = arr_of_Vrtx[j + i*modul].get_idx();
					to = arr_of_Vrtx[j + idx * modul].get_idx();
					add_Edges(from, to);
				}			
			}
		}
	}
	
private:
	int INDEX;
	int last_idx;
	bool Type_of_Graph;//false - for non-directed, true
	int Num_of_Vertex;
	int Num_of_Edges;
	int Rad;
	int Diam;
	int center;
	//bool AoV;//false - non-created
	bool UPD;//false - graph didn't changed, true - need update marixes
	bool UPD_ECNTRI;//false - need to upd eccentricity,true - no need
	bool MoI;//false - non-created
	bool MoA;//false - non-created
	bool LoA;//false - non-created
	int** Matrix_of_incidence;
	int** Matrix_of_adjacent;
	std:: vector <std::string> List_of_adjacent;
	std::vector <node> arr_of_Vrtx;

};
int graph::find_by_idx(int idx)
{
	for (int i = 0; i < Num_of_Vertex; i++)
		if (arr_of_Vrtx[i].get_idx() == idx)
			return i;
	return -1;
}
//Shoud UPD Matrixes after each time i addind/removing vertex/edge
void graph::add_Vertex()
{
	++last_idx;
	arr_of_Vrtx.push_back(node(last_idx));
	Num_of_Vertex++;
	if(MoI || MoA || LoA)
		UPD = true;
	UPD_Forms(Num_of_Vertex - 1);
	/*if (!AoV)
	{
		arr_of_Vrtx = new node * [Num_of_Vertex + 1];
		last_idx++;
		arr_of_Vrtx[Num_of_Vertex] = new node(last_idx);
		Num_of_Vertex++;
		AoV = true;
	}
	else
	{
		node** temp = new node * [Num_of_Vertex];
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			temp[i] = arr_of_Vrtx[i];//maybe shoud use 'new node(*arr_of_Vrtx[i])'
		}
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			delete[] arr_of_Vrtx[i];
		}
		delete[] arr_of_Vrtx;
		arr_of_Vrtx = new node * [Num_of_Vertex + 1];
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			arr_of_Vrtx[i] = temp[i];
		}
		last_idx++;
		arr_of_Vrtx[Num_of_Vertex] = new node(last_idx);
		Num_of_Vertex++;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
	}*/

}
void graph::rem_Vertex(int idx)
{
	for (int i = 0; i < Num_of_Vertex; i++)
	{
		if (arr_of_Vrtx[i].get_idx() == idx)
		{
			std::vector<int> list_of_connected;
			arr_of_Vrtx[i].link_to_list(list_of_connected);
			int num_of_connected = list_of_connected.size();

			for (int k = 0; k < num_of_connected; k++)
				for (int j = 0; j < Num_of_Vertex; j++)
				{
					if (arr_of_Vrtx[j].get_idx() == list_of_connected[k]
						&& list_of_connected[k] != idx)
					{
						arr_of_Vrtx[j].remove_connec(idx, Type_of_Graph);
						Num_of_Edges--;
					}
				}
			for (int i = 0; i < num_of_connected; i++)
			{
				if (list_of_connected[i] == idx && !Type_of_Graph)
					Num_of_Edges-=1;
			}
			arr_of_Vrtx.erase(arr_of_Vrtx.begin() + i);
			Num_of_Vertex--;
			UPD = true;
			UPD_Forms(Num_of_Vertex+1);
		}
	}
	//std::cout << "There is no vertex to delete!" << std::endl;
	/*if (!AoV)
		std::cout << "There is no vertex to delete!" << std::endl;
	else
	{
		int vert = -1;
		for (int i = 0; i < Num_of_Vertex; i++)
			if (arr_of_Vrtx[i]->get_idx() == idx)
				vert = i;
		if (vert == -1)
		{
			std::cout << "There is no such vertex!" << std::endl;
			return;
		}
		const int * list_of_connected = arr_of_Vrtx[vert]->link_to_list();
		int num_of_connected = arr_of_Vrtx[vert]->get_deg(Type_of_Graph);

		for(int i=0; i < num_of_connected;i++)
			for (int j = 0; j < Num_of_Vertex; j++)
				if (arr_of_Vrtx[j]->get_idx() == list_of_connected[i] && list_of_connected[i] != idx)
					arr_of_Vrtx[j]->remove_connec(list_of_connected[i], Type_of_Graph);

		node** temp = new node * [Num_of_Vertex - 1];
		int counter=0;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if(i != vert)
				temp[counter++] = arr_of_Vrtx[i];//maybe shoud use 'new node(*arr_of_Vrtx[i])'
		}
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			delete[] arr_of_Vrtx[i];
		}
		delete[] arr_of_Vrtx;
		arr_of_Vrtx = new node * [Num_of_Vertex - 1];
		for (int i = 0; i < Num_of_Vertex - 1; i++)
		{
			arr_of_Vrtx[i] = temp[i];
		}
		//last_idx++; - because we deleting vertex
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			delete[] temp[i];
		}
		delete[] temp;
		Num_of_Vertex--;
	}
	*/
}
void graph::add_Edges(int idx_1, int idx_2)
{
	if (idx_1 != idx_2)
	{
		int v1=-1, v2=-1;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx_1)
				v1 = i;
			if (arr_of_Vrtx[i].get_idx() == idx_2)
				v2 = i;
		}
		if (!Type_of_Graph && v1 != -1 && v2 != -1)
		{
			arr_of_Vrtx[v1].adding_connec(idx_2, Type_of_Graph);
			arr_of_Vrtx[v2].adding_connec(idx_1, Type_of_Graph);
			Num_of_Edges++;
			if (MoI || MoA || LoA)
				UPD = true;
			UPD_Forms(Num_of_Vertex);
			UPD_ECNTRI = true;
		}
		else if(v1 != -1 && v2 != -1)
		{
			arr_of_Vrtx[v1].adding_connec(idx_2, Type_of_Graph);
			arr_of_Vrtx[v2].adding_connec(idx_1, Type_of_Graph, true);
			Num_of_Edges++;
			if (MoI || MoA || LoA)
				UPD = true;
			UPD_Forms(Num_of_Vertex);
			UPD_ECNTRI = true;
		}
		if (v1 == -1 || v2 == -1)
			std::cout << "One or both vertex not found!" << std::endl;
	}
	else
	{
		int v1 = -1;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx_1)
			{
				v1 = i;
				break;
			}
		}
		if (!arr_of_Vrtx[v1].no_loop())
			std::cout << "There is already exist loops!" << std::endl;
		else if (v1 > 0)
		{
			if (!Type_of_Graph)
			{
				arr_of_Vrtx[v1].adding_connec(idx_2, Type_of_Graph);
			}
			else
			{
				arr_of_Vrtx[v1].adding_connec(idx_2, Type_of_Graph);
				arr_of_Vrtx[v1].adding_connec(idx_2, Type_of_Graph,true);
			}
			Num_of_Edges++;
			if (MoI || MoA || LoA)
				UPD = true;
			UPD_Forms(Num_of_Vertex);
			UPD_ECNTRI = true;
		}
		else
			std::cout << "Vertex not found!" << std::endl;
		
	}
}
void graph::rem_Edges(int idx_1, int idx_2)
{
	if (idx_1 != idx_2)
	{
		int v1 = -1, v2 = -1;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx_1)
				v1 = i;
			if (arr_of_Vrtx[i].get_idx() == idx_2)
				v2 = i;
		}
		if (!Type_of_Graph && v1 != -1 && v2 != -1)
		{
			arr_of_Vrtx[v1].remove_connec(idx_2, Type_of_Graph);
			arr_of_Vrtx[v2].remove_connec(idx_1, Type_of_Graph);
			Num_of_Edges--;
			UPD = true;
			UPD_Forms(Num_of_Vertex);
			UPD_ECNTRI = true;
		}
		else if (v1 != -1 && v2 != -1)
		{
			arr_of_Vrtx[v1].remove_connec(idx_2, Type_of_Graph);
			arr_of_Vrtx[v2].remove_connec(idx_1, Type_of_Graph, true);
			Num_of_Edges--;
			UPD = true;
			UPD_Forms(Num_of_Vertex);
			UPD_ECNTRI = true;
		}
		if (v1 == -1 || v2 == -1)
			std::cout << "One or both vertex not found!"<<std::endl;
	}
	else
	{
		int v1 = -1;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			if (arr_of_Vrtx[i].get_idx() == idx_1)
			{
				v1 = i;
				break;
			}
		}
		if (arr_of_Vrtx[v1].no_loop())
			std::cout << "There is no loops!" << std::endl;
		if (v1 > 0 && !arr_of_Vrtx[v1].no_loop())
		{
			arr_of_Vrtx[v1].remove_connec(idx_2, Type_of_Graph);
			Num_of_Edges--;
			UPD = true;
			UPD_Forms(Num_of_Vertex);
			UPD_ECNTRI = true;
		}
		if (v1 == -1)
			std::cout << "Vertex not found!" << std::endl;
		
	}
}

void graph::create_by_MoI(int** matrix, int n,int m)
{
	for (int i=0; i < n; i++)
		add_Vertex();
	Matrix_of_incidence = new int* [n];
	for (int i = 0; i < n; i++)
		Matrix_of_incidence[i] = new int[m];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
		{
			Matrix_of_incidence[i][j] = matrix[i][j];
			if (matrix[i][j] < 0)
				Type_of_Graph = true;
		}
	int to_ = -1, from_ = -1;
	if (!Type_of_Graph)
	{
		for (int i = 0; i < m; i++)
		{
			to_ = -1;
			from_ = -1;
			for (int j = 0; j < n; j++)
			{
				if (matrix[j][i] > 0)
				{
					if (from_ != -1)
						to_ = j + 1;
					if(from_ == -1)
						from_ = j + 1;
				}
			}
			if (to_ != -1 && from_ != -1)
				add_Edges(from_, to_);
			else if (to_ == -1)
				add_Edges(from_, from_);
		}
	}
	else
	{
		for (int i = 0; i < m; i++)
		{
			to_ = -1;
			from_ = -1;
			for (int j = 0; j < n; j++)
			{
				if (matrix[j][i] < 0 || (matrix[j][i] > 0 && from_ != -1))
					to_ = j + 1;
				if (matrix[j][i] > 0)
					from_ = j + 1;	
			}
			if (to_ != -1 && from_ != -1)
			{
				if(matrix[to_ - 1][i] < 0)
					add_Edges(from_, to_);
				else
				{
					add_Edges(from_, to_);
					add_Edges(to_, from_);
				}
			}		
			else if (to_ == -1)
				add_Edges(from_, from_);
		}
	}
	MoI = true;
	convert_to_all_forms(2);
}
void graph::create_by_MoA(int** matrix, int n)
{
	for (int i=0; i < n; i++)
		add_Vertex();
	Matrix_of_adjacent = new int* [n];
	for (int i = 0; i < n; i++)
		Matrix_of_adjacent[i] = new int[n];
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
		{
			Matrix_of_adjacent[i][j] = matrix[i][j];
			if (matrix[i][j] != matrix[j][i])
				Type_of_Graph = true;
		}
	int to_ = -1, from_ = -1;
	if (!Type_of_Graph)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				if(matrix[i][j] != 0)
					add_Edges(i + 1, j + 1);
			}
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (matrix[i][j] != 0)
					add_Edges(i + 1, j + 1);
			}
		}
	}
	MoA = true;
	convert_to_all_forms(0);
}
void graph::create_by_LoA(std::vector<std::string> &List, int n)
{
	for (int i=0; i < n; i++)
		add_Vertex();
	for (int i = 0; i < n; i++)
		List_of_adjacent.push_back(List[i]);
	Matrix_of_adjacent = new int* [n];
	for (int i = 0; i < n; i++)
		Matrix_of_adjacent[i] = new int[n];

	int num = 0, idx = -1, start = 0;
	std::string s;
	int len = 0;
	for (int i = 0; i < n; i++)
	{
		start = 0;
		for (int j = 0; j < n; j++)
			Matrix_of_adjacent[i][j] = 0;
		len = List_of_adjacent[i].size();
		idx = List_of_adjacent[i].find(' ', start);
		if (idx == -1)
		{
			s = List_of_adjacent[i].substr(start, len - start);
			num = atoi(s.c_str());
			if (num - 1 != i)
				Matrix_of_adjacent[i][num - 1] = 1;
			else
				Matrix_of_adjacent[i][num - 1] = 2;
		}
		while (idx != -1)
		{
			
			s = List_of_adjacent[i].substr(start, idx - start);
			num = atoi(s.c_str());
			if(num-1 != i)
				Matrix_of_adjacent[i][num - 1] = 1;
			else
				Matrix_of_adjacent[i][num - 1] = 2;

			start = idx + 1;
			if (start >= len)
				break;
			idx = List_of_adjacent[i].find(' ', start);
			if (idx == -1)
			{
				s = List_of_adjacent[i].substr(start, len - start);
				num = atoi(s.c_str());
				if (num - 1 != i)
					Matrix_of_adjacent[i][num - 1] = 1;
				else
					Matrix_of_adjacent[i][num - 1] = 2;
			}
		}
	} // Converting List_of_adjacent to Matrix_of_adjacent

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (Matrix_of_adjacent[i][j] != Matrix_of_adjacent[j][i])
				Type_of_Graph = true;
	if(Type_of_Graph)
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (Matrix_of_adjacent[i][j] == 2)
					Matrix_of_adjacent[i][j] = 1;
	int to_ = -1, from_ = -1;
	if (!Type_of_Graph)
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = i; j < n; j++)
			{
				if (Matrix_of_adjacent[i][j] != 0)
					add_Edges(i + 1, j + 1);
			}
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < n; j++)
			{
				if (Matrix_of_adjacent[i][j] != 0)
					add_Edges(i + 1, j + 1);
			}
		}
	}
	MoA = true;
	LoA = true;
	convert_to_all_forms(1);
}
void graph::convert_to_all_forms(int way)
{
	if (way == 0)//MoA
	{
		if (!MoI)
		{
			int cur_col = 0;
			int* Vertex = new int[Num_of_Vertex];
			int border = 0;
			Matrix_of_incidence = new int* [Num_of_Vertex];
			for (int i = 0; i < Num_of_Vertex; i++)
				Matrix_of_incidence[i] = new int[Num_of_Edges];
			for (int i = 0; i < Num_of_Vertex; i++)
				for (int j = 0; j < Num_of_Edges; j++)
					Matrix_of_incidence[i][j] = 0;
			if (!Type_of_Graph)
			{
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					for (int j = i; j < Num_of_Vertex; j++)
						if (Matrix_of_adjacent[i][j] != 0)
							Vertex[border++] = j;
					border += cur_col;
					for (int j = cur_col; j < border; j++)
					{
						Matrix_of_incidence[i][j] = 1;
						Matrix_of_incidence[Vertex[j - cur_col]][j] = 1;
					}
					cur_col = border;
					border = 0;

				}
				MoI = true;
			}
			else
			{
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					for (int j = 0; j < Num_of_Vertex; j++)
						if (Matrix_of_adjacent[i][j] != 0)
							Vertex[border++] = j;
					border += cur_col;
					for (int j = cur_col; j < border; j++)
					{
						Matrix_of_incidence[i][j] = 1;
						if (Vertex[j - cur_col] != i)
							Matrix_of_incidence[Vertex[j - cur_col]][j] = -1;
					}
					cur_col = border;
					border = 0;
				}
				MoI = true;
			}
		}
		if (!LoA)
		{
			std::vector <int> Connections;
			std::vector <int> backorder;
			std::string str;
			int size_ = 0;
			int k = 0;
			int value = 0;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				arr_of_Vrtx[i].link_to_list(Connections);
				size_ = Connections.size();
				for (int j = 0; j < size_; j++)
				{
					if (Connections[j] < 10)
						str.push_back(Connections[j] + '0');
					else
					{
						value = Connections[j];
						while (value > 0)
						{
							backorder.push_back(value % 10);
							value /= 10;
						}
						for (int k = backorder.size() - 1; k > -1; k--)
						{
							str.push_back(backorder[k] + '0');
						}
						backorder.clear();
					}
					if (j != size_ - 1)
						str.push_back(' ');
				}
				//std::cout << str << std::endl;
				List_of_adjacent.push_back(str);
				str.clear();

			}
			LoA = true;
		}
	}
	else if (way == 1)//LoA
	{
		if (!MoA)
		{
			Matrix_of_adjacent = new int* [Num_of_Vertex];
			for (int i = 0; i < Num_of_Vertex; i++)
				Matrix_of_adjacent[i] = new int[Num_of_Vertex];

			int num = 0, idx = -1, start = 0;
			std::string s;
			int len = 0;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				start = 0;
				for (int j = 0; j < Num_of_Vertex; j++)
					Matrix_of_adjacent[i][j] = 0;
				len = List_of_adjacent[i].size();
				idx = List_of_adjacent[i].find(' ', start);
				if (idx == 0)
					continue;
				if (idx == -1)
				{
					s = List_of_adjacent[i].substr(start, len - start);
					num = atoi(s.c_str());
					num = find_by_idx(num);
					if (num == -1)
						continue;
					if (num!= i)
						Matrix_of_adjacent[i][num] = 1;
					else
						Matrix_of_adjacent[i][num] = 2;
				}
				while (idx != -1)
				{

					s = List_of_adjacent[i].substr(start, idx - start);
					num = atoi(s.c_str());
					num = find_by_idx(num);
					if (num != i)
						Matrix_of_adjacent[i][num] += 1;
					else
						Matrix_of_adjacent[i][num] += 2;

					start = idx + 1;
					if (start >= len)
						break;
					idx = List_of_adjacent[i].find(' ', start);
					if (idx == -1)
					{
						s = List_of_adjacent[i].substr(start, len - start);
						num = atoi(s.c_str());
						num = find_by_idx(num);
						if (num != i)
							Matrix_of_adjacent[i][num] += 1;
						else
							Matrix_of_adjacent[i][num] += 2;
					}
				}
			} // Converting List_of_adjacent to Matrix_of_adjacent
			for (int i = 0; i < Num_of_Vertex; i++)
				for (int j = 0; j < Num_of_Vertex; j++)
					if (Matrix_of_adjacent[i][j] != Matrix_of_adjacent[j][i])
						Type_of_Graph = true;
			MoA = true;
		}
		if (!MoI)
		{
			int cur_col = 0;
			int *Vertex = new int[Num_of_Vertex];
			int border = 0;
			Matrix_of_incidence = new int* [Num_of_Vertex];
			for (int i = 0; i < Num_of_Vertex; i++)
				Matrix_of_incidence[i] = new int[Num_of_Edges];
			for (int i = 0; i < Num_of_Vertex; i++)
				for (int j = 0; j < Num_of_Edges; j++)
					Matrix_of_incidence[i][j] = 0;
			if(!Type_of_Graph)
			{
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					for (int j = i; j < Num_of_Vertex; j++)
						if (Matrix_of_adjacent[i][j] != 0)
							Vertex[border++] = j;
					border += cur_col;
					for (int j = cur_col; j < border; j++)
					{
						Matrix_of_incidence[i][j] = 1;
						Matrix_of_incidence[Vertex[j- cur_col]][j] = 1;
					}
					cur_col = border;
					border = 0;
				}
				MoI = true;
			}
			else
			{
				for (int i = 0; i < Num_of_Vertex; i++)
				{
					for (int j = 0; j < Num_of_Vertex; j++)
						if (Matrix_of_adjacent[i][j] != 0)
							Vertex[border++] = j;
					border += cur_col;
					for (int j = cur_col; j < border; j++)
					{
						Matrix_of_incidence[i][j] = 1;
						if(Vertex[j - cur_col] != i)
							Matrix_of_incidence[Vertex[j - cur_col]][j] = -1;
					}
					cur_col = border;
					border = 0;
				}
				MoI = true;
			}
			delete[] Vertex;
		}
	}
	else
	{
		if (!MoA)
		{
			int to_ = -1, from_ = -1;
			
			Matrix_of_adjacent = new int* [Num_of_Vertex];
			for (int i = 0; i < Num_of_Vertex; i++)
				Matrix_of_adjacent[i] = new int[Num_of_Vertex];
			for (int i = 0; i < Num_of_Vertex; i++)
				for (int j = 0; j < Num_of_Vertex; j++)
					Matrix_of_adjacent[i][j] = 0;
			for (int i = 0; i < Num_of_Edges; i++)
			{
				for (int j = 0; j < Num_of_Vertex; j++)
				{
					if (Matrix_of_incidence[j][i] > 0 && from_ != -1)
						to_ = j;
					if (Matrix_of_incidence[j][i] > 0 && from_ == -1)
						from_ = j;
					if (Matrix_of_incidence[j][i] < 0 && to_ == -1)
						to_ = j;
				}
				if (from_ >= 0 && to_ >= 0)
				{
					if (!Type_of_Graph)
					{
						Matrix_of_adjacent[from_][to_] = 1;
						Matrix_of_adjacent[to_][from_] = 1;
					}
					else
					{
						if (from_ != to_)
							Matrix_of_adjacent[from_][to_] = 1;
						else
							Matrix_of_adjacent[from_][to_] = 2;
					}
				}
				else if (from_ > -1)
				{
					if(!Type_of_Graph)
						Matrix_of_adjacent[from_][from_] = 2;
					else
						Matrix_of_adjacent[from_][from_] = 1;
				}
				from_ = to_ = -1;
			}
			MoA = true;
		}
		if (!LoA)
		{
			std::vector <int> Connections;
			std::vector <int> backorder;
			std::string str;
			int size_ = 0;
			int k = 0;
			int value = 0;
			for (int i = 0; i < Num_of_Vertex; i++)
			{
				arr_of_Vrtx[i].link_to_list(Connections);
				size_ = Connections.size();
				for (int j = 0; j < size_; j++)
				{
					if (Connections[j] < 10)
						str.push_back(Connections[j] + '0');
					else
					{
						value = Connections[j];
						while (value > 0)
						{
							backorder.push_back(value % 10);
							value /= 10;
						}
						for (int k = backorder.size() - 1; k > -1; k--)
						{
							str.push_back(backorder[k] + '0');
						}
						backorder.clear();
					}
					if (j != size_ - 1)
						str.push_back(' ');
				}
				//std::cout << str << std::endl;
				List_of_adjacent.push_back(str);
				str.clear();

			}
			LoA = true;
		}	
	}
}
int graph::get_distance(int idx1, int idx2, bool printing)
{
	int cur_elem = 0,gear = 0;
	int * Sequence = new int[Num_of_Vertex]; // вершины графа
	for (int i = 0; i < Num_of_Vertex; i++) // исходно все вершины равны -1
		Sequence[i] = -1;
	std::vector<int> arr_con;
	int node = -1;
	int size_ = 0;
	bool present = false;
	Sequence[cur_elem++] = idx1;
	while (cur_elem < Num_of_Vertex)//ƒоработать стартовую позицию 
	{
		node = find_by_idx(Sequence[gear]);
		if (node == -1)
			break;
		arr_of_Vrtx[node].link_to_list(arr_con);
		size_ = arr_con.size();
		for (int i = 0; i < size_; i++)
		{
			for (int j = 0; j < cur_elem; j++)
			{
				if (Sequence[j] == arr_con[i])
					present = true;
			}
			if (!present)
				Sequence[cur_elem++] = arr_con[i];
			present = false;
		}
		gear++;
	}
	cur_elem = -1;
	for (int i = 0; i < Num_of_Vertex; i++)
	{

		if (Sequence[i] == idx2)
			cur_elem = i;
	}
	if (cur_elem == -1)
	{
		if (printing)
			std::cout << "No way to vertex " << idx2;
		return -1;
	}
	int steps = 0;
	if (printing)
		std::cout << "Way: " << idx2;
	if (cur_elem == 0)
	{
		if (printing)
			std::cout << " -> ";
		node = find_by_idx(Sequence[cur_elem]);
		if (!Type_of_Graph)
			arr_of_Vrtx[node].link_to_list(arr_con);
		else
			arr_of_Vrtx[node].link_to_list(arr_con, true);
		size_ = arr_con.size();
		for (int j = 0; j < size_; j++)
		{
			if (Sequence[0] == arr_con[j])
			{
				if (printing)
					std::cout << Sequence[0];
				steps++;
				if (Sequence[cur_elem] == idx1)
				{
					if (printing)
						std::cout << std::endl;
					delete[] Sequence;
					return steps;
				}
				break;
			}
		}
		std::cout <<"No way"<< std::endl;
		return -1;
	}
	int Old_cur = -1;
	while (1)
	{
		if (cur_elem == Old_cur)
		{
			std::cout <<"No way"<< std::endl;
			return -1;
		}
		Old_cur = cur_elem;
		if (printing)
			std::cout << " <- ";
		node = find_by_idx(Sequence[cur_elem]);
		if (!Type_of_Graph)
			arr_of_Vrtx[node].link_to_list(arr_con);
		else
			arr_of_Vrtx[node].link_to_list(arr_con ,true);
		size_ = arr_con.size();
		for (int i = 0; i < cur_elem; i++)
		{
			for (int j = 0; j < size_; j++)
			{
				if (Sequence[i] == arr_con[j])
				{
					if (printing)
						std::cout << Sequence[i];
					cur_elem = i;
					steps++;
					if (Sequence[cur_elem] == idx1)
					{
						if (printing)
							std::cout << std::endl;
						delete[] Sequence;
						return steps;
					}
					break;
				}
			}
		}
		//return -1;
	}
	
}
void graph::UPD_Forms(int OldV)
{
	if (UPD)
	{
		for (int i = 0; i < OldV; i++)
		{
			delete[]Matrix_of_adjacent[i];
			delete[]Matrix_of_incidence[i];
		}
		delete [] Matrix_of_adjacent;
		delete [] Matrix_of_incidence;
		MoI = false;
		MoA = false;
		List_of_adjacent.clear();
		std::vector <int> Connections;
		std::string str;
		std::vector <int> backorder;
		int size_ = 0;
		int k = 0;
		int value = 0;
		for (int i = 0; i < Num_of_Vertex; i++)
		{
			arr_of_Vrtx[i].link_to_list(Connections);
			size_ = Connections.size();
			for (int j = 0; j < size_; j++)
			{
				if(Connections[j] < 10)
					str.push_back(Connections[j] + '0');
				else
				{
					value = Connections[j];
					while (value > 0)
					{
						backorder.push_back(value % 10);
						value /= 10;
					}
					for (int k = backorder.size()-1; k > -1; k--)
					{
						str.push_back( backorder[k] + '0');
					}
					backorder.clear();
					
				}
				if (j != size_ - 1)
					str.push_back(' ');
			}

			//std::cout << str << std::endl;
			if (size_ == 0)
				str += ' ';
			List_of_adjacent.push_back(str);
			str.clear();

		}
		LoA = true;
		convert_to_all_forms(1);
		UPD = false;
	}
	//Delete all forms for next re-assigned
}