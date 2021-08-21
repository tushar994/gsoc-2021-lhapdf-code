
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



double interpolate_average(double x, double* a, double* x_val){
    // y(x1) and y(x2)
    double y1 = a[1];
    double y2 = a[2];

    // first derivative
    double dy1,dy2;
    double dy_[3];
    for(int i=0;i<3;i++){
    dy_[i] = (a[i+1] - a[i])/(x_val[i+1]-x_val[i]);
    }

    dy1 = ((dy_[1]*(x_val[1] - x_val[0])) + (dy_[0]*(x_val[2] - x_val[1])))/(x_val[2] - x_val[0]);


    dy2 = ((dy_[2]*(x_val[2] - x_val[1])) + (dy_[1]*(x_val[3] - x_val[2])))/(x_val[3] - x_val[1]);


    double delta_x = x_val[2] - x_val[1];
    double A,B,C,D;
    // the polynomial is of the form A(x-x1)^3 + B(x-x1)^2 + C(x-x1) + D
    D = y1;
    C = dy1;
    A = (dy2*delta_x + dy1*delta_x + 2*y1 - 2*y2)/(delta_x*delta_x*delta_x);
    B  = (3*y2 - 3*y1 - 2*dy1*delta_x - dy2*delta_x)/(delta_x*delta_x);
    double val = x - x_val[1];
    return A*val*val*val + B*val*val + C*val + D;

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
    // int x_i = x_index(x);
    // int q_i = q_index(q);
    int x_i = 8;
    int q_i = 2;
    int x_a[4],q_a[4];
    for(int i=0;i<4;i++){
        x_a[i] = return_index(x_i, x_size-1, 0, i-1);
        q_a[i] = return_index(q_i, q_size-1, 0, i-1);
    }
    double values[4];
    if(x_a[0]==x_a[1]||x_a[2]==x_a[3]){
        // degrenate to linear
        // cout<<"here\n";
        double x_vals[2];
        x_vals[0] = x_arr[x_a[1]];
        x_vals[1] = x_arr[x_a[2]];
        for(int i=0;i<4;i++){
            double vals[2];
            vals[0] = get_val(x_a[1],q_a[i],0);
            vals[1] = get_val(x_a[2],q_a[i],0);
            values[i] = linear_inter(x,vals,x_vals);
        }
    }
    else{
        double x_vals[4];
        for(int i=0;i<4;i++){
            x_vals[i]= x_arr[x_a[i]];
        }
        for(int i=0;i<4;i++){
            double vals[4];
            for(int j=0;j<4;j++){
                vals[j] = get_val(x_a[j],q_a[i],0);
            }
            values[i] = interpolate_average(x,vals,x_vals);
            // cout<<values[i]<<" ";
        }
    }

    if(q_a[0]==q_a[1]||q_a[2]==q_a[3]){
        // degrenate to linear
        // cout<<"here\n";
        double q_vals[2];
        q_vals[0] = q_arr[q_a[1]];
        q_vals[1] = q_arr[q_a[2]];
        double vals[2];
        vals[0] = values[1];
        vals[1] = values[2];
        return linear_inter(q,vals,q_vals);
    }
    else{
        double q_vals[4];
        for(int i=0;i<4;i++){
            q_vals[i]= q_arr[q_a[i]];
        }
        return interpolate_average(q,values,q_vals);
    }

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
    ofstream MyFile("./vague_analysis/avg_slope_inter.csv");
    // ofstream MyFile("./dense_data/avg_slope_inter.csv");

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

    // for(int i=0;i<10000;i++){
    //     interpolate((-16.4),(1.4),0);
    // }


}