#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class Proc {
public:
	int com_t;
	int start_t;
	int b_t;
	int w_t;
	int realization_t;
	int end_t;
};

int main()
{
	int proc_count, av_wait = 0, av_exec = 0, i, j;
	char alg, method_fill;
	vector <Proc> p;
	while (1) {
		cout << "Choose algorithm\nFCFS(0)/LCFS(1) :";
		cin >> alg;
		cout << "Choose a method\nRandom(0)/Manually(1) :";
		cin >> method_fill;
		if (method_fill == '1'&&(alg == '0' || alg == '1')) {

			cout << "Enter total number of processes(maximum 20):";
			cin >> proc_count;

			p.resize(proc_count);

			cout << "\nEnter Process Arrival Time\n";
			for (i = 0; i < proc_count; i++)
			{
				cout << "P[" << i << "]:";
				cin >> p[i].com_t;
			}

			cout << "\nEnter Process Burst Time\n";
			for (i = 0; i < proc_count; i++)
			{
				cout << "P[" << i << "]:";
				cin >> p[i].b_t;
			}
			break;

		}
		else if (method_fill == '0' && (alg == '0' || alg == '1')) {

			proc_count = (rand() % 10) + (rand() % 10) + 1;

			p.resize(proc_count);

			for (i = 0; i < proc_count; i++)
			{
				p[i].b_t = 1 + (rand() % 100);
				p[i].com_t = (rand() % 100);
			}
			break;

		}
		else {
			cout << "\n\nCheck the input data\n\n";
		}
	}


	vector <int> sort_pos; 
	sort_pos.resize(proc_count);

	vector <int> sort_value; 
	sort_value.resize(proc_count);

	for (int i = 0; i < proc_count; i++) {
		sort_pos[i] = i;
		sort_value[i] = p[i].com_t;
	}


	int miniPos, temp_time, temp_pos;

	for (int i = 0; i < sort_value.size(); i++) 
	{
		miniPos = i;
		for (int j = i + 1; j < sort_value.size(); j++)
		{
			if (sort_value[j] < sort_value[miniPos])
			{
				miniPos = j;
			}
		}

		temp_time = sort_value[miniPos];
		sort_value[miniPos] = sort_value[i];
		sort_value[i] = temp_time;

		temp_pos = sort_pos[miniPos];
		sort_pos[miniPos] = sort_pos[i];
		sort_pos[i] = temp_pos;
	}


	vector <int> order_row;

	if (alg == '0') { 
		p[sort_pos[0]].w_t = 0;
		p[sort_pos[0]].start_t = p[sort_pos[0]].com_t;
		p[sort_pos[0]].realization_t = p[sort_pos[0]].b_t;
		p[sort_pos[0]].end_t = p[sort_pos[0]].b_t + p[sort_pos[0]].com_t;

		order_row.push_back(sort_pos[0]);

		for (i = 1; i < proc_count; i++) {
			if (p[sort_pos[i]].com_t >= p[sort_pos[i - 1]].end_t) {
				p[sort_pos[i]].w_t = 0;
				p[sort_pos[i]].start_t = p[sort_pos[i]].com_t;
			}
			else {
				p[sort_pos[i]].w_t = p[sort_pos[i - 1]].end_t - p[sort_pos[i]].com_t;
				p[sort_pos[i]].start_t = p[sort_pos[i]].com_t + p[sort_pos[i]].w_t;
			}
			p[sort_pos[i]].realization_t = p[sort_pos[i]].b_t + p[sort_pos[i]].w_t;
			p[sort_pos[i]].end_t = p[sort_pos[i]].com_t + p[sort_pos[i]].realization_t;

			order_row.push_back(sort_pos[i]);
		}
	}

	int n = 0;
	int last_end_t = 0;
	bool repeat;

	if (alg == '1') { 

	NewQ:

		if (sort_pos.size() == 1) {
			p[sort_pos[0]].w_t = 0;
			p[sort_pos[0]].start_t = p[sort_pos[0]].com_t;
			p[sort_pos[0]].realization_t = p[sort_pos[0]].b_t;
			p[sort_pos[0]].end_t = p[sort_pos[0]].b_t + p[sort_pos[0]].com_t;

			order_row.push_back(sort_pos[0]);
		}

		for (int i = 0; i < sort_pos.size() - 1; i++) {

			if (p[sort_pos[i]].com_t < p[sort_pos[i + 1]].com_t) { 
				p[sort_pos[i]].w_t = 0;
				p[sort_pos[i]].start_t = p[sort_pos[i]].com_t;
				p[sort_pos[i]].realization_t = p[sort_pos[i]].b_t;
				p[sort_pos[i]].end_t = p[sort_pos[i]].b_t + p[sort_pos[i]].com_t;

				last_end_t = p[sort_pos[i]].end_t;
				order_row.push_back(sort_pos[i]);


				for (int k = 0; k < order_row.size(); k++) {
					for (int j = sort_pos.size() - 1; j >= 0; j--) { 
						if (last_end_t >= p[sort_pos[j]].com_t && j != i) {
							repeat = false;
							for (int a = 0; a < order_row.size(); a++) { 
								if (sort_pos[j] == order_row[a])
									repeat = true;
							}
							if (!repeat) { 
								order_row.push_back(sort_pos[j]);

								p[order_row[order_row.size() - 1]].w_t = p[order_row[order_row.size() - 2]].end_t - p[order_row[order_row.size() - 1]].com_t;
								p[order_row[order_row.size() - 1]].start_t = p[order_row[order_row.size() - 1]].com_t + p[order_row[order_row.size() - 1]].w_t;
								p[order_row[order_row.size() - 1]].realization_t = p[order_row[order_row.size() - 1]].b_t + p[order_row[order_row.size() - 1]].w_t;
								p[order_row[order_row.size() - 1]].end_t = p[order_row[order_row.size() - 1]].com_t + p[order_row[order_row.size() - 1]].realization_t;

								last_end_t = p[order_row[order_row.size() - 1]].end_t;
								j = sort_pos.size() - 1;
								break;
							}
						}
					}
				}

				bool duplicat;

				if (order_row.size() == proc_count) { 
					break;
				}
				else {
				Again:
					duplicat = false;
					for (int p = 0; p < sort_pos.size(); p++) {
						for (int pq = 0; pq < order_row.size(); pq++) {
							if (sort_pos[p] == order_row[pq]) {
								sort_pos.erase(sort_pos.begin() + p);
								sort_value.erase(sort_value.begin() + p);
								duplicat = true;
								goto Again;
							}
						}
					}
					if (!duplicat) {
						goto NewQ;
					}

				}

			}
			else if ((i + 1) == proc_count - 1) { 
				p[sort_pos[i + 1]].w_t = 0;
				p[sort_pos[i + 1]].start_t = p[sort_pos[i + 1]].com_t;
				p[sort_pos[i + 1]].realization_t = p[sort_pos[i + 1]].b_t;
				p[sort_pos[i + 1]].end_t = p[sort_pos[i + 1]].b_t + p[sort_pos[i + 1]].com_t;

				order_row.push_back(sort_pos[i + 1]);

				for (int j = proc_count - 2; j >= 0; j--) 
				{
					p[sort_pos[j]].w_t = p[sort_pos[j + 1]].end_t - p[sort_pos[j]].com_t;
					p[sort_pos[j]].start_t = p[sort_pos[j]].com_t + p[sort_pos[j]].w_t;
					p[sort_pos[j]].realization_t = p[sort_pos[j]].b_t + p[sort_pos[j]].w_t;
					p[sort_pos[j]].end_t = p[sort_pos[j]].start_t + p[sort_pos[j]].b_t;

					order_row.push_back(sort_pos[j]);
				}
			}
		}
	}

	float av_realization_t = 0, av_w_t = 0;

	if (alg == '0') {
		cout << "\nFCFS :\n";
	}
	else if (alg == '1') {
		cout << "\nLCFS :\n";
	}

	cout << "\nProcess\t\tArrival time\tStart time\tCPU Burst time\tWaiting time\tFull exec time\tEnd time";

	for (i = 0; i < proc_count; i++)
	{
		av_realization_t += p[i].realization_t;
		av_w_t += p[i].w_t;
		cout << "\nP[" << i << "]" << "\t\t" << p[i].com_t << "\t\t" << p[i].start_t << "\t\t" << p[i].b_t << "\t\t" << p[i].w_t << "\t\t" << p[i].realization_t << "\t\t" << p[i].end_t;
	}

	cout << "\n\nThe order of execution : ";

	for (i = 0; i < proc_count; i++)
	{
		cout << "P[" << order_row[i] << "]\t";
	}

	av_realization_t = av_realization_t / proc_count;
	av_w_t = av_w_t / proc_count;

	cout << "\n\nAverage full execution time : " << av_realization_t;
	cout << "\nAverage waiting time : " << av_w_t << "\n";

	return 0;
}
