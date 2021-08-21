
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>


using namespace std;

int x_size = 91;
int q_size = 20;
double q_arr[20], x_arr[91]; 
double xf[20*91][3];

int x_binary(int min, int max, double val){
    while(max-min>1){
        int mid  = (min+max)/2; 
        if(x_arr[mid]>val){
            max = mid;
        }
        else{
            min = mid;
        }
    }
    return min;
}

int x_index(double x){
    return x_binary(0,x_size-1,x);
}

int q_binary(int min, int max, double val){
    while(max-min>1){
        int mid  = (min+max)/2; 
        if(q_arr[mid]>val){
            max = mid;
        }
        else{
            min = mid;
        }
    }
    return min;
}

int q_index(double x){
    return q_binary(0,q_size-1,x);
}

int return_index(int index, int max, int min, int add){
    if(index+add < min){
        return min;
    }
    else if(index+add > max){
        return max;
    }
    else{
        return index+add;
    }

}   

double get_val(int x_index, int q_index, int flavour){
    int index = x_index*q_size + q_index;
    return xf[index][flavour];
}

double interpolate_x(double x, int q_i, int n, int flavour){
    int x_i[n];
    int index1 = x_index(x);
    for(int i=0;i<n;i++){
        x_i[i] = return_index(index1, x_size-1, 0, i-1);
    }
    // x_i contains the index at which you'll find the x's you want
    double a[n];
    for(int i=0;i<n;i++){
        a[i] = get_val(x_i[i],q_i,flavour);
    }
    // a contains the four values
    double y1 = a[1];
    double y2 = a[2];
    double x1 = x_arr[x_i[1]];
    double x2 = x_arr[x_i[2]];
    return y1 + (y2-y1)*(x-x1)/(x2-x1);
    
}

double interpolate_q(double q, double* values , int n){
    int q_i[n];
    int index1 = q_index(q);
    for(int i=0;i<n;i++){
        q_i[i] = return_index(index1, q_size-1, 0, i-1);
    }
    double a[n];
    // cout<<"values are (2):\n";
    for(int i=0;i<n;i++){
        a[i] = values[i];
        // cout<<a[i]<<" ";
    }
    // a contains the four values
    double y1 = a[1];
    double y2 = a[2];
    double x1 = q_arr[q_i[1]];
    double x2 = q_arr[q_i[2]];
    return y1 + (y2-y1)*(q-x1)/(x2-x1);
}

double linear_inter(double x, double* values, double* x_val){
    double y1 = values[0];
    double y2 = values[1];
    double x1 = x_val[0];
    double x2 = x_val[1];
    return y1 + (y2-y1)*(x-x1)/(x2-x1);
}

// This is the main function that is called for interpolating

double interpolate(double x, double q, int flavour){
    int x_i = x_index(x);
    int q_i = q_index(q);
    int x_a[2],q_a[2];
    for(int i=0;i<2;i++){
        x_a[i] = return_index(x_i, x_size-1, 0, i);
        q_a[i] = return_index(q_i, q_size-1, 0, i);
    }

    double x_vals[2];
    double values[2];
    x_vals[0] = x_arr[x_a[0]];
    x_vals[1] = x_arr[x_a[1]];
    for(int i=0;i<2;i++){
        double vals[2];
        vals[0] = get_val(x_a[0],q_a[i],0);
        vals[1] = get_val(x_a[1],q_a[i],0);
        values[i] = linear_inter(x,vals,x_vals);
    }

    double q_vals[2];
    q_vals[0] = q_arr[q_a[0]];
    q_vals[1] = q_arr[q_a[1]];
    double vals[2];
    vals[0] = values[0];
    vals[1] = values[1];
    return linear_inter(q,vals,q_vals);

}


int main(){


    // <---------------------------------------------------------------------------------------getting all the input-------------------------------------------------------------------------------------------------------------------->

    fstream fin;

    // change these according to dataset
    // Open an existing file
    fin.open("./vague_analysis/my_info.csv", ios::in);
    vector<string> row;
    string line, word, temp;
    int line1 = 0;
    // getting xf
    while (fin >> temp) {

        row.clear();
        // cout<<temp<<"\n";
        // read an entire row and
        // store it in a string variable 'line'
        // getline(fin, line);
        // cout<<line<<"\n";
        // used for breaking words
        stringstream s(temp);

        // read every column data of a row and
        // store it in a string variable, 'word'
        int flavour  =0 ;
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            // cout<<word<<"\n";
            // if(word=="---"){
            //     break;
            // }
            xf[line1][flavour] = stod(word);
            flavour++;
        }
        // if(word=='---'){
        //     break;
        // }
        line1++;
    }
    fstream fin1;
    fin1.open("./vague_analysis/x.csv", ios::in);
    line1 = 0;
    while (fin1 >> temp) {

        row.clear();
        // cout<<temp<<"\n";
        // read an entire row and
        // store it in a string variable 'line'
        // getline(fin, line);
        // cout<<line<<"\n";
        // used for breaking words
        stringstream s(temp);

        // read every column data of a row and
        // store it in a string variable, 'word'
        int flavour  =0 ;
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            x_arr[line1] = stod(word);
            line1++;

        }
    }
    // for(int i=0;i<190;i++){
    //     cout<<x[i]<<" ";
    // }
    // cout<<"\n";
    fstream fin2;
    fin2.open("./vague_analysis/q.csv", ios::in);
    line1 = 0;
    while (fin2 >> temp) {

        row.clear();
        // cout<<temp<<"\n";
        // read an entire row and
        // store it in a string variable 'line'
        // getline(fin, line);
        // cout<<line<<"\n";
        // used for breaking words
        stringstream s(temp);

        // read every column data of a row and
        // store it in a string variable, 'word'
        int flavour  =0 ;
        while (getline(s, word, ',')) {

            // add all the column data
            // of a row to a vector
            q_arr[line1] = stod(word);
            line1++;

        }
    }
    //<<----------------------------------_-----------------_-----------------_-----------------_-----------------_-----------------_-----------------_-----------------_>
    // for(int i=0;i<4560;i++){
    //     cout<<xf[i][0]<<" ";
    // }
    // cout<<"\n";
    // cout<<get_val(1,1,0)<<" is the val\n";
    ofstream MyFile("./vague_analysis/linear.csv");
    // ofstream MyFile("./dense_data/linear.csv");

    double x_val = -20;
    double q_val = 0.5;
    // cout<<interpolate(exp(-18),exp(1),0)<<"\n";
    MyFile<<"lnx,lnq,xf\n";
    while(q_val<10){
        x_val = -18;
        while(x_val<0){
            MyFile<<x_val<<","<<q_val<<","<<interpolate((x_val),(q_val),0)<<"\n";
            // cout<<x_val<<"\r";
            x_val+=0.01;
        }
        q_val+=0.05;
        cout<<q_val<<"\n";
    }
    MyFile.close();


}