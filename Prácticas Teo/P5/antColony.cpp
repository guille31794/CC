#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <thread>

using namespace std;

struct City
{
	int coordX;
	int coordY;
};

double d_euclidea(const City& a, const City& b)
{
	return sqrt(pow(b.coordX-a.coordX,2) + pow(b.coordY-a.coordY,2));
}


vector<vector<double>> getDistances(const vector<City>& cities)
{
	vector<vector<double>> Map(cities.size(), vector<double>(cities.size(), 0));

	for (int i = 0; i < cities.size(); ++i)
		for (int j = 0; j < cities.size(); ++j)
			Map[i][j] = d_euclidea(cities[i], cities[j]);
		
	return Map;
}

double pathCost(const vector<int>& Path, const vector<vector<double>> Map)
{
	double cost = 0;

	for(int i = 1; i < Path.size(); ++i)
		cost += Map[Path[i-1]][Path[i]];

	cost += Map[*(Path.end()-1)][*(Path.begin())];

	return cost;
}

vector<int> ACO(const vector<City>& cities, const vector<vector<double>> Map, 
int max_it, int num_ants, double decay_factor, double pher_coef, 
double pher_coef_elit, double alpha, double beta, bool expansion, int randomseed)
{
	srand(randomseed);

	int nCities = cities.size();

	//Initialise colony of ants (each ant is a vector of city indices)
	vector<vector<int>> Colony(num_ants, vector<int>(nCities, 0));

	//Initialise pheromone matrix
	vector<vector<double>> pheromones(nCities, vector<double>(nCities, 0));

	//Initialise costs vector(for etilist expansion)
	vector<double> costs(num_ants, 0);

	//Auxiliar vector of indices
	vector<int> cityIndices(nCities);
	for (int i = 0; i < nCities; ++i)
		cityIndices[i] = i;

	//Longest distance from Map, used for heuristic values.
	vector<double> longests(nCities, 0);
	for(int i = 0; i < nCities; ++i)
		longests[i] = *(max_element(Map[i].begin(), Map[i].end()));

	const double MAX_DIST = *(max_element(longests.begin(), longests.end()));
	longests.clear();

	int i=0;
	while(i<max_it)
	{
		for(int ant_i = 0; ant_i < num_ants; ++ant_i)
		{
			//City for ant_i to start at; each ant is assigned a determined starting city
			int starting_city = (int) ((float)ant_i/num_ants*nCities);
			Colony[ant_i][0] = starting_city;

			//Get a vector with the cities left to visit
			vector<int> RemainingCities = cityIndices;

			//Remove starting city from remaining cities
			RemainingCities.erase(RemainingCities.begin() + starting_city);

			//Create path for ant_i
			for(int city_i = 1; city_i < Colony[ant_i].size(); ++city_i)
			{
				//Create roulette for next city selection
				vector<double> Roulette(RemainingCities.size(), 0);
				double total = 0;

				for(int j = 0; j < RemainingCities.size(); ++j)
				{
					//Heuristic value is MAX_DIST - current edge.
					Roulette[j] = pow((MAX_DIST - Map[Colony[ant_i][city_i-1]][RemainingCities[j]]), alpha) 
					+ pow((pheromones[Colony[ant_i][city_i-1]][RemainingCities[j]]), beta);
					total += Roulette[j];
				}

				//Transform roulette into stacked probabilities
				Roulette[0] = Roulette[0]/total;

				for(int j = 1; j < Roulette.size(); ++j)
					Roulette[j] = Roulette[j-1] + Roulette[j] / total;

				//Select a city from Roulette
				int chosen = 0;
				double r = (double) rand()/RAND_MAX;
				while(Roulette[chosen] < r)
					chosen++;

				//Add chosen city to ant path
				Colony[ant_i][city_i] = RemainingCities[chosen];
				RemainingCities.erase(RemainingCities.begin() + chosen);
			}

			//Save cost of ant_i, for elitist expansion
			costs[ant_i] = pathCost(Colony[ant_i], Map);
		}

		//Spreading pheromones
		for(int ant_i = 0; ant_i < num_ants; ++ant_i)
		{
			//Edge from last city to first city
			int i = Colony[ant_i][0];
			int j = Colony[ant_i][nCities];
			pheromones[i][j] = pheromones[j][i] = pheromones[i][j] + pher_coef/costs[ant_i];

			//Rest of edges
			for(int k = 1; k < nCities; ++k)
			{
				i = Colony[ant_i][k];
				j = Colony[ant_i][k-1];
				pheromones[i][j] = pheromones[j][i] = pheromones[i][j] + pher_coef/costs[ant_i];
			}
		}

		//Elitist expansion
		if(expansion)
		{
			//Edge from last city to first city
			int best_ant = (min_element(costs.begin(), costs.end()) - costs.begin());
			int i = Colony[best_ant][0];
			int j = Colony[best_ant][nCities];
			pheromones[i][j] = pheromones[j][i] = pheromones[i][j] + pher_coef/costs[best_ant];

			//Rest of edges
			for(int k = 1; k < nCities; ++k)
			{
				i = Colony[best_ant][k];
				j = Colony[best_ant][k-1];
				pheromones[i][j] = pheromones[j][i] = pheromones[i][j] + pher_coef_elit/costs[best_ant];
			}
		}

		//Decay of pheromones
		for(int i = 0; i < pheromones.size(); ++i)
			for(int j = i+1; j < pheromones[i].size(); ++j)
				pheromones[i][j] = pheromones[j][i] = pheromones[i][j]*(1-decay_factor);

		i++;
	}

	//Get best ant from the resulting colony
	int best_result = (min_element(costs.begin(), costs.end()) - costs.begin());

	return Colony[best_result];
}


