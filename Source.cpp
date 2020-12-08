
/*
Basil Atawneh	161073
Layla Alhammoury	177092
Ibrahim Ahmad AbuSamrah	161004
*/
#include<iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include<algorithm>

using namespace std;
//Functions
void genMap(vector<double> &map,int size);
double GaussianCalculation(double m, double s, double x);
double mean (vector<double> &values);
double standerdiv (vector<double> &values, double m);
double RandomNumber(double Min, double Max);

struct particl{
double pos;
double weight;
};

// parameters
int robPos = 35;
int stepSize = 7;
int numOfParticls = 500;
int maxStepError = 1;
double maxSensorError = 0.1;
const double pi = 3.14159265358979323846;

int main(){
    //sensor reading generation
	vector<double>sensor(1000);
	genMap(sensor,1000);
    double standerDiv_value = standerdiv(sensor,mean(sensor));
	double mu_value = mean(sensor);
    vector<particl> particls(numOfParticls);

	//Random seed change
    srand(time(NULL));
	int randomNumber ;

	//genarate the particles 
	for(int i=0;i<numOfParticls;i++){
		randomNumber = rand() % 1000;
		particls[i].pos = randomNumber;
		particls[i].weight = 1.0/numOfParticls;
	}

	while(robPos < 1000){
		//Move the robot 
		robPos += stepSize;
		if(robPos>=1000)
			continue;
		double totalWeights = 0;
		//Calculate the cumulative array
		vector<double> cumulativeArray(numOfParticls+1);
		cumulativeArray[0] = 0;
		for(int i=1;i<numOfParticls+1;i++){
			cumulativeArray[i]=cumulativeArray[i-1]+particls[i-1].weight;
		}
		vector<double> temppos(numOfParticls);
		vector<particl>new_particals(numOfParticls);
		double floatRandomNumber;
		//Select from the cumulative array
		for(int i = 0; i < numOfParticls; i++){
			floatRandomNumber = RandomNumber(0,1.0);
			int selectItem = 0;
			/*
			0 0.1 0.5 0.7 0.8 1
			0.9
			0 1 2 3 4
			*/
			for(int j=1;j<numOfParticls;j++){
				if(cumulativeArray[j] >=  floatRandomNumber)
					break;
				else
					selectItem++;

			}

			particl selectedPartical = particls[selectItem];
			//update
			//update the position
			int stepError = rand()%maxStepError;
			stepError = (rand()%2 == 1)? -1 * stepError : stepError;
			selectedPartical.pos += stepSize + stepError;
			if(selectedPartical.pos>=1000)
				selectedPartical.pos = rand() % 1000;
			//update the weights
			double x_value = sensor[robPos]-sensor[selectedPartical.pos];
			x_value += RandomNumber(-1*maxSensorError,maxSensorError);/*-0.1 , 0.1*/
			selectedPartical.weight = GaussianCalculation(mu_value,standerDiv_value,x_value);

			temppos[i]=selectedPartical.pos;
			totalWeights += selectedPartical.weight;
			new_particals[i] = selectedPartical;
		}
		// update the weightes (normalization)
		for(int i = 0; i < numOfParticls; i++){
			new_particals[i].weight /= totalWeights;
		}
		swap(new_particals,particls);
		//print the data
		double tempm = mean(temppos);
		cout<<"The particls positions: \n[ ";
		for(int i = 0 ;i<numOfParticls ;i++){
			if(i!=numOfParticls-1)
				cout<<particls[i].pos<<", ";
			else
				cout<<particls[i].pos<<" ]\n";
		}
		cout<<"--------------------------------------------------\n";
		cout<<"Robot position = "<<robPos<<endl;
		cout<<"     Mean      = "<<tempm<<endl;
		cout<<"   Variance    = "<<pow(standerdiv(temppos, tempm),2.0)<<endl;
		cout<<"*********************************************************************************\n";
		system("pause");
}
 return 0;
}
double RandomNumber(double Min, double Max){

    return ((double(rand()) /RAND_MAX) * (Max - Min)) + Min;
}
double mean (vector<double> &values){
double sum = 0;
for(int i=0;i<values.size();i++){
    sum+=values[i];
}
return sum/values.size();
}
double standerdiv (vector<double> &values, double m){
    double sum = 0;
    for(int i= 0;i<values.size();i++){
            //cout<<values[i]<<endl;
		/*
		
		
		*/
        sum += ((values[i]-m)*(values[i]-m))/values.size();
    }
   // sum /= values.size();
    double res = sqrt(sum);
    return res;

}
double GaussianCalculation(double m, double s, double x){
    double constant = 1/(s*sqrt(2*pi));
    double Epow = -1*(x - m)*(x - m)/(2 * s * s);
    double res = constant * exp(Epow);
    return res;
}

void genMap(vector<double> &map,int size){
double theta = 0;
    for(int i=0;i<size;i++){
        double temp = theta;
        theta *= 2*pi;
        map[i]=cos(theta)+0.5*cos(3*theta+0.23) +0.5*cos(5*theta-0.4)+0.5*cos(7*theta+2.09)+0.5*cos(9*theta-3);
        //map[i] += 2.5;
        theta =temp + 0.001;
    }
}
