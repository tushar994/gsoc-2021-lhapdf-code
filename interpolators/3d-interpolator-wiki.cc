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
    double a[n];
    for(int i=0;i<n;i++){
        a[i] = get_val(x_i[i],q_i,flavour);
        // cout<<"a:"<<a[i]<<"\n";
    }
    double h[n-1];
    for(int i=0;i<n-1;i++){
        h[i] = x_arr[x_i[i+1]] - x_arr[x_i[i]];
    }
    double A[n-1];
    for(int i=1;i<n-1;i++){
        A[i] = ((((double)3)/h[i])*(a[i+1]-a[i])) - ((((double)3)/h[i-1])*(a[i]-a[i-1]));
    }
    double c[n],l[n],u[n],z[n];
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;
    for(int i=1;i<n-1;i++){
        l[i] = 2*(x_arr[x_i[i+1]] - x_arr[x_i[i-1]]) - (h[i-1]*u[i-1]);
        u[i] = h[i]/l[i];
        z[i] = (a[i] - (h[i-1]*z[i-1]))/l[i];
    }
    l[n-1] = 1;
    z[n-1] = 0;
    c[n-1] = 0;
    double b[n],d[n];
    for(int i=n-2;i>=0;i--){
        c[i] = z[i] - (u[i]*c[i+1]);
        b[i] = ((a[i+1]-a[i])/h[i]) - (h[i]*(c[i+1]+2*c[i])/3);
        d[i] = (c[i+1]-c[i])/(3*h[i]);
    }
    int index = 1;
    double val = x-x_arr[index1];
    // cout<<"x\n";
    // cout<<a[index]<<","<< b[index]*(val) <<","<< c[index]*val*val <<","<< d[index]*val*val*val<<"\n";
    return a[index] + b[index]*(val) + c[index]*val*val + d[index]*val*val*val;
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
    // cout<<"\n";
    
    double h[n-1];
    for(int i=0;i<n-1;i++){
        h[i] =q_arr[q_i[i+1]] - q_arr[q_i[i]];
    }
    // cout<<"h is \n";
    // for(int i=0;i<n-1;i++){
    //     cout<<h[i]<<" ";
    // }
    // cout<<"\n";
    double A[n-1];
    for(int i=1;i<n-1;i++){
        A[i] = ((((double)3)/h[i])*(a[i+1]-a[i])) - ((((double)3)/h[i-1])*(a[i]-a[i-1]));
    }
    double c[n],l[n],u[n],z[n];
    l[0] = 1;
    u[0] = 0;
    z[0] = 0;
    for(int i=1;i<n-1;i++){
        l[i] = 2*(q_arr[q_i[i+1]] - q_arr[q_i[i-1]]) - (h[i-1]*u[i-1]);
        u[i] = h[i]/l[i];
        z[i] = (a[i] - (h[i-1]*z[i-1]))/l[i];
    }
    l[n-1] = 1;
    z[n-1] = 0;
    c[n-1] = 0;
    double b[n],d[n];
    for(int i=n-2;i>=0;i--){
        c[i] = z[i] - (u[i]*c[i+1]);
        b[i] = ((a[i+1]-a[i])/h[i]) - (h[i]*(c[i+1]+2*c[i])/3);
        d[i] = (c[i+1]-c[i])/(3*h[i]);
    }
    int index = 1;
    double val = q-q_arr[index1];
    // cout<<"values are (3):\n";
    // for(int i=0;i<n;i++){
    //     cout<<a[i]<<" ";
    // }
    // cout<<"\n";
    // cout<<a[index]<<","<< b[index] <<","<< c[index] <<","<< d[index]<<"\n";
    // cout<<val<<"\n";
    return a[index] + b[index]*(val) + c[index]*val*val + d[index]*val*val*val;
}

// This is the main function that is called for interpolating

double interpolate(double x, double q, int flavour){
    int x_i = x_index(x);
    int q_i = q_index(q);
    int n = 4;
    int x_a[n],q_a[n];
    for(int i=0;i<n;i++){
        x_a[i] = return_index(x_i, x_size-1, 0, i-1);
        q_a[i] = return_index(q_i, q_size-1, 0, i-1);
    }

    // now we have all four coordinates for x, q
    double values[4];
    // we interpolate along x four times for the relevant values of q and store the obtained values
    // cout<<"values are\n";
    for(int i=0;i<4;i++){
        values[i] = interpolate_x(x,q_a[i],n,flavour);
        // cout<<values[i]<<" ";
    }
    // cout<<"\n";
    // Using the four values obtained we interpolate along q
    return interpolate_q(q,values, n);

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
    ofstream MyFile("./vague_analysis/slope_zero.csv");
    // ofstream MyFile("./dense_data/slope_zero.csv");

    double x_val = -20;
    double q_val = 0.5;
    // cout<<interpolate(exp(-18),exp(5.29),0)<<"\n";
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