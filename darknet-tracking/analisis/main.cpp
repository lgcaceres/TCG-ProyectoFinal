#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <map>


#include <cstdlib>

#include <stdlib.h>     /* atoi */

using namespace std;


class data
{
public:
	int x;
	int y;
	data(){
		x=0;
		y=0;
	}
	data(int _a, int _b){
		x=_a;
		y=_b;
	}

};


int main(){


    map<string,data> mymap;
    map<string,data>::iterator it_mymap;
	

	char buffer[100] ;
	string bufferSTR ;

	std::vector<string> a;
	std::vector<int> b;
	ifstream infile;
    infile.open ("all-noFigths.txt", ifstream::in);
    //infile.open ("all-figths.txt", ifstream::in);


	string delimiter = ",";
	
	if(infile.is_open())
    {
        while (infile.good())
        {
            //infile.getline(cNum, 256, ',');
            infile.getline(buffer, 256);
            bufferSTR=buffer;

    		size_t pos = 0;
			string token;
			while ((pos = bufferSTR.find(delimiter)) != std::string::npos) {
			    token = bufferSTR.substr(0, pos);

			    //cout <<"ar:"<< token << endl;


			    it_mymap = mymap.find(token);
			    if(it_mymap==mymap.end()){
			    	//data tempD(0,0);
			    	//cout<<"adentro"<<endl;
			    	mymap.insert(std::make_pair(token,data(0,0)));
			    }

			    bufferSTR.erase(0, pos + delimiter.length());
			}
			if(!bufferSTR.empty()){
				it_mymap = mymap.find(token);
				int num = stoi(bufferSTR);
				if(num==0){
					it_mymap->second.x++;
				}
				if(num==1){
					it_mymap->second.y++;
				}
				//cout <<"flag:"<< num << endl;
			}

        }
        infile.close();
    }
    else
    {
            cout << "Error opening file";
    }


    //cout<< "fin" <<endl;


    map<string,data>::iterator it_mymap2;

    it_mymap2 = mymap.begin();
    int i = 0;
    int j = 0;

    int mediaX=0;
    int mediaY=0;





    while(it_mymap2!=mymap.end()){
    	
    	cout<<it_mymap2->first<<","<<it_mymap2->second.x<<","<<it_mymap2->second.y<<endl; 
    	//cout<<it_mymap2->first<<","; 
    	double tempX = it_mymap2->second.x;
    			mediaX = (mediaX+tempX)/2;
    	double tempY = it_mymap2->second.y;
    			mediaY = (mediaY+tempY)/2;
    	if(tempX>tempY) //0>1
    	{ 
    		//cout<<"0"<<endl; 
    		i++;

    	}else{			//0<1
     		//cout<<"1"<<endl; 
    		j++;
    	}
    	it_mymap2++;

    }

    //cout<<"total 0 :"<<i<<endl;
    //cout<<"total 1 :"<<j<<endl;
	//cout<<"mediaX 0 :"<<mediaX<<endl;
    //cout<<"mediaY 1 :"<<mediaY<<endl;



	return 0;
}