vector<City> readFile(string name)
{

	vector<City> ciudades;
	ifstream file;
	string linea_texto;

	file.open(name, ios::in);

	if(file.fail())
	{
		cout << "Error al abrir el archivo" << endl;
		exit(1);
	}

	while(!file.eof())
	{
		getline(file,linea_texto);
		
		//Starts reading coordinates
		if(linea_texto[0] == '1' || linea_texto[0] == '2' || 
		linea_texto[0] == '3' || linea_texto[0] == '4' || linea_texto[0] == '5' 
		|| linea_texto[0] == '6' || linea_texto[0] == '7' || linea_texto[0] == '8'
		|| linea_texto[0] == '9')
		{
			int pos = linea_texto.find(" ");
			string nuevo_texto = linea_texto.substr(pos+1);
			string::size_type sz;

			double first_coord = stod(nuevo_texto, &sz);
			double second_coord = stod(nuevo_texto.substr(sz));

			City ciudad;
			ciudad.coordX = first_coord;
			ciudad.coordY = second_coord;
			ciudades.push_back(ciudad);
		}
	}
	return ciudades;
}

vector<int> readOpt(string name)
{
	ifstream file;
	string linea_texto;
	vector<int> opt_tour;

	file.open(name, ios::in);

	if(file.fail())
	{
		cout << "Error al abrir el archivo" << endl;
		exit(1);
	}

	while(!file.eof())
	{
		getline(file,linea_texto);

		//Starts reading indices
		if(linea_texto[0] == '1' || linea_texto[0] == '2' || linea_texto[0] == '3' 
		|| linea_texto[0] == '4' || linea_texto[0] == '5' || linea_texto[0] == '6' 
		|| linea_texto[0] == '7' || linea_texto[0] == '8'|| linea_texto[0] == '9')
			opt_tour.push_back(stoi(linea_texto) - 1);
	}
	return opt_tour;
}

void concurrentCall(string nameFile, string optNameFile)
{
	int max_it, num_ants, randomseed;
	double decay_factor, c_phero, c_elite, alpha, beta;
	bool doExpansion;
	vector<City> cities = readFile(nameFile);

	//Buidling map matrix
	vector<vector<double>> Map = getDistances(cities);

	//Configuration parameters
	randomseed = 100;
	max_it = 100;
	num_ants = cities.size()*5;
	decay_factor = 0.8;
	alpha = 30;
	beta = 10;
	c_phero = 10000;
	c_elite = num_ants*c_phero*100;
	doExpansion = true;

	//Algorithm starts
	vector<int> Result = ACO(cities, Map, max_it, num_ants, decay_factor, 
	c_phero, c_elite, alpha, beta, doExpansion, randomseed);

	cout << nameFile << " results\n";
	cout << "Final path:" << endl;
	for(int i = 0; i < Result.size(); ++i)
		cout << Result[i] << " ";

	cout << endl << "Final cost: ";
	cout << pathCost(Result, Map) << endl;

	//Show optimal path
	vector<int> opt_tour = readOpt(optNameFile);
	cout << endl << "Optimal path:" << endl;
	for(int i = 0; i < opt_tour.size(); ++i)
		cout << opt_tour[i] << " ";

	cout << endl << "Optimal cost: ";
	cout << pathCost(opt_tour, Map) << "\n" << endl;
}

int main()
{
	thread t1{concurrentCall, "berlin52.tsp",
	"berlin52.opt.tour"};
	thread t2{concurrentCall, "kroA100.tsp", 
	"kroA100.opt.tour"};
	thread t3{concurrentCall, "eil51.tsp", 
	"eil51.opt.tour"};

	t3.join();
	t2.join();
	t1.join();

	return 0;
}
