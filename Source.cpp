#include "Graph_info.h"


std::vector <graph> Graphs;
int Last_graph_idx = 0;
void help();
void create();
void info();
void info(int idx);
int main()
{
	std::string Answer;
	std::cout << "Welcome!" << std::endl;
	while (1)
	{
		std::cout << "You in main menu" << std::endl;
		std::cout << "There are " << Graphs.size() << " available Graphs"<< std::endl;
		std::cout << "Enter \"help\" to see available commands" << std::endl;
		std::cout << "Or any other command if you know any" << std::endl;
		std::cout << "> ";
		std::cin >> Answer;
		if (Answer == "help")
			help();
		else if (Answer == "create")
		{
			create();
		}
		else if (Answer == "info")
		{
			int idx = 0;
			system("cls");
			std::cout << "Please enter the index" << std::endl;
			std::cout << "To show information about a specific graph" << std::endl;
			std::cout << "Or enter\"0\" - to show brief info about each graph" << std::endl;
			std::cin >> idx;
			if (idx > 0)
				info(idx);
			else
				info();
		}
		else if (Answer == "exit")
			return 0;
		else
		{
			std::cout << "Wrong input. Try again. Please press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}

	}
	
}
void create()
{
	std::string Answer;
	graph G(++Last_graph_idx);
	while(1)
	{
		std::cout << "How do you wanna create graph:" << std::endl;
		std::cout << "By matrix of incidence - input \"MoI\"" << std::endl;
		std::cout << "By matrix of adjacent - input \"MoA\"" << std::endl;
		std::cout << "By List of adjacent - input \"LoA\"" << std::endl;
		std::cin >> Answer;
		if (Answer == "MoA")
		{
			int n = 0;
			std::cout << "Please, enter size of matrix" << std::endl;
			std::cin >> n;
			int** matrix = new int* [n];
			for (int i = 0; i < n; i++)
				matrix[i] = new int[n];
			for (int i = 0; i < n; i++)
			{
				std::cout << "Please, enter row ¹" << i + 1 << ":" << std::endl;
				for (int j = 0; j < n; j++)
					std::cin >> matrix[i][j];
			}
			G.create_by_MoA(matrix, n);
			Graphs.push_back(G);
			system("cls");
			return;
		}
		else if (Answer == "MoI")
		{
			int n = 0, m = 0;
			std::cout << "Please, enter number of vertex" << std::endl;
			std::cin >> n;
			std::cout << "Please, enter number of edges" << std::endl;
			std::cin >> m;
			int** matrix = new int* [n];
			for (int i = 0; i < n; i++)
				matrix[i] = new int[m];
			for (int i = 0; i < n; i++)
				for (int j = 0; j < m; j++)
					matrix[i][j] = 0;
			std::cin.get();
			for (int i = 0; i < n; i++)
			{
				std::cout << "Please, enter row ¹" << i + 1 << ":" << std::endl;
				for (int j = 0; j < m; j++)
					std::cin >> matrix[i][j];
			}
			G.create_by_MoI(matrix,n,m);
			Graphs.push_back(G);
			system("cls");
			return;
		}
		else if (Answer == "LoA")
		{
			std::vector<std::string> List;
			int n = 0;
			std::cout << "Please, enter number of vertex" << std::endl;
			std::cin >> n;
			std::cin.get();

			std::string str;
			std::cout << "Please, enter connections in format: \"1 2 3\" without any additional symbols" << std::endl;
			for (int i = 0; i < n; i++)
			{
				std::cout << i + 1 << ": ";
				getline(std::cin, str);
				if (str.size() == 0)
					str += ' ';
				List.push_back(str);
			}
			G.create_by_LoA(List, n);
			Graphs.push_back(G);
			system("cls");
			return;
		}
		else
		{
			std::cout << "Wrong Answer" << std::endl;
			system("cls");
		}

	}
}
void help()
{
	system("cls");
	std::cout << "\"create\" - to create new graph" << std::endl;
	std::cout << "\"info\" - to get information about any graph" << std::endl;
	std::cout << "Please press Enter to continue" << std::endl;
	_getch();
	system("cls");
}
void info()
{
	system("cls");
	for (int i = 0; i < Graphs.size(); i++)
	{
		Graphs[i].show_idx();
		Graphs[i].show_type();
		Graphs[i].show_NoV();
		Graphs[i].show_NoE();
		std::cout << "Please press Enter to continue" << std::endl;
		_getch();
	}
	system("cls");
}
void info(int idx)
{
	system("cls");
	int G_i = -1;
	for (int i = 0; i < Graphs.size(); i++)
	{
		int j = Graphs[i].get_INDEX();
		if (j == idx)
			G_i = i;
	}
		
	if (G_i == -1)
	{
		std::cout << "No graph with that index" << std::endl;
		system("cls");
		return;
	}

	std::string Answer;
	while (1)
	{
		std::cout << "What info about graph you wanna see?" << std::endl;
		std::cout << "\"back\" - to back in main menu" << std::endl;

		std::cout << "\"add_v\" - to add vertex" << std::endl;
		std::cout << "\"rem_v\" - to remove vertex" << std::endl;
		std::cout << "\"add_e\" - to add edge" << std::endl;
		std::cout << "\"rem_e\" - to remove edge" << std::endl;
		std::cout << "\"show_LoA\" - to show list of adjacent" << std::endl;
		std::cout << "\"show_MoA\" - to show Matrix of adjacent" << std::endl;
		std::cout << "\"show_MoI\" - to show Matrix of incidence" << std::endl;
		std::cout << "\"show_dist\" - to show distance betwen two vertex in graph" << std::endl;
		std::cout << "\"show_chain\" - to show chain of degrees" << std::endl;
		std::cout << "\"show_eccent\" - to show eccentricity of vertex" << std::endl;
		std::cout << "\"show_rad\" - to show radius of graph" << std::endl;
		std::cout << "\"show_diam\" - to show diametr of graph" << std::endl;
		std::cout << "\"show_center\" - to show center of graph" << std::endl;
		std::cout << "\"show_hang\" - to show hanged or isolated vertexes" << std::endl;
		std::cout << "\"show_deg\" - to show degree of vertex" << std::endl;
		std::cout << "\"show_periph\" - to show peripheral vertexes" << std::endl;
		std::cout << "\"show_complement\" - to show complement of graph" << std::endl;
		std::cout << "\"save_graph\" - to save graph in file" << std::endl;
		std::cout << "\"e_subdiv\" - for edge subdivision" << std::endl;
		std::cout << "\"v_contr\" - for vertex contraction" << std::endl;
		std::cout << "\"v_identif\" - for vertex identification" << std::endl;
		std::cout << "\"v_duplic\" - for vertex duplicate" << std::endl;
		std::cout << "\"v_cleav\" - for vertex cleaving" << std::endl;
		std::cout << "\"graph_uni\" - for graphs union" << std::endl;
		std::cout << "\"graph_con\" - for graphs connection" << std::endl;
		std::cout << "\"graph_mul\" - for graphs multiplication" << std::endl;
		std::cout << "\"main\" - to see Number of vertex, edges and type of graph" << std::endl;
		std::cin >> Answer;
		if (Answer == "main")
		{
			system("cls");
			Graphs[G_i].show_idx();
			Graphs[G_i].show_type();
			Graphs[G_i].show_NoV();
			Graphs[G_i].show_NoE();
			std::cout << "Please press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "graph_uni")
		{
			system("cls");
			if (Graphs.size()> 1)
			{
				int from_ = 0;
				std::cout << "Enter index of graph for union" << std::endl;
				std::cout << "> ";
				std::cin >> from_;
				system("cls");
				Graphs[G_i].graph_union(Graphs[from_ - 1]);
				std::cout << "Press Enter to continue" << std::endl;
				_getch();
				system("cls");
			}
			else
			{
				std::cout << "Not enough graphs for operation.Press Enter to continue" << std::endl;
				_getch();
				system("cls");
			}
			
		}
		else if (Answer == "graph_con")
		{
			system("cls");
			if (Graphs.size() > 1)
			{
				int from_ = 0;
				std::cout << "Enter index of graph for union" << std::endl;
				std::cout << "> ";
				std::cin >> from_;
				system("cls");
				Graphs[G_i].graph_connection(Graphs[from_ - 1]);
				std::cout << "Press Enter to continue" << std::endl;
				_getch();
				system("cls");
			}
			else
			{
				std::cout << "Not enough graphs for operation.Press Enter to continue" << std::endl;
				_getch();
				system("cls");
			}

		}
		else if (Answer == "graph_mul")
		{
			system("cls");
			if (Graphs.size() > 1)
			{
				int from_ = 0;
				std::cout << "Enter index of graph for union" << std::endl;
				std::cout << "> ";
				std::cin >> from_;
				system("cls");
				Graphs[G_i].graph_mul(Graphs[from_ - 1]);
				std::cout << "Press Enter to continue" << std::endl;
				_getch();
				system("cls");
			}
			else
			{
				std::cout << "Not enough graphs for operation.Press Enter to continue" << std::endl;
				_getch();
				system("cls");
			}

		}
		else if (Answer == "show_dist")
		{
			system("cls");
			int idx1 = -1, idx2 = -1;
			std::cout << "Enter index 1 - from what vertex start" << std::endl;
			std::cout << "> ";
			std::cin >> idx1;
			std::cout << "Enter index 2 - to what vertex reach" << std::endl;
			std::cout << "> ";
			std::cin >> idx2;
			system("cls");
			int dist = Graphs[G_i].get_distance(idx1, idx2, true);
			std::cout << "Steps need = " << dist << std::endl;
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_MoI")
		{
			system("cls");
			Graphs[G_i].show_MoI();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_MoA")
		{
			system("cls");
			Graphs[G_i].show_MoA();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_LoA")
		{
			system("cls");
			Graphs[G_i].show_LoA();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_chain")
		{
			system("cls");
			Graphs[G_i].show_chain_of_deg();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "add_v")
		{
			system("cls");
			Graphs[G_i].add_Vertex();
			std::cout << "Vertex successfully added! Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "rem_v")
		{
			system("cls");
			int n = 0;
			std::cout << "Enter index of vertex you want to delete" << std::endl;
			std::cout << "> ";
			std::cin >> n;
			system("cls");
			Graphs[G_i].rem_Vertex(n);
			std::cout << "Vertex successfully removed! Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_eccent")
		{
			system("cls");
			int n = 0;
			std::cout << "Enter index of vertex which eccentricity you want to know" << std::endl;
			std::cout << "> ";
			std::cin >> n;
			system("cls");
			int res = Graphs[G_i].get_eccentricity(n);
			std::cout << "Eccentricity of vertex " << n << " = " << res << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_deg")
		{
			system("cls");
			int n = 0;
			std::cout << "Enter index of vertex which degree you want to know" << std::endl;
			std::cout << "> ";
			std::cin >> n;
			system("cls");
			Graphs[G_i].show_Vertex_deg(n);
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_rad")
		{
			system("cls");
			Graphs[G_i].show_rad();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_diam")
		{
			system("cls");
			Graphs[G_i].show_diam();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_center")
		{
			system("cls");
			Graphs[G_i].show_center();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_hang")
		{
			system("cls");
			Graphs[G_i].show_hang_isol_vertex();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "show_complement")
		{
		system("cls");
		Graphs[G_i].show_complement_of_graph();
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "show_periph")
		{
			system("cls");
			Graphs[G_i].show_peripheral();
			std::cout << "Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "add_e")
		{
			system("cls");
			int from_ = 0,to_ = 0;
			std::cout << "Enter index of vertex from which edge starts" << std::endl;
			std::cout << "> ";
			std::cin >> from_;
			std::cout << "Enter index of vertex in which edge ends" << std::endl;
			std::cout << "> ";
			std::cin >> to_;
			system("cls");
			Graphs[G_i].add_Edges(from_, to_);
			std::cout << "Edge successfully added! Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "rem_e")
		{
			system("cls");
			int from_ = 0, to_ = 0;
			std::cout << "Enter index of vertex from which edge starts" << std::endl;
			std::cout << "> ";
			std::cin >> from_;
			std::cout << "Enter index of vertex in which edge ends" << std::endl;
			std::cout << "> ";
			std::cin >> to_;
			system("cls");
			Graphs[G_i].rem_Edges(from_, to_);
			std::cout << "Edge successfully removed! Press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
		else if (Answer == "v_contr")
		{
		system("cls");
		int from_ = 0, to_ = 0;
		std::cout << "Enter index of first vertex" << std::endl;
		std::cout << "> ";
		std::cin >> from_;
		std::cout << "Enter index of second vertex" << std::endl;
		std::cout << "> ";
		std::cin >> to_;
		system("cls");
		Graphs[G_i].vertex_contraction(from_, to_);
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "v_identif")
		{
		system("cls");
		int from_ = 0, to_ = 0;
		std::cout << "Enter index of first vertex" << std::endl;
		std::cout << "> ";
		std::cin >> from_;
		std::cout << "Enter index of second vertex" << std::endl;
		std::cout << "> ";
		std::cin >> to_;
		system("cls");
		Graphs[G_i].vertex_identification(from_, to_);
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "v_duplic")
		{
		system("cls");
		int from_ = 0;
		std::cout << "Enter index of vertex" << std::endl;
		std::cout << "> ";
		std::cin >> from_;
		system("cls");
		Graphs[G_i].vertex_duplicate(from_);
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "v_cleav")
		{
		system("cls");
		int from_ = 0;
		std::cout << "Enter index of vertex" << std::endl;
		std::cout << "> ";
		std::cin >> from_;
		system("cls");
		Graphs[G_i].vertex_cleaving(from_);
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "e_subdiv")
		{
		system("cls");
		int from_ = 0, to_ = 0;
		std::cout << "Enter index of vertex from which edge starts" << std::endl;
		std::cout << "> ";
		std::cin >> from_;
		std::cout << "Enter index of vertex in which edge ends" << std::endl;
		std::cout << "> ";
		std::cin >> to_;
		system("cls");
		Graphs[G_i].edge_subdivision(from_, to_);
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "save_graph")
		{
		system("cls");
		Graphs[G_i].output_graph();
		std::cout << "Press Enter to continue" << std::endl;
		_getch();
		system("cls");
		}
		else if (Answer == "back")
		{
			system("cls");
			return;
		}
		else
		{
			system("cls");
			std::cout << "Wrong input. Try again. Please press Enter to continue" << std::endl;
			_getch();
			system("cls");
		}
	}

